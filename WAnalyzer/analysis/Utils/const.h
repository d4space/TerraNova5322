#define NWptBinPlus 14
//#define NWqaBinPlus 25
#define NWqaBinPlus 12
//#define NWqaBins 22
//#define NWqaBins 25 
#define NWqaBins 12 
//#define NWptBinPlus 14
//#define NWptBinPlus 18 //Pt bins + 1 to include total ; the total is 0th bin
#define NBINS_1 60 
#define NBINS_2 30
#define NBINS_3 30
//#define NBINS_1 30
//#define NBINS_2 15
//#define NBINS_3 15
#define METMAX_1 100
#define METMAX_2 200
#define METMAX_3 300
#define NBIN_PT_DIVIDER_1and2 9 //PtBin less than this W_pt range is [0,100]
#define NBIN_PT_DIVIDER_2and3 12 //PtBin less than this W_pt range is [0,200] otherwise [0,300]
#define NOQCD_PT_UP 14 //PtBin less than this include QCD
#define NOQCD_PT_DOWN 1 //PtBin greater or equal to this include QCD
#define NBINS_LANDAU 2 //LANDAU QCD less than this bin
#define NBINS_Eta 50
#define METMAX_Eta 100
//All of these come up with doube Bins at WMuNeu.C
//
//Recoil related constants
#define u1Bin 16
#define u2Bin 16
//#define EtaBin 22
//#define EtaBin 25
#define EtaBin 12
#define WqaBinEta 24
#define ReCoil_MassLow 60
#define ReCoil_MassHigh 120
#define lept1eta 12
#define lept2eta 12
//Written on WMuNeu.h=============
// RecoBins[0]	= 0.;
// RecoBins[1]	= 5.;
// RecoBins[2]	= 10.;
// RecoBins[3]	= 15.;
// RecoBins[4]	= 20.;
// RecoBins[5]	= 25.;
// RecoBins[6]	= 30.;
// RecoBins[7]	= 35.;
// RecoBins[8]	= 40.;
// RecoBins[9]	= 50.;
// RecoBins[10]	= 60.;
// RecoBins[11]	= 70.;
// RecoBins[12]	= 80.;
// RecoBins[13]	= 90.;
//==================
//Lepton scale smear
//==================
#define ScElCombiBins  21	
#define ScElCombiBinsHighPU  66	
#define ScMuCombiBins  15
#define ScaleBins	6
#define ScaleBinsHighPU	11
//#define ScaleBins	51
#define ScaleL	0.9
#define ScaleH	1.05
#define SmearL	0.001
#define SmearH	2.00

#define Lumi_LowPU 18.977 //pb
// N = L*Sigma*eff -> L = N/(Sigma*eff)

//NNLO cross section
//#define LumiWeight_Muon_WpToMuNu_S8   (18.977*1*7322.0/935446) // RDLumi/MC Lum
//#define LumiWeight_Muon_WmToMuNu_S8   (18.977*1*5181.0/1.97346e6)
//#define LumiWeight_Ele_WpToEleNu_S8   (18.977*1*7322.0/2401905)
//#define LumiWeight_Ele_WmToEleNu_S8   (18.977*1*5181.0/2127666)

//NLO cross section
#define LumiWeight_Muon_WpToMuNu_S8   (18.977*1*6702.0/935446) // RDLumi/MC Lum
#define LumiWeight_Muon_WmToMuNu_S8   (18.977*1*4697.0/1.97346e6)
#define LumiWeight_Ele_WpToEleNu_S8   (18.977*1*6702.0/2401905)
#define LumiWeight_Ele_WmToEleNu_S8   (18.977*1*4697.0/2127666)


namespace GenType
{
  enum{
    kElectron   = 11,
    kMuon       = 13,
    kTau        = 15,
    kTauElectron= 150011,
    kTauMuon    = 150013,
    kGamma	= 22,
    kZ          = 23,
    kW          = 24,
    kHiggs      = 25,
    kWW         = 24024,
    kVZ         = 26023,
    kZgamma     = 23022,
    kWgamma     = 24022
  };
}
