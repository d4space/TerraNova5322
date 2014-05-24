{
  //TChain *myChain = new TChain("WMuNeu/tree");
  TChain *myChain = new TChain("WAcceptanceMuon/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/W_Ntuple2012LowPU/AcceptanceFSR/WpToMuNu/wAcceptance_1_1_FGW.root");
  //myChain->Add("/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/WpToMuNu/wNTuple_1.root");
  //myChain->Add("/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V22/WpToMuNu/wNTuple_1.root");
  //myChain->MakeClass("WlnuNT");
  myChain->MakeClass("Wlnu12LoNT");
}
