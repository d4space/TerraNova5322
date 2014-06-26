// $Log: Wlnu12LoTempl.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define Wlnu12LoTempl_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoTempl.h"
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

void Wlnu12LoTempl::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoTempl Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoTempl");

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
    mTTW = CalcEvtWeight();
    
    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
   
    // Select the Best W boson
    WbestSelect();

    if( W.Pass)
    {
    }

    //Fill the W==================
    //GoodW
    if(W.Pass && addLepN <2){
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
  Write_Histo();
  //myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("Wlnu12LoTempl");
}


void Wlnu12LoTempl::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
  }
}
int Wlnu12LoTempl::InitVar()
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
      Rcl.ZRDfilename="../Recoil/ZmmData/fits.root";
      Rcl.ZMCfilename="../Recoil/ZmmMC/fits.root";
      Rcl.Wpfilename="../Recoil/WmpMC/fits.root";
      Rcl.Wmfilename="../Recoil/WmmMC/fits.root";
    }else if((AnaChannel == "Electron2012LoPU") || AnaChannel == "ElectronHighPU")
    {
      Rcl.ZRDfilename="../Recoil/ZeeData/fits.root";
      Rcl.ZMCfilename="../Recoil/ZeeMC/fits.root";
      Rcl.Wpfilename="../Recoil/WepMC/fits.root";
      Rcl.Wmfilename="../Recoil/WemMC/fits.root";
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
int Wlnu12LoTempl::InitVar4Evt()
{
  //cout<<"Wlnu12LoTempl::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}

int Wlnu12LoTempl::InitHistogram()
{
  myFile   = new TFile(mResultDir+"/"+OutNameBase+"_"+Mode+".root","RECREATE");
  h1_W_pt  = new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wp_pt = new TH1D("h1_Wp_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wm_pt = new TH1D("h1_Wm_pt","Wpt",NWptBinPlus-1,WptBins);
  
  return 0;
}
int Wlnu12LoTempl::Fill_Histo()
{
  h1_W_pt->Fill(W.pt, mTTW);
  if(W.charge>0)h1_Wp_pt->Fill(W.pt,mTTW);
  if(W.charge<0)h1_Wm_pt->Fill(W.pt,mTTW);
  return 0;
}

int Wlnu12LoTempl::Write_Histo()
{
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  return 0;
}
