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
    WbestFiducialCut();
    if(W.Pass)
    {
      DumpWbestCand(W.idxBest);
      FillFiducialCutHisto();
    }
    WbestSelect();

    if( W.Pass)
    {
      //Fill_Histo();
    }

    //Fill the W==================
    //GoodW
    //if(W.Pass && addLepN <2){
    if(W.Pass){
      DumpWbestCand(W.idxBest);
      if(Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr")mTTW=mTTW*DoEffiCorr();
      if(Mode == "SmeaRecEffCorr")DoRecoilCorr();
      evtSelected+=mTTW;
      Fill_Histo();
      Nselected4Bin();
    }
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
  for(int i(0); i< 6; i++)
  {
    sprintf(histName, "h1_PlusLepPtFidCut_%d",i);
    h1_PlusLepPtFidCut[i] = new TH1D(histName,"LeptonPt",30,20,100);
    sprintf(histName, "h1_MinuLepPtFidCut_%d",i);
    h1_MinuLepPtFidCut[i] = new TH1D(histName,"LeptonPt",30,20,100);

    sprintf(histName, "h1_PlusLepPtAllCut_%d",i);
    h1_PlusLepPtAllCut[i] = new TH1D(histName,"LeptonPt",30,20,100);
    sprintf(histName, "h1_MinuLepPtAllCut_%d",i);
    h1_MinuLepPtAllCut[i] = new TH1D(histName,"LeptonPt",30,20,100);
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
    if(W.pt >0 && W.pt <7.5)
    {
      h1_PlusLepPtAllCut[0]->Fill(W.lep_pt);
    }else if(W.pt >= 7.5 && W.pt <12.5)
    {
      h1_PlusLepPtAllCut[1]->Fill(W.lep_pt);
    }else if(W.pt >= 12.5 && W.pt <17.5)
    {
      h1_PlusLepPtAllCut[2]->Fill(W.lep_pt);
    }else if(W.pt >= 17.5 && W.pt <50)
    {
      h1_PlusLepPtAllCut[3]->Fill(W.lep_pt);
    }else if(W.pt >= 50 && W.pt <110)
    {
      h1_PlusLepPtAllCut[4]->Fill(W.lep_pt);
    }else if(W.pt >= 110 && W.pt <600)
    {
      h1_PlusLepPtAllCut[5]->Fill(W.lep_pt);
    }
  }
  if(W.charge <0)
  {
    if(W.pt >0 && W.pt <7.5)
    {
      h1_MinuLepPtAllCut[0]->Fill(W.lep_pt);
    }else if(W.pt >= 7.5 && W.pt <12.5)
    {
      h1_MinuLepPtAllCut[1]->Fill(W.lep_pt);
    }else if(W.pt >= 12.5 && W.pt <17.5)
    {
      h1_MinuLepPtAllCut[2]->Fill(W.lep_pt);
    }else if(W.pt >= 17.5 && W.pt <50)
    {
      h1_MinuLepPtAllCut[3]->Fill(W.lep_pt);
    }else if(W.pt >= 50 && W.pt <150)
    {
      h1_MinuLepPtAllCut[4]->Fill(W.lep_pt);
    }else if(W.pt >= 150 && W.pt <600)
    {
      h1_MinuLepPtAllCut[5]->Fill(W.lep_pt);
    }
  }
  return 0;
}
int Wlnu12LoCtrPlt::FillFiducialCutHisto()
{
  if(W.charge>0)
  {
    if(W.pt >0 && W.pt <7.5)
    {
      h1_PlusLepPtFidCut[0]->Fill(W.lep_pt);
    }else if(W.pt >= 7.5 && W.pt <12.5)
    {
      h1_PlusLepPtFidCut[1]->Fill(W.lep_pt);
    }else if(W.pt >= 12.5 && W.pt <17.5)
    {
      h1_PlusLepPtFidCut[2]->Fill(W.lep_pt);
    }else if(W.pt >= 17.5 && W.pt <50)
    {
      h1_PlusLepPtFidCut[3]->Fill(W.lep_pt);
    }else if(W.pt >= 50 && W.pt <110)
    {
      h1_PlusLepPtFidCut[4]->Fill(W.lep_pt);
    }else if(W.pt >= 110 && W.pt <600)
    {
      h1_PlusLepPtFidCut[5]->Fill(W.lep_pt);
    }
  }
  if(W.charge <0)
  {
    if(W.pt >0 && W.pt <7.5)
    {
      h1_MinuLepPtFidCut[0]->Fill(W.lep_pt);
    }else if(W.pt >= 7.5 && W.pt <12.5)
    {
      h1_MinuLepPtFidCut[1]->Fill(W.lep_pt);
    }else if(W.pt >= 12.5 && W.pt <17.5)
    {
      h1_MinuLepPtFidCut[2]->Fill(W.lep_pt);
    }else if(W.pt >= 17.5 && W.pt <50)
    {
      h1_MinuLepPtFidCut[3]->Fill(W.lep_pt);
    }else if(W.pt >= 50 && W.pt <150)
    {
      h1_MinuLepPtFidCut[4]->Fill(W.lep_pt);
    }else if(W.pt >= 150 && W.pt <600)
    {
      h1_MinuLepPtFidCut[5]->Fill(W.lep_pt);
    }
  }
  return 0;
}

int Wlnu12LoCtrPlt::Write_Histo()
{
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  for(int i(0);i<6;i++)
  {
    h1_PlusLepPtAllCut[i]->Write();
    h1_MinuLepPtAllCut[i]->Write();
    h1_PlusLepPtFidCut[i]->Write();
    h1_MinuLepPtFidCut[i]->Write();
  }
  return 0;
}
