#include <sstream>

#include <crombie2/LumiSelection.h>


using namespace crombie2;


void LumiSelection::add(unsigned long run, std::pair<unsigned, unsigned> lumi) {

  auto& to_insert = store[run];

  auto before{to_insert.begin()};  // Iterator the beginning of the new pair should go
  auto after{before};              // Iterator where the end of the new pair should go

  for (; after != to_insert.end(); ++after) {
    if ((lumi.second + 1) < after->first)  // If would not merge higher, stop here
      break;
    if (before == after) {                  // If still finding, drag that along
      if (lumi.first > (after->second + 1))
        ++before;
    }
  }

  // Just need to insert
  if (before == after)
    to_insert.insert(before, lumi);
  else {
    // Otherwise, need best values
    auto insertion = std::make_pair(std::min(lumi.first, before->first),
                                    std::max(lumi.second, (--after)->second));
    // Placed in front of "before"
    to_insert.insert(before, insertion);
    // Remove the other values
    // Go forward one for after again, since we went backwards above for range
    to_insert.erase(before, ++after);
  }
}


void LumiSelection::add(unsigned long run, unsigned lumi) {
  add(run, std::make_pair(lumi, lumi));
}


void LumiSelection::add(const LumiSelection& other) {
  for (auto& run : other.store) {
    for (auto& pair : run.second)
      add(run.first, pair);
  }
}


std::string LumiSelection::show () const {
  std::stringstream os {};
  os << "{";
  bool startedrun = false;
  for (auto& run : store) {
    bool startedlumi = false;
    if (startedrun)
      os << "], ";
    startedrun = true;
    os << '"' << run.first << '"' << ": [";
    for (auto& lumi : run.second) {
      if (startedlumi)
        os << ", ";
      startedlumi = true;
      os << "[" << lumi.first << ", " << lumi.second << "]";
    }
  }
  os << "]}";
  return os.str();
}
