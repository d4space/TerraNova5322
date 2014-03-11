{
  TChain *myChain = new TChain("MonoJet/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("MonoJetNT");
}
