#include <iostream>

#include <crombie2/Hist2D.h>


using namespace crombie2;


Hist2D::Hist2D(unsigned xnbins, double xmin, double xmax,
               unsigned ynbins, double ymin, double ymax) :
  nbins {ynbins},
  min {ymin},
  max {ymax}
{

  if (xnbins) {
    hists.reserve(xnbins + 2);
    for (unsigned i_hist = 0; i_hist < xnbins + 2; ++i_hist)
      hists.emplace_back("", xnbins, xmin, xmax);
  }

}


void Hist2D::fill(double xval, double yval, double weight) {
  unsigned bin {std::min(nbins + 1, static_cast<unsigned>(std::ceil(((yval - min) * nbins/(max - min)))))};
  if (bin >= hists.size()) {
    std::cerr << bin << " " << yval << " " << nbins << " " << min << " " << max << std::endl;
    throw std::runtime_error{"bin too big"};
  }
  hists[bin].fill(xval, weight);
}


void Hist2D::add(const Hist2D& other) {

  if (nbins == 0)
    *this = other;                 // If this not set yet, just simple assignment
  else {
    if (other.nbins != nbins) {    // Check for binning error
      std::cerr << "Num bins other: " << other.nbins << " me: " << nbins << std::endl;
      throw std::runtime_error{"Hists don't have same number of bins"};
    }

    // Add these histograms together
    for (unsigned ibin = 0; ibin < hists.size(); ++ibin)
      hists[ibin].add(other.hists[ibin]);

  }
}
