#ifndef CROMBIE2_HIST_H
#define CROMBIE2_HIST_H

// I really don't like ROOT's global hash tables and confusing lifetimes
// Here, I make a simple data structure that can make a histogram

#include <vector>
#include <list>
#include <tuple>

#include "crombie2/Types.h"

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
       @param w2 If true, store the squared sum of weights, otherwise don't bother
       @param total_events Is the total weight of events in the file(s) filling this histogram
    */
    Hist(const std::string label = "",
         unsigned nbins = 0, double min = 0, double max = 0,
         bool w2 = true, double total_events = 0)
      : label{label}, nbins{nbins}, min{min}, max{max},
        contents(nbins + 2), sumw2((nbins + 2) * w2),
        total{total_events} {}

    /// Fills this histogram with some value and weight
    void fill (double val, double weight = 1.0);
    /// Get a reference to a histogram representing an uncertainty
    Hist& get_unc_hist(const std::string& sys);
    /// Create and return a histogram inside an envelope
    Hist& get_env_hist(const std::string& sys);

    /// Get the uncertainty histogram, either up or down. Helpful for dumping datacards.
    const Hist& fetch_unc (const std::string& key, const std::string& direction) const;

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
       @param allunc If this is false, only the stat uncertainties will be included in the histogram.
    */
    TH1D* roothist (bool allunc = true) const;

    /**
       Get all of the uncertainty histograms.
       The keys are the name of the uncertainty including "Up" or "Down" at the end.
    */
    Types::map<TH1D*> unchists () const;

    /**
       Get the maximum bin and the total number of bins.
       Does not include overflow bins.
    */
    std::pair<unsigned, unsigned> get_maxbin_outof () const;

    /// Get the maximum value including uncertainties (for plotting)
    double max_w_unc () const;
    /// Get the minimum value including uncertainties, but not less than 0.0 (for plotting)
    double min_w_unc (const bool includezeros = true) const;

    /// Sets the value of the total number of events, throws exception if total is already set.
    void set_total (double newtotal);

  private:
    std::string label {};
    unsigned nbins {};
    double min {};
    double max {};

    std::vector<double> contents {};
    std::vector<double> sumw2 {};

    double total {};                                           ///< Stores the total weights of files filling this

    double get_unc (unsigned bin, bool allunc = true) const;   ///< Find the full uncertainty from uncs hists and sumw2
    void doscale (const double scale);                         ///< Scales histogram without scaling uncertainties
    void doscale (const double lumi, const double xs);         ///< Scales histogram without scaling uncertainties
    Types::map<Hist> uncs;                                     ///< Store of alternate histograms for uncertainties

    /// Apply some function to this histogram and all its uncertainties
    template<typename F> void doall (const F& func);

    using Envelope = std::tuple<Hist, Hist, std::list<Hist>>;
    mutable Types::map<Envelope> envs;                         ///< Envelope information
    mutable bool envs_set{false};                              ///< Determine whether envelope minmax has been set or not
    void set_env_min_max () const;                             ///< Sets the min and max histograms for each envelope
  };

}


#endif
