#ifndef CROMBIE2_GLOBALMODEL_H
#define CROMBIE2_GLOBALMODEL_H


#include <crombie2/SimpleModel.h>
#include <crombie2/BoolConfigurable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  /**
     @brief A SimpleModel for variables that are used in multiple Analyzer types
  */
  class GlobalModel : public SimpleModel {
  public:
    GlobalModel ();
    GlobalModel (const GlobalModel& other);

    std::string get_name () const override;

    bool is_valid () const override;

    /// Input directory for files
    Configurable<std::string> inputdir {"Input directory", ".",
        "Input directory for files"};

    /// The number of threads to do all jobs
    Configurable<unsigned> nthreads {"Number Threads", 1,
        "The number of threads to do all jobs"};

    /// The name of the tree to read events from
    Configurable<std::string> tree {"Tree", "events",
        "The name of the TTree to read events from"};

    /// The luminosity in pb
    Configurable<double> luminosity {"Luminosity [/pb]", 10000,
        "The luminosity in pb"};

    /// The weights to read to normalize MC
    Configurable<std::string> normhist {"Weight Hist", "hSumW"};

    /// If true, dump a nicer datacard table when making datacards
    BoolConfigurable printdatacardview {"Print Datacard Table"};

    BoolConfigurable no_stats {"Don't plot stats"};

  };

}


#endif
