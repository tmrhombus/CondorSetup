#include "helperDisplacedDijets.C"
#include "helperDisplacedDijetTriggers.C"

void dumpMacro(const char* ifname=
	       //"root://cmseos.fnal.gov//store/group/lpchbb/mwalker/2016/DisplacedDijet/SingleMuon/Run2016G-PromptReco-v1_AOD/161019_214744/0000/results_999.root"
	       //"root://cmseos.fnal.gov//store/group/lpchbb/mwalker/2016/DisplacedDijet/SingleElectron/Run2016G-PromptReco-v1_AOD/161019_214728/0004/results_4000.root"
	       "root://cmseos.fnal.gov//store/user/lnujj/noreplica/kreis/2016/DisplacedDijet/WminusH_HToSSTo4Tau_WToLNu_MH-125_MS-7_ctauS-0p05_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16DR80-premix_withHLT_80X_mcRun2_asymptotic_v14-v1_AODSIM/161027_224930/0000/results_1.root"
		  , const char* ofname="exampleAnalyzed.root"
		  , bool isSignal = false
		  , int mode = 0
		       , bool isMC = false
		  , int maxEvents = 1000000
		  , const char* json = "/home/mwalker/golden_246908-260627_20151120.txt"
)
{
  TChain* tree = new TChain("tree");
  TString input=ifname;
  //input += "/*.root";
  tree->Add(input);

  FlatTreeReader* reader = new FlatTreeReader(tree);

  AdvancedHandler* handler = new AdvancedHandler(ofname,reader);

  AnalysisTreeWriter* writer = new AnalysisTreeWriter(handler,"treeR");

  handler->setWriter(writer);

  ////////////////////////////////////////////////////
  //Setup some products jets, electrons, muons, etc//
  ///////////////////////////////////////////////////
  setupProducts(handler,isSignal);
  //handler->addProductCut("goodSignalJets","fromSecondary");

  //////////////////////
  //Add some variables//
  //////////////////////
  setupVariables(handler);
  setupListVariablesAndHistograms(handler);
  setupTriggers(handler);
  //setupListMaxVariablesAndHistograms(handler);
  if(isMC)setupMC(handler);
  //else handler->readGoodRunLumiFromJSON(TString(json));

  ////////////////////////
  //Add some signatures//
  //////////////////////
  //handler->addSignature("SigMET150","")
  //  ->addCut("MET150")
  //  ;

  //////////////////////////
  //Create some histograms//
  //////////////////////////
  //addHistograms(handler);

  //////////////////////////////////
  //Final bookkeeping and execution//
  ///////////////////////////////////

  //handler->setMode("nEntryHigh",maxEvents);
  handler->setMode("nEntryLow",1);
  handler->setMode("nEntryHigh",2);
  handler->setDebugMode(true);
  handler->addPrintModule(new PrintModuleEverything("everything"));

  handler->initSignatures();
  handler->eventLoop();
  //handler->eventLoop(1,24248);
  handler->finishSignatures();

  cout<<"Done, exiting ...."<<endl;
}
