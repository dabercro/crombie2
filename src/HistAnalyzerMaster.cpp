#include <fstream>
#include <iomanip>

#include <crombie2/DatacardModel.h>
#include <crombie2/FileSystem.h>
#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/Lock.h>

#include "TCanvas.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"


using namespace crombie2;


HistAnalyzerMaster::HistAnalyzerMaster (bool dohists,
                                        const std::string& outdir, std::vector<Job>& jobs,
                                        const PlotModel& plotmodel, const CutModel& cutmodel,
                                        const ReweightModel& reweightmodel,
                                        const GlobalModel& globalmodel,
                                        const PlotStyleModel& plotstylemodel,
                                        const OnTheFlyModel& onthefly) :
  outputdir {outdir},
  plotmodel {plotmodel},
  cutmodel {cutmodel},
  reweightmodel {reweightmodel},
  globalmodel {globalmodel},
  plotstylemodel {plotstylemodel}
{

  // If no output directory, we are not going to make hist analyzers
  if (not dohists)
    return;

  for (auto& job : jobs) {
    auto& entry = job.get_entry();
    if (xs.insert({entry.name, entry.xs}).second) {
      types.insert({entry.name, job.get_group().type});
      for (auto& legend : job.get_group().entries)
        styles.insert({legend.legend, legend.style});
    }

    for (auto& plot : plotmodel.list) {
      for (auto& selection : cutmodel.selections) {
        auto output_file = selection.get_name() + "_" + plot.name.get();

        histmodels[output_file].
          insert({job.get_entry().name.get(),
                  {job, globalmodel, plot, cutmodel, selection, onthefly}}).
          first->second.add_job(job);
      }
    }
  }

}


void HistAnalyzerMaster::output () const {

  if (not outputdir.size())
    return;

  // Map to output file and to input file
  Types::map<Types::map<HistSplit>> hists;

  // Now make each output
  for (auto& key_output : histmodels) {
    // Merge them using legend entries
    Types::map<Hist> datahists;
    Types::map<Hist> mchists;
    Types::map<Hist> signalhists;

    // Scale all of the histograms
    for (auto& key_input : key_output.second) {

      auto histsplit = scaled_split(key_input);

      auto type = types.at(key_input.first);

      auto& outmap = type == FileGroup::FileType::MC
        ? mchists
        : (type == FileGroup::FileType::DATA
           ? datahists
           : signalhists);

      for (auto& entry : histsplit.get_hists())
        outmap[entry.first].add(entry.second);

    }

    Lock lock {};
    draw_plot(key_output.first, datahists, mchists, signalhists);

  }

}


HistSplit HistAnalyzerMaster::scaled_split (const std::pair<std::string, HistModel>& histentry) const {

  auto histsplit = histentry.second.get_histsplit();

  if (types.at(histentry.first) != FileGroup::FileType::DATA)
    histsplit.scale(globalmodel.luminosity, xs.at(histentry.first));

  return histsplit;

}


namespace {

  void add_to (Hist& target, Types::map<Hist>& input) {

    for (auto& hist : input)
      target.add(hist.second);

  }


  std::vector<std::pair<std::string, TH1D*>> sorted_vec (Types::map<Hist>& hists) {
    std::vector<std::pair<std::string, TH1D*>> sortvec {};
    sortvec.reserve(hists.size());

    for (auto& hist : hists)
      sortvec.push_back(std::make_pair(hist.first, hist.second.roothist()));

    std::sort(sortvec.begin(), sortvec.end(), [] (auto& a, auto& b) {
        return a.second->Integral() > b.second->Integral();
      });

    return sortvec;
  }


  TH1D* styled (TH1D* hist, FileGroup::FileType type, short style, double scale = 1.0) {

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

}


void HistAnalyzerMaster::draw_plot(const std::string& output,
                                   Types::map<Hist>& data,
                                   Types::map<Hist>& mc,
                                   Types::map<Hist>& signal) const {

  // Stores TH1D for this function
  std::list<TH1D> histstore {};

  // Use this to store sums for ratios
  Hist data_hist {};
  Hist bkg_hist {};
  Hist signal_hist {};

  add_to(data_hist, data);
  add_to(bkg_hist, mc);
  add_to(signal_hist, signal);
  // Add backgrounds to signal sums too
  add_to(signal_hist, mc);

  auto mcvec = sorted_vec(mc);

  double scale = plotstylemodel.normalize
    ? data_hist.integral()/bkg_hist.integral()
    : 1.0;

  bkg_hist.scale(scale);

  auto* max_hist = &bkg_hist;

  THStack hs{"hs", ""};
  // Get the maximum value
  auto max = bkg_hist.max_w_unc();
  // Check the data histogram(s)
  for(auto& dat : data) {
    auto check = dat.second.max_w_unc();
    if (check > max) {
      max = check;
      max_hist = &dat.second;
    }
  }

  hs.SetMaximum(max);

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
  // Top pad
  const double bottom = mcvec.size() ? 0.3 : 0.0;

  TPad pad1{"pad1", "pad1", 0.0, bottom, 1.0, 1.0};
  pad1.SetBottomMargin(bottom ? 0.025 : 0.1);
  pad1.Draw();
  pad1.cd();

  const double nomfont = 0.03;          // Target font size for plot labels
  const double titleoff = 1.55;         // Title offset

  if (mcvec.size()) {

    hs.Draw("hist");

    hs.GetYaxis()->SetLabelSize(nomfont/(1 - bottom));
    hs.GetYaxis()->SetTitleSize(nomfont/(1 - bottom));
    hs.GetYaxis()->SetTitleOffset(titleoff);
    hs.GetYaxis()->SetTitle("Events/Bin");

    hs.GetXaxis()->SetLabelSize(0);
    hs.GetXaxis()->SetTitleSize(0);

    auto* bkg_sum = bkg_hist.roothist();
    bkg_sum->SetFillStyle(3001);
    bkg_sum->SetFillColor(kGray);
    bkg_sum->Draw("e2,same");

    for (auto& sig : sorted_vec(signal)) {

      leg.AddEntry(styled(sig.second,
                          FileGroup::FileType::SIGNAL,
                          styles.at(sig.first)),
                   sig.first.data(), "lp");

      sig.second->Add(bkg_sum);
      sig.second->Draw("hist,same");

    }

  }

  for (auto& dat : sorted_vec(data)) {
    leg.AddEntry(styled(dat.second,
                        FileGroup::FileType::DATA,
                        styles.at(dat.first)),
                 dat.first.data(), "lp");
    dat.second->Draw("PE,same");
  }

  canv.cd();
  TPad pad2{"pad2", "pad2", 0.0, 0.0, 1.0, bottom};

  if (bottom) {
    pad2.SetTopMargin(0.025);
    pad2.SetBottomMargin(0.4);
    pad2.cd();

    auto bkg_ratio = bkg_hist.ratio(bkg_hist);
    auto data_ratio = data_hist.ratio(bkg_hist);

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

    bhist->SetMinimum(std::max(std::min(bkg_ratio.min_w_unc(), data_ratio.min_w_unc(false)), double(plotstylemodel.minratio)));
    bhist->SetMaximum(std::min(std::max(bkg_ratio.max_w_unc(), data_ratio.max_w_unc()), double(plotstylemodel.maxratio)));
    bhist->Draw("e2");

    // All of the signals should be drawn separately...
    styled(signal_hist.ratio(bkg_hist).roothist(&histstore), FileGroup::FileType::SIGNAL, 2, scale)->Draw("hist,same");
    styled(data_ratio.roothist(&histstore), FileGroup::FileType::DATA, 1)->Draw("PE,same");

    pad2.SetGridy(1);

    canv.cd();
    pad2.Draw();

  }

  pad1.cd();
  leg.Draw();

  canv.cd();
  // Labels
  TLatex latex{};
  constexpr double toplocation = 0.96;
  latex.SetTextSize(0.035);

  double currentlumi {globalmodel.luminosity * scale};

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

  // Save everything
  FileSystem::mkdirs(outputdir);

  for (auto& suff : {".pdf", ".png", ".C"}) {
    auto outname = outputdir + "/" + output + suff;
    canv.SaveAs(outname.data());
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


void HistAnalyzerMaster::dumpdatacard (const std::string& datadir,
                                       const DatacardModel& model,
                                       const FileModel& filemodel) const {

  FileSystem::mkdirs(datadir);

  std::ofstream datacard {datadir + "/datacard.txt"};

  datacard << "imax   *   number of channels" << std::endl
           << "jmax   *   number of backgrounds" << std::endl
           << "kmax   *   number of systematics (automatic)" << std::endl
           << "------------------------------" << std::endl
           << "shapes * * plots.root $PROCESS_$CHANNEL $PROCESS_$CHANNEL_$SYSTEMATIC" << std::endl
           << "------------------------------" << std::endl;

  for (auto& hist : model.hists) {
    auto key = hist.selection.get() + "_" + hist.plot.get();

    

  }

}
