#ifndef CROMBIE2_LUMISELECTION_H
#define CROMBIE2_LUMISELECTION_H


#include <list>
#include <map>
#include <utility>


namespace crombie2 {
  class LumiSelection {
  public:

    /// Add a lumi range to this object
    void add(unsigned long run, std::pair<unsigned, unsigned> lumi);

    /// Add a single run, lumi to this object
    void add(unsigned long run, unsigned lumi);

    /// Merge other LumiSelection objects into this one
    void add(const LumiSelection& other);

    /// Show the JSON object that represents the LumiSelection
    std::string show () const;

  private:
    /// A store that is kept in order and merges lumis in
    std::map<unsigned long, std::list<std::pair<unsigned, unsigned>>> store {};

  };
}


#endif
