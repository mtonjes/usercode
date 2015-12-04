from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'HIRun2015-PromptReco-v1_YYYYMMDD'
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName = 'RunForwardAnalyzer_PbPb2015_262694_HF.py'

config.Data.inputDataset = '/HIMinimumBias1/HIRun2015-PromptReco-v1/AOD'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.publication = False
# This string is used to construct the output dataset name
config.Data.outputDatasetTag = 'HIZeroBias1_HIRun2015-PromptReco-v1_AOD_3pmEST'
#config.outputFiles  = 'ForwardAnalyzerRun262694_ZeroBiasPromptReco_HF.root' #not necessary

# These values only make sense for processing data
#    Select input data based on a lumi mask
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#    Select input data based on run-ranges
config.Data.runRange = '262694'

# Where the output files will be transmitted to
config.Site.storageSite = 'T2_US_MIT'