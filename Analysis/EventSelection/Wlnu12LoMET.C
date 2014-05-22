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
  TTW =1;
  cout<<"Total: "<<Ntries<<endl;

  //============================================
  // Looping for each Event 
  //============================================
  //for (int i(0); i<Ntries;i++)
  for (int i(0); i<20;i++)
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

    if(Mode == "Acceptance")if(GenW_Born_Id->size() > 0) 
    {    
      //TTW = 1;
      if( FillAcceptInfo() != 0 ) exit(-1);
      // Don't go futher
      continue;
    }    

    // Dump MET informations
    DumpMETs();

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
   
    //===================
    // Apply Scale Correction to RD
    //=====================

    DumpWSideCand();
    if (W.pt_side != 0)
      //cout<<i<<" Side\t"<<W.pt_side<<"\t"<<W.Met_side<<"\t"<<W.charge_side<<"\t"<<mTTW<<endl;
    Fill_SideHisto();

    // Select the Best W boson
    WbestSelect();

    if( W.Pass)
    {
    }

    //Fill the W==================
    if(W.Pass && addLepN <2){
      DumpWbestCand(W.idxBest);
      
      if((Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
	  || Mode == "Unfold")
	if(GenW_Born_Id->size() >0)
	DoRecoilCorr();

      evtSelected+=mTTW;
      
      effiSF = DoEffiCorr();
      
    //if (W.pt != 0)
    //  cout<<i<<" Signal\t"<<W.pt<<"\t"<<corrMet<<"\t"<<W.Met<<"\t"<<W.charge<<"\t"<<mTTW<<"\t"<<effiSF<<endl;
      Fill_Histo();

      Nselected4Bin();
    
    }//good W

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
  if( (  Mode == "AllCorrectionsMC"
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
    if(Mode == "AllCorrectionsMC")
    {
      h1_W_Neu_pt[0]->Fill(corrMet,mTTW*effiSF);
      h1_Wp_Neu_pt[0]->Fill(corrMet,mTTW*effiSF);
    
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
      {
	if(W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1])
	{
	  h1_W_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effiSF);
	  h1_Wp_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effiSF);
	}
      }
    }else{
      h1_W_Neu_pt[0]->Fill(W.Met,mTTW);
      h1_Wp_Neu_pt[0]->Fill(W.Met,mTTW);
    
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
      {
	if(W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1])
	{
	  h1_W_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
	  h1_Wp_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
	}
      }
    }
  }else if(W.charge<0)
  {
    h1_Wm_pt->Fill(W.pt,mTTW);
    if(Mode == "AllCorrectionsMC")
    {
      h1_W_Neu_pt[0]->Fill(corrMet,mTTW*effiSF);
      h1_Wm_Neu_pt[0]->Fill(corrMet,mTTW*effiSF);
      
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++) {
	if( W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1] )
	{
	  h1_W_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effiSF);
	  h1_Wm_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effiSF);
	}
      }
    }else{
      h1_W_Neu_pt[0]->Fill(W.Met,mTTW);
      h1_Wm_Neu_pt[0]->Fill(W.Met,mTTW);
      
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++) {
	if( W.pt >= WptBins[iBin] && W.pt < WptBins[iBin+1] )
	{
	  h1_W_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
	  h1_Wm_Neu_pt[iBin+1]->Fill(W.Met,mTTW);
	}
      }
    }
  }
  return 0;
}

int Wlnu12LoMET::Fill_SideHisto()
{
  if(W.charge_side>0)
  {
    h1_WSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
    h1_WpSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
  
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++){
      if( W.pt_side >= WptBins[iBin] && W.pt_side < WptBins[iBin+1])
      {
        h1_WSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
        h1_WpSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
      }
    }
  }else if (W.charge_side<0){
    h1_WSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
    h1_WmSide_Neu_pt[0]->Fill(W.Met_side,mTTW);
    
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++){
      if( W.pt_side >= WptBins[iBin] && W.pt_side < WptBins[iBin+1])
      {
        h1_WSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
        h1_WmSide_Neu_pt[iBin+1]->Fill(W.Met_side,mTTW);
      }
    }
  }
  return 0;
}
int Wlnu12LoMET::DefineAcceptHist()
{
   //Acceptance Histograms
   h1_Born_AP=new TH1D("h1_Born_AP","Born WpT All Phase",NWptBinPlus-1,Bins);
   h1_Born_BornFid=new TH1D("h1_Born_BornFid","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BornFid_Even=new TH1D("h1_Born_BornFid_Even","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid=new TH1D("h1_Born_BothFid","Born WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid_Even=new TH1D("h1_Born_BothFid_Even","Born WpT at BothFid",NWptBinPlus-1,Bins);

   h1_Post_PostFid=new TH1D("h1_Post_PostFid","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_PostFid_Even=new TH1D("h1_Post_PostFid_Even","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid=new TH1D("h1_Post_BothFid","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid_weightFSR=new TH1D("h1_Post_BothFid_weightFSR","Post WpT at BothFid weightFSR",NWptBinPlus-1,Bins);
   h1_Post_BothFid_Even=new TH1D("h1_Post_BothFid_Even","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h2_PostBorn_BothFid=new TH2D("h2_PostBorn_BothFid","Post vs Born at BothFid",NWptBinPlus-1,Bins, NWptBinPlus-1,Bins);
}

int Wlnu12LoMET::FillAcceptInfo()
{
  cout << "check 1" << endl;
  isPostPassAcc = false;
  isBornPassAcc = false;
  int NGenW = GenW_Born_pt->size();
  //Check W number and Lept1 id
  if( NGenW != 1) cout<<"Notice: Number of GenW is not 1 but "<<NGenW<<endl;
  if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")if( fabs((*GenW_BornLept1_id)[0]) != GenType::kMuon)
  {
    cout<<"Error: Muon Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }
  cout << "check 2" << endl;
  if( AnaChannel=="ElectronLowPU")
    if( fabs((*GenW_BornLept1_id)[0]) != GenType::kElectron)
  {
    cout<<"Error: Electron Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }
  cout << "check 3" << endl;

  // Gen Information
  TVector2 genW_Post_2D(
	(*GenW_PostLept1_px)[0] + (*GenW_PostLept2_px)[0],
	(*GenW_PostLept1_py)[0] + (*GenW_PostLept2_py)[0]);
  genInfo.PostW_pt = genW_Post_2D.Mod();
  genInfo.BornW_pt = (*GenW_Born_pt)[0];

  // Fill Born Level
  // Acceptance
    //Full Phase Spece
  // Fiducial 
  if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  if( (*GenW_BornLept1_pt)[0] > 20 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.1 )
    isBornPassAcc = true;
  if( AnaChannel=="ElectronLowPU")
  if( (*GenW_BornLept1_pt)[0] > 25 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.5 )
  //if( (fabs((*GenW_BornLept1_eta)[0]) < 1.444) || (fabs( (*GenW_BornLept1_eta)[0]) >1.566 ) )  
    isBornPassAcc = true;
  cout << "check 4" << endl;

  // Fiducial of Post 
  if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  if( (*GenW_PostLept1_pt)[0] > 20 )
  if( fabs( (*GenW_PostLept1_eta)[0]) < 2.1 )
    isPostPassAcc = true;
  if( AnaChannel=="ElectronLowPU")
  if( (*GenW_PostLept1_pt)[0] > 25 )
  if( fabs((*GenW_PostLept1_eta)[0]) < 2.5 )
  //if( (fabs((*GenW_PostLept1_eta)[0]) < 1.444) || (fabs((*GenW_PostLept1_eta)[0]) >1.566 ) )  
    isPostPassAcc = true;
  // Fill Histo
  cout << "check 5" << endl;
  h1_Born_AP->Fill( genInfo.BornW_pt,TTW);
  cout << "check 6" << endl;
  //cout <<"Checking Lumiweight = "<<TTW<<endl;
  if( isBornPassAcc )
  {
    /*
    ////PDFsyst calculation
    for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
    {
      //if( wCand.pt >= Bins[iBin] && wCand.pt < Bins[iBin+1] )
      if( genInfo.BornW_pt >= Bins[iBin] && genInfo.BornW_pt < Bins[iBin+1] )
      {
        for(int j=0; j<weightPDF->size(); ++j)
        {
          weightedSelectedEvents[iBin][j] += (*weightPDF)[j];
          weighted2SelectedEvents[iBin][j] += (*weightPDF)[j] * (*weightPDF)[j];
          //cout<<wCand.pt<<" weightPDF: "<<j<<"\t"<<(*weightPDF)[j]<<"\t"<<weightedSelectedEvents[iBin][j]<<"\t"<<weighted2SelectedEvents[iBin][j]<<endl;
        }
      }
    }
  for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
  {
    unsigned int nmembers = weightPDF->size();
    unsigned int npairs = (nmembers-1)/2;
    //cout<<npairs<<endl;
    events_central[iBin] = weightedSelectedEvents[iBin][0];
    events2_central[iBin] = weighted2SelectedEvents[iBin][0];
    if (npairs>0){
      for (unsigned int j=0; j<npairs; ++j) {
        wa[iBin] = weightedSelectedEvents[iBin][2*j+1]/events_central[iBin]-1.;
        wb[iBin] = weightedSelectedEvents[iBin][2*j+2]/events_central[iBin]-1.; 
        if (wa[iBin]>wb[iBin]) {
          if (wa[iBin]<0.) wa[iBin] = 0.;
          if (wb[iBin]>0.) wb[iBin] = 0.;
          wplus[iBin] += wa[iBin]*wa[iBin];
          wminus[iBin] += wb[iBin]*wb[iBin];
        } else {
          if (wb[iBin]<0.) wb[iBin] = 0.;
          if (wa[iBin]>0.) wa[iBin] = 0.;
          wplus[iBin] += wb[iBin]*wb[iBin];
          wminus[iBin] += wa[iBin]*wa[iBin];
        }
        //cout<<iBin<<"\t"<<wa[iBin]<<"\t"<<wb[iBin]<<"\t"<<wplus[iBin]<<"\t"<<wminus[iBin]<<endl;
      }
      if (wplus[iBin]>0) wplus[iBin] = sqrt(wplus[iBin]);
      if (wminus[iBin]>0) wminus[iBin] = sqrt(wminus[iBin]);
      //cout<<wplus[iBin]<<"\t"<<wminus[iBin]<<"\t"<<endl;
    }else{
      cout << "\tNO eigenvectors for uncertainty estimation" << endl;
    }
    cout <<iBin+1<<" Bin: Relative uncertainty with respect to central member: +" << setprecision(4) << 100.*wplus[iBin] << " / -" << setprecision(4) << 100.*wminus[iBin] << " [%]" << endl;
    //cout<<"End"<<endl;
  }
 */
    h1_Born_BornFid->Fill(genInfo.BornW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BornFid_Even->Fill(genInfo.BornW_pt,TTW);
    }
  }
  if( isPostPassAcc )
  {
    h1_Post_PostFid->Fill(genInfo.PostW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Post_PostFid_Even->Fill(genInfo.PostW_pt,TTW);
    }
  }
  if( isPostPassAcc && isBornPassAcc )
  {
    h1_Born_BothFid->Fill(genInfo.BornW_pt,TTW);
    h1_Post_BothFid->Fill(genInfo.PostW_pt,TTW);
    if(weightFSR<0) weightFSR=1;
    h1_Post_BothFid_weightFSR->Fill(genInfo.PostW_pt,TTW*weightFSR);
    h2_PostBorn_BothFid->Fill(genInfo.PostW_pt,genInfo.BornW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BothFid_Even->Fill(genInfo.BornW_pt,TTW);
      h1_Post_BothFid_Even->Fill(genInfo.PostW_pt,TTW);
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
