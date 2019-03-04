#include <thread>

#include <crombie2/FileSystem.h>
#include <crombie2/MainController.h>
#include <crombie2/Misc.h>
#include <crombie2/Runner.h>


using namespace crombie2;


MainController::MainController (std::map<std::string, ConfigPage>& pagemap,
                                ConfigPage& jobpage) :
  globalcontrol {pagemap.at("globals"), globalmodel},
  jsoncontrol {pagemap.at("json"), jsonmodel},
  reweightcontrol {pagemap.at("reweight"), reweightmodel},
  ontheflycontrol {pagemap.at("onthefly"), ontheflymodel},
  plotstylecontrol {pagemap.at("plotstyle"), plotstylemodel},
  filecontrol {pagemap.at("files"), filemodel},
  plotcontrol {pagemap.at("plots"), plotmodel},
  cutcontrol {pagemap.at("selections"), cutmodel},
  allmodels  {pagemap},
  allcontrol {jobpage, allmodels, pagemap},
  jobpage {jobpage}
{

  button.set_border_width(10);

  // Histogram making

  setup_controls(histsbox, dohists, histslabel, histoutput,
                 histnorm_label, histnorm);

  dohists.set_active(true);

  histoutput.set_text(Misc::shell("printf $(date +%y%m%d)"));
  histoutput.show();

  // Cutflow making

  setup_controls(cutflowbox, docutflow, cutflowlabel);

  // Lumi JSON making

  setup_controls(lumibox, dolumi, lumilabel);

  // Reweight histograms

  setup_controls(reweightbox, doreweight,
                 reweight_norm_label, reweight_norm);

  // Submission buttons

  jobpage.pack_end(submitbox, Gtk::PACK_SHRINK);
  submitbox.pack_start(button, Gtk::PACK_SHRINK);
  button.signal_clicked().
    connect(sigc::mem_fun(*this, &MainController::on_submit_job));

  submitbox.show();
  button.show();

}


void MainController::setup_controls (Gtk::HBox& box, Gtk::Widget& to_add) {

  box.pack_start(to_add, Gtk::PACK_SHRINK);
  to_add.show();

  jobpage.pack_start(box, Gtk::PACK_SHRINK);
  box.show();

}


void MainController::on_submit_job () {

  auto num_files = filemodel.num_files(globalmodel.inputdir);

  if (not num_files)
    return;

  auto& progress = progresses.emplace_back(jobpage.box());

  progress.set_progress(std::string("Setting up ") +
                        std::to_string(num_files) + " files");

  std::string outdir = dohists.get_active()
    ? plotstylemodel.outplotdir.get() + "/" + histoutput.get_text()
    : "";

  // Check if everything is okay
  if (globalmodel.is_valid() and
      ontheflymodel.is_valid() and
      cutmodel.is_valid() and
      (not outdir.size() or FileSystem::confirm_overwrite(outdir))
      ) {

    std::thread thread {[num_files, &progress, outdir, this] () { run(num_files, outdir, progress); }};
    thread.detach();

  }
  else
    progress.set_progress(std::string("Aborted"));

}


void MainController::run (unsigned num_files, const std::string& histoutdir, Progress& progress) {

  if (histoutdir.size())
    allmodels.save(histoutdir + "/models.cnf");

  Runner runner {
    num_files, cutmodel, filemodel,
    globalmodel, jsonmodel,
    reweightmodel, ontheflymodel,
    plotmodel, plotstylemodel, progress
  };
  runner.run(histoutdir, histnorm.get_active(),
             docutflow.get_active(), dolumi.get_active(),
             doreweight.get_active(), reweight_norm.get_active());

}
