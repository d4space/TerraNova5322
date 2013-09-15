// $Id: wEleNeuFilter.h,v 1.2 2013/08/07 13:08:25 salee Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

//EGamma
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
//#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//Triggers
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "KNUPhy/DataFormats/interface/Lepton.h"
#include "KNUPhy/DataFormats/interface/ZCandidate.h"
#include "KNUPhy/DataFormats/interface/TTbarGenEvent.h"
#include "KNUPhy/DataFormats/interface/TTbarMass.h"
#include "KNUPhy/DataFormats/interface/WLeptNeuCand.h"
#include "KNUPhy/DataFormats/interface/METCandidate.h"
#include "KNUPhy/DataFormats/interface/Maos.h"
#include "KNUPhy/WAnalyzer/interface/wLeptNeuBranchVars.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

//template<typename T1, typename T2>
class wEleNeuFilter : public edm::EDFilter{
 public:
  explicit wEleNeuFilter(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    Channel = iConfig.getUntrackedParameter< std::string >("Channel");
    leptonLabel1_ = iConfig.getParameter<edm::InputTag>("leptonLabel1");
    leptonLabel2_ = iConfig.getParameter<edm::InputTag>("leptonLabel2");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    vertexLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    //applyIso_ = iConfig.getUntrackedParameter<bool>("applyIso",true);
    //oppPair_ = iConfig.getUntrackedParameter<bool>("oppPair",true);
    
    PileUpRD_ = iConfig.getParameter< std::vector<double> >("PileUpRD");
    PileUpMC_ = iConfig.getParameter< std::vector<double> >("PileUpMC");

    TriggerResultsTag = iConfig.getUntrackedParameter<InputTag>		("TriggerResultsTag");
    HLTTriggers = iConfig.getUntrackedParameter< std::vector<std::string> >("HLTTriggers");
    beamSpotInputTag=iConfig.getParameter<edm::InputTag>("beamSpotInputTag");
    rhoIsoInputTag = iConfig.getParameter<edm::InputTag>("rhoIsoInputTag");
    conversionsInputTag=iConfig.getParameter<edm::InputTag>("conversionsInputTag");

    tree = fs->make<TTree>("tree", "Tree for W boson");

    EventData.vtx_isFake = new std::vector<int>;
    EventData.vtx_ndof = new std::vector<int>;
    EventData.vtx_z = new std::vector<double>;
    EventData.vtx_Rho = new std::vector<double>;


    Zs.Lept1_isGlobal= new std::vector<bool>;
    Zs.Lept1_isTrker= new std::vector<bool>;
    Zs.Lept1_pt= new std::vector<double>;
    Zs.Lept1_eta= new std::vector<double>;
    Zs.Lept1_phi= new std::vector<double>;
    Zs.Lept1_px= new std::vector<double>;
    Zs.Lept1_py= new std::vector<double>;
    Zs.Lept1_pz= new std::vector<double>;
    Zs.Lept1_matchStations= new std::vector<int>;
    Zs.Lept1_dB= new std::vector<double>;
    Zs.Lept1_dz= new std::vector<double>;
    Zs.Lept1_globalNormChi2= new std::vector<double>;
    Zs.Lept1_muonHits= new std::vector<double>;
    Zs.Lept1_trkLayers= new std::vector<double>;
    Zs.Lept1_trackerHits= new std::vector<double>;
    Zs.Lept1_pixelHits= new std::vector<double>;
    Zs.Lept1_etaSC= new std::vector<double>;
    Zs.Lept1_phiSC= new std::vector<double>;
    Zs.Lept1_dEtaIn= new std::vector<double>;
    Zs.Lept1_dPhiIn= new std::vector<double>;
    Zs.Lept1_sigmaIEtaIEta= new std::vector<double>;
    Zs.Lept1_HoverE= new std::vector<double>;
    Zs.Lept1_fbrem= new std::vector<double>;
    Zs.Lept1_energyEC= new std::vector<double>;
    Zs.Lept1_Pnorm= new std::vector<double>;
    Zs.Lept1_InvEminusInvP= new std::vector<double>;
    Zs.Lept1_dxy= new std::vector<double>;
    Zs.Lept1_AEff03= new std::vector<double>;
    Zs.Lept1_hasConversion= new std::vector<bool>;
    Zs.Lept1_mHits= new std::vector<int>;
    Zs.Lept1_chIso03= new std::vector<double>;
    Zs.Lept1_chIso04= new std::vector<double>;
    Zs.Lept1_nhIso03= new std::vector<double>;
    Zs.Lept1_nhIso04= new std::vector<double>;
    Zs.Lept1_phIso03= new std::vector<double>;
    Zs.Lept1_phIso04= new std::vector<double>;
    Zs.Lept1_pcIso03= new std::vector<double>;
    Zs.Lept1_pcIso04= new std::vector<double>;
    Zs.Lept1_relIsoCom03= new std::vector<double>;
    Zs.Lept1_relIsoCom04= new std::vector<double>;
    Zs.Lept1_relIsoBeta03= new std::vector<double>;
    Zs.Lept1_relIsoBeta04= new std::vector<double>;
    Zs.Lept1_relIsoRho03= new std::vector<double>;

    Zs.Lept2_isGlobal= new std::vector<bool>;
    Zs.Lept2_isTrker= new std::vector<bool>;
    Zs.Lept2_pt= new std::vector<double>;
    Zs.Lept2_eta= new std::vector<double>;
    Zs.Lept2_phi= new std::vector<double>;
    Zs.Lept2_px= new std::vector<double>;
    Zs.Lept2_py= new std::vector<double>;
    Zs.Lept2_pz= new std::vector<double>;
    Zs.Lept2_matchStations= new std::vector<int>;
    Zs.Lept2_dB= new std::vector<double>;
    Zs.Lept2_dz= new std::vector<double>;
    Zs.Lept2_globalNormChi2= new std::vector<double>;
    Zs.Lept2_muonHits= new std::vector<double>;
    Zs.Lept2_trkLayers= new std::vector<double>;
    Zs.Lept2_trackerHits= new std::vector<double>;
    Zs.Lept2_pixelHits= new std::vector<double>;
    Zs.Lept2_etaSC= new std::vector<double>;
    Zs.Lept2_phiSC= new std::vector<double>;
    Zs.Lept2_dEtaIn= new std::vector<double>;
    Zs.Lept2_dPhiIn= new std::vector<double>;
    Zs.Lept2_sigmaIEtaIEta= new std::vector<double>;
    Zs.Lept2_HoverE= new std::vector<double>;
    Zs.Lept2_fbrem= new std::vector<double>;
    Zs.Lept2_energyEC= new std::vector<double>;
    Zs.Lept2_Pnorm= new std::vector<double>;
    Zs.Lept2_InvEminusInvP= new std::vector<double>;
    Zs.Lept2_dxy= new std::vector<double>;
    Zs.Lept2_AEff03= new std::vector<double>;
    Zs.Lept2_hasConversion= new std::vector<bool>;
    Zs.Lept2_mHits= new std::vector<int>;
    Zs.Lept2_chIso03= new std::vector<double>;
    Zs.Lept2_chIso04= new std::vector<double>;
    Zs.Lept2_nhIso03= new std::vector<double>;
    Zs.Lept2_nhIso04= new std::vector<double>;
    Zs.Lept2_phIso03= new std::vector<double>;
    Zs.Lept2_phIso04= new std::vector<double>;
    Zs.Lept2_pcIso03= new std::vector<double>;
    Zs.Lept2_pcIso04= new std::vector<double>;
    Zs.Lept2_relIsoCom03= new std::vector<double>;
    Zs.Lept2_relIsoCom04= new std::vector<double>;
    Zs.Lept2_relIsoBeta03= new std::vector<double>;
    Zs.Lept2_relIsoBeta04= new std::vector<double>;
    Zs.Lept2_relIsoRho03= new std::vector<double>;

    Zs.diLeptVtxProb = new std::vector<double>;
    Zs.ZMass = new std::vector<double>;
    Zs.phi = new std::vector<double>;
    Zs.eta = new std::vector<double>;
    Zs.pt = new std::vector<double>;
    Zs.px = new std::vector<double>;
    Zs.py = new std::vector<double>;
    Zs.pz = new std::vector<double>;
    Zs.pz = new std::vector<double>;
    Zs.Neut_pt = new std::vector<double>;
    Zs.Neut_phi = new std::vector<double>;
    Zs.Neut_px = new std::vector<double>;
    Zs.Neut_py = new std::vector<double>;
    Zs.Sign=new std::vector<double>; //--(-2), +-(0), ++(2)

    Ws.Lept1_isGlobal=new std::vector<bool>;
    Ws.Lept1_isTrker=new std::vector<bool>;
    Ws.Lept1_pt=new std::vector<double>;
    Ws.Lept1_eta=new std::vector<double>;
    Ws.Lept1_phi=new std::vector<double>;
    Ws.Lept1_px=new std::vector<double>;
    Ws.Lept1_py=new std::vector<double>;
    Ws.Lept1_pz=new std::vector<double>;
    Ws.Lept1_matchStations=new std::vector<int>;
    Ws.Lept1_dB=new std::vector<double>;
    Ws.Lept1_dz=new std::vector<double>;
    Ws.Lept1_globalNormChi2=new std::vector<double>;
    Ws.Lept1_muonHits=new std::vector<double>;
    Ws.Lept1_trkLayers=new std::vector<double>;
    Ws.Lept1_trackerHits=new std::vector<double>;
    Ws.Lept1_pixelHits=new std::vector<double>;
    Ws.Lept1_etaSC=new std::vector<double>;
    Ws.Lept1_phiSC=new std::vector<double>;
    Ws.Lept1_dEtaIn=new std::vector<double>;
    Ws.Lept1_dPhiIn=new std::vector<double>;
    Ws.Lept1_sigmaIEtaIEta=new std::vector<double>;
    Ws.Lept1_HoverE=new std::vector<double>;
    Ws.Lept1_fbrem=new std::vector<double>;
    Ws.Lept1_energyEC=new std::vector<double>;
    Ws.Lept1_Pnorm=new std::vector<double>;
    Ws.Lept1_InvEminusInvP=new std::vector<double>;
    Ws.Lept1_dxy=new std::vector<double>;
    Ws.Lept1_AEff03=new std::vector<double>;
    Ws.Lept1_chIso03=new std::vector<double>;
    Ws.Lept1_chIso04=new std::vector<double>;
    Ws.Lept1_nhIso03=new std::vector<double>;
    Ws.Lept1_nhIso04=new std::vector<double>;
    Ws.Lept1_phIso03=new std::vector<double>;
    Ws.Lept1_phIso04=new std::vector<double>;
    Ws.Lept1_pcIso03=new std::vector<double>;
    Ws.Lept1_pcIso04=new std::vector<double>;
    Ws.Lept1_relIsoCom03=new std::vector<double>;
    Ws.Lept1_relIsoCom04=new std::vector<double>;
    Ws.Lept1_relIsoBeta03=new std::vector<double>;
    Ws.Lept1_relIsoBeta04=new std::vector<double>;
    Ws.Lept1_relIsoRho03=new std::vector<double>;
    Ws.Lept1_hasConversion=new std::vector<bool>;
    Ws.Lept1_mHits=new std::vector<int>;

    Ws.W_invm = new std::vector<double>;
    Ws.Neut_pt = new std::vector<double>;
    Ws.Neut_phi = new std::vector<double>;
    Ws.Neut_px = new std::vector<double>;
    Ws.Neut_py = new std::vector<double>;
    Ws.W_pt = new std::vector<double>;
    Ws.W_eta = new std::vector<double>;
    Ws.W_phi = new std::vector<double>;
    Ws.W_px = new std::vector<double>;
    Ws.W_py = new std::vector<double>;
    Ws.W_pz = new std::vector<double>;
    Ws.W_Mt = new std::vector<double>;
    Ws.W_Acop = new std::vector<double>;
    Ws.W_Charge = new std::vector<double>;
    //Ws.Lptn_global = new std::vector<int>;

    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    h_lept1_pt   = fs->make<TH1F>( "h_lept1_pt"  , "p_{t}", 50,  0., 100. );
    h_lept2_pt   = fs->make<TH1F>( "h_lept2_pt"  , "p_{t}", 50,  0., 100. );
    h_Zmass      = fs->make<TH1F>( "h_Zmass", "Z Mass", 300, 0., 300. );
    h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
    h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);
    h_npileupin = fs->make<TH1F>( "h_npileupin", "npileupin", 30, 0, 30);
    h_npileup = fs->make<TH1F>( "h_npileup", "npileup", 30, 0, 30);
    h_nvertex = fs->make<TH1F>( "h_nvertex", "nvertex", 30, 0, 30);

    //Z = new std::vector<Ky::ZCandidate>();
    lepton1 = new std::vector<Ky::Lepton>();
    lepton2 = new std::vector<Ky::Lepton>();
    pfMet = new std::vector<Ky::METCandidate>();
    //WLeptNeuCand_v = new std::vector<Ky::WLeptNeuCand>();
    //W_invm = new std::vector<double>;
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
}
  ~wEleNeuFilter()
  {
  }
 private:
  virtual void beginJob()
{
    std::vector< float > PuMC ;
    std::vector< float > PuReal;
    //for( int i=0; i< 25; ++i)
    for( int i=0; i< 60; ++i) {
      PuReal.push_back((float)PileUpRD_[i]);
      PuMC.push_back((float)PileUpMC_[i]);
    }
    LumiWeights_ = edm::LumiReWeighting(PuMC, PuReal);

    PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
    PShiftUp_ = reweight::PoissonMeanShifter(0.5);

    bookTree();
}
  //virtual bool beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
  virtual bool beginRun( edm::Run& iRun, const edm::EventSetup& iSetup)
{
  //initialization
  FullHLTTriggerNames.clear();
  HLTVersions.clear();
  //Trigger information
  if(HLTTriggers.size() > 0)
  {
    bool changed(true);
    if(HltConfig.init(iRun,iSetup,TriggerResultsTag.process(),changed))
    {
      // if init returns TRUE, initialization has succeeded
      TrigIndex.clear();
      for(unsigned int i(0); i<HLTTriggers.size(); i++)
      {
        //find the full name with version number in this particular menu.
	FullHLTTriggerNames.push_back(HLTTriggers[i]);
	HLTVersions.push_back(0);
	for(unsigned int iv(1);iv<10;iv++)
	{
	  std::stringstream trigstream;
	  trigstream<<HLTTriggers[i]<<"_v"<<iv;
	  if(HltConfig.triggerIndex(trigstream.str())<HltConfig.size())
	  {
	    FullHLTTriggerNames[i] = trigstream.str();
	    HLTVersions[i] = iv;
	  }
	}
	cout<<FullHLTTriggerNames[i]<<" "<<HltConfig.triggerIndex(FullHLTTriggerNames[i])<<endl;
	TrigIndex.push_back(HltConfig.triggerIndex(FullHLTTriggerNames[i]));
	if(TrigIndex[i] == HltConfig.size())
	{
	  string errorMessage="Requested TriggerName does not exist! -- "+HLTTriggers[i]+"\n";
	}
      }
      if(changed)
      {
	std::cout<<"Run: "<<iRun.run()<<".....Changed HLTConfig"<<std::endl;
      }
    }
    else
    {
      cout<<" HLT config extraction failure with process name "<<TriggerResultsTag.process()<<std::endl;
    }
  }
  return true;
}
virtual bool endRun(const edm::Run&, const edm::EventSetup&)
{
  return true;
}

virtual void bookTree()
{
  EventData.Register(tree);
  for(unsigned int i(0); i<HLTTriggers.size(); i++)
  {
    HLTData.TrigNames[i]=HLTTriggers[i];
    HLTData.Register(tree,i);
  }
  Zs.Register(tree);
  Ws.Register(tree);
}
//  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
virtual void GetHLTResults(edm::Event &iEvent, const edm::EventSetup& iSetup)
{

  //Trigger Information----
  Handle<TriggerResults> trgRsltsHandle;
  //cout<<"HLTTriggers size: "<<HLTTriggers.size()<<" HLTVersions size: "<<HLTVersions.size()<<endl;
  if( (HLTTriggers.size()>0) && (HLTTriggers.size() == HLTVersions.size()))
  {
    int ErrFlag(0);
    iEvent.getByLabel(TriggerResultsTag,trgRsltsHandle);
    if(!trgRsltsHandle.isValid())
    {
      cout<<"TriggerResults "<<"TriggerResultsTag"<<" not available!"<<endl;
      ErrFlag= -1;
    }
    for(unsigned int i(0); i<HLTTriggers.size(); i++)
    {
      //cout<<"HLT version : "<<HLTVersions[i]<<endl;
      HLTData.trigState[i].version = HLTVersions[i];
      HLTData.trigState[i].fired = ErrFlag;
      HLTData.trigState[i].L1prescale = -1;
      HLTData.trigState[i].HLTprescale = -1;
      bool acceptHLT=false;
      if(ErrFlag>-1)
      {
	//here we play this game of adding "v..." to the requested trigger
	//and hunt for the version number of the thing...
	//and there are a lot of try and open catches here because HLT code
	//seems to want to segfault at the slightest provocation
	//bool waslegal(false);
	string theRealTriggername;
	try{
	  unsigned int trIndex=HltConfig.triggerIndex(FullHLTTriggerNames[i]);
	  if(HltConfig.size() != trIndex)
	  {
	    acceptHLT = trgRsltsHandle->accept(trIndex);
	  }
	  else
	  {
	    acceptHLT=false;
	    HLTData.trigState[i].fired= -1;
	  }
	}
	catch(...)
	{
	  acceptHLT=false;
	  HLTData.trigState[i].fired=-1;
	}
	if(acceptHLT)
	{
	  //cout<<"HLT fired hahahahahhahahhaha"<<endl;
	  HLTData.trigState[i].fired=1;
	}
	std::pair<int,int>prescalePair;
	try
	{
	  prescalePair=HltConfig.prescaleValues(iEvent,iSetup,FullHLTTriggerNames[i]);
	  //cout<<"L1 prescale: "<<prescalePair.first<<" HLT prescale: "<<prescalePair.second<<endl;;
	  HLTData.trigState[i].L1prescale=prescalePair.first;
	  HLTData.trigState[i].HLTprescale=prescalePair.second;
	}
	catch(...)
	{
	  HLTData.trigState[i].L1prescale=-1;
	  HLTData.trigState[i].HLTprescale=-1;
	}
      }//ErrFlag

    }
  }
  else
  {
    cout<<"HLTTRiggers is 0 or HLTVersions.size is not the same"<<endl;
  }


}
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup);
  void clear()
{
  EventData.EVENT	= -999;
  EventData.RUN		= -999;
  EventData.LUMI	= -999;
  EventData.npileup	= -999;
  EventData.rhoIso	= -999;
  //EventData.nvertex	= -999;
  EventData.weightin	= -999;
  EventData.weight	= -999;
  EventData.weightplus	= -999;
  EventData.weightminus	= -999;
  EventData.vtx_isFake->clear();
  EventData.vtx_ndof->clear();
  EventData.vtx_z->clear();
  EventData.vtx_Rho->clear();

  Zs.Lept1_isGlobal->clear();
  Zs.Lept1_isTrker->clear();
  Zs.Lept1_pt->clear();
  Zs.Lept1_eta->clear();
  Zs.Lept1_phi->clear();
  Zs.Lept1_px->clear();
  Zs.Lept1_py->clear();
  Zs.Lept1_pz->clear();
  Zs.Lept1_matchStations->clear();
  Zs.Lept1_dB->clear();
  Zs.Lept1_dz->clear();
  Zs.Lept1_globalNormChi2->clear();
  Zs.Lept1_muonHits->clear();
  Zs.Lept1_trkLayers->clear();
  Zs.Lept1_trackerHits->clear();
  Zs.Lept1_pixelHits->clear();
  Zs.Lept1_etaSC->clear();
  Zs.Lept1_phiSC->clear();
  Zs.Lept1_dEtaIn->clear();
  Zs.Lept1_dPhiIn->clear();
  Zs.Lept1_sigmaIEtaIEta->clear();
  Zs.Lept1_HoverE->clear();
  Zs.Lept1_fbrem->clear();
  Zs.Lept1_energyEC->clear();
  Zs.Lept1_Pnorm->clear();
  Zs.Lept1_InvEminusInvP->clear();
  Zs.Lept1_dxy->clear();
  Zs.Lept1_AEff03->clear();
  Zs.Lept1_chIso03->clear();
  Zs.Lept1_chIso04->clear();
  Zs.Lept1_nhIso03->clear();
  Zs.Lept1_nhIso04->clear();
  Zs.Lept1_phIso03->clear();
  Zs.Lept1_phIso04->clear();
  Zs.Lept1_pcIso03->clear();
  Zs.Lept1_pcIso04->clear();
  Zs.Lept1_relIsoCom03->clear();
  Zs.Lept1_relIsoCom04->clear();
  Zs.Lept1_relIsoBeta03->clear();
  Zs.Lept1_relIsoBeta04->clear();
  Zs.Lept1_relIsoRho03->clear();
  Zs.Lept1_hasConversion->clear();
  Zs.Lept1_mHits->clear();

  Zs.Lept2_isGlobal->clear();
  Zs.Lept2_isTrker->clear();
  Zs.Lept2_pt->clear();
  Zs.Lept2_eta->clear();
  Zs.Lept2_phi->clear();
  Zs.Lept2_px->clear();
  Zs.Lept2_py->clear();
  Zs.Lept2_pz->clear();
  Zs.Lept2_matchStations->clear();
  Zs.Lept2_dB->clear();
  Zs.Lept2_dz->clear();
  Zs.Lept2_globalNormChi2->clear();
  Zs.Lept2_muonHits->clear();
  Zs.Lept2_trkLayers->clear();
  Zs.Lept2_trackerHits->clear();
  Zs.Lept2_pixelHits->clear();
  Zs.Lept2_etaSC->clear();
  Zs.Lept2_phiSC->clear();
  Zs.Lept2_dEtaIn->clear();
  Zs.Lept2_dPhiIn->clear();
  Zs.Lept2_sigmaIEtaIEta->clear();
  Zs.Lept2_HoverE->clear();
  Zs.Lept2_fbrem->clear();
  Zs.Lept2_energyEC->clear();
  Zs.Lept2_Pnorm->clear();
  Zs.Lept2_InvEminusInvP->clear();
  Zs.Lept2_dxy->clear();
  Zs.Lept2_AEff03->clear();
  Zs.Lept2_hasConversion->clear();
  Zs.Lept2_mHits->clear();
  Zs.Lept2_chIso03->clear();
  Zs.Lept2_chIso04->clear();
  Zs.Lept2_nhIso03->clear();
  Zs.Lept2_nhIso04->clear();
  Zs.Lept2_phIso03->clear();
  Zs.Lept2_phIso04->clear();
  Zs.Lept2_pcIso03->clear();
  Zs.Lept2_pcIso04->clear();
  Zs.Lept2_relIsoCom03->clear();
  Zs.Lept2_relIsoCom04->clear();
  Zs.Lept2_relIsoBeta03->clear();
  Zs.Lept2_relIsoBeta04->clear();
  Zs.Lept2_relIsoRho03->clear();

  Zs.diLeptVtxProb->clear();
  Zs.ZMass->clear();
  Zs.phi->clear();
  Zs.eta->clear();
  Zs.pt->clear();
  Zs.px->clear();
  Zs.py->clear();
  Zs.pz->clear();
  Zs.Neut_pt->clear();
  Zs.Neut_phi->clear();
  Zs.Neut_px->clear();
  Zs.Neut_py->clear();
  Zs.Sign->clear(); //--(-2), +-(0), ++(2)

  Ws.Lept1_isGlobal->clear();
  Ws.Lept1_isTrker->clear();
  Ws.Lept1_pt->clear();
  Ws.Lept1_eta->clear();
  Ws.Lept1_phi->clear();
  Ws.Lept1_px->clear();
  Ws.Lept1_py->clear();
  Ws.Lept1_pz->clear();
  Ws.Lept1_matchStations->clear();
  Ws.Lept1_dB->clear();
  Ws.Lept1_dz->clear();
  Ws.Lept1_globalNormChi2->clear();
  Ws.Lept1_muonHits->clear();
  Ws.Lept1_trkLayers->clear();
  Ws.Lept1_trackerHits->clear();
  Ws.Lept1_pixelHits->clear();
  Ws.Lept1_etaSC->clear();
  Ws.Lept1_phiSC->clear();
  Ws.Lept1_dEtaIn->clear();
  Ws.Lept1_dPhiIn->clear();
  Ws.Lept1_sigmaIEtaIEta->clear();
  Ws.Lept1_HoverE->clear();
  Ws.Lept1_fbrem->clear();
  Ws.Lept1_energyEC->clear();
  Ws.Lept1_Pnorm->clear();
  Ws.Lept1_InvEminusInvP->clear();
  Ws.Lept1_dxy->clear();
  Ws.Lept1_AEff03->clear();
  Ws.Lept1_chIso03->clear();
  Ws.Lept1_chIso04->clear();
  Ws.Lept1_nhIso03->clear();
  Ws.Lept1_nhIso04->clear();
  Ws.Lept1_phIso03->clear();
  Ws.Lept1_phIso04->clear();
  Ws.Lept1_pcIso03->clear();
  Ws.Lept1_pcIso04->clear();
  Ws.Lept1_relIsoCom03->clear();
  Ws.Lept1_relIsoCom04->clear();
  Ws.Lept1_relIsoBeta03->clear();
  Ws.Lept1_relIsoBeta04->clear();
  Ws.Lept1_relIsoRho03->clear();
  Ws.Lept1_hasConversion->clear();
  Ws.Lept1_mHits->clear();


  Ws.W_invm->clear();
  Ws.Neut_pt->clear();
  Ws.Neut_phi->clear();
  Ws.Neut_px->clear();
  Ws.Neut_py->clear();
  Ws.W_pt->clear();
  Ws.W_eta->clear();
  Ws.W_phi->clear();
  Ws.W_px->clear();
  Ws.W_py->clear();
  Ws.W_pz->clear();
  Ws.W_Mt->clear();
  Ws.W_Acop->clear();
  Ws.W_Charge->clear();



  lepton1->clear();
  lepton2->clear();
  pfMet->clear();
  met->clear();
  jetspt30->clear();

    //weight = 1.0;
    //weightin = 1.0;
    //weightplus = 1.0;
    //weightminus = 1.0;

    dphimetlepton1 = -999;  
    dphimetlepton2 = -999;  
    dphimetjet1 = -999;
    dphimetjet2 = -999;

    genttbarM = -999;
}
  virtual bool endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup)
{
  //cout<<"end lumi "<<endl;
    if(useEventCounter_){
      for(unsigned int i=0;i<filters_.size();++i) {
        std::string name = filters_[i];
        edm::Handle<edm::MergeableCounter> numEventsCounter;
        lumi.getByLabel(name, numEventsCounter);
        if( numEventsCounter.isValid()){
          tmp->AddBinContent(i+1, numEventsCounter->value);
          tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
        }
      }
    }
    return true;
}
  bool checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2)
  {

    bool overlap = false;
    if( reliso1 < relIso1_ ) {
      overlap = dRval1 < 0.4 ;
      if(overlap) return overlap;
    }

    if( reliso2 < relIso2_ ) {
      overlap = dRval2 < 0.4 ;
      if(overlap) return overlap;
    }

    return overlap;

}

  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact )
{
    double proEta = proObj.eta();
    double proPhi = proObj.phi();
    double proPt  = proObj.pt();
    double pasEta = pasObj.eta();
    double pasPhi = pasObj.phi();
    double pasPt  = pasObj.pt();

    double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);
    double dPtRel = 999.0;
    if( proPt > 0.0 ) dPtRel = fabs( pasPt - proPt )/proPt;
    // If we are comparing two objects for which the candidates should
    // be exactly the same, cut hard. Otherwise take cuts from user.
    if( exact ) return ( dRval < 1e-3 && dPtRel < 1e-3 );
    else        return ( dRval < 0.025 && dPtRel < 0.025 );
}

// Variables ==================================================
// ============================================================
  typedef pat::JetCollection::const_iterator JI;

  std::string Channel;

  edm::InputTag leptonLabel1_;
  edm::InputTag leptonLabel2_;
  edm::InputTag muonLabel2_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag TriggerResultsTag;
  edm::InputTag rhoIsoInputTag;
  edm::InputTag conversionsInputTag;
  edm::InputTag beamSpotInputTag;
  //Handle
  edm::Handle<double>rhoIso_h;
  edm::Handle<reco::ConversionCollection>conversions_h;
  edm::Handle<reco::BeamSpot> beamSpot_h;
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;

  std::vector<std::string> filters_;

  HLTConfigProvider HltConfig;
  std::vector<std::string> HLTTriggers;
  std::vector<unsigned int> TrigIndex;
  std::vector<std::string> FullHLTTriggerNames;
  std::vector<int> HLTVersions;

  bool metStudy_;
  bool useEventCounter_;
  
  // relIso
  double relIso1_;
  double relIso2_;
  // btag Discriminator
  std::vector<std::string> bTagAlgos_;
  std::vector<std::string> bTagNames_;
  std::vector<double> bTagCutValues_;
  std::vector<bool> bTagIsCutMin_;
  std::vector<int> nbjetsCache_;
  //std::string bTagAlgo_;
  //double minBTagValue_;

  edm::Service<TFileService> fs;
  TTree* tree;
  EventBranches	EventData;
  TrigBranches	HLTData;
  Zboson	Zs;
  Wboson	Ws;

  TH1F * tmp;
  TH1F * h_lept1_pt;
  TH1F * h_lept2_pt;
  TH1F * h_Zmass;
  TH1F * h_MET;
  TH1F * h_jetpt30_multi;
  TH1F * h_npileupin;
  TH1F * h_npileup;
  TH1F * h_nvertex;

  //std::vector<Ky::ZCandidate>* Z;
  std::vector<Ky::Lepton>* lepton1;
  std::vector<Ky::Lepton>* lepton2;
  std::vector<Ky::METCandidate>* pfMet;
  //std::vector<Ky::WLeptNeuCand>* WLeptNeuCand_v;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jetspt30;

  double MET;
  double dphimetlepton1;
  double dphimetlepton2;
  double dphimetjet1;
  double dphimetjet2;

  double discr;

  double genttbarM;




  // ----------member data ---------------------------

  //add run event data
  //unsigned int EVENT;
  //unsigned int RUN;
  //unsigned int LUMI;
  //unsigned int npileup;
  //unsigned int nvertex;
  //double weightin;
  //double weight;
  //double weightplus;
  //double weightminus;

  edm::LumiReWeighting LumiWeights_;

  std::vector<double> PileUpRD_;
  std::vector<double> PileUpMC_;

  reweight::PoissonMeanShifter PShiftUp_;
  reweight::PoissonMeanShifter PShiftDown_;


  double Lept1_chIso03,Lept1_chIso04;
  double Lept2_chIso03,Lept2_chIso04;
  double Lept1_nhIso03,Lept1_nhIso04;
  double Lept2_nhIso03,Lept2_nhIso04;
  double Lept1_phIso03,Lept1_phIso04;
  double Lept2_phIso03,Lept2_phIso04;
  double Lept1_pcIso03,Lept1_pcIso04;
  double Lept2_pcIso03,Lept2_pcIso04;
  bool Lept1_isGlobal, Lept2_isGlobal;
  bool Lept1_isTrker,  Lept2_isTrker;
  double Lept1_globalNormChi2,Lept2_globalNormChi2;
  double Lept1_muonHits,Lept2_muonHits;
  double Lept1_trackerHits,Lept2_trackerHits;
  double Lept1_dxy,Lept1_dz;
  double Lept2_dxy,Lept2_dz;
  double Lept1_trkLayers,Lept2_trkLayers;
  double Lept1_pixelHits,Lept2_pixelHits;
  int Lept1_matchStations, Lept2_matchStations;
  double Lept1_relIsoCom03,Lept1_relIsoCom04;
  double Lept2_relIsoCom03,Lept2_relIsoCom04;
  double Lept1_relIsoBeta03,Lept1_relIsoBeta04;
  double Lept2_relIsoBeta03,Lept2_relIsoBeta04;
  double Lept1_relIsoRho03;
  double Lept2_relIsoRho03;
  double Lept1_pt, Lept1_eta,Lept1_etaSC,Lept1_phi,Lept1_phiSC,Lept1_dB, Lept1_px, Lept1_py, Lept1_pz;
  double Lept2_pt, Lept2_eta,Lept2_etaSC,Lept2_phi,Lept2_phiSC,Lept2_dB, Lept2_px, Lept2_py, Lept2_pz;

  double rhoIso;
  double Lept1_dEtaIn,Lept1_dPhiIn,Lept1_sigmaIEtaIEta;
  double Lept2_dEtaIn,Lept2_dPhiIn,Lept2_sigmaIEtaIEta;
  double Lept1_HoverE,Lept1_fbrem;
  double Lept2_HoverE,Lept2_fbrem;
  double Lept1_energyEC,Lept1_Pnorm,Lept1_InvEminusInvP;
  double Lept2_energyEC,Lept2_Pnorm,Lept2_InvEminusInvP;
  double Lept1_AEff03;
  double Lept2_AEff03;
  bool   Lept1_hasConversion;
  bool   Lept2_hasConversion;
  int    Lept1_mHits;
  int    Lept2_mHits;

};

