#include "TFile.h"

#include <crombie2/FileSystem.h>
#include <crombie2/HistAnalysis.h>
#include <crombie2/Lock.h>


using namespace crombie2;


HistAnalysis::HistAnalysis (const Hist& data, const Hist& mc) :
  data {data},
  mc {mc} {}


HistAnalysis::HistAnalysis (const Hist& data, const Hist& mc, const Hist& background) :
  has_background {true},
  data {data},
  mc {mc},
  background {background} {}


void HistAnalysis::reweight (bool normalize, const std::string& output,
                             const std::string& histname) const {

  // Copy data
  Hist data_copy {data};

  // Normalize to match mc
  if (normalize) {

    auto mc_total = mc.integral() + background.integral();
    data_copy.scale(mc_total / data_copy.integral());

  }

  // Subtract background, if necessary
  if (has_background)
    data_copy.add(background, -1.0);

  // Get the reweight histogram and save it
  auto result = data_copy.ratio(mc);

  Lock lock {};
  TFile outfile {output.data(), FileSystem::exists(output) ? "UPDATE" : "RECREATE"};
  outfile.WriteTObject(result.roothist(), histname.data());
  outfile.Close();

}
