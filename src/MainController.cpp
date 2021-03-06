#include <thread>

#include <crombie2/FileSystem.h>
#include <crombie2/MainController.h>
#include <crombie2/Runner.h>


using namespace crombie2;


MainController::MainController (std::map<std::string, ConfigPage>& pagemap,
                                ConfigPage& jobpage) :
  globalcontrol {pagemap.at("globals"), globalmodel},
  jsoncontrol {pagemap.at("json"), jsonmodel},
  reweightcontrol {pagemap.at("reweight"), reweightmodel},
  datacardcontrol {pagemap.at("datacards"), datacardmodel},
  ontheflycontrol {pagemap.at("onthefly"), ontheflymodel},
  plotstylecontrol {pagemap.at("plotstyle"), plotstylemodel},
  filecontrol {pagemap.at("files"), filemodel},
  plotcontrol {pagemap.at("plots"), plotmodel},
  cutcontrol {pagemap.at("selections"), cutmodel},
  envcontrol {pagemap.at("envelopes"), envmodel},
  fitcontrol {pagemap.at("fits"), fitmodel},
  comparecontrol {pagemap.at("compare"), comparemodel},
  allmodels  {pagemap},
  allcontrol {jobpage, allmodels, pagemap},
  jobpage {jobpage}
{

  button.set_border_width(10);

  // Histogram making

  setup_controls(histsbox, dohists, histslabel, histoutput);

  dohists.set_active(true);
  histoutput.set_text(Misc::shell("printf $(date +%y%m%d)"));

  // Datacard making

  setup_controls(datacardbox, dodatacard,
                 datacardlabel, datacardoutput);

  datacardoutput.set_text(Misc::shell("printf $(date +%y%m%d)"));

  // Cutflow making

  setup_controls(cutflowbox, docutflow, cutflowlabel);

  // Lumi JSON making

  setup_controls(lumibox, dolumi, lumilabel);

  // Reweight histograms

  setup_controls(reweightbox, doreweight,
                 reweight_label);

  // Fit histograms

  setup_controls(fitbox, dofit,
                 fit_label);

  // Replace in configs

  setup_controls(replace_box, replace1, replace_label, replace2, replace_button);

  replace_button.signal_clicked().
    connect(sigc::mem_fun(*this, &MainController::on_replace_all));

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

  auto& progress = progresses.emplace_back(jobpage.box());

  std::string outdir = dohists.get_active()
    ? plotstylemodel.outplotdir.get() + "/" + histoutput.get_text()
    : "";

  std::string datadir = dodatacard.get_active()
    ? datacardmodel.outdir.get() + "/" + datacardoutput.get_text()
    : "";

  // Returns if it's okay to run
  auto checkdir = [] (const std::string& dir) {
    return not dir.size() or FileSystem::confirm_overwrite(dir);
  };

  if (not filemodel.is_valid(globalmodel)) {
    progress.set_progress(std::string("Aborted"));
    return;
  }

  auto checkfile = filemodel.get_one(globalmodel);

  // Check if everything is okay
  if (globalmodel.is_valid() and
      ontheflymodel.is_valid() and
      (not (dodatacard.get_active() or dohists.get_active()) or plotmodel.is_valid(checkfile)) and
      cutmodel.is_valid(checkfile, globalmodel.skip_branch_check) and
      (not dodatacard.get_active() or datacardmodel.is_valid(cutmodel, plotmodel)) and
      checkdir(outdir) and
      checkdir(datadir) and
      comparemodel.is_valid(cutmodel, plotmodel) and
      (not doreweight.get_active() or reweightmodel.is_valid(plotmodel)) and
      (not dolumi.get_active() or jsonmodel.is_valid(checkfile))
      ) {

    auto num_files = filemodel.num_files(globalmodel.inputdir);

    if (not num_files)
      return;

    progress.set_progress(std::string("Setting up ") +
                          std::to_string(num_files) + " files");

    std::thread thread {
      [num_files, &progress, outdir, datadir, this] () {
        run(num_files,
            {{"plots", outdir},
             {"datacards", datadir}},
            progress);
      }
    };
    thread.detach();

  }
  else
    progress.set_progress(std::string("Aborted"));

}


void MainController::run (unsigned num_files,
                          const std::map<std::string, std::string>& dirs,
                          Progress& progress) {

  for (auto& dir : dirs) {
    if (dir.second.size())
      allmodels.save(dir.second + "/models.cnf");
  }

  Runner runner {
    num_files, allmodels, progress
  };
  runner.run({dirs,
        docutflow.get_active(),
        dolumi.get_active(),
        doreweight.get_active(),
        dofit.get_active()
        });

}


void MainController::on_replace_all () {

  auto target = replace1.get_text();
  auto newstr = replace2.get_text();

  if ((target.size() and newstr.size()) or Misc::confirm("One entry is empty. Continue?")) {

    histoutput.set_text(Misc::replace(histoutput.get_text(), target, newstr));
    datacardoutput.set_text(Misc::replace(datacardoutput.get_text(), target, newstr));

    for (auto& model : allmodels.models)
      model.second->replace(target, newstr);

  }

}
