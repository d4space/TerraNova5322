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
#define Wlnu12LoTemplAccept_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoTemplAccept.h"
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

void Wlnu12LoTemplAccept::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoTempl Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoTemplAccept");

  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();

  cout<<"Total: "<<Ntries<<endl;

  //============================================
  // Looping for each Event 
  //============================================
  //for (int i(0); i<Ntries;i++)
  for (int i(0); i<20;i++)
  {
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

    //===================
    // Calculate Event Weight
    //=====================
    //mTTW = CalcEvtWeight();
    
    // Acceptance
    if(Mode == "Acceptance")if(GenW_Born_Id->size() > 0)
    {
      if( FillAcceptInfo() != 0 ) exit(-1);
      // Don't go futher
      continue;
    }

    // Dump MET informations To put MET as TLorentz vector
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
      mNWevt++;

    }

    //Fill the W==================
    if( W.Pass && addLepN <2 ){
      DumpWbestCand(W.idxBest);

      //Apply Recoil Correction
      if(Mode == "AllCorrectionsMC")DoRecoilCorr();

      evtSelected+=mTTW;

      if(Mode == "AllCorrectionsMC")mTTW=mTTW*DoEffiCorr();
      
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
  gBenchmark->Show("Wlnu12LoTemplAccept");
}

void Wlnu12LoTemplAccept::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
  }
}
int Wlnu12LoTemplAccept::InitVar()
{
  cout<<"Initialize variable at Wlnu12LoTempl class ==========="<<endl;
  evtCnt = 0;
  mNWevt = 0;
  TString FoutName = mResultDir+"/"+OutNameBase+".txt";
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
    }else if((AnaChannel == "Electron2012LoPU" ) || AnaChannel == "ElectronHighPU" )
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
int Wlnu12LoTemplAccept::InitVar4Evt()
{
  //cout<<"Wlnu12LoTempl::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}
int Wlnu12LoTemplAccept::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_W_pt	= new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);
   //Acceptance Histograms
   h1_Born_AP=new TH1D("h1_Born_AP","Born WpT All Phase",NWptBinPlus-1,WptBins);
   h1_Born_BornFid=new TH1D("h1_Born_BornFid","Born WpT at BornFid",NWptBinPlus-1,WptBins);
   h1_Born_BornFid_Even=new TH1D("h1_Born_BornFid_Even","Born WpT at BornFid",NWptBinPlus-1,WptBins);
   h1_Born_BothFid=new TH1D("h1_Born_BothFid","Born WpT at BothFid",NWptBinPlus-1,WptBins);
   h1_Born_BothFid_Even=new TH1D("h1_Born_BothFid_Even","Born WpT at BothFid",NWptBinPlus-1,WptBins);

   h1_Post_PostFid=new TH1D("h1_Post_PostFid","Post WpT at PostFid",NWptBinPlus-1,WptBins);
   h1_Post_PostFid_Even=new TH1D("h1_Post_PostFid_Even","Post WpT at PostFid",NWptBinPlus-1,WptBins);
   h1_Post_BothFid=new TH1D("h1_Post_BothFid","Post WpT at BothFid",NWptBinPlus-1,WptBins);
   h1_Post_BothFid_weightFSR=new TH1D("h1_Post_BothFid_weightFSR","Post WpT at BothFid weightFSR",NWptBinPlus-1,WptBins);
   h1_Post_BothFid_Even=new TH1D("h1_Post_BothFid_Even","Post WpT at BothFid",NWptBinPlus-1,WptBins);
   h2_PostBorn_BothFid=new TH2D("h2_PostBorn_BothFid","Post vs Born at BothFid",NWptBinPlus-1,WptBins, NWptBinPlus-1,WptBins);
  return 0;
}
int Wlnu12LoTemplAccept::Fill_Histo()
{
  h1_W_pt->Fill(W.pt, mTTW);
  return 0;
}

int Wlnu12LoTemplAccept::FillAcceptInfo()
{
  isPostPassAcc = false;
  isBornPassAcc = false;
  int NGenW = GenW_Born_pt->size();
  //Check W number and Lept1 id
  if( NGenW != 1) cout<<"Notice: Number of GenW is not 1 but "<<NGenW<<endl;
  if( AnaChannel=="Muon2012LoPU" || AnaChannel=="MuonHighPU")if( fabs((*GenW_BornLept1_id)[0]) != GenType::kMuon)
  {
    cout<<"Error: Muon Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }
  if( AnaChannel=="Electron2012LoPU")
    if( fabs((*GenW_BornLept1_id)[0]) != GenType::kElectron)
  {
    cout<<"Error: Electron Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }

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
  if( AnaChannel=="Muon2012LoPU" || AnaChannel=="MuonHighPU")
  if( (*GenW_BornLept1_pt)[0] > 20 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.1 )
    isBornPassAcc = true;
  if( AnaChannel=="Electron2012LoPU")
  if( (*GenW_BornLept1_pt)[0] > 25 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.5 )
  //if( (fabs((*GenW_BornLept1_eta)[0]) < 1.444) || (fabs( (*GenW_BornLept1_eta)[0]) >1.566 ) )  
    isBornPassAcc = true;

  // Fiducial of Post 
  if( AnaChannel=="Muon2012LoPU" || AnaChannel=="MuonHighPU")
  if( (*GenW_PostLept1_pt)[0] > 20 )
  if( fabs( (*GenW_PostLept1_eta)[0]) < 2.1 )
    isPostPassAcc = true;
  if( AnaChannel=="Electron2012LoPU")
  if( (*GenW_PostLept1_pt)[0] > 25 )
  if( fabs((*GenW_PostLept1_eta)[0]) < 2.5 )
  //if( (fabs((*GenW_PostLept1_eta)[0]) < 1.444) || (fabs((*GenW_PostLept1_eta)[0]) >1.566 ) )  
    isPostPassAcc = true;
  // Fill Histo
  //cout << " genInfo.BornW_pt : " <<  genInfo.BornW_pt << " mTTW : " << mTTW << endl;
  h1_Born_AP->Fill( genInfo.BornW_pt,mTTW);
  //cout <<"Checking Lumiweight = "<<mTTW<<endl;
  //cout << "isBornPassAcc : " <<isBornPassAcc << endl;
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
    //cout << "h1_Born_BornFid :" << genInfo.BornW_pt << " mTTW : " << mTTW <<endl;
    h1_Born_BornFid->Fill(genInfo.BornW_pt,mTTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BornFid_Even->Fill(genInfo.BornW_pt,mTTW);
    }
  }
  if( isPostPassAcc )
  {
    h1_Post_PostFid->Fill(genInfo.PostW_pt,mTTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Post_PostFid_Even->Fill(genInfo.PostW_pt,mTTW);
    }
  }
  if( isPostPassAcc && isBornPassAcc )
  {
    h1_Born_BothFid->Fill(genInfo.BornW_pt,mTTW);
    h1_Post_BothFid->Fill(genInfo.PostW_pt,mTTW);
    if(weightFSR<0) weightFSR=1;
    h1_Post_BothFid_weightFSR->Fill(genInfo.PostW_pt,mTTW*weightFSR);
    h2_PostBorn_BothFid->Fill(genInfo.PostW_pt,genInfo.BornW_pt,mTTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BothFid_Even->Fill(genInfo.BornW_pt,mTTW);
      h1_Post_BothFid_Even->Fill(genInfo.PostW_pt,mTTW);
    }
  }
  return 0;
}



int Wlnu12LoTemplAccept::Write_Histo()
{
  h1_W_pt->Write();
  h1_Born_AP->Write();
  h1_Born_BornFid->Write();
  h1_Born_BornFid_Even->Write();
  h1_Born_BothFid->Write();
  h1_Born_BothFid_Even->Write();

  h1_Post_PostFid->Write();
  h1_Post_PostFid_Even->Write();
  h1_Post_BothFid->Write();
  h1_Post_BothFid_weightFSR->Write();
  h1_Post_BothFid_Even->Write();
  h2_PostBorn_BothFid->Write();
  return 0;
}
