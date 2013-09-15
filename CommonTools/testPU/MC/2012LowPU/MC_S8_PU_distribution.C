#include <iostream>
#include <iomanip>

/// #define Nfile 3

int  MC_S8_PU_distribution()
{
//  TString resultDir = "results";

  ofstream Fout;
//  TString FoutName = resultDir+"/eventSummary.txt";
  Fout.open( "MC_S8_PU_distribution.txt");

TFile *f= new TFile("fillrandom.root");

//  TFile *f[nfile];
//  f[0] = new TFile("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_01.root");
//  f[1] = new TFile("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_02.root");
//  f[2] = new TFile("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_03.root");
  //Muon Cut Flow
//  f[0]->cd("Muons");
//  TH1D* TT_cutflow = (TH1D*)cutflow->Clone("TT_cutflow");
 
// for( int i=1; i<Nfile; i++)
//  {
//    f[i]->cd("Muons");
//    TT_cutflow->Add(cutflow);
//  }


//  TT_cutflow->Draw();
 // TString cutflowPlot = resultDir+"/cutflowPlot";
 
// c1->SaveAs(cutflowPlot+".jpg");
//  c1->SaveAs(cutflowPlot+".eps");

	TH1F *h = (TH1F*)f->Get("P25");
	 for( int i=1; i<26; i++)
	{
	cout << h->GetBinContent(i) << endl;
	Fout << h->GetBinContent(i) << endl;

	}	


//  Fout<<"Muon Cut flow ------------------------"<<endl;
//  Fout<<"pre:		"<<TT_cutflow->GetBinContent(1)<<endl;
//  Fout<<"dxy:		"<<TT_cutflow->GetBinContent(2)<<endl;
//  Fout<<"isGlobal:	"<<TT_cutflow->GetBinContent(3)<<endl;
//  Fout<<"isTracker:	"<<TT_cutflow->GetBinContent(4)<<endl;
//  Fout<<"tracksHits:	"<<TT_cutflow->GetBinContent(5)<<endl;
//  Fout<<"chi2:		"<<TT_cutflow->GetBinContent(6)<<endl;
//  Fout<<"muonHits:	"<<TT_cutflow->GetBinContent(7)<<endl;
//  Fout<<"WMuNu:		"<<TT_cutflow->GetBinContent(8)<<endl;

  //Event Summary
//  f[0]->cd("WMuNeu");
//  TH1D* TT_eventSum = (TH1D*)EventSummary->Clone("TT_eventSum");
//  for( int i(1); i<Nfile; i++)
//  {
//    f[i]->cd("WMuNeu");
//    TT_eventSum->Add(EventSummary);
//  }
//  TT_eventSum->Draw();
//  TString eventSumPlot = resultDir+"/eventSumPlot";
//  c1->SaveAs(eventSumPlot+".jpg");
//  c1->SaveAs(eventSumPlot+".eps");
//  Fout<<"Event Summary ------------------------"<<endl;
//  Fout<<"nEventsTotal:		"<<TT_eventSum->GetBinContent(1)<<endl;
//  Fout<<"nEventsClean:		"<<TT_eventSum->GetBinContent(2)<<endl;
//  Fout<<"nEventsHLT:		"<<TT_eventSum->GetBinContent(3)<<endl;
//  Fout<<"nEventsFiltered:	"<<TT_eventSum->GetBinContent(4)<<endl;
//  Fout<<"nEventsPatHLT:		"<<TT_eventSum->GetBinContent(5)<<endl;

  Fout.close();

  return 0;
}

