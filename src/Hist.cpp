#include <iostream>
#include <cmath>
#include <exception>
#include <mutex>


#include <crombie2/Hist.h>


using namespace crombie2;


Hist::Hist(const std::string& label,
           unsigned nbins, double min, double max,
           double total_events) :
  label{label}, nbins{nbins}, min{min}, max{max},
  contents(nbins + 2), sumw2((nbins + 2)),
  total{total_events} {}


void Hist::fill(double val, double weight) {
  unsigned bin {std::min(nbins + 1, static_cast<unsigned>(std::ceil(((val - min) * nbins/(max - min)))))};
  if (bin >= contents.size()) {
    std::cerr << bin << " " << val << " " << nbins << " " << min << " " << max << std::endl;
    throw std::runtime_error{"bin too big"};
  }
  contents[bin] += weight;
  if (sumw2.size())
    sumw2[bin] += std::pow(weight, 2);
}


void Hist::add(const Hist& other, double factor) {

  if (nbins == 0)
    *this = other;                 // If this not set yet, just simple assignment
  else {
    total += factor * other.total; // Increase the total events count
    if (other.nbins != nbins) {    // Check for binning error
      std::cerr << "Num bins other: " << other.nbins << " me: " << nbins << std::endl;
      throw std::runtime_error{"Hists don't have same number of bins"};
    }

    // Add these histograms together
    for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {
      contents[ibin] += factor * other.contents[ibin];
      if (sumw2.size())
        sumw2[ibin] += std::pow(factor, 2) * other.sumw2[ibin];
    }

    for (auto& [key, histlist] : envs) {
      auto& otherlist = other.envs.at(key);

      for (unsigned i_env = 0; i_env < histlist.size(); i_env++)
        histlist[i_env].add(otherlist[i_env], factor);
    }

  }
}


void Hist::scale(const double scale) {
  for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {
    contents[ibin] *= scale;
    if (sumw2.size())
      sumw2[ibin] *= std::pow(scale, 2);
  }

  for (auto& [key, histlist] : envs) {
    for (auto& hist : histlist)
      hist.scale(scale);
  }

}


void Hist::scale(const double lumi, const double xs) {
  scale(lumi * xs / total);
}


namespace {
  std::mutex roothistlock {};
}


TH1D* Hist::roothist(std::list<TH1D>* storeptr) {

  std::unique_lock<std::mutex> lock {roothistlock};

  auto& histstore {storeptr ? *storeptr : localstore};

  static unsigned plot = 0;
  auto title = std::string(";") + label + ";Events";
  histstore.emplace_back(std::to_string(plot++).data(), title.data(), static_cast<int>(nbins), min, max);
  auto& hist = histstore.back();

  for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {
    hist.SetBinContent(ibin, contents[ibin]);
    hist.SetBinError(ibin, get_unc(ibin));
  }

  return &hist;

}


Hist Hist::ratio(const Hist& other) const {

  if (other.nbins != nbins)
    throw std::logic_error{"Wrong number of bins in Hist::ratio"};

  Hist output{*this};

  for (unsigned ibin = 0; ibin < other.contents.size(); ++ibin) {
    auto bincontent = other.contents.at(ibin);
    if (bincontent) {
      output.contents[ibin] /= other.contents.at(ibin);
      if (output.sumw2.size())
        output.sumw2[ibin] /= std::pow(other.contents.at(ibin), 2);
    }
    else {
      output.contents[ibin] = 1.0;
      if (other.sumw2.size())
        output.sumw2[ibin] = 0;
    }
  }

  return output;

}


void Hist::set_total (double newtotal) {

  if (total)
    throw std::logic_error{"Attempted to set total value for histogram twice. Probably a bug."};
  total = newtotal;

}


double Hist::get_unc(unsigned bin) const {

  double w2 = sumw2.size() ? sumw2.at(bin) : 0;
  return std::sqrt(w2);

}


double Hist::max_w_unc () const {
  double output = 0;
  for (unsigned ibin = 1; ibin <= nbins; ++ibin)
    output = std::max(contents[ibin] + get_unc(ibin), output);
  return output;
}


double Hist::min_w_unc (const bool includezeros) const {

  double output = std::numeric_limits<double>::max();
  for (unsigned ibin = 1; ibin <= nbins; ++ibin) {
    if (contents[ibin] or includezeros)
      output = std::min(contents[ibin] - get_unc(ibin), output);
  }
  return std::max(output, 0.0);

}


std::pair<unsigned, unsigned> Hist::get_maxbin_outof () const {

  double max = 0;
  unsigned maxbin = 0;
  for (unsigned ibin = 1; ibin <= nbins; ++ibin) {
    if (contents[ibin] > max) {
      max = contents[ibin];
      maxbin = ibin;
    }
  }
  return std::make_pair(maxbin, std::max(nbins, 1u));

}


void Hist::set_contents (const std::vector<double>& newcont,
                         const std::vector<double>& neww2) {

  if (newcont.size() != neww2.size() or
      newcont.size() != contents.size())
    throw std::logic_error {"Assigning the wrong sized contents to histogram"};

  contents = newcont;
  sumw2 = neww2;

}


double Hist::get_total () const {

  return total;

}


const std::vector<double>& Hist::get_contents () const {

  return contents;

}


const std::vector<double>& Hist::get_errors () const {

  return sumw2;

}


double Hist::integral (bool overflow) const {

  double output {0};
  for (unsigned bin = 1 - overflow; bin < contents.size() - !overflow; bin++)
    output += contents.at(bin);
  return output;

}


double Hist::get_bin (unsigned index) const {

  return contents.at(index);

}


void Hist::set_bin (unsigned index, double value) {

  contents.at(index) = value;

}


void Hist::add_env (const std::string& key, const Hist& env) {

  envs[key].emplace_back(env);

}


Hist& Hist::merge_envs (const std::string& key) {

  if (not merged.insert(key).second)
    throw std::logic_error(key + " envelope was merged twice on same hist.");

  // Merge envelopes into sum of weights squared
  auto minmax = get_minmax_env(key);
  for (unsigned ibin = 0; ibin < contents.size(); ++ibin)
    sumw2[ibin] += std::pow((minmax.second.contents[ibin] - minmax.first.contents[ibin])/2, 2);

  return *this;

}


std::pair<Hist, Hist> Hist::get_minmax_env (const std::string& key) const {

  auto output = std::make_pair(*this, *this);

  for (auto& hist : envs.at(key)) {
    for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {

      output.first.contents[ibin] = std::min(output.first.contents[ibin], hist.contents[ibin]);
      output.second.contents[ibin] = std::max(output.second.contents[ibin], hist.contents[ibin]);

    }
  }

  return output;

}
