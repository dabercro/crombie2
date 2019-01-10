#include <iomanip>

#include <crombie2/FileSystem.h>
#include <crombie2/HistAnalyzerMaster.h>

#include "TCanvas.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"


using namespace crombie2;


HistAnalyzerMaster::HistAnalyzerMaster (const std::string& outdir, std::vector<Job>& jobs,
                                        const PlotModel& plotmodel, const CutModel& cutmodel,
                                        const GlobalModel& globalmodel) :
  outputdir {outdir.size() ? globalmodel.outplotdir.get() + "/" + outdir : ""},
  globalmodel {globalmodel}
{

  // If no output directory, we are not going to make hist analyzers
  if (not outputdir.size())
    return;

  for (auto& job : jobs) {
    auto& entry = job.get_entry();
    if (xs.insert({entry.name, entry.xs}).second) {
      types.insert({entry.name, job.get_group().type});
      for (auto& legend : job.get_group().entries)
        styles.insert({legend.legend, legend.style});
    }

    for (auto& plot : plotmodel.plots) {
      for (auto& selection : cutmodel.selections) {
        auto output_file = selection.cut.get() + "_" + plot.name.get();

        histmodels[output_file].
          insert({job.get_entry().name.get(),
                  {job, globalmodel, plot, cutmodel, selection}}).
          first->second.add_job(job);
      }
    }
  }

}

void HistAnalyzerMaster::output () {

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
      auto& histmodel = key_input.second;

      auto histsplit = histmodel.get_histsplit();

      auto type = types.at(key_input.first);

      if (type != FileGroup::FileType::DATA)
        histsplit.scale(globalmodel.luminosity, xs.at(key_input.first));

      auto& outmap = type == FileGroup::FileType::MC
        ? mchists
        : (type == FileGroup::FileType::DATA
           ? datahists
           : signalhists);

      for (auto& entry : histsplit.get_hists())
        outmap[entry.first].add(entry.second);

    }

    draw_plot(key_output.first, datahists, mchists, signalhists);

  }

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


  TH1D* styled (TH1D* hist, FileGroup::FileType type, short style) {

    hist->SetLineColor(kBlack);
    switch(type) {
    case(FileGroup::FileType::DATA) :
      hist->SetMarkerStyle(8);
      hist->SetMarkerColor(style);
      hist->SetLineColor(style);
      break;
    case(FileGroup::FileType::SIGNAL) :
      hist->SetLineStyle(style);
      break;
    case(FileGroup::FileType::MC) :
      hist->SetFillStyle(1001);
      hist->SetFillColor(style);
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
                                   Types::map<Hist>& signal) {

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

  THStack hs{"hs", ""};
  // Get the maximum value
  auto max = bkg_hist.max_w_unc();
  // Check the data histogram(s)
  for(auto& dat : data)
    max = std::max(dat.second.max_w_unc(), max);

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
             styles.at(i_mc->first))
    );

  }

  TLegend leg{legend(bkg_hist, styles.size())};

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
    pad2.Draw();
    pad2.cd();

    auto bkg_ratio = bkg_hist.ratio(bkg_hist);
    auto data_ratio = data_hist.ratio(bkg_hist);

    auto set_yaxis = [bottom, titleoff] (auto* hist) {
      auto* axis = hist->GetYaxis();
      axis->SetNdivisions(504, true);
      axis->SetTitle("Data/Pred.");
      axis->SetTitleOffset((bottom)/(1-bottom) * titleoff);
      axis->CenterTitle();
      return hist;
    };

    auto* bhist = set_yaxis(bkg_ratio.roothist());

    for (auto* axis : {bhist->GetXaxis(), bhist->GetYaxis()}) {
      axis->SetTitleSize(nomfont/bottom);
      axis->SetLabelSize(nomfont/bottom);
    }

    bhist->SetFillStyle(3001);
    bhist->SetFillColor(kGray);

    bhist->SetMinimum(std::max(std::min(bkg_ratio.min_w_unc(), data_ratio.min_w_unc(false)), double(globalmodel.minratio)));
    bhist->SetMaximum(std::min(std::max(bkg_ratio.max_w_unc(), data_ratio.max_w_unc()), double(globalmodel.maxratio)));
    bhist->Draw("e2");

    // All of the signals should be drawn separately...
    styled(signal_hist.ratio(bkg_hist).roothist(), FileGroup::FileType::SIGNAL, 2)->Draw("hist,same");
    styled(data_ratio.roothist(), FileGroup::FileType::DATA, 1)->Draw("PE,same");

    pad2.SetGridy(1);
    pad2.Draw();

    canv.cd();
  }

  pad1.cd();
  leg.Draw();

  canv.cd();
  // Labels
  TLatex latex{};
  constexpr double toplocation = 0.96;
  latex.SetTextSize(0.035);

  double currentlumi {globalmodel.luminosity};

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

  latex.DrawLatex(0.2, toplocation, "Preliminary");

  // Save everything
  FileSystem::mkdirs(outputdir);

  for (auto& suff : {".pdf", ".png", ".C"}) {
    auto outname = outputdir + "/" + output + suff;
    canv.SaveAs(outname.data());
  }

}
