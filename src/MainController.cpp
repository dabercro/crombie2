#include <thread>

#include <crombie2/MainController.h>
#include <crombie2/Misc.h>
#include <crombie2/Runner.h>


using namespace crombie2;


MainController::MainController (ConfigPage& globalpage,
                                ConfigPage& plotstylepage,
                                ConfigPage& filepage,
                                ConfigPage& plotpage,
                                ConfigPage& selectionpage,
                                ConfigPage& uncertaintypage,
                                ConfigPage& jobpage) :
  globalcontrol {globalpage, globalmodel},
  plotstylecontrol {plotstylepage, plotstylemodel},
  filecontrol {filepage, filemodel},
  plotcontrol {plotpage, plotmodel},
  cutcontrol {selectionpage, cutmodel},
  jobpage {jobpage}
{

  button.set_border_width(10);

  jobpage.pack_start(histsbox, Gtk::PACK_SHRINK);

  histsbox.pack_start(dohists, Gtk::PACK_SHRINK);
  histsbox.pack_start(histslabel, Gtk::PACK_SHRINK);
  histsbox.pack_start(histoutput);
  histsbox.show();

  dohists.show();
  histslabel.show();

  histoutput.set_text(Misc::shell("printf $(date +%y%m%d)"));
  histoutput.show();

  jobpage.pack_end(submitbox, Gtk::PACK_SHRINK);
  submitbox.pack_start(button, Gtk::PACK_SHRINK);
  button.signal_clicked().
    connect(sigc::mem_fun(*this, &MainController::on_submit_job));

  submitbox.show();
  button.show();

}


void MainController::on_submit_job () {

  auto num_files = filemodel.num_files(globalmodel.inputdir);

  if (not num_files)
    return;

  auto& progress = progresses.emplace_back(jobpage.box());

  progress.set_progress(std::string("Setting up ") +
                        std::to_string(num_files) + " files");

  if (cutmodel.is_valid()) {

    std::thread thread {[num_files, &progress, this] () { run(num_files, progress); }};
    thread.detach();

  }
  else
    progress.set_progress(std::string("Aborted"));

}


void MainController::run (unsigned num_files, Progress& progress) {

  Runner runner {
    num_files, cutmodel, filemodel,
    globalmodel, plotmodel, plotstylemodel, progress
  };
  runner.run(dohists.get_active() ? histoutput.get_text() : "");

}
