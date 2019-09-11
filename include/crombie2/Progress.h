#ifndef CROMBIE2_PROGRESS_H
#define CROMBIE2_PROGRESS_H


#include <glibmm/dispatcher.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/progressbar.h>


namespace crombie2 {
  class Progress {
  public:
    explicit Progress (Gtk::Box& page);

    void set_progress (const std::string& text, double frac = 0);

    bool aborted ();

  private:
    void on_update_progress ();
    void on_abort ();

    bool abort {false};
    Gtk::Button abort_button {"Abort"};

    Glib::Dispatcher emitter {};
    Gtk::ProgressBar bar {};

    std::string newtext {};
    double newfrac {0};

  };
}


#endif
