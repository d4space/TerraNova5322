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

   WpT(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",int etaRange_=-999);//Electron
   ~WpT();
   virtual void     Loop();
   void		Init(TTree *tree);
protected:
   double Nselected4bin[NwPtBin];
};

#endif

#ifdef WpT_cxx

void WpT::Init(TTree *tree)
{
  for(int i(0);i<NwPtBin;i++)
  {
    Nselected4bin[i]=0;
  }
}

WpT::WpT(TTree *WpTTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_, int etaRange_) :
WLepNeu::WLepNeu(WpTTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_, etaRange_)
{
  Init(WLepTree);
}

WpT::~WpT()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WpT_cxx


