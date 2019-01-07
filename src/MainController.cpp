#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/MainController.h>


using namespace crombie2;


MainController::MainController (ConfigPage& globalpage,
                                ConfigPage& filepage,
                                ConfigPage& plotpage,
                                ConfigPage& selectionpage,
                                ConfigPage& uncertaintypage,
                                ConfigPage& jobpage) :
  cutcontrol {selectionpage, cutmodel},
  filecontrol {filepage, filemodel},
  globalcontrol {globalpage, globalmodel},
  plotcontrol {plotpage, plotmodel},
  jobpage {jobpage}
{

  button.set_border_width(10);

  jobpage.pack_end(submitbox, Gtk::PACK_SHRINK);
  submitbox.pack_start(button, Gtk::PACK_SHRINK);
  button.signal_clicked().
    connect(sigc::mem_fun(*this, &MainController::on_submit_job));

  submitbox.show();
  button.show();

}


void MainController::on_submit_job () {

  auto num_files = filemodel.num_files(globalmodel);

  if (not num_files)
    return;

  auto& progress = progresses.emplace_back();

  jobpage.box().pack_start (progress, Gtk::PACK_SHRINK);
  progress.show();
  progress.set_text(std::string("Setting up ") +
                    std::to_string(num_files) + " files");

  runners.emplace_back(num_files,
                       cutmodel,
                       filemodel,
                       globalmodel,
                       plotmodel,
                       progress);

}

