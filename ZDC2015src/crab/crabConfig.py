from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'HIRun2015-PromptReco-v1_YYYYMMDD'
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName = 'RunForwardAnalyzer_PbPb2015_all.py'

config.Data.inputDataset = '/HIExpressPhysics/HIRun2015-Express-v1/FEVT'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 1000
config.Data.publication = False
# This string is used to construct the output dataset name
config.Data.outputDatasetTag = 'HIExpress_HIRun2015-v1_HIL1MinimumBiasHFstarTrig'
#config.outputFiles  = 'ForwardAnalyzerRun262694_ZeroBiasPromptReco_HF.root' #not necessary

# These values only make sense for processing data
#    Select input data based on a lumi mask
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#    Select input data based on run-ranges
config.Data.runRange = '262811'

# Where the output files will be transmitted to
config.Site.storageSite = 'T2_US_MIT'