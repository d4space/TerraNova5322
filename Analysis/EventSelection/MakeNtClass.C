{
  TChain *myChain = new TChain("WZ3LNu/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("WZ3LNT");
}
