#ifndef CROMBIE2_ENVELOPEMODEL_H
#define CROMBIE2_ENVELOPEMODEL_H


#include <crombie2/Envelopes.h>
#include <crombie2/ListModel.h>
#include <crombie2/Tree.h>


namespace crombie2 {

  class EnvelopeModel : public ListModel<Envelopes> {
  public:
    using cutstype = Envelopes;

    std::string get_name () const override;

    RemoveWrapper<cutstype>& add_cutstring (const std::string& label);

    bool is_valid (Tree& tree) const;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };

}


#endif
