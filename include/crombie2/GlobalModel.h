#ifndef CROMBIE2_GLOBALMODEL_H
#define CROMBIE2_GLOBALMODEL_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {

  class GlobalModel : public ConfigModel {
  public:

    std::string get_name () const override;

    /// Input directory for files
    Configurable<std::string> inputdir {"Input directory", "."};

    /// The number of threads to do all jobs
    Configurable<int> nthreads {"Number Threads", 1};

    /// The name of the tree to read events from
    Configurable<std::string> tree {"Tree", "events"};

    /// The luminosity in pb
    Configurable<double> luminosity {"Luminosity [/pb]", 10000};

    /// The weights to read
    Configurable<std::string> normhist {"Weight Hist", "hSumW"};

    Configurable<std::string> runnum {"Run Expression", "runNumber"};

    Configurable<std::string> luminum {"Lumi Expression", "lumiNumber"};

    Configurable<double> minratio {"Ratio Minimum", 0.0};

    Configurable<double> maxratio {"Ratio Maximum", 2.0};

    ConfigTable configs {
      &inputdir,
      &nthreads,
      &tree,
      &luminosity,
      &normhist,
      &runnum,
      &luminum,
      &minratio,
      &maxratio
    };

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };

}


#endif
