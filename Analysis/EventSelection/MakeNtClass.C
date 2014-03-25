{
  TChain *myChain = new TChain("WW/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("WWNT");
}
