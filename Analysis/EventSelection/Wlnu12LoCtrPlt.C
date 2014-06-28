// $Log: Wlnu12LoCtrPlt.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define Wlnu12LoCtrPlt_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoCtrPlt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TVector2.h>
#include <TLorentzVector.h>
//#include "../Utils/MyTools.hh"	          // various helper functions

#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;

void Wlnu12LoCtrPlt::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoCtrPlt Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoCtrPlt");

  //gRandom->SetSeed(0);
  //gRandom->SetSeed(0x1234);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;

  //============================================
  // Looping for each Event 
  //============================================
  //for (int i(0); i<200;i++)
  for (int i(0); i<Ntries;i++)
  {
   // cout<<i<<" th Event"<<endl;
    evtCnt = i;
    //===============================
    //W study
    //===============================
    if(i % 100000 == 0) cout<<i<<"th event"<<endl;
    if(Debug)cout<<"check point 1"<<endl;

    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

    // Dump MET informations
    //DumpMETs();

    //===================
    // Check the channel : To check if the ntuple is for each lepton flavor
    //===================
    if(Wlnu12LoBase::CheckChannel()!=0) exit(-1);

    //============
    //Trigger Cut
    //============
    if(Wlnu12LoBase::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;

    //===================
    // Calculate Event Weight
    //=====================
    //mTTW = CalcEvtWeight();
    mTTW = 1;
    
    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
   
    // Select the Best W boson
    WreconEff();
    ZreconEff();
    if(W.Pass)
    {
    }
    WbestSelect();

    if( W.Pass)
    {
      //Fill_Histo();
    }

    //Fill the W==================
    //GoodW
    //if(W.Pass && addLepN <2){
    //  DumpWbestCand(W.idxBest);
    //  if(Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr")mTTW=mTTW*DoEffiCorr();
    //  if(Mode == "SmeaRecEffCorr")DoRecoilCorr();
    //  evtSelected+=mTTW;
    //  Fill_Histo();
    //  Nselected4Bin();
    //}
  }//Ntries
  cout<<"Passed W evts: "<<mNWevt<<endl;
  Fout<<"Passed W evts: "<<mNWevt<<endl;
  //Results======================
  cout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;
  Fout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;
  Fout<<"selected events for each bin"<<endl;
  for( int i(0); i<NwPtBin; i++)
  {
    Fout<<i<<"   "<<mNselect4WptBin[i]<<endl;
  }

  // Notice: Use one of Write_Histo or myFile->Write
  // Write_Histo: to Save specific histograms
  // myFile->Write: to Save all Histograms
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("Wlnu12LoCtrPlt");
}


void Wlnu12LoCtrPlt::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
  }
}
int Wlnu12LoCtrPlt::InitVar()
{
  cout<<"Initialize variable at WlnuMET class ==========="<<endl;
  evtCnt = 0;
  mNWevt = 0;
  TString FoutName = mResultDir+"/"+OutNameBase+"_"+Mode+".txt";
  Fout.open(FoutName);
  for(int i(0);i<NwPtBin;i++)
  {
    mNselect4WptBin[i]=0;
  }
  // Recoil CorrWptection initializaWpttion
  // Recoil CorrWptection Parameter WptFiles
  if( (  Mode == "SmeaRecEffCorr"
      || Mode == "RecoilCorrMC")
      || Mode =="DumpUnfInfo" )
  {
    if(AnaChannel == "Muon2012LoPU" )
    {
      Rcl.ZRDfilename="../Recoil/ZmmData/fits_V2.root";
      Rcl.ZMCfilename="../Recoil/ZmmMC/fits_V2.root";
      Rcl.Wpfilename="../Recoil/WmpMC/fits_V2.root";
      Rcl.Wmfilename="../Recoil/WmmMC/fits_V2.root";
    }else if((AnaChannel == "Electron2012LoPU") || AnaChannel == "ElectronHighPU")
    {
      Rcl.ZRDfilename="../Recoil/ZeeData/fits_V2.root";
      Rcl.ZMCfilename="../Recoil/ZeeMC/fits_V2.root";
      Rcl.Wpfilename="../Recoil/WepMC/fits_V2.root";
      Rcl.Wmfilename="../Recoil/WemMC/fits_V2.root";
    }
    // RecoilCorrection Object.
    RecoilCorr= new RecoilCorrector(
      Rcl.ZRDfilename,
      Rcl.Wpfilename,Rcl.Wmfilename,
      Rcl.ZMCfilename,
      0x1234);
  //Int_t iSeed=0xDEADBEEF default seed for random number generator at constructor
  }
  return 0;
}
int Wlnu12LoCtrPlt::InitVar4Evt()
{
  //cout<<"Wlnu12LoCtrPlt::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}

int Wlnu12LoCtrPlt::InitHistogram()
{
  myFile   = new TFile(mResultDir+"/"+OutNameBase+"_"+Mode+".root","RECREATE");
  h1_W_pt  = new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wp_pt = new TH1D("h1_Wp_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wm_pt = new TH1D("h1_Wm_pt","Wpt",NWptBinPlus-1,WptBins);
  h2_PlusLepPtEtaAllCut=new TH2D("h2_PlusLepPtEtaAllCut","LepPt vs LeptEta at AllCut",6,20,100,10,-2.1,2.1);
  h2_MinuLepPtEtaAllCut=new TH2D("h2_MinuLepPtEtaAllCut","LepPt vs LeptEta at AllCut",6,20,100,10,-2.1,2.1);
  h2_PlusLepPtEtaFidCut=new TH2D("h2_PlusLepPtEtaFidCut","LepPt vs LeptEta at FidCut",6,20,100,10,-2.1,2.1);
  h2_MinuLepPtEtaFidCut=new TH2D("h2_MinuLepPtEtaFidCut","LepPt vs LeptEta at FidCut",6,20,100,10,-2.1,2.1);
  h1_PlusLepPtAllCutFullRange = new TH1D("h1_PlusLepPtAllCutFullRange","LeptonPt",1,20,100);
  h1_MinuLepPtAllCutFullRange = new TH1D("h1_MinuLepPtAllCutFullRange","LeptonPt",1,20,100);
  h1_PlusLepPtFidCutFullRange = new TH1D("h1_PlusLepPtFidCutFullRange","LeptonPt",1,20,100);
  h1_MinuLepPtFidCutFullRange = new TH1D("h1_MinuLepPtFidCutFullRange","LeptonPt",1,20,100);
  h1_PlusLepEtaAllCutFullRange = new TH1D("h1_PlusLepEtaAllCutFullRange","LeptonPt",1,-2.1,2.1);
  h1_MinuLepEtaAllCutFullRange = new TH1D("h1_MinuLepEtaAllCutFullRange","LeptonPt",1,-2.1,2.1);
  h1_PlusLepEtaFidCutFullRange = new TH1D("h1_PlusLepEtaFidCutFullRange","LeptonPt",1,-2.1,2.1);
  h1_MinuLepEtaFidCutFullRange = new TH1D("h1_MinuLepEtaFidCutFullRange","LeptonPt",1,-2.1,2.1);
  //for(int i(0); i< 6; i++)
  for(int i(0); i< 3; i++)
  {
    sprintf(histName, "h1_PlusLepPtFidCut_%d",i);
    h1_PlusLepPtFidCut[i] = new TH1D(histName,"LeptonPt",6,20,100);
    sprintf(histName, "h1_MinuLepPtFidCut_%d",i);
    h1_MinuLepPtFidCut[i] = new TH1D(histName,"LeptonPt",6,20,100);

    sprintf(histName, "h1_PlusLepPtAllCut_%d",i);
    h1_PlusLepPtAllCut[i] = new TH1D(histName,"LeptonPt",6,20,100);
    sprintf(histName, "h1_MinuLepPtAllCut_%d",i);
    h1_MinuLepPtAllCut[i] = new TH1D(histName,"LeptonPt",6,20,100);
    
    sprintf(histName, "h1_PlusLepEtaFidCut_%d",i);
    h1_PlusLepEtaFidCut[i] = new TH1D(histName,"LeptonEta",10,-2.1,2.1);
    sprintf(histName, "h1_MinuLepEtaFidCut_%d",i);
    h1_MinuLepEtaFidCut[i] = new TH1D(histName,"LeptonEta",10,-2.1,2.1);

    sprintf(histName, "h1_PlusLepEtaAllCut_%d",i);
    h1_PlusLepEtaAllCut[i] = new TH1D(histName,"LeptonEta",10,-2.1,2.1);
    sprintf(histName, "h1_MinuLepEtaAllCut_%d",i);
    h1_MinuLepEtaAllCut[i] = new TH1D(histName,"LeptonEta",10,-2.1,2.1);
  }
  
  return 0;
}
int Wlnu12LoCtrPlt::Fill_Histo()
{
  h1_W_pt->Fill(W.pt, mTTW);
  if(W.charge>0)h1_Wp_pt->Fill(W.pt,mTTW);
  if(W.charge<0)h1_Wm_pt->Fill(W.pt,mTTW);

  if(W.charge>0)
  {
    h2_PlusLepPtEtaAllCut->Fill(W.lep_pt,W.lep_eta);
    h1_PlusLepPtAllCutFullRange->Fill(W.lep_pt);
    h1_PlusLepEtaAllCutFullRange->Fill(W.lep_eta);
    if(W.pt >0 && W.pt <12.5)
    {
      h1_PlusLepPtAllCut[0]->Fill(W.lep_pt);
      h1_PlusLepEtaAllCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_PlusLepPtAllCut[1]->Fill(W.lep_pt);
      h1_PlusLepEtaAllCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_PlusLepPtAllCut[2]->Fill(W.lep_pt);
      h1_PlusLepEtaAllCut[2]->Fill(W.lep_eta);
    }
  }
  if(W.charge <0)
  {
    h2_MinuLepPtEtaAllCut->Fill(W.lep_pt,W.lep_eta);
    h1_MinuLepPtAllCutFullRange->Fill(W.lep_pt);
    h1_MinuLepEtaAllCutFullRange->Fill(W.lep_eta);
    if(W.pt >0 && W.pt <12.5)
    {
      h1_MinuLepPtAllCut[0]->Fill(W.lep_pt);
      h1_MinuLepEtaAllCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_MinuLepPtAllCut[1]->Fill(W.lep_pt);
      h1_MinuLepEtaAllCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_MinuLepPtAllCut[2]->Fill(W.lep_pt);
      h1_MinuLepEtaAllCut[2]->Fill(W.lep_eta);
    }
  }
  return 0;
}
int Wlnu12LoCtrPlt::FillFiducialCutHisto()
{
  if(W.charge>0)
  {
    h2_PlusLepPtEtaFidCut->Fill(W.lep_pt,W.lep_eta);
    h1_PlusLepPtFidCutFullRange->Fill(W.lep_pt);
    h1_PlusLepEtaFidCutFullRange->Fill(W.lep_eta);
    if(W.pt >0 && W.pt <12.5)
    {
      h1_PlusLepPtFidCut[0]->Fill(W.lep_pt);
      h1_PlusLepEtaFidCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_PlusLepPtFidCut[1]->Fill(W.lep_pt);
      h1_PlusLepEtaFidCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_PlusLepPtFidCut[2]->Fill(W.lep_pt);
      h1_PlusLepEtaFidCut[2]->Fill(W.lep_eta);
    }
  }
  if(W.charge <0)
  {
    h2_MinuLepPtEtaFidCut->Fill(W.lep_pt,W.lep_eta);
    h1_MinuLepPtFidCutFullRange->Fill(W.lep_pt);
    h1_MinuLepEtaFidCutFullRange->Fill(W.lep_eta);
    if(W.pt >0 && W.pt <12.5)
    {
      h1_MinuLepPtFidCut[0]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_MinuLepPtFidCut[1]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_MinuLepPtFidCut[2]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[2]->Fill(W.lep_eta);
    }
  }
  return 0;
}
int Wlnu12LoCtrPlt::FillZmu1FiducialCutHist(int i)
{
  if( (*Z_Lept1_charge)[i]>0)
  {
    h2_ZPlusLepPtEtaFidCut->Fill( (*Z_Lept1_pt)[i],(*Z_Lept1_eta)[i]);
    h1_ZPlusLepPtFidCutFullRange->Fill( (*Z_Lept1_pt)[i]);
    h1_ZPlusLepEtaFidCutFullRange->Fill( (*Z_Lept1_eta)[i]);
    if((*Z_pt)[i] >0 && (*Z_pt)[i] <12.5)
    {
      h1_ZPlusLepPtFidCut[0]->Fill(W.lep_pt);
      h1_ZPlusLepEtaFidCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_PlusLepPtFidCut[1]->Fill(W.lep_pt);
      h1_PlusLepEtaFidCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_PlusLepPtFidCut[2]->Fill(W.lep_pt);
      h1_PlusLepEtaFidCut[2]->Fill(W.lep_eta);
    }
  }
  if( (*Z_Lept1_charge)[i]<0)
  {
    h2_MinuLepPtEtaFidCut->Fill(W.lep_pt,W.lep_eta);
    h1_MinuLepPtFidCutFullRange->Fill(W.lep_pt);
    h1_MinuLepEtaFidCutFullRange->Fill(W.lep_eta);
    if(W.pt >0 && W.pt <12.5)
    {
      h1_MinuLepPtFidCut[0]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[0]->Fill(W.lep_eta);
    }else if(W.pt >= 12.5 && W.pt <50)
    {
      h1_MinuLepPtFidCut[1]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[1]->Fill(W.lep_eta);
    }else if(W.pt >= 50 && W.pt <600)
    {
      h1_MinuLepPtFidCut[2]->Fill(W.lep_pt);
      h1_MinuLepEtaFidCut[2]->Fill(W.lep_eta);
    }
  }
  return 0;
}

int Wlnu12LoCtrPlt::Write_Histo()
{
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  h2_PlusLepPtEtaFidCut->Write();
  h2_MinuLepPtEtaFidCut->Write();
  h2_PlusLepPtEtaAllCut->Write();
  h2_MinuLepPtEtaAllCut->Write();
  h1_PlusLepPtAllCutFullRange->Write();
  h1_MinuLepPtAllCutFullRange->Write();
  h1_PlusLepPtFidCutFullRange->Write();
  h1_MinuLepPtFidCutFullRange->Write();
  h1_PlusLepEtaAllCutFullRange->Write();
  h1_MinuLepEtaAllCutFullRange->Write();
  h1_PlusLepEtaFidCutFullRange->Write();
  h1_MinuLepEtaFidCutFullRange->Write();
  //for(int i(0);i<6;i++)
  for(int i(0);i<3;i++)
  {
    h1_PlusLepPtAllCut[i]->Write();
    h1_MinuLepPtAllCut[i]->Write();
    h1_PlusLepPtFidCut[i]->Write();
    h1_MinuLepPtFidCut[i]->Write();
    h1_PlusLepEtaAllCut[i]->Write();
    h1_MinuLepEtaAllCut[i]->Write();
    h1_PlusLepEtaFidCut[i]->Write();
    h1_MinuLepEtaFidCut[i]->Write();
  }
  return 0;
}
int Wlnu12LoCtrPlt::WreconEff()
{
  double lep_Big(0);
  W_Lept1_pt_Corr.clear();
  for(int iw(0); iw<W.size; iw++)
  {
    if( (*W_Lept1_genDeltaR)[iw] > 0.025) continue;
    //Cut to W.lep_pt_corr
    W.lep_pt_corr = (*W_Lept1_pt)[iw];
    if (Mode=="ScaleCorr")DoScaleCorr(iw);
    if((Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr") || Mode == "Unfold")DoSmearCorr(iw);
    W_Lept1_pt_Corr.push_back(W.lep_pt_corr);
    //additional lepton count
    if(AnaChannel == "Muon2012LoPU")	if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Muon2012")	if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Electron2012LoPU")if(AddElectronCut(iw)>0)addLepN++;
    if(AnaChannel == "Electron2012")	if(AddElectronCutHighPU(iw)>0) addLepN++;
    if(AnaChannel == "Tau2012")		if(TauCut(iw)>0) addLepN++;

    if( ((AnaChannel == "Muon2012LoPU" ) && (MuonFidCut(iw) >0))||
	((AnaChannel == "Muon2012") && (MuonCut(iw) >0))||
	((AnaChannel == "Electron2012LoPU")&& (ElectronCut(iw) > 0))||
	((AnaChannel =="Electron2012") &&(ElectronCutHighPU(iw) > 0)) ||
	((AnaChannel =="Tau2012") && (TauCut(iw)) > 0)
	  //Best Candidate selection
    )
    {
      DumpWbestCand(iw);
      FillFiducialCutHisto();
      //lep_Big = W.lep_pt_corr;
      //W.idxBest = iw;
      //W.Pass = true;
    }
    if( ((AnaChannel == "Muon2012LoPU" ) && (MuonCut(iw) >0))||
	((AnaChannel == "Muon2012") && (MuonCut(iw) >0))||
	((AnaChannel == "Electron2012LoPU")&& (ElectronCut(iw) > 0))||
	((AnaChannel =="Electron2012") &&(ElectronCutHighPU(iw) > 0)) ||
	((AnaChannel =="Tau2012") && (TauCut(iw)) > 0)
	  //Best Candidate selection
    )
    {
      DumpWbestCand(iw);
      Fill_Histo();
      //lep_Big = W.lep_pt_corr;
      //W.idxBest = iw;
      //W.Pass = true;
    }
    return 1;
  }
  //W.lep_pt_corr = lep_Big;
  return 0;
}
int Wlnu12LoCtrPlt::ZreconEff()
{
  for(int i(0); i<Z_Mass->size(); i)
  {
    if( (*Z_Lept1_genIdxMatch)[i] < 0) continue;

    if( ((AnaChannel == "Muon2012LoPU" ) && (ZMuon1FidCut(iw) >0))
	  //Best Candidate selection
    )
    {
      FillZmu1FiducialCutHist(i);
    }

    if( ((AnaChannel == "Muon2012LoPU" ) && (ZMuon2FidCut(iw) >0))
	  //Best Candidate selection
    )
    {
      FillZmu2FiducialCutHist(i);
    }

    if( ((AnaChannel == "Muon2012LoPU" ) && (ZMuon1Cut(iw) >0))
	  //Best Candidate selection
    )
    {
      FillZmu1CutHist(i);
    }

    if( ((AnaChannel == "Muon2012LoPU" ) && (ZMuon2Cut(iw) >0))
	  //Best Candidate selection
    )
    {
      FillZmu2CutHist(i);
    }

    return 1;
  }
  //W.lep_pt_corr = lep_Big;
  return 0;
}
