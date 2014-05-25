// $Log: Wlnu12LoScaleSmearCorr.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define Wlnu12LoScaleSmearCorr_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoScaleSmearCorr.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TVector2.h>
#include <TLorentzVector.h>
//#include "../Utils/MyTools.hh"	          // various helper functions
#include <TRandom3.h>
#include <TRandom.h>


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;

void Wlnu12LoScaleSmearCorr::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==================================================================="<<endl;
  cout<<"Wlnu12LoScaleSmearCorr Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==================================================================="<<endl;
  gBenchmark->Start("Wlnu12LoScaleSmearCorr");




   double eleMass=0.000510998902;
   double muMass=0.105658389;


  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();

  cout<<"Total: "<<Ntries<<endl;

  //============================================
  // Looping for each Event 
  //============================================
  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<1000;i++)
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
  
    ZbestSelect();
    if( Z.Pass)
    {
      mNZevt++;
   
     if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
      {
        int etaRange1 = EtaRange(Z.Lep1etaSC);
        int etaRange2 = EtaRange(Z.Lep2etaSC);
        if( AnaChannel == "Electron2012LoPU"  )
        {
          Fill_EleZmassDaughEta(etaRange1,etaRange2);
        }

       if( AnaChannel == "Muon2012LoPU"  )
        {
          Fill_MuZmassDaughEta(etaRange1,etaRange2);
        }
      }
      
     Fill_ZHisto();

     
     if(Mode == "ScaleMakeMC")
     {
     
       Scale_corrZlep1Pt = 1.0/GetScaleCorr(Z.Lep1etaSC)*Z.Lep1Pt;
       Scale_corrZlep2Pt = 1.0/GetScaleCorr(Z.Lep2etaSC)*Z.Lep2Pt;
       
       PtEtaPhiMLorentzVector Zele1_4(   Scale_corrZlep1Pt,Z.Lep1etaSC,Z.Lep1Phi,eleMass);
       PtEtaPhiMLorentzVector Zele2_4(   Scale_corrZlep2Pt,Z.Lep2etaSC,Z.Lep2Phi,eleMass);
       
       smearSFLep1 = gRandom->Gaus(Zele1_4.E(), GetSmearCorr(Z.Lep1etaSC))/Zele1_4.E();
       smearSFLep2 = gRandom->Gaus(Zele2_4.E(), GetSmearCorr(Z.Lep2etaSC))/Zele2_4.E();

       PtEtaPhiMLorentzVector Z_4 =  smearSFLep1*Zele1_4 + smearSFLep2* Zele2_4;

       Z.mass=Z_4.M();
       Fill_CorrectedZHisto();
        
     }
     
    }//Zpass


   // // Select the Best W boson
   // WbestSelect();

   // if( W.Pass)
   // {
   // }
   // //Fill the W==================
   // if( W.Pass && addLepN <2 ){
   //   DumpWbestCand(W.idxBest);

   //   //Apply Recoil Correction
   //   if(Mode == "AllCorrectionsMC")DoRecoilCorr();

   //   evtSelected+=mTTW;

   //   if(Mode == "AllCorrectionsMC")mTTW=mTTW*DoEffiCorr();
   //   
   //   Fill_Histo();

   //   Nselected4Bin();
   // 
   // }//good W

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
  Write_ZHisto();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("Wlnu12LoScaleSmearCorr");
}

void Wlnu12LoScaleSmearCorr::Nselected4Bin()
{
 // for(int i(0);i<NwPtBin;i++)
 // {
 //   if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselect4WptBin[i]+=mTTW;
 // }
}
int Wlnu12LoScaleSmearCorr::InitVar()
{
//  cout<<"Initialize variable at Wlnu12LoScaleSmearCorr class ==========="<<endl;
//  evtCnt = 0;
//  mNWevt = 0;
//  mNZevt = 0;
//  TString FoutName = mResultDir+"/"+OutNameBase+".txt";
//  Fout.open(FoutName);
//  for(int i(0);i<NwPtBin;i++)
//  {
//    mNselect4WptBin[i]=0;
//  }
//  // Recoil CorrWptection initializaWpttion
//  // Recoil CorrWptection Parameter WptFiles
//  if( (  Mode == "AllCorrectionsMC"
//      || Mode == "RecoilCorrMC")
//      || Mode =="DumpUnfInfo" )
//  {
//    if(AnaChannel == "Muon2012LoPU" )
//    {
//      Rcl.ZRDfilename="../Recoil/ZmmData/fits.root";
//      Rcl.ZMCfilename="../Recoil/ZmmMC/fits.root";
//      Rcl.Wpfilename="../Recoil/WmpMC/fits.root";
//      Rcl.Wmfilename="../Recoil/WmmMC/fits.root";
//    }else if((AnaChannel == "Electron2012LoPU" ) || AnaChannel == "ElectronHighPU" )
//    {
//      Rcl.ZRDfilename="../Recoil/ZeeData/fits.root";
//      Rcl.ZMCfilename="../Recoil/ZeeMC/fits.root";
//      Rcl.Wpfilename="../Recoil/WepMC/fits.root";
//      Rcl.Wmfilename="../Recoil/WemMC/fits.root";
//    }
//    // RecoilCorrection Object.
//    RecoilCorr= new RecoilCorrector(
//      Rcl.ZRDfilename,
//      Rcl.Wpfilename,Rcl.Wmfilename,
//      Rcl.ZMCfilename,
//      0x1234);
//  //Int_t iSeed=0xDEADBEEF default seed for random number generator at constructor
//  }
//  return 0;
}
int Wlnu12LoScaleSmearCorr::InitVar4Evt()
{
  //cout<<"Wlnu12LoScaleSmearCorr::InitVar4Evt ==========================="<<endl;
  Wlnu12LoBase::InitVar4Evt();
  return 0;
}
int Wlnu12LoScaleSmearCorr::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_W_pt	= new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,WptBins);

  h1_Zmass   = new TH1D("h1_Zmass","Z Mass",60,60.,120);
  h1_Zmass_BB= new TH1D("h1_Zmass_BB","Inv Mass for dilepts BB",60.,60.,120.);
  h1_Zmass_BE= new TH1D("h1_Zmass_BE","Inv Mass for dilepts BE",60.,60.,120.);
  h1_Zmass_EE= new TH1D("h1_Zmass_EE","Inv Mass for dilepts EE",60.,60.,120.);
  
  h1_ZmassCorr= new TH1D("h1_ZmassCorr","Inv Mass for dilepts after Scale&Smear",60.,60.,120.);
  h1_ZmassCorr_BB= new TH1D("h1_ZmassCorr_BB","Inv Mass for dilepts after Scale&Smear BB",60.,60.,120.);
  h1_ZmassCorr_BE= new TH1D("h1_ZmassCorr_BE","Inv Mass for dilepts after Scale&Smear BE",60.,60.,120.);
  h1_ZmassCorr_EE= new TH1D("h1_ZmassCorr_EE","Inv Mass for dilepts after Scale&Smear EE",60.,60.,120.);
   
 
  if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
   {
      if( AnaChannel=="Electron2012LoPU")
     {
       for(int i(0);i<ScElCombiBins;i++)
       {
         sprintf(histName,"h1_ZmassDaughEtaEle_%d",i);
         h1_ZmassDaughEtaEle[i]= new TH1D(histName,"ZmassDaughterEtaEle",60,60,120);
       }
       for(int i(0);i<ScElCombiBinsDiag;i++)
       {
         sprintf(histName,"h1_ZmassDaughEtaEleDiag_%d",i);
         h1_ZmassDaughEtaEleDiag[i]= new TH1D(histName,"ZmassDaughterEtaEleDiag",60,60,120);
       }
     }
     if( AnaChannel=="Muon2012LoPU" )
     {
       for(int i(0);i<ScMuCombiBins;i++)
       {
         sprintf(histName,"h1_ZmassDaughEtaMu_%d",i);
         h1_ZmassDaughEtaMu[i]= new TH1D(histName,"ZmassDaughterEtaMu",60,60,120);
       }
     }
  }
  
  return 0;
}
int Wlnu12LoScaleSmearCorr::Fill_Histo()
{
  h1_W_pt->Fill(W.pt, mTTW);
  return 0;
}
int Wlnu12LoScaleSmearCorr::Fill_ZHisto()
{
  h1_Zmass->Fill(Z.mass,mTTW);
 
  //Barrel Barrel
  if( (fabs(Z.Lep1etaSC) >= 0.0   && fabs(Z.Lep1etaSC) < 1.4442) && (fabs(Z.Lep2etaSC) >= 0.0   && fabs(Z.Lep2etaSC) < 1.4442))
   {
     h1_Zmass_BB->Fill(Z.mass,mTTW);
    }
    
   //Barrel Endcap
   if( (fabs(Z.Lep1etaSC) >= 0.0   && fabs(Z.Lep1etaSC) < 1.4442 ) && (fabs(Z.Lep2etaSC) >= 1.566   && fabs(Z.Lep2etaSC) < 2.5) )
   {
       h1_Zmass_BE->Fill(Z.mass,mTTW);
   }else if( (fabs(Z.Lep1etaSC) >= 1.566   && fabs(Z.Lep1etaSC) < 2.5) && ( fabs(Z.Lep2etaSC) >= 0.0   && fabs(Z.Lep2etaSC) < 1.4442) )
   {
       h1_Zmass_BE->Fill(Z.mass,mTTW);
   }

  // Endcap Endcap
  if( (fabs(Z.Lep1etaSC) >= 1.566  && fabs(Z.Lep1etaSC) < 2.5) && (fabs(Z.Lep2etaSC) >= 1.566   && fabs(Z.Lep2etaSC) < 2.5))
  {
      h1_Zmass_EE->Fill(Z.mass,mTTW);
  }
  

  return 0;
}


int Wlnu12LoScaleSmearCorr::Fill_CorrectedZHisto()
{
  h1_ZmassCorr->Fill(Z.mass,mTTW);

  //Barrel Barrel
  if( (fabs(Z.Lep1etaSC) >= 0.0   && fabs(Z.Lep1etaSC) < 1.4442) && (fabs(Z.Lep2etaSC) >= 0.0   && fabs(Z.Lep2etaSC) < 1.4442))
   {
     h1_ZmassCorr_BB->Fill(Z.mass,mTTW);
    }
    
   //Barrel Endcap
   if( (fabs(Z.Lep1etaSC) >= 0.0   && fabs(Z.Lep1etaSC) < 1.4442 ) && (fabs(Z.Lep2etaSC) >= 1.566   && fabs(Z.Lep2etaSC) < 2.5) )
   {
       h1_ZmassCorr_BE->Fill(Z.mass,mTTW);
   }else if( (fabs(Z.Lep1etaSC) >= 1.566   && fabs(Z.Lep1etaSC) < 2.5) && ( fabs(Z.Lep2etaSC) >= 0.0   && fabs(Z.Lep2etaSC) < 1.4442) )
   {
       h1_ZmassCorr_BE->Fill(Z.mass,mTTW);
   }

  // Endcap Endcap
  if( (fabs(Z.Lep1etaSC) >= 1.566  && fabs(Z.Lep1etaSC) < 2.5) && (fabs(Z.Lep2etaSC) >= 1.566   && fabs(Z.Lep2etaSC) < 2.5))
  {
      h1_ZmassCorr_EE->Fill(Z.mass,mTTW);
  }
 

  return 0;
}

int Wlnu12LoScaleSmearCorr::Write_Histo()
{
  h1_W_pt->Write();
  return 0;
}
int Wlnu12LoScaleSmearCorr::Write_ZHisto()
{
  h1_Zmass->Write();
  h1_Zmass_BB->Write();
  h1_Zmass_BE->Write();
  h1_Zmass_EE->Write();
 
  if(Mode == "ScaleMakeMC")
  {
    h1_ZmassCorr->Write();
    h1_ZmassCorr_BB->Write();
    h1_ZmassCorr_BE->Write();
    h1_ZmassCorr_EE->Write(); 
  }
  
  if(Mode =="ScaleMakeMC" || Mode =="ScaleMakeRD")
  {
    if( AnaChannel == "Electron2012LoPU" )
    {
      for(int i(0);i<ScElCombiBins;i++)
      {
        h1_ZmassDaughEtaEle[i]->Write();
      }
      for(int i(0);i<ScElCombiBinsDiag;i++)
      {
        h1_ZmassDaughEtaEleDiag[i]->Write();
      }
    }
    if( AnaChannel == "MuonLowPU"  )
    {
      for(int i(0);i<ScMuCombiBins;i++)
      {
        h1_ZmassDaughEtaMu[i]->Write();
      }
    }
  }


  return 0;
}


int Wlnu12LoScaleSmearCorr::ZbestSelect()
{

  //Z boson
   Z.Pass = false;
   mZ_size = Z_Mass->size();
  
   diLeptVtxProb = 0;
  double tmpVar(0);
  double ZLep2PtTmp;
  for(int iz(0); iz<mZ_size;iz++)
  {
    if(AnaChannel == "TauHighPU")if( TauCutZ(iz) == -1) continue;
    if(AnaChannel == "Muon2012LoPU" )if( MuonCutZ(iz) == -1) continue;
    if(AnaChannel == "Electron2012LoPU" )if( ElectronCutZ(iz) == -1) continue;
    if(Mode =="ScaleMakeRD")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if(Mode =="ScaleMakeMC")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if((Mode =="RecoilEvaRD")||(Mode == "RecoilEvaMC"))if((*Z_Lept2_pt)[iz] < 15 )continue;
    
    Z.Pass=true;
    tmpVar = (*Z_diLeptVtxProb)[iz];
    if( fabs(Channel) != GenType::kTau) if( tmpVar > diLeptVtxProb )
    {
      Z.idxBest = iz;
      diLeptVtxProb = tmpVar;
        Z.mass          = (*Z_Mass)[iz];
        Z.Lep1Pt        = (*Z_Lept1_pt)[iz];
        Z.Lep1Pz        = (*Z_Lept1_pz)[iz];
        Z.Lep1En        = (*Z_Lept1_en)[iz];
        Z.Lep1Phi       = (*Z_Lept1_phi)[iz];
        Z.Lep2Pt        = (*Z_Lept2_pt)[iz];
        Z.Lep2Pz        = (*Z_Lept2_pz)[iz];
        Z.Lep2En        = (*Z_Lept2_en)[iz];
        Z.Lep2Phi       = (*Z_Lept2_phi)[iz];

        TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

        if(AnaChannel == "Electron2012LoPU"  )
	{
          Z.Lep1etaSC   = (*Z_Lept1_etaSC)[iz];
          Z.Lep2etaSC   = (*Z_Lept2_etaSC)[iz];
        }else
	{
          Z.Lep1etaSC   = (*Z_Lept1_eta)[iz];
          Z.Lep2etaSC   = (*Z_Lept2_eta)[iz];
        }
    }//fi diLeptVtxProb
    ZLep2PtTmp = (*Z_Lept2_pt)[iz];
    if( fabs(Channel) == GenType::kTau) if( ZLep2PtTmp > Z.Lep2Pt )
    {
      Z.idxBest = iz;
        Z.mass          = (*Z_Mass)[iz];
        Z.Lep1Pt        = (*Z_Lept1_pt)[iz];
        Z.Lep1Pz        = (*Z_Lept1_pz)[iz];
        Z.Lep1En        = (*Z_Lept1_en)[iz];
        Z.Lep1Phi       = (*Z_Lept1_phi)[iz];
        Z.Lep2Pt        = (*Z_Lept2_pt)[iz];
        Z.Lep2Pz        = (*Z_Lept2_pz)[iz];
        Z.Lep2En        = (*Z_Lept2_en)[iz];
        Z.Lep2Phi       = (*Z_Lept2_phi)[iz];

        TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

        if(AnaChannel == "Electron2012LoPU" )
	{
          Z.Lep1etaSC   = (*Z_Lept1_etaSC)[iz];
          Z.Lep2etaSC   = (*Z_Lept2_etaSC)[iz];
        }else
	{
          Z.Lep1etaSC   = (*Z_Lept1_eta)[iz];
	  Z.Lep2etaSC   = (*Z_Lept2_eta)[iz];
	}
    }//fi diLeptVtxProb
    
    }//Z
   
  return 0;
}

int Wlnu12LoScaleSmearCorr::Fill_EleZmassDaughEta(int etaRange1, int etaRange2)
{
  //ScaleSmear Electron 6 only Diagobal category Fill 
  if( (etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEtaEleDiag[0]->Fill(Z.mass);
  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEtaEleDiag[1]->Fill(Z.mass);
  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEtaEleDiag[2]->Fill(Z.mass);
  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEtaEleDiag[3]->Fill(Z.mass);
  if((etaRange1==4 && etaRange2==4))
    h1_ZmassDaughEtaEleDiag[4]->Fill(Z.mass);
  if((etaRange1==5 && etaRange2==5))
    h1_ZmassDaughEtaEleDiag[5]->Fill(Z.mass);
  
  
  
  //ScaleSmear Electron 21 category Fill 
  if( (etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEtaEle[0]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==1) || (etaRange1==1 && etaRange2==0))
    h1_ZmassDaughEtaEle[1]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==2) || (etaRange1==2 && etaRange2==0))
    h1_ZmassDaughEtaEle[2]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==3) || (etaRange1==3 && etaRange2==0))
    h1_ZmassDaughEtaEle[3]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==4) || (etaRange1==4 && etaRange2==0))
    h1_ZmassDaughEtaEle[4]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==5) || (etaRange1==5 && etaRange2==0))
    h1_ZmassDaughEtaEle[5]->Fill(Z.mass);
  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEtaEle[6]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==2) || (etaRange1==2 && etaRange2==1))
    h1_ZmassDaughEtaEle[7]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==3) || (etaRange1==3 && etaRange2==1))
    h1_ZmassDaughEtaEle[8]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==4) || (etaRange1==4 && etaRange2==1))
    h1_ZmassDaughEtaEle[9]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==5) || (etaRange1==5 && etaRange2==1))
    h1_ZmassDaughEtaEle[10]->Fill(Z.mass);
  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEtaEle[11]->Fill(Z.mass);
  if((etaRange1==2 && etaRange2==3) || (etaRange1==3 && etaRange2==2))
    h1_ZmassDaughEtaEle[12]->Fill(Z.mass);
  if((etaRange1==2 && etaRange2==4) || (etaRange1==4 && etaRange2==2))
    h1_ZmassDaughEtaEle[13]->Fill(Z.mass);
  if((etaRange1==2 && etaRange2==5) || (etaRange1==5 && etaRange2==2))
    h1_ZmassDaughEtaEle[14]->Fill(Z.mass);
  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEtaEle[15]->Fill(Z.mass);
  if((etaRange1==3 && etaRange2==4) ||( etaRange1==4 && etaRange2==3))
    h1_ZmassDaughEtaEle[16]->Fill(Z.mass);
  if((etaRange1==3 && etaRange2==5) || ( etaRange1==5 && etaRange2==3))
    h1_ZmassDaughEtaEle[17]->Fill(Z.mass);
  if((etaRange1==4 && etaRange2==4))
    h1_ZmassDaughEtaEle[18]->Fill(Z.mass);
  if((etaRange1==4 && etaRange2==5) || (etaRange1==5 && etaRange2==4))
    h1_ZmassDaughEtaEle[19]->Fill(Z.mass);
  if((etaRange1==5 && etaRange2==5))
    h1_ZmassDaughEtaEle[20]->Fill(Z.mass);

  return 0;
}

int Wlnu12LoScaleSmearCorr::Fill_MuZmassDaughEta(int etaRange1, int etaRange2)
{
  //ScaleSmear Muon 15 category Fill
  if((etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEtaMu[0]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==1) || (etaRange1==1 && etaRange2==0))
    h1_ZmassDaughEtaMu[1]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==2) || (etaRange1==2 && etaRange2==0))
    h1_ZmassDaughEtaMu[2]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==3) || (etaRange1==3 && etaRange2==0))
    h1_ZmassDaughEtaMu[3]->Fill(Z.mass);
  if((etaRange1==0 && etaRange2==4) || (etaRange1==4 && etaRange2==0))
    h1_ZmassDaughEtaMu[4]->Fill(Z.mass);
  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEtaMu[5]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==2) || (etaRange1==2 && etaRange2==1))
    h1_ZmassDaughEtaMu[6]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==3) || (etaRange1==3 && etaRange2==1))
    h1_ZmassDaughEtaMu[7]->Fill(Z.mass);
  if((etaRange1==1 && etaRange2==4) || (etaRange1==4 && etaRange2==1))
    h1_ZmassDaughEtaMu[8]->Fill(Z.mass);
  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEtaMu[9]->Fill(Z.mass);
  if((etaRange1==2 && etaRange2==3) || (etaRange1==3 && etaRange2==2))
    h1_ZmassDaughEtaMu[10]->Fill(Z.mass);
  if((etaRange1==2 && etaRange2==4) || (etaRange1==4 && etaRange2==2))
    h1_ZmassDaughEtaMu[11]->Fill(Z.mass);
  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEtaMu[12]->Fill(Z.mass);
  if((etaRange1==3 && etaRange2==4) || (etaRange1==4 && etaRange2==3))
    h1_ZmassDaughEtaMu[13]->Fill(Z.mass);
  if((etaRange1==4) && (etaRange2==4))
    h1_ZmassDaughEtaMu[14]->Fill(Z.mass);

  return 0;
}


Int_t Wlnu12LoScaleSmearCorr::EtaRange(double lep1Eta)
{

  int lep1Range(-1);
  if( AnaChannel=="Electron2012LoPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4442) lep1Range=3;
    if( fabs(lep1Eta) >= 1.566 && fabs(lep1Eta) < 2.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.5)    lep1Range=5;

  }

 if( AnaChannel=="Muon2012LoPU" )
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.6)    lep1Range=3;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 2.1)    lep1Range=4;

  }

 return lep1Range;
}

Double_t Wlnu12LoScaleSmearCorr::GetScaleCorr(double LepEta)
{
  if(AnaChannel == "Electron2012LoPU")
  {
    ///Scale to be applied on MC to check on Z 
    if(fabs(LepEta) >= 0.0   && fabs(LepEta) < 0.4) 	 {return  0.999315;}
    if(fabs(LepEta) >= 0.4   && fabs(LepEta) < 0.8) 	 {return  1.00358;} 
    if(fabs(LepEta) >= 0.8   && fabs(LepEta) < 1.2) 	 {return  1.00325;}
    if(fabs(LepEta) >= 1.2   && fabs(LepEta) < 1.4442)   {return  1.00244;}
    if(fabs(LepEta) >= 1.566 && fabs(LepEta) < 2.0) 	 {return  1.0067;}
    if(fabs(LepEta) >= 2.0   && fabs(LepEta) < 2.5)	 {return  0.992737;}
  
  }
}

Double_t Wlnu12LoScaleSmearCorr::GetSmearCorr(double LepEta)
{
  //double EndcapSystFactor =3.0;

  if(AnaChannel == "Electron2012LoPU")
  {
    ///21 category result: smear to be applied on MC to check on Z 
    if(fabs(LepEta) >= 0.0   && fabs(LepEta) < 0.4)	 {return  0.382443;}
    if(fabs(LepEta) >= 0.4   && fabs(LepEta) < 0.8)	 {return  0.356171;}
    if(fabs(LepEta) >= 0.8   && fabs(LepEta) < 1.2) 	 {return  0.559123;}
    if(fabs(LepEta) >= 1.2   && fabs(LepEta) < 1.4442)   {return  0.01;}
    //if(fabs(LepEta) >= 1.566 && fabs(LepEta) < 2.0)  	 {return  0.972944*EndcapSystFactor ;}
    //if(fabs(LepEta) >= 2.0   && fabs(LepEta) < 2.5)  	 {return  1.84788*EndcapSystFactor;}
    if(fabs(LepEta) >= 1.566 && fabs(LepEta) < 2.0)  	 {return  0.972944*2.5 ;}
    if(fabs(LepEta) >= 2.0   && fabs(LepEta) < 2.5)  	 {return  1.84788*2.5;}
    
    
    ///6 category result: smear to be applied on MC to check on Z 
   // if(fabs(LepEta) >= 0.0   && fabs(LepEta) < 0.4)	 {return  0.236791;}
   // if(fabs(LepEta) >= 0.4   && fabs(LepEta) < 0.8)	 {return  0.248012;}
   // if(fabs(LepEta) >= 0.8   && fabs(LepEta) < 1.2) 	 {return  0.334847;}
   // if(fabs(LepEta) >= 1.2   && fabs(LepEta) < 1.4442)   {return  1.39538;}
   // if(fabs(LepEta) >= 1.566 && fabs(LepEta) < 2.0)  	 {return  0.496947;}
   // if(fabs(LepEta) >= 2.0   && fabs(LepEta) < 2.5)  	 {return  1.88972;}
  
  }
}
