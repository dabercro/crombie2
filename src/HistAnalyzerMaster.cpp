#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>

#include <crombie2/FileSystem.h>
#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/Lock.h>
#include <crombie2/Misc.h>

#include "TCanvas.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"


using namespace crombie2;


HistAnalyzerMaster::HistAnalyzerMaster (bool dohists,
                                        const std::string& outdir, std::vector<Job>& jobs,
                                        const PlotModel& plotmodel, const CutModel& cutmodel,
                                        const ReweightModel& reweightmodel,
                                        const GlobalModel& globalmodel,
                                        const PlotStyleModel& plotstylemodel,
                                        const DatacardModel& datacardmodel,
                                        const OnTheFlyModel& onthefly,
                                        bool dofit,
                                        const FitModel& fitmodel,
                                        const CompareModel& comparemodel,
                                        const EnvelopeModel& envelope) :
  outputdir {outdir},
  plotmodel {plotmodel},
  cutmodel {cutmodel},
  reweightmodel {reweightmodel},
  globalmodel {globalmodel},
  plotstylemodel {plotstylemodel},
  datacardmodel {datacardmodel},
  dofit {dofit},
  fitmodel {fitmodel},
  comparemodel {comparemodel},
  envmodel {envelope}
{

  // If no output directory, we are not going to make hist analyzers
  if (not dohists)
    return;

  // Get the list of branches from the first job

  Tree onefile {jobs[0].get_file_name(), globalmodel.tree};

  std::set<std::string> branchlist {};
  for (auto* branch : *(onefile.get<TTree>(globalmodel.tree)->GetListOfBranches()))
    branchlist.emplace(branch->GetName());

  for (auto& job : jobs) {
    auto& entry = job.get_entry();
    if (xs.insert({entry.name, entry.xs}).second) {
      types.insert({entry.name, job.get_group().type});
      for (auto& legend : job.get_group().entries)
        styles.insert({legend.legend, legend.style});
      for (auto& compare : comparemodel.list)
        styles.insert({compare.legend, compare.style});
    }

    for (auto& plot : plotmodel.list) {
      for (auto& selection : cutmodel.selections) {
        auto output_file = selection.get_name() + "_" + plot.name.get();

        auto cutstr = plotstylemodel.donminus1
          ? Misc::nminus1(plot.expr(job.get_group().type), cutmodel.expand(selection.cut))
          : cutmodel.expand(selection.cut);

        auto weightstr = cutmodel.expand(job.get_group().type == FileGroup::FileType::DATA
                                         ? selection.data_weight
                                         : selection.mc_weight);

        auto& model = histmodels[output_file];
        model.insert({job.get_entry().name.get(),
              {job, globalmodel, plot, plot.expr(job.get_group().type), cutstr, weightstr, onthefly, envelope}}
          ).first->second.add_job(job);

        if (not model.lines.size())
          model.lines = plot.vert_lines();
        if (not model.labels.size())
          model.labels = cutmodel.labels(selection.cut);

        // If the selection is in the "shape" uncertainies, add a histogram
        for (auto& hist : datacardmodel.hists) {
          if (hist.selection.get() + "_" + hist.plot.get() == output_file) {
            for (auto& unc : datacardmodel.flats) {

              if (unc.shape.get() == "shape" and unc.has_region(hist.selection)) {

                for (auto dir : {Misc::uncdir::UP, Misc::uncdir::DOWN}) {

                  auto unc_output_file = selection.get_name() + "_"
                    + unc.name.get() + (dir == Misc::uncdir::UP ? "Up" : "Down") + "_"
                    + plot.name.get();

                  histmodels[unc_output_file].
                    insert({job.get_entry().name.get(),
                          {job, globalmodel, plot,
                           Misc::uncertify(branchlist, plot.expr(job.get_group().type), unc.name, dir),
                           Misc::uncertify(branchlist, cutstr, unc.name, dir),
                           Misc::uncertify(branchlist, weightstr, unc.name, dir),
                           onthefly, EnvelopeModel()}}).first->second.add_job(job);

                }

              }
            }
          }
        }

      }
    }
  }

}


void HistAnalyzerMaster::output () const {

  if (not outputdir.size())
    return;

  // Map to output file
  Types::map<Hist> comparehists;

  // Now make each output
  for (auto& key_output : histmodels) {
    // Merge them using legend entries
    Types::map<Hist> datahists {};
    Types::map<Hist> mchists {};
    Types::map<Hist> signalhists {};

    auto* compareuses = comparemodel.get(key_output.first);

    // Scale all of the histograms
    for (auto& key_input : key_output.second) {

      auto histsplit = scaled_split(key_input, true);

      auto type = types.at(key_input.first);

      auto& outmap = type == FileGroup::FileType::MC
        ? mchists
        : (type == FileGroup::FileType::DATA
           ? datahists
           : signalhists);

      for (auto& entry : histsplit.get_hists()) {
        outmap[entry.first].add(entry.second);
        if (compareuses)
          comparehists[compareuses->legend].
            add(entry.second);
      }

    }

    Lock lock {};
    draw_plot(key_output.first, datahists, mchists, signalhists,
              Misc::split(key_output.first, "_").front() == plotstylemodel.blind.get(),
              false, key_output.second.lines, key_output.second.labels);

  }

  if (comparemodel.list.size()) {
    Lock lock {};
    Types::map<Hist> emptyhists {};

    if (plotstylemodel.normalize) {
      for (auto& hist : comparehists)
        hist.second.scale(1.0/hist.second.integral());
    }

    draw_plot("comparison", emptyhists, emptyhists, comparehists, false, true);
  }

}


HistSplit HistAnalyzerMaster::scaled_split (const std::pair<std::string, HistModel>& histentry, bool withenv) const {

  auto histsplit = (withenv
                    ? histentry.second.get_histsplit_with_env()
                    : histentry.second.get_histsplit());

  if (types.at(histentry.first) != FileGroup::FileType::DATA)
    histsplit.scale(globalmodel.luminosity, xs.at(histentry.first));

  return histsplit;

}


namespace {

  void add_to (Hist& target, const Types::map<Hist>& input) {

    for (auto& hist : input)
      target.add(hist.second);

  }


  std::vector<std::pair<std::string, TH1D*>> sorted_vec (Types::map<Hist>& hists, bool usemax = false) {
    std::vector<std::pair<std::string, TH1D*>> sortvec {};
    sortvec.reserve(hists.size());

    for (auto& hist : hists)
      sortvec.push_back(std::make_pair(hist.first, hist.second.roothist()));

    std::sort(sortvec.begin(), sortvec.end(), [usemax] (auto& a, auto& b) {
        return usemax 
          ? a.second->GetMaximum() > b.second->GetMaximum()
          : a.second->Integral() > b.second->Integral();
      });

    return sortvec;
  }


  TH1D* styled (TH1D* hist, FileGroup::FileType type, short style, double scale = 1.0, bool comparing = false) {

    hist->Scale(scale);

    hist->SetLineColor(kBlack);
    switch(type) {
    case(FileGroup::FileType::DATA) :
      hist->SetMarkerStyle(8);
      hist->SetMarkerColor(style);
      hist->SetLineColor(style);
      hist->SetLineWidth(1);
      break;
    case(FileGroup::FileType::SIGNAL) :
      if (comparing)
        hist->SetLineColor(style);
      else
        hist->SetLineStyle(style);
      break;
    case(FileGroup::FileType::MC) :
      hist->SetFillStyle(1001);
      hist->SetFillColor(style);
      hist->SetLineWidth(1);
      break;
    default: // Don't know what you would want to do here
      throw;
    }

    return hist;
  }


  TLegend legend(const Hist& hist, unsigned numlabels) {
    auto bins = hist.get_maxbin_outof();
    // The upper left corner of the legend;
    double x_left = ((bins.first * 2)/bins.second) ? 0.15 : 0.65;

    // Height determined by number of anticipated legend entries
    TLegend leg{x_left, 0.875 - std::min(0.5, 0.075 * numlabels), x_left + 0.25, 0.875};
    leg.SetBorderSize(0);
    leg.SetFillStyle(0);
    return leg;
  }

  std::vector<TLatex> labels_maker (const std::vector<std::string>& labels, double legend_location) {
    std::vector<TLatex> output {};

    std::string wrapper = "#bf{";

    double left = legend_location < 0.5 ? 0.9 : 0.15;
    short align = legend_location < 0.5 ? 31 : 11;
    double top = 0.875;

    for (auto& label : labels) {
      std::string wrapped_label = wrapper + label + "}";
      output.emplace_back(left, top, wrapped_label.data());
      output.back().SetTextAlign(align);
      top -= 0.075;
    }

    return output;
  }

}


void HistAnalyzerMaster::draw_plot(const std::string& output,
                                   Types::map<Hist>& data,
                                   Types::map<Hist>& mc,
                                   Types::map<Hist>& signal,
                                   bool blinding,
                                   bool comparing,
                                   std::vector<double> lines,
                                   std::vector<std::string> labels) const {

  // Stores TH1D for this function
  std::list<TH1D> histstore {};
  // Stores fit functions
  std::list<TF1> fitstore {};

  for (auto& env : envmodel.list) {
    // If process level, merge envelopes now.
    // Otherwise, merge later
    if (env.joiner) {
      for (auto& [legend, hist] : mc)
        hist.merge_envs(env.name);
    }
  }

  // Use this to store sums for ratios
  Hist data_hist {};
  Hist bkg_hist {};
  Hist signal_hist {};

  add_to(data_hist, data);
  if (blinding)
    data_hist.scale(0);

  add_to(bkg_hist, mc);
  add_to(signal_hist, signal);
  // Add backgrounds to signal sums too
  add_to(signal_hist, mc);

  auto mcvec = sorted_vec(mc);

  double scale = (plotstylemodel.normalize and data.size() and not blinding)
    ? data_hist.integral()/bkg_hist.integral()
    : 1.0;

  bkg_hist.scale(scale);

  for (auto& env : envmodel.list) {
    // If not process level, merge envelopes here
    if (not env.joiner)
      bkg_hist.merge_envs(env.name);
  }


  const auto* max_hist = &bkg_hist;

  THStack hs{"hs", ""};
  // Get the maximum value
  auto max = bkg_hist.max_w_unc();
  if (not blinding) {
    // Check the data histogram(s)
    for (auto* hist : {&data, &signal}) {
      for(auto& dat : *hist) {
        auto check = dat.second.max_w_unc();
        if (check > max) {
          max = check;
          max_hist = &dat.second;
        }
      }
    }
  }

  hs.SetMaximum(max/std::max(1.0 - 0.1 * labels.size(), 0.5));

  // Need to add to stack in reverse order
  auto i_mc = mcvec.end();
  while(i_mc != mcvec.begin()) {

    // Iterate backwards
    --i_mc;
    // Add pointer to stack
    hs.Add(
      styled(i_mc->second,
             FileGroup::FileType::MC,
             styles.at(i_mc->first),
             scale)
    );

  }

  TLegend leg{legend(*max_hist, styles.size())};

  // MC entries
  for (auto& mc : mcvec)
    leg.AddEntry(mc.second, mc.first.data(), "f");

  // Draw everything
  TCanvas canv{"canv", "canv", 600, 700};
  canv.cd();
  canv.SetTitle(bkg_hist.get_title().data());

  // Top pad
  const double bottom = mcvec.size() ? 0.3 : 0.0;

  TPad pad1{"pad1", "pad1", 0.0, bottom, 1.0, 1.0};
  pad1.SetBottomMargin(bottom ? 0.025 : 0.1);

  if (plotstylemodel.logy)
    pad1.SetLogy();

  pad1.Draw();
  pad1.cd();

  const double nomfont = 0.03;          // Target font size for plot labels
  const double titleoff = 1.55;         // Title offset

  TH1D* bkg_sum = nullptr;

  // Verticle Lines

  std::list<TLine> vlines {};

  if (mcvec.size()) {

    if (plotstylemodel.forcetop) {
      hs.SetMinimum(plotstylemodel.minimum);
      hs.SetMaximum(plotstylemodel.maximum);
    }

    hs.Draw("hist");

    hs.GetYaxis()->SetLabelSize(nomfont/(1 - bottom));
    hs.GetYaxis()->SetTitleSize(nomfont/(1 - bottom));
    hs.GetYaxis()->SetTitleOffset(titleoff);
    hs.GetYaxis()->SetTitle("Events/Bin");

    hs.GetXaxis()->SetLabelSize(0);
    hs.GetXaxis()->SetTitleSize(0);

    bkg_sum = bkg_hist.roothist();
    bkg_sum->SetFillStyle(3001);
    bkg_sum->SetFillColor(kGray);
    bkg_sum->Draw("e2,same");

    if (dofit) {
      for (auto& fit : fitmodel.fits) {
        std::cout << std::endl
                  << "For: " << output << " background Fitting: " << fit.get()
                  << std::endl << std::endl;
        fitstore.emplace_back(fit.fit_hist(bkg_sum));
      }
    }

    for (auto val : lines) {
      auto& line = vlines.emplace_back(val, hs.GetMinimum(), val, hs.GetMaximum());
      line.SetLineColor(kRed);
      line.SetLineWidth(2);
      line.SetLineStyle(2);
      line.Draw("same");
    }

  }

  for (auto& sig : sorted_vec(signal, true)) {

    auto style = styles.at(sig.first);

    leg.AddEntry(styled(sig.second,
                        FileGroup::FileType::SIGNAL,
                        style, 1.0, comparing),
                 sig.first.data(), "lp");

    if (bkg_sum)
      sig.second->Add(bkg_sum);

    if (plotstylemodel.forcetop) {
      sig.second->SetMinimum(plotstylemodel.minimum);
      sig.second->SetMaximum(plotstylemodel.maximum);
    }

    sig.second->Draw("hist,same");

    if (dofit) {
      for (auto& fit : fitmodel.fits) {
        std::cout << std::endl
                  << "For: " << output << " " << sig.first << " Fitting: " << fit.get()
                  << std::endl << std::endl;
        fitstore.emplace_back(fit.fit_hist(sig.second));
        fitstore.back().SetLineColor(style);
      }
    }

  }

  if (not blinding) {
    for (auto& dat : sorted_vec(data, true)) {
      leg.AddEntry(styled(dat.second,
                          FileGroup::FileType::DATA,
                          styles.at(dat.first)),
                   dat.first.data(), "lp");
      dat.second->Draw("PE,same");
    }
  }

  canv.cd();
  TPad pad2{"pad2", "pad2", 0.0, 0.0, 1.0, bottom};

  if (bottom) {
    pad2.SetTopMargin(0.025);
    pad2.SetBottomMargin(0.4);
    pad2.cd();

    auto bkg_ratio = bkg_hist.ratio(bkg_hist);
    auto data_ratio = data.size() ? data_hist.ratio(bkg_hist) : bkg_ratio;
    auto signal_ratio = signal.size() ? signal_hist.ratio(bkg_hist) : bkg_ratio;

    auto set_yaxis = [bottom, titleoff, this] (auto* hist) {
      auto* axis = hist->GetYaxis();
      axis->SetNdivisions(504, true);
      axis->SetTitle(std::string(plotstylemodel.ratiolabel).data());
      axis->SetTitleOffset((bottom)/(1-bottom) * titleoff);
      axis->CenterTitle();
      return hist;
    };

    auto* bhist = set_yaxis(bkg_ratio.roothist(&histstore));

    for (auto* axis : {bhist->GetXaxis(), bhist->GetYaxis()}) {
      axis->SetTitleSize(nomfont/bottom);
      axis->SetLabelSize(nomfont/bottom);
    }

    bhist->SetFillStyle(3001);
    bhist->SetFillColor(kGray);

    const float buffer = plotstylemodel.ratiobuffer;

    bhist->SetMinimum(std::max(std::min({bkg_ratio.min_w_unc(), data_ratio.min_w_unc(false), signal_ratio.min_w_unc(false)}) * (1.0 + buffer) - buffer,
                               double(plotstylemodel.minratio)));
    bhist->SetMaximum(std::min(std::max({bkg_ratio.max_w_unc(), data_ratio.max_w_unc(), signal_ratio.max_w_unc()}) * (1.0 + buffer) - buffer,
                               double(plotstylemodel.maxratio)));
    bhist->Draw("e2");

    for (auto val : lines) {
      auto& line = vlines.emplace_back(val, bhist->GetMinimum(), val, bhist->GetMaximum());
      line.SetLineColor(kRed);
      line.SetLineWidth(2);
      line.SetLineStyle(2);
      line.Draw("same");
    }

    // All of the signals should be drawn separately...
    if (signal.size())
      styled(signal_ratio.roothist(&histstore), FileGroup::FileType::SIGNAL, 2, scale, comparing)->Draw("hist,same");
    if (not blinding and data.size())
      styled(data_ratio.roothist(&histstore), FileGroup::FileType::DATA, 1)->Draw("PE,same");

    pad2.SetGridy(1);

    canv.cd();
    pad2.Draw();

  }

  pad1.cd();

  for (auto& fit : fitstore)
    fit.Draw("same");

  leg.Draw();

  canv.cd();
  // Labels
  TLatex latex{};
  constexpr double toplocation = 0.96;
  latex.SetTextSize(0.035);

  double currentlumi {globalmodel.luminosity * (plotstylemodel.usegloballumi ? 1.0 : scale)};

  if (currentlumi) {
    latex.SetTextAlign(31);

    std::stringstream lumistream;
    lumistream << std::setprecision(3) << currentlumi/1000.0;
    std::string lumilabel;
    lumistream >> lumilabel;
    lumilabel += " fb^{-1} (13 TeV)";

    latex.DrawLatex(0.95, toplocation, lumilabel.data());
  }
  latex.SetTextFont(62);
  latex.SetTextAlign(11);
  latex.DrawLatex(0.12, toplocation, "CMS");
  latex.SetTextSize(0.030);
  latex.SetTextFont(52);
  latex.SetTextAlign(11);

  latex.DrawLatex(0.2, toplocation, std::string(plotstylemodel.plottype).data());

  auto labels_latex = labels_maker(labels, std::min(leg.GetX1(), leg.GetX2()));

  for (auto& label_latex : labels_latex)
    label_latex.Draw();

  // Save everything
  FileSystem::mkdirs(outputdir);

  const std::regex replace_expr {"/|\\*|\\+|-"};

  for (auto& suff : {".pdf", ".png", ".C"}) {
    auto outname = outputdir + "/" +
      std::regex_replace(output, replace_expr, "_") +
      suff;
    canv.SaveAs(outname.data());
  }

  if (plotstylemodel.saveroot) {
    auto outname = outputdir + "/" +
      std::regex_replace(output, replace_expr, "_") + ".root";

    TFile rootout {outname.data(), "RECREATE"};
    for (auto* hists : {&data, &mc, &signal}) {
      for (auto& hist : *hists) {
        rootout.WriteTObject(hist.second.roothist(), hist.first.data());
      }
    }
    
  }

}


HistAnalysis HistAnalyzerMaster::get_analysis_histograms (const std::string& selection) const {

  Hist data {};
  Hist mc {};
  Hist background {};

  auto _plotname = reweightmodel.plotname.get();
  auto plotname = _plotname.size()
    ? _plotname
    : plotmodel.list.front().name.get();

  auto signal = reweightmodel.signal.get();

  auto keyname = selection + "_" + plotname;

  for (auto& hists : histmodels.at(keyname)) {

    auto histsplit = scaled_split(hists);

    for (auto& histpair : histsplit.get_hists()) {
      auto& hist = histpair.second;

      if (histpair.first == reweightmodel.candle.get())
        data.add(hist);
      else if (not signal.size() or histpair.first == signal)
        mc.add(hist);
      else
        background.add(hist);
    }

  }

  return signal.size()
    ? HistAnalysis(std::move(data), std::move(mc), std::move(background))
    : HistAnalysis(std::move(data), std::move(mc));

}


namespace {

  class MCColumn {
  public:
    std::string bin;
    std::string processname;
    int processnum;
    double obs;
  };

}


void HistAnalyzerMaster::dumpdatacard (const std::string& datadir,
                                       const FileModel& filemodel) const {

  if (not datadir.size())
    return;

  // Maps "bin" (region), then process, then Hist
  std::map<std::string, std::map<std::string, Hist>> bin_proc_hist {};

  // Adds the region histograms to our bin_proc_hist
  auto add_region = [&bin_proc_hist, &filemodel, this] (const std::string& region, const std::string& plot) {

    auto key = region + "_" + plot;

    for (auto& infile : histmodels.at(key)) {

      auto histsplit = scaled_split(infile);

      for (auto& hist : histsplit.get_hists())
        bin_proc_hist[region][filemodel.get_datacard_name(hist.first)].add(hist.second);

    }

  };

  for (auto& hist : datacardmodel.hists) {
    auto plot = hist.plot.get();
    auto region = hist.selection.get();

    add_region(region, plot);

    for (auto& unc : datacardmodel.flats) {
      if (unc.shape.get() == "shape" and unc.has_region(hist.selection)) {
        for (auto dir : {Misc::uncdir::UP, Misc::uncdir::DOWN}) {
          auto unc_region = region + "_"
            + unc.name.get() + (dir == Misc::uncdir::UP ? "Up" : "Down");

          add_region(unc_region, plot);
        }
      }
    }
  }

  FileSystem::mkdirs(datadir);

  // Make the histograms in the .root file

  auto histfilename = datadir + "/plots.root";
  TFile histfile {histfilename.data(), "RECREATE"};

  for (auto& bin : bin_proc_hist) {
    for (auto& proc : bin.second) {
      auto histname = proc.first + "_" + bin.first;
      histfile.WriteTObject(proc.second.roothist(), histname.data());
    }
  }

  histfile.Close();

  std::ofstream datacard {datadir + "/datacard.txt"};

  // Standard header

  datacard << "imax   *   number of channels" << std::endl
           << "jmax   *   number of backgrounds" << std::endl
           << "kmax   *   number of systematics (automatic)" << std::endl
           << "------------------------------" << std::endl
           << "shapes * * plots.root $PROCESS_$CHANNEL $PROCESS_$CHANNEL_$SYSTEMATIC" << std::endl
           << "------------------------------" << std::endl
           << std::left << std::setw(25) << "bin";

  // Get the columns for the data yields

  std::vector<double> bin_contents {};

  bool print {globalmodel.printdatacardview};

  if (print)
    std::cout << std::left << std::setw(15) << " ";

  for (auto& hist : datacardmodel.hists) {
    auto& bin = bin_proc_hist.at(hist.selection);
    double value = 0;
    for (auto& data : filemodel.get_datacard_names(FileGroup::FileType::DATA)) {
      auto& hist = bin.at(data);
      value += hist.integral();
    }
    bin_contents.push_back(value);

    auto selection = hist.selection.get();

    datacard << std::left << std::setw(15) << selection;
    if (print)
      std::cout << std::right << std::setw(15) << selection;
  }

  datacard << std::endl << std::left << std::setw(25) << "observation";
  if (print)
    std::cout << std::endl << std::left << std::setw(15) << "Data";

  for (auto value : bin_contents) {
    datacard << std::left << std::setw(15) << std::setprecision(1) << std::fixed << value;
    if (print)
      std::cout << std::right << std::setw(15) << std::setprecision(1) << std::fixed << value;
  }

  datacard << std::endl << "------------------------------" << std::endl;

  // Get the columns for the MC yields

  std::vector<MCColumn> columns {};
  int signalnum = 0;
  int mcnum = 1;

  for (auto& proc : filemodel.get_datacard_names(FileGroup::FileType::SIGNAL)) {
    for (auto& hist : datacardmodel.hists) {
      auto& bin = bin_proc_hist.at(hist.selection);
      auto& prochist = bin.at(proc);
      columns.push_back({hist.selection, proc, signalnum, prochist.integral()});
    }
    --signalnum;
  }

  for (auto& proc : filemodel.get_datacard_names(FileGroup::FileType::MC)) {
    for (auto& hist : datacardmodel.hists) {
      auto& bin = bin_proc_hist.at(hist.selection);
      auto& prochist = bin.at(proc);
      columns.push_back({hist.selection, proc, mcnum, prochist.integral()});
    }
    ++mcnum;
  }

  auto mcline = [&datacard, &columns] (std::string head, auto MCColumn::*offset) {
    datacard << std::left << std::setw(25) << head;
    for (auto& column : columns) {
      datacard << std::left << std::setw(17);
      datacard << std::setprecision(6) << std::fixed;
      datacard << column.*offset;
    }
    datacard << std::endl;
  };

  mcline("bin", &MCColumn::bin);
  mcline("process", &MCColumn::processname);
  mcline("process", &MCColumn::processnum);
  mcline("rate", &MCColumn::obs);

  if (print) {
    std::string lastprocess = "";
    for (auto& column : columns) {
      if (column.processname != lastprocess) {
        std::cout << std::endl << std::left << std::setw(15) << column.processname;
        lastprocess = column.processname;
      }

      std::cout << std::right << std::setw(15)
                << std::setprecision(6) << std::fixed
                << column.obs;
    }
    std::cout << std::endl;
  }

  datacard << "------------------------------" << std::endl;

  // Now make the uncertainties

  for (auto& unc : datacardmodel.flats) {

    datacard << std::left << std::setw(15) << unc.name.get()
             << std::left << std::setw(10) << unc.shape.get();

    for (auto& column : columns) {

      datacard << std::left << std::setw(17)
               << (unc.has_process(column.processname) and unc.has_region(column.bin) ?
                   unc.value.get() : "-");

    }

    datacard << std::endl;

  }

  // Finally the rate params

  datacard << "------------------------------" << std::endl;

  for (auto& proc : filemodel.get_datacard_names(FileGroup::FileType::MC)) {
    auto* rate = datacardmodel.get_rateparams(proc);
    if (rate) {
      for (auto& hist : datacardmodel.hists) {
        auto region = hist.selection.get();
        datacard << "SF_" << proc << "  rateParam  " << region << "  " << proc
                 << "  1  [" << rate->min.get() << "," << rate->max.get() << "]"
                 << std::endl;
      }
    }
  }

  datacard << "* autoMCStats 1 1 1" << std::endl;
}
