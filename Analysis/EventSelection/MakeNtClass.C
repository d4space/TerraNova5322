{
  TChain *myChain = new TChain("WMuNeu/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  //myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->Add("/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToMuMu/wNTuple_1.root");
  //myChain->MakeClass("WlnuNT");
  myChain->MakeClass("Wlnu12LoNT");
}
