#ifndef CROMBIE2_UPDATEBOX_H
#define CROMBIE2_UPDATEBOX_H


#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>


namespace crombie2 {
  class UpdateBox : public Gtk::HButtonBox {
  public:
    UpdateBox ();

    /// Get reference to update button to set the click signal
    Gtk::Button& update ();

  private:
    Gtk::Button updatebutton {"Update"};
    
  };
}


#endif
