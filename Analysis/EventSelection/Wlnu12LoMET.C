// $Log: Wlnu12LoMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define Wlnu12LoMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoMET.h"
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

void Wlnu12LoMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoMET");

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
      if(Mode == "SmeaRecEffCorr")DoRecoilCorr();
      evtSelected+=mTTW;
      if(Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr")mTTW=mTTW*DoEffiCorr();
      Fill_Histo();
      Nselected4Bin();
    }else if (!W.Pass){
      for(int iw(0); iw<W.size; iw++)
      {
	FillWSide(iw);
	if(Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr")mTTW=mTTW*DoEffiCorr();
	Fill_SideHisto();
      }
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
  gBenchmark->Show("Wlnu12LoMET");
}


void Wlnu12LoMET::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
  }
}
int Wlnu12LoMET::InitVar()
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
int Wlnu12LoMET::InitVar4Evt()
{
  //cout<<"Wlnu12LoMET::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}

int Wlnu12LoMET::InitHistogram()
{
  myFile   = new TFile(mResultDir+"/"+OutNameBase+"_"+Mode+".root","RECREATE");
  h1_W_pt  = new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wp_pt = new TH1D("h1_Wp_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wm_pt = new TH1D("h1_Wm_pt","Wpt",NWptBinPlus-1,WptBins);
  
  for( int ipt=0;ipt<NWptBinPlus;ipt++){
    if( ipt < NBIN_PT_DIVIDER_1and2 ){
      sprintf(histName,"h1_W_Neu_pt_%d",ipt);
      h1_W_Neu_pt[ipt] = new TH1D(histName,"W_Neut_pt",NBINS_1,0,METMAX_1);
      sprintf(histName,"h1_WSide_Neu_pt_%d",ipt);
      h1_WSide_Neu_pt[ipt] = new TH1D(histName,"WSide_Neut_pt",NBINS_1,0,METMAX_1);
      sprintf(histName,"h1_Wp_Neu_pt_%d",ipt);
      h1_Wp_Neu_pt[ipt] = new TH1D(histName,"Wp_Neut_pt",NBINS_1,0,METMAX_1);
      sprintf(histName,"h1_WpSide_Neu_pt_%d",ipt);
      h1_WpSide_Neu_pt[ipt] = new TH1D(histName,"WpSide_Neut_pt",NBINS_1,0,METMAX_1);
      sprintf(histName,"h1_Wm_Neu_pt_%d",ipt);
      h1_Wm_Neu_pt[ipt] = new TH1D(histName,"Wm_Neut_pt",NBINS_1,0,METMAX_1);
      sprintf(histName,"h1_WmSide_Neu_pt_%d",ipt);
      h1_WmSide_Neu_pt[ipt] = new TH1D(histName,"WmSide_Neut_pt",NBINS_1,0,METMAX_1);
    } else if ( ipt < NBIN_PT_DIVIDER_2and3 ){
      sprintf(histName,"h1_W_Neu_pt_%d",ipt);
      h1_W_Neu_pt[ipt] = new TH1D(histName,"W_Neut_pt",NBINS_2,0,METMAX_2);
      sprintf(histName,"h1_WSide_Neu_pt_%d",ipt);
      h1_WSide_Neu_pt[ipt] = new TH1D(histName,"WSide_Neut_pt",NBINS_2,0,METMAX_2);
      sprintf(histName,"h1_Wp_Neu_pt_%d",ipt);
      h1_Wp_Neu_pt[ipt] = new TH1D(histName,"Wp_Neut_pt",NBINS_2,0,METMAX_2);
      sprintf(histName,"h1_WpSide_Neu_pt_%d",ipt);
      h1_WpSide_Neu_pt[ipt] = new TH1D(histName,"WpSide_Neut_pt",NBINS_2,0,METMAX_2);
      sprintf(histName,"h1_Wm_Neu_pt_%d",ipt);
      h1_Wm_Neu_pt[ipt] = new TH1D(histName,"Wm_Neut_pt",NBINS_2,0,METMAX_2);
      sprintf(histName,"h1_WmSide_Neu_pt_%d",ipt);
      h1_WmSide_Neu_pt[ipt] = new TH1D(histName,"WmSide_Neut_pt",NBINS_2,0,METMAX_2);
    } else {
      sprintf(histName,"h1_W_Neu_pt_%d",ipt);
      h1_W_Neu_pt[ipt] = new TH1D(histName,"W_Neut_pt",NBINS_3,0,METMAX_3);
      sprintf(histName,"h1_WSide_Neu_pt_%d",ipt);
      h1_WSide_Neu_pt[ipt] = new TH1D(histName,"WSide_Neut_pt",NBINS_3,0,METMAX_3);
      sprintf(histName,"h1_Wp_Neu_pt_%d",ipt);
      h1_Wp_Neu_pt[ipt] = new TH1D(histName,"Wp_Neut_pt",NBINS_3,0,METMAX_3);
      sprintf(histName,"h1_WpSide_Neu_pt_%d",ipt);
      h1_WpSide_Neu_pt[ipt] = new TH1D(histName,"WpSide_Neut_pt",NBINS_3,0,METMAX_3);
      sprintf(histName,"h1_Wm_Neu_pt_%d",ipt);
      h1_Wm_Neu_pt[ipt] = new TH1D(histName,"Wm_Neut_pt",NBINS_3,0,METMAX_3);
      sprintf(histName,"h1_WmSide_Neu_pt_%d",ipt);
      h1_WmSide_Neu_pt[ipt] = new TH1D(histName,"WmSide_Neut_pt",NBINS_3,0,METMAX_3);
    }
  }
  
  return 0;
}
int Wlnu12LoMET::Fill_Histo()
{
  h1_W_pt->Fill(W.pt, mTTW);
  if(W.charge>0)
  {
    h1_Wp_pt->Fill(W.pt,mTTW);
    h1_W_Neu_pt[0] ->Fill(W.Met,mTTW);
    h1_Wp_Neu_pt[0]->Fill(W.Met,mTTW);
    
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
    {
      if(W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1])
      {
	h1_W_Neu_pt[iBin+1] ->Fill(W.Met,mTTW);
	h1_Wp_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
      }
    }
  }else if(W.charge<0){
    h1_Wm_pt->Fill(W.pt,mTTW);
    h1_W_Neu_pt[0] ->Fill(W.Met,mTTW);
    h1_Wm_Neu_pt[0]->Fill(W.Met,mTTW);
    
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++) {
      if( W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1] )
      {
	h1_W_Neu_pt[iBin+1] ->Fill(W.Met,mTTW);
	h1_Wm_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
      }
    }
  }
  return 0;
}

int Wlnu12LoMET::Fill_SideHisto()
{
  if(W.charge>0)
  {
    h1_WSide_Neu_pt[0] ->Fill(W.Met_side,mTTW);
    h1_WpSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
  
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++){
      if( W.pt_side >= WptBins[iBin] && W.pt_side < WptBins[iBin+1])
      {
        h1_WSide_Neu_pt[iBin+1] ->Fill(W.Met_side,mTTW);
        h1_WpSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
      }
    }
  }else if (W.charge<0){
    h1_WSide_Neu_pt[0] ->Fill(W.Met_side,mTTW);
    h1_WmSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
    
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++){
      if( W.pt_side >= WptBins[iBin] && W.pt_side < WptBins[iBin+1])
      {
        h1_WSide_Neu_pt[iBin+1] ->Fill(W.Met_side,mTTW);
        h1_WmSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
      }
    }
  }
  return 0;
}

int Wlnu12LoMET::Write_Histo()
{
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  for( int ipt=0;ipt<NWptBinPlus;ipt++)
  {
    h1_W_Neu_pt[ipt]->Write();
    h1_WSide_Neu_pt[ipt]->Write();
    h1_Wp_Neu_pt[ipt]->Write();
    h1_WpSide_Neu_pt[ipt]->Write();
    h1_Wm_Neu_pt[ipt]->Write();
    h1_WmSide_Neu_pt[ipt]->Write();
  }
  return 0;
}
