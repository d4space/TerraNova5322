{
   //gSystem->Load("libRooFit") ;
   //gSystem->Load("libMinuit") ;
   //gSystem->Load("libRooFitCore") ;
   //gSystem->AddIncludePath("-I/d2/scratch/khakim/root/include/root");
    // using namespace RooFit;
  /*******************
  if(gSystem->Getenv("CMSSW_VERSION")) {
     cout << endl;
     cout << " *** RooFit version in CMSSW is too old! ***" << endl;
     cout << "  Please use a non-CMSSW environment." << endl;
     cout << endl;
     
  }
  else {
  ******************/
    cout<<"compile library ================="<<endl;
    gROOT->Macro("../Utils/RooVoigtianShape.cc+");
    gROOT->Macro("../Utils/RooCMSShape.cc+");

    gROOT->Macro("../Utils/CPlot.cc++");
    gROOT->Macro("../Utils/MitStyleRemix.cc++");  
    cout<<"compile done================="<<endl;
  //}
               
  // Show which process needs debugging
  gInterpreter->ProcessLine(".! ps |grep root.exe");
}
