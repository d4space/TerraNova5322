//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WEleQ/tree/
//////////////////////////////////////////////////////////
//$Log: WEleQ.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WEleQ_h
#define WEleQ_h
#include "WLepNeu.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WEleQ: public WLepNeu {
public :

    TH1D*        h1_i_ToTal[EtaBin];
    TH1D*        h1_i_All[EtaBin];
    TH1D*        h1_i_other[EtaBin];
    TH1D*        h1_i_Side[EtaBin];
    TH1D*        h1_W_Neu_All[EtaBin];
    TH1D*        h1_W_Neu_other[EtaBin];
    TH1D*        h1_W_Neu_pt_ToTal[EtaBin];
    TH1D*        h1_W_Neu_pt_ToTal_beforeTrigger[EtaBin];
    TH1D*        h1_W_Neu_AddElectron[EtaBin];
    TH1D*        h1_W_Neu_pt_Side[EtaBin];

    TH1D*        h1_check_iw;
    TH1D*        h1_check_side_iw;
    TH1D*        h1_check_pt;
    TH1D*        h1_check_side_pt;
    TH1D*        h1_check_sigmaIetaIeta;
    TH1D*        h1_check_side_sigmaIetaIeta;
    TH1D*        h1_check_dEtaIn;
    TH1D*        h1_check_side_dEtaIn;
    TH1D*        h1_check_dPhiin;
    TH1D*        h1_check_side_dPhiin;
    TH1D*        h1_check_HoverE;
    TH1D*        h1_check_side_HoverE;
    TH1D*        h1_check_dxy;
    TH1D*        h1_check_side_dxy;
    TH1D*        h1_check_dz;
    TH1D*        h1_check_side_dz;
    TH1D*        h1_check_InvE_InvP;
    TH1D*        h1_check_side_InvE_InvP;
    TH1D*        h1_check_mHits;
    TH1D*        h1_check_side_mHits;
    TH1D*        h1_check_lep_eta;
    TH1D*        h1_check_side_lep_eta;

   WEleQ(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",int etaRange_=-999);//Electron
   ~WEleQ();
   virtual void     Loop();
   void		Init(TTree *tree);
   virtual Int_t    WQElectronCutHighPUToTal(int entry);
   virtual Int_t    WQElectronCutHighPU(int entry);
   virtual Int_t    WQElectronCutSideHighPU(int entry);
   virtual Int_t    AddWQElectronCutHighPU(int entry);
protected:
   //double Nselected4bin[NwPtBin];
   double Nselected4bin[EtaBin];
   int iw;
   double temp_elpT;
};

#endif

#ifdef WEleQ_cxx

void WEleQ::Init(TTree *tree)
{
  char histName[30];
  //for(int i(0);i<NwPtBin;i++)
  for(int i(0);i<EtaBin;i++)
  {
    sprintf(histName,"h1_i_ToTal_%d",i);
    h1_i_ToTal[i] = new TH1D(histName,"W_i_ToTal",7000000,0.,7000000);
    sprintf(histName,"h1_i_All_%d",i);
    h1_i_All[i] = new TH1D(histName,"W_i_All",7000000,0.,7000000);
    sprintf(histName,"h1_i_other_%d",i);
    h1_i_other[i] = new TH1D(histName,"W_i_other",7000000,0.,7000000);
    sprintf(histName,"h1_i_Side_%d",i);
    h1_i_Side[i] = new TH1D(histName,"W_i_Side",7000000,0.,7000000);
    sprintf(histName,"h1_W_Neu_All_%d",i);
    h1_W_Neu_All[i] = new TH1D(histName,"W_Neu_pt_All",50,0.,100);
    sprintf(histName,"h1_W_Neu_pt_Side_%d",i);
    h1_W_Neu_pt_Side[i] = new TH1D(histName,"h1_W_Neu_pt_Side_check",50,0.,100);
    sprintf(histName,"h1_W_Neu_ToTal_beforeTrigger_%d",i);
    h1_W_Neu_pt_ToTal_beforeTrigger[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_beforeTrigger_check",50,0.,100);
    sprintf(histName,"h1_W_Neu_ToTal_%d",i);
    h1_W_Neu_pt_ToTal[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_check",50,0.,100);
    sprintf(histName,"h1_W_Neu_other_%d",i);
    h1_W_Neu_other[i] = new TH1D(histName,"h1_W_Neu_other_check",50,0.,100);
    sprintf(histName,"h1_W_Neu_AddElectron_%d",i);
    h1_W_Neu_AddElectron[i] = new TH1D(histName,"h1_W_Neu_AddElectron",50,0.,100);

    Nselected4bin[i]=0;
    }

    h1_check_iw = new TH1D("h1_check_iw","h1_cutcheck_iw",10000,-2,2);
    h1_check_side_iw = new TH1D("h1_check_side_iw","h1_cutcheck_side_iw",10000,-2,2);
    h1_check_pt = new TH1D("h1_check_pt","h1_cutcheck_pt",100,0.,100);
    h1_check_side_pt = new TH1D("h1_check_side_pt","h1_cutcheck_side_pt",100,0.,100);
    h1_check_sigmaIetaIeta = new TH1D("h1_check_sigmaIetaIeta","h1_cutcheck_sigmaIetaIeta",100000,-1,1);
    h1_check_side_sigmaIetaIeta = new TH1D("h1_check_side_sigmaIetaIeta","h1_cutcheck_side_sigmaIetaIeta",100000,-1,1);
    h1_check_dEtaIn = new TH1D("h1_check_dEtaIn","h1_cutcheck_dEtaIn",100000,-1,1);
    h1_check_side_dEtaIn = new TH1D("h1_check_side_dEtaIn","h1_cutcheck_side_dEtaIn",100000,-1,1);
    h1_check_dPhiin = new TH1D("h1_check_dPhiin","h1_cutcheck_dPhiin",100000,-1,1);
    h1_check_side_dPhiin = new TH1D("h1_check_side_dPhiin","h1_cutcheck_side_dPhiin",100000,-1,1);
    h1_check_HoverE = new TH1D("h1_check_HoverE","h1_cutcheck_HoverE",100000,-1,1);
    h1_check_side_HoverE = new TH1D("h1_check_side_HoverE","h1_cutcheck_side_HoverE",100000,-1,1);
    h1_check_dxy = new TH1D("h1_check_dxy","h1_cutcheck_dxy",100000,-1,1);
    h1_check_side_dxy = new TH1D("h1_check_side_dxy","h1_cutcheck_side_dxy",100000,-1,1);
    h1_check_dz = new TH1D("h1_check_dz","h1_cutcheck_dz",100000,-1,1);
    h1_check_side_dz = new TH1D("h1_check_side_dz","h1_cutcheck_side_dz",100000,-1,1);
    h1_check_InvE_InvP = new TH1D("h1_check_InvE_InvP","h1_cutcheck_InvE_InvP",100000,-1,1);
    h1_check_side_InvE_InvP = new TH1D("h1_check_side_InvE_InvP","h1_cutcheck_side_InvE_InvP",100000,-1,1);
    h1_check_mHits = new TH1D("h1_check_mHits","h1_cutcheck_mHits",100000,-1,1);
    h1_check_side_mHits = new TH1D("h1_check_side_mHits","h1_cutcheck_side_mHits",100000,-1,1);
    h1_check_lep_eta = new TH1D("h1_check_lep_eta","h1_cutcheck_lep_eta",1000,-2.6,2.6);
    h1_check_side_lep_eta = new TH1D("h1_check_side_lep_eta","h1_cutcheck_side_lep_eta",1000,-2.6,2.6);

    
}

WEleQ::WEleQ(TTree *WEleQTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_, int etaRange_) :
WLepNeu::WLepNeu(WEleQTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_, etaRange_)
{
  Init(WLepTree);
}

WEleQ::~WEleQ()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

   Int_t WEleQ::WQElectronCutHighPUToTal(int i)
     {
       if((*W_Lept1_pt)[i] < 35) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;

       if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       {
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i]) == 0.004 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i]) == 0.06 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
       } else{
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i])  == 0.007 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i])  == 0.03 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
       } 
      
       if( (*W_Lept1_hasConversion)[i] ) return -1;
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
	       
       return 1;
    }


   Int_t WEleQ::WQElectronCutHighPU(int i)
     {
       //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
       //double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
       if((*W_Lept1_pt)[i] < 35) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;

       if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       {
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
       } else{
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
       }

       if( (*W_Lept1_hasConversion)[i] ) return -1;
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
       return 1;
     }


   Int_t WEleQ::WQElectronCutSideHighPU(int i)
     { 
       //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
       // double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
       if((*W_Lept1_pt)[i] < 35) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
		           
       if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       {   
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
       } else{ 
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
         if( fabs((*W_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1; 
         if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
         if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
       }
	        
       if( (*W_Lept1_hasConversion)[i] ) return -1;
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
			          
       return 1;
     }


   Int_t WEleQ::AddWQElectronCutHighPU(int i)
     {
       if((*W_Lept1_pt)[i] < 20) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
       if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
           
       if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       {   
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
         if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
         if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
         if( (*W_Lept1_HoverE)[i] > 0.15 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
       } else{ 
         if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
         if( fabs((*W_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
         if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
         if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
         if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
       }
     
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
			     
       return 1;
     }




#endif // #ifdef WEleQ_cxx


