#ifndef CROMBIE2_CUT_H
#define CROMBIE2_CUT_H


#include <crombie2/TextConfigurable.h>


namespace crombie2 {

  /**
     A Cut is just a configurable string with a default relabel,
     which is based on the LHS of the cut.
  */
  class Cut : public TextConfigurable {
  public:
    Cut (const std::string& cut);

    std::string label () const override;

    std::string get () const override;

    void set (const std::string& input) override;

    bool is_literal () const;

    /// Get the cut without quotes, in the case of literal cut
    std::string cut () const;

  private:
    /// Holds whether or not this cut is a literal cut or a substitution
    bool literal;

    /// Holds the cut value, without quotes
    std::string value;

  };

}

#endif
