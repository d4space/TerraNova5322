{
  TChain *myChain = new TChain("TT2Hadron/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("TT2HadNT");
}
