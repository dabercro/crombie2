#ifndef CROMBIE2_HIST2D_H
#define CROMBIE2_HIST2D_H

#include <crombie2/Hist.h>


namespace crombie2 {
  class Hist2D {
  public:
    Hist2D (unsigned xnbins = 0, double xmin = 0, double xmax = 0,
            unsigned ynbins = 0, double ymin = 0, double ymax = 0);

    void fill (double xval, double yval, double weight);

    void add (const Hist2D& other);

  private:
    std::vector<Hist> hists {};

    unsigned nbins;
    double min;
    double max;

  };
}


#endif
