//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WpT/tree/
//////////////////////////////////////////////////////////
//$Log: WpT.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WpT_h
#define WpT_h

#include "WLepNeu.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WpT: public WLepNeu {
public :
   WpT(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~WpT();
   virtual void     Loop();
protected:
   void Nselected4Bin();
   int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int WbestSelect();
   // Member variables
   int mIdxWcan;
   double mNselected4Bin[NwPtBin];
   double mNmetA[NWptBinPlus];
   double mNmetB[NWptBinPlus];
   double mNmetAp[NWptBinPlus];
   double mNmetBp[NWptBinPlus];
   double mNmetAm[NWptBinPlus];
   double mNmetBm[NWptBinPlus];
};

#endif

#ifdef WpT_cxx


WpT::WpT(TTree *WpTTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
WLepNeu::WLepNeu(WpTTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
}

WpT::~WpT()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WpT_cxx


