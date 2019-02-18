#include <crombie2/ReweightReader.h>

#include "TFile.h"


using namespace crombie2;


ReweightReader::ReweightReader (const ReweightReader& other) :
  expr {other.expr},
  cut {other.cut},
  file {other.file},
  hist {other.hist} {}


std::string ReweightReader::extract_index () const {

  auto expr_str = expr.get();
  auto start = expr_str.find('[');
  auto end = expr_str.find(']');

  if (start != std::string::npos and end != std::string::npos) {
    // Return the characters between '[' and ']'
    return expr_str.substr(start + 1, end - start - 1);
  }

  return "1";

}


TH1D ReweightReader::extract_hist () const {

  TFile input {file.get().data()};
  TH1D output = *(static_cast<TH1D*>(input.Get(hist.get().data())));
  input.Close();

  return output;

}
