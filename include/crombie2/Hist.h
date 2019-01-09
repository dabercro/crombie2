#ifndef CROMBIE2_HIST_H
#define CROMBIE2_HIST_H

// I really don't like ROOT's global hash tables and confusing lifetimes
// Here, I make a simple data structure that can make a histogram
// Try to use this and only get the TH1D object at the end

#include <list>
#include <string>
#include <vector>

#include "TH1D.h"

namespace crombie2 {

  class Hist {
  public:

    /**
       Constructor of custom Hist class
       @param label Is the label to go on the x-axis
       @param nbins The number of bins to show in the plot.
              There is also one overflow and one underflow bin stored internally.
       @param min The minimum value shown on the x-axis
       @param max The maximum value on the x-axis
       @param total_events Is the total weight of events in the file(s) filling this histogram
    */
    Hist(const std::string label = "",
         unsigned nbins = 0, double min = 0, double max = 0,
         double total_events = 0);


    /// Fills this histogram with some value and weight
    void fill (double val, double weight = 1.0);


    /// Adds another histogram's bin contents to this Hist
    void add  (const Hist& other);


    /// Scale this histogram by a direct scale factor
    void scale (const double scale);


    /**
       Scale this histogram to a luminosity and cross section. 
       The result will be invalid if this scale function is called
       after any other call to Hist::scale.
    */
    void scale (const double lumi, const double xs);


    /// Returns a Hist that is a ratio between this and another Hist
    Hist ratio (const Hist& other) const;


    /**
       Returns a pointer to a histogram that is owned by global list.
       This list will handle the deletion when the program is done running.
       Not thread-safe.
    */
    TH1D* roothist ();


    /// Sets the value of the total number of events, throws exception if total is already set
    void set_total (double newtotal);


    /// Gives the total number of events in the histogram
    double integral (bool include_under_over = true);

    /// Get the maximum value including uncertainties (for plotting)
    double max_w_unc () const;

    /// Get the minimum value including uncertainties, but not less than 0.0 (for plotting)
    double min_w_unc (const bool includezeros = true) const;

    /**
       Get the maximum bin and the total number of bins.
       Does not include overflow bins.
    */
    std::pair<unsigned, unsigned> get_maxbin_outof () const;

    void set_contents (const std::vector<double>& newcont,
                       const std::vector<double>& neww2);

    double get_total () const;
    const std::vector<double>& get_contents () const;
    const std::vector<double>& get_errors () const;

  private:

    std::string label {};
    unsigned nbins {};
    double min {};
    double max {};

    std::vector<double> contents {};
    std::vector<double> sumw2 {};

    double total {};                             ///< Stores the total weights of files filling this

    std::list<TH1D> histstore {};

    double get_unc (unsigned bin) const;         ///< Find the full uncertainty from uncs hists and sumw2

  };

}


#endif
