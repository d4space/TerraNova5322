#include <TChain.h>
// Electron header S10
 #include "chain_Electron_WpToEleNu_S10.h"
 #include "chain_Electron_WmToEleNu_S10.h"
 #include "chain_Electron_WToENu_S10.h"
 #include "chain_Electron_WpToTauNu_S10.h"
 #include "chain_Electron_WmToTauNu_S10.h"
 #include "chain_Electron_WJetsToLNu_S10.h"
 #include "chain_Electron_DYToEE_S10.h"
 #include "chain_Electron_WToTauNu_S10.h"
 #include "chain_Electron_DYToTauTau_S10.h"
 #include "chain_Electron_TTJets_S10.h"
 #include "chain_Electron_TT_CT10_S10.h"
 #include "chain_Electron_QCD30to50_S10.h"
 #include "chain_Electron_QCD50to80_S10.h"
 #include "chain_Electron_QCD80to120_S10.h"
 #include "chain_Electron_QCD120to170_S10.h"
 #include "chain_Electron_DYJetsToLL_S10.h"
 #include "chain_Electron_G_Pt50to80_S10.h"
 #include "chain_Electron_RD_HighPU.h"
 #include "chain_Electron_RD_HighPU_A.h"
 #include "chain_Electron_RD_HighPU_B.h"
 #include "chain_Electron_RD_HighPU_C.h"
 #include "chain_Electron_RD_HighPU_D.h"
 #include "chain_Electron_RD_HighPU_1.h"
 #include "chain_Electron_RD_HighPU_2.h"
 #include "chain_Electron_RD_HighPU_3.h"
 #include "chain_Electron_RD_HighPU_4.h"
 #include "chain_Electron_RD_HighPU_5.h"
 #include "chain_Electron_RD_HighPU_6.h"
 #include "chain_Electron_RD_HighPU_7.h"
 #include "chain_Electron_RD_HighPU_8.h"
 #include "chain_Electron_RD_HighPU_9.h"
 #include "chain_Electron_RD_HighPU_10.h"
 #include "chain_Electron_RD_HighPU_11.h"
 #include "chain_Electron_RD_HighPU_12.h"
 #include "chain_Electron_RD_HighPU_13.h"
 #include "chain_Electron_RD_HighPU_14.h"
 #include "chain_Electron_RD_HighPU_15.h"
 #include "chain_Electron_RD_HighPU_16.h"
 #include "chain_Electron_RD_HighPU_17.h"
 #include "chain_Electron_RD_HighPU_18.h"
 #include "chain_Electron_RD_HighPU_19.h"
 #include "chain_Electron_QCD_EMEnriched_20to30_S10.h"
 #include "chain_Electron_QCD_EMEnriched_30to80_S10.h"
 #include "chain_Electron_QCD_EMEnriched_80to170_S10.h"
 #include "chain_Electron_QCD_EMEnriched_170to250_S10.h"
 #include "chain_Electron_QCD_EMEnriched_250to350_S10.h"
 #include "chain_Electron_QCD_EMEnriched_350_S10.h"

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
   else if(sample == "Ele_RD_HighPU_A")
        {
	       chain_Electron_RD_HighPU_A(chains);
	          }
   else if(sample == "Ele_RD_HighPU_B")
        {
	       chain_Electron_RD_HighPU_B(chains);
	          }
   else if(sample == "Ele_RD_HighPU_C")
        {
	       chain_Electron_RD_HighPU_C(chains);
	          }
   else if(sample == "Ele_RD_HighPU_D")
        {
	       chain_Electron_RD_HighPU_D(chains);
	          }
   else if(sample == "Ele_RD_HighPU_1")
   {
     chain_Electron_RD_HighPU_1(chains);
   }
      else if(sample == "Ele_RD_HighPU_2")
	   {
	          chain_Electron_RD_HighPU_2(chains);
		     }
      else if(sample == "Ele_RD_HighPU_3")
	   {
	          chain_Electron_RD_HighPU_3(chains);
		     }
      else if(sample == "Ele_RD_HighPU_4")
	   {
	          chain_Electron_RD_HighPU_4(chains);
		     }
      else if(sample == "Ele_RD_HighPU_5")
	   {
	          chain_Electron_RD_HighPU_5(chains);
		     }
      else if(sample == "Ele_RD_HighPU_6")
	   {
	          chain_Electron_RD_HighPU_6(chains);
		     }
      else if(sample == "Ele_RD_HighPU_7")
	   {
	          chain_Electron_RD_HighPU_7(chains);
		     }
      else if(sample == "Ele_RD_HighPU_8")
	   {
	          chain_Electron_RD_HighPU_8(chains);
		     }
      else if(sample == "Ele_RD_HighPU_9")
	   {
	          chain_Electron_RD_HighPU_9(chains);
		     }
      else if(sample == "Ele_RD_HighPU_10")
	   {
	          chain_Electron_RD_HighPU_10(chains);
		     }
      else if(sample == "Ele_RD_HighPU_11")
	   {
	          chain_Electron_RD_HighPU_11(chains);
		     }
      else if(sample == "Ele_RD_HighPU_12")
	   {
	          chain_Electron_RD_HighPU_12(chains);
		     }
      else if(sample == "Ele_RD_HighPU_13")
	   {
	          chain_Electron_RD_HighPU_13(chains);
		     }
      else if(sample == "Ele_RD_HighPU_14")
	   {
	          chain_Electron_RD_HighPU_14(chains);
		     }
      else if(sample == "Ele_RD_HighPU_15")
	   {
	          chain_Electron_RD_HighPU_15(chains);
		     }
      else if(sample == "Ele_RD_HighPU_16")
	   {
	          chain_Electron_RD_HighPU_16(chains);
		     }
      else if(sample == "Ele_RD_HighPU_17")
	   {
	          chain_Electron_RD_HighPU_17(chains);
		     }
      else if(sample == "Ele_RD_HighPU_18")
	   {
	          chain_Electron_RD_HighPU_18(chains);
		     }
      else if(sample == "Ele_RD_HighPU_19")
	   {
	          chain_Electron_RD_HighPU_19(chains);
		     }
   else
   {
     cout<<"[SetupTree.h] Nanigorae? "<<endl;
   }
}






