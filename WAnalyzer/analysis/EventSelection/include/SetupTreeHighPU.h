#include <TChain.h>
// Electron header S10
 #include "2012HighPU/chain_Electron_WpToEleNu_S10.h"
 #include "2012HighPU/chain_Electron_WmToEleNu_S10.h"
 #include "2012HighPU/chain_Electron_WToENu_S10.h"
 #include "2012HighPU/chain_Electron_WpToTauNu_S10.h"
 #include "2012HighPU/chain_Electron_WmToTauNu_S10.h"
 #include "2012HighPU/chain_Electron_WJetsToLNu_S10.h"
 #include "2012HighPU/chain_Electron_DYToEE_S10.h"
 #include "2012HighPU/chain_Electron_WToTauNu_S10.h"
 #include "2012HighPU/chain_Electron_DYToTauTau_S10.h"
 #include "2012HighPU/chain_Electron_TTJets_S10.h"
 #include "2012HighPU/chain_Electron_TT_CT10_S10.h"
 #include "2012HighPU/chain_Electron_QCD30to50_S10.h"
 #include "2012HighPU/chain_Electron_QCD50to80_S10.h"
 #include "2012HighPU/chain_Electron_QCD80to120_S10.h"
 #include "2012HighPU/chain_Electron_QCD120to170_S10.h"
 #include "2012HighPU/chain_Electron_DYJetsToLL_S10.h"
 #include "2012HighPU/chain_Electron_G_Pt50to80_S10.h"
 #include "2012HighPU/chain_Electron_RD_HighPU.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_20to30_S10.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_30to80_S10.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_80to170_S10.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_170to250_S10.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_250to350_S10.h"
 #include "2012HighPU/chain_Electron_QCD_EMEnriched_350_S10.h"

//#include "chain_Tau_DYJetsToLL_S10.h"


 void SetupTreeHighPU( TString sample, TChain* chains )
 {
   cout<<"SetupTreeHighPU.h: "<<sample<<endl;
   //================
   //Electron Scripts S10
   //================
//   if( sample == "Tau_DYJetsToLL_S10")
//   {
//     chain_Tau_DYJetsToLL_S10(chains);
//   }
//   else if( sample == "Ele_WpToENu_S10")
   if( sample == "Ele_WpToENu_S10")
   {
     chain_Electron_WpToEleNu_S10(chains);
   }
   else if( sample == "Ele_WmToENu_S10")
   {
     chain_Electron_WmToEleNu_S10(chains);
   }
   else if( sample == "Ele_WToENu_S10")
   {
     chain_Electron_WToENu_S10(chains);
   }
   else if( sample == "Ele_WpToTauNu_S10")
   {
     chain_Electron_WpToTauNu_S10(chains);
   }
   else if( sample == "Ele_WmToTauNu_S10")
   {
     chain_Electron_WmToTauNu_S10(chains);
   }
   else if( sample == "Ele_WJetsToLNu_S10")
   {
     chain_Electron_WJetsToLNu_S10(chains);
   }
   else if( sample == "Ele_DYToEE_S10")
   {
     chain_Electron_DYToEE_S10(chains);
   }
   else if( sample == "Ele_WToTauNu_S10")
   {
     chain_Electron_WToTauNu_S10(chains);
   }
   else if( sample == "Ele_DYToTauTau_S10")
   {
     chain_Electron_DYToTauTau_S10(chains);
   }
   else if(sample == "Ele_TTJets_S10")
   {
     chain_Electron_TTJets_S10(chains);
   }
   else if(sample == "Ele_TT_CT10_S10")
   {
     chain_Electron_TT_CT10_S10(chains);
   }
   else if(sample == "Ele_QCD30to50_S10")
   {
     chain_Electron_QCD30to50_S10(chains);
   }
   else if(sample == "Ele_QCD50to80_S10")
   {
     chain_Electron_QCD50to80_S10(chains);
   }
   else if(sample == "Ele_QCD80to120_S10")
   {
     chain_Electron_QCD80to120_S10(chains);
   }
   else if(sample == "Ele_QCD120to170_S10")
   {
     chain_Electron_QCD120to170_S10(chains);
   }
   else if(sample == "Ele_DYJetsToLL_S10")
   {
     chain_Electron_DYJetsToLL_S10(chains);
   }
   else if(sample == "Ele_G_Pt50to80_S10")
   {
     chain_Electron_G_Pt50to80_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_20to30_S10")
   {
     chain_Electron_QCD_EMEnriched_20to30_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_30to80_S10")
   {
     chain_Electron_QCD_EMEnriched_30to80_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_80to170_S10")
   {
     chain_Electron_QCD_EMEnriched_80to170_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_170to250_S10")
   {
     chain_Electron_QCD_EMEnriched_170to250_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_250to350_S10")
   {
     chain_Electron_QCD_EMEnriched_250to350_S10(chains);
   }
   else if(sample == "Ele_QCD_EMEnriched_350_S10")
   {
     chain_Electron_QCD_EMEnriched_350_S10(chains);
   }
   else if(sample == "Ele_RD_HighPU")
   {
     chain_Electron_RD_HighPU(chains);
   }
   else
   {
     cout<<"[SetupTree.h] Nanigorae? "<<endl;
   }
}






