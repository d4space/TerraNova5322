// $Log: Wlnu12LoUnfold.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define Wlnu12LoUnfold_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoUnfold.h"
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

void Wlnu12LoUnfold::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoUnfold Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoUnfold");

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
  //for (int i(2870); i<Ntries;i++)
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
    if(W.Pass && addLepN < 2){
      DumpWbestCand(W.idxBest);
      if(GenW_Born_Id->size() > 0)DoRecoilCorr();
      DumpUnfInfo(W.idxBest);
      evtSelected+=mTTW;
      mTTW=mTTW*DoEffiCorr();
      // For systematic of WPt distribution
      cout<<"CalcWPtWeight: "<<CalcWPtWeight()<<endl;
      mTTW=mTTW*CalcWPtWeight();

      if(TruthRecoPost)if(WCHARGE == W.charge) FillUnfHisto();
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
  gBenchmark->Show("Wlnu12LoUnfold");
}


void Wlnu12LoUnfold::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
  }
}
int Wlnu12LoUnfold::InitVar()
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
  if(Mode == "SmeaRecEffCorr" ||  Mode =="Unfold")
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
int Wlnu12LoUnfold::InitVar4Evt()
{
  //cout<<"Wlnu12LoUnfold::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}

int Wlnu12LoUnfold::InitHistogram()
{
  myFile   = new TFile(mResultDir+"/"+OutNameBase+"_"+Mode+".root","RECREATE");
  h1_W_pt  = new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wp_pt = new TH1D("h1_Wp_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Wm_pt = new TH1D("h1_Wm_pt","Wpt",NWptBinPlus-1,WptBins);
  h1_Truth_Rec         =new TH1D("h1_Truth_Rec","Simul Wpt Truth",NWptBinPlus-1,WptBins);
  h1_Truth_Rec_Even    =new TH1D("h1_Truth_Rec_Even","Simul Wpt Truth_Even",NWptBinPlus-1,WptBins);
  h1_Truth_Rec_Odd     =new TH1D("h1_Truth_Rec_Odd","Simul Wpt Truth_Odd",NWptBinPlus-1,WptBins);
  h1_Truth_Post        =new TH1D("h1_Truth_Post","Post Wpt Truth",NWptBinPlus-1,WptBins);
  h1_Truth_Post_Even   =new TH1D("h1_Truth_Post_Even","Post Wpt Truth_Even",NWptBinPlus-1,WptBins);
  h1_Truth_Post_Odd    =new TH1D("h1_Truth_Post_Odd" ,"Post Wpt Truth_Odd",NWptBinPlus-1,WptBins);
  h1_Truth_Post_EffCorr=new TH1D("h1_Truth_Post_EffCorr","Post Wpt Truth EffCorr",NWptBinPlus-1,WptBins);
  h2_Truth_Rec_AP_Post =new TH2D("h2_Truth_Rec_AP_Post" ,"Truth Rec All Phase Post",NWptBinPlus-1,WptBins,NWptBinPlus-1, WptBins);
  h2_Truth_Rec_AP_PostEffCorr = new TH2D("h2_Truth_Rec_AP_PostEffCorr" ,"Truth Rec All Phase Post EffCorr",NWptBinPlus-1,WptBins,NWptBinPlus-1, WptBins);
  h1_Truth_Post_EffCorr_weightFSR = new TH1D("h1_Truth_Post_EffCorr_weightFSR","Post Wpt Truth EffCorr weightFSR",NWptBinPlus-1,WptBins);
  //for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
  //{
  //  if(ipt==1 || ipt==2)
  //  {
  //    sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",ipt);
  //    h1_W_pt_RecoPreFsrGenRes[ipt] = new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
  //    sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",ipt);
  //    h1_W_pt_RecoPstFsrGenRes[ipt]=new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
  //  }else{
  //    sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",ipt);
  //    h1_W_pt_RecoPreFsrGenRes[ipt] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
  //    sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",ipt);
  //    h1_W_pt_RecoPstFsrGenRes[ipt] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
  //  }
  //}
  return 0;
}
int Wlnu12LoUnfold::DumpUnfInfo(int i)
{
  //Gen Level Study
  TruthRecoPost = true;
  if(GenW_Born_Id->size()<1)
  {
    TruthRecoPost=false;
    cout<<"Notice: No of GenW <1"<<endl;
    return -1;
  }
  int NGenW = GenW_Born_pt->size();
  if( NGenW != 1) cout<<"Notice: Number of GenW is not 1 but "<<NGenW<<endl;
  // Assuming there is only one GenW
  //Response 
  W.genIdx = (*W_Lept1_genIdxMatch)[i];
  //TODO use this at the moment
  if(W.genIdx < 0)
  {
    TruthRecoPost=false;
    //cout<<"Notice: genIdx < 0"<<endl;
    return -1;
  }
  if(W.genIdx != 0)
    cout<<"Warning: How come the gen Idx is not 0 ================"<<endl;
  // Only for matched one
  if( (*W_Lept1_genDeltaR)[i] > 0.025){TruthRecoPost=false;return -1;}
  //Set wCand pt, phi
  TVector2 genPostW_2D(
      (*GenW_PostLept1_px)[W.genIdx]+(*GenW_PostLept2_px)[W.genIdx],
      (*GenW_PostLept1_py)[W.genIdx]+(*GenW_PostLept2_py)[W.genIdx]);
  genInfo.PostW_pt= genPostW_2D.Mod();
  genInfo.BornW_pt = (*GenW_Born_pt)[W.genIdx];
  return 0;
}

int Wlnu12LoUnfold::FillUnfHisto()
{
  h1_W_pt->Fill(W.pt, mTTW);
  if(W.charge>0)h1_Wp_pt->Fill(W.pt,mTTW);
  if(W.charge<0)h1_Wm_pt->Fill(W.pt,mTTW);
  h1_Truth_Rec->Fill(W.pt,mTTW);//dUnf bini
  h1_Truth_Post->Fill(genInfo.PostW_pt,mTTW); //dUnf xini
  if( evtCnt % 2 == 0 )
  {
    h1_Truth_Rec_Even->Fill(W.pt,mTTW);
    h1_Truth_Post_Even->Fill(genInfo.PostW_pt,mTTW);
  }else{
    h1_Truth_Rec_Odd->Fill(W.pt,mTTW);
    h1_Truth_Post_Odd->Fill(genInfo.PostW_pt,mTTW);
  }
  h2_Truth_Rec_AP_Post->Fill(W.pt,genInfo.PostW_pt,mTTW);
  h2_Truth_Rec_AP_PostEffCorr->Fill(W.pt,genInfo.PostW_pt,mTTW); //dUnf Response Matrix

  //if (W.pt>genInfo.BornW_pt && W.pt>genInfo.PostW_pt)
  //{
  //  unfoldInfo.recoPreFsrGenWptRes = (W.pt-genInfo.BornW_pt)/genInfo.BornW_pt;
  //  unfoldInfo.recoPstFsrGenWptRes = (W.pt-genInfo.PostW_pt)/genInfo.PostW_pt;
  //}
  //h1_W_pt_RecoPreFsrGenRes[0]->Fill(unfoldInfo.recoPreFsrGenWptRes);
  //h1_W_pt_RecoPstFsrGenRes[0]->Fill(unfoldInfo.recoPstFsrGenWptRes);

  //for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
  //{
  //  if(genInfo.BornW_pt > WptBins[ipt] && genInfo.BornW_pt < WptBins[ipt+1])
  //  {
  //    h1_W_pt_RecoPreFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPreFsrGenWptRes);
  //    h1_W_pt_RecoPstFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPstFsrGenWptRes);
  //  }
  //}
  h1_Truth_Post_EffCorr->Fill(genInfo.PostW_pt,mTTW);
  if(weightFSR<0) weightFSR=1;
  h1_Truth_Post_EffCorr_weightFSR->Fill(genInfo.PostW_pt,mTTW*weightFSR);
  return 0;
}

int Wlnu12LoUnfold::Write_Histo()
{
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  h1_Truth_Rec->Write();
  h1_Truth_Rec_Even->Write();
  h1_Truth_Rec_Odd->Write();
  h1_Truth_Post->Write();
  h1_Truth_Post_Even->Write();
  h1_Truth_Post_Odd->Write();
  h1_Truth_Post_EffCorr->Write();
  h1_Truth_Post_EffCorr_weightFSR->Write();
  h2_Truth_Rec_AP_Post->Write();
  h2_Truth_Rec_AP_PostEffCorr->Write();
  //for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
  //{
  //  h1_W_pt_RecoPreFsrGenRes[ipt]->Write();
  //  h1_W_pt_RecoPstFsrGenRes[ipt]->Write();
  //}
  return 0;
}
