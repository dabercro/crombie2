#ifndef CROMBIE2_SELECTIONDISPLAY_H
#define CROMBIE2_SELECTIONDISPLAY_H


#include <gtkmm/button.h>

#include <crombie2/CutModel.h>


namespace crombie2 {
  class SelectionDisplay : public Gtk::Button {
  public:
    SelectionDisplay (CutModel& cutmodel, Selection& selection);

    /// A box to draw the selection table and button inside of
    Gtk::VBox box {};

  private:
    CutModel& model;
    Selection& selection;

    void on_click ();

  };
}

#endif
