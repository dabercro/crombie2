#include <iostream>
#include <cmath>
#include <exception>


#include <crombie2/Hist.h>


using namespace crombie2;



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


void Hist::add(const Hist& other) {

  if (nbins == 0)
    *this = other;               // If this not set yet, just simple assignment
  else {
    total += other.total;        // Increase the total events count
    if (other.nbins != nbins) {  // Check for binning error
      std::cerr << "Num bins other: " << other.nbins << " me: " << nbins << std::endl;
      throw std::runtime_error{"Hists don't have same number of bins"};
    }

    // Add these histograms together
    for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {
      contents[ibin] += other.contents[ibin];
      if (sumw2.size())
        sumw2[ibin] += other.sumw2[ibin];
    }

  }
}


void Hist::scale(const double scale) {
  for (unsigned ibin = 0; ibin < contents.size(); ++ibin) {
    contents[ibin] *= scale;
    if (sumw2.size())
      sumw2[ibin] *= std::pow(scale, 2);
  }
}


void Hist::scale(const double lumi, const double xs) {
  scale(lumi * xs / total);
}


TH1D* Hist::roothist() {
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
