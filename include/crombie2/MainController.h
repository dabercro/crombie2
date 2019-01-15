#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H


#include <mutex>

#include <crombie2/CutController.h>
#include <crombie2/FileController.h>
#include <crombie2/GlobalModel.h>
#include <crombie2/PlotController.h>
#include <crombie2/Progress.h>
#include <crombie2/SimpleController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& filepage,
                    ConfigPage& plotpage,
                    ConfigPage& selectionpage,
                    ConfigPage& uncertaintypage,
                    ConfigPage& jobpage);

  private:
    CutModel cutmodel {};
    CutController cutcontrol;

    FileModel filemodel {};
    FileController filecontrol;

    GlobalModel globalmodel {};
    SimpleController globalcontrol;

    PlotModel plotmodel {};
    PlotController plotcontrol;

    ConfigPage& jobpage;

    void on_submit_job ();
    void run (unsigned num_files, Progress& progress);

    std::list<Progress> progresses {};

    Gtk::HBox histsbox {};
    Gtk::CheckButton dohists {};
    Gtk::Label histslabel {"Plot output directory"};
    Gtk::Entry histoutput {};

    Gtk::HButtonBox submitbox {};
    Gtk::Button button {"Submit"};

  };
}


#endif
