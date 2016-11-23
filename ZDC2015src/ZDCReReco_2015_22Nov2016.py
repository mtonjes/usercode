# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 -n 1000 --conditions auto:run2_data -s RAW2DIGI,L1Reco,RECO --datatier RECO --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --eventcontent RECO --magField AutoFromDBCurrent --no_exec --scenario pp
import FWCore.ParameterSet.Config as cms

process = cms.Process('ReRECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
# Event selection recommendations (not final)
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Analyzers.ForwardAnalyzer.HIClusterCompatibilityFilter_cfi') # manually changed
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:pPb_MB_RAW.root')
    
    	#'file:USC_261664.root')
        #'root://xrootd.ba.infn.it//store/data/Run2015A/ZeroBias1/RAW/v1/000/247/324/00000/92067870-580D-E511-940D-02163E013891.root')
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/0002B478-ECA7-E511-9CB4-02163E012BB7.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/00059C74-ECA7-E511-9541-02163E0136FD.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/00346478-ECA7-E511-85E5-02163E011BA0.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/00BE069B-EDA7-E511-8934-02163E0129F2.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/02DBEF7A-ECA7-E511-83E6-02163E0133F0.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/046E6A75-ECA7-E511-88F6-02163E012408.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/047F987C-ECA7-E511-BD83-02163E012AD0.root',
'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias1/AOD/PromptReco-v1/000/262/988/00000/FE7AA556-ECA7-E511-A990-02163E011D46.root'
        )
)
process.TFileService = cms.Service("TFileService",
                                   #  fileName = cms.string(outfile)
                                   fileName = cms.string('Run262988_100events_ZDCTrees.root')
                                   )
### if you want trigger selection uncomment these as well as including them below in the Path
### import HLTrigger.HLTfilters.hltHighLevel_cfi                                                                     
### process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
### process.hltMinBias.HLTPaths = [
###                                "HLT_HIL1MinimumBiasHF1AND_*",
###                                "HLT_HIL1MinimumBiasHF2AND_*"
###                                ]
                                                                  
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.fwdana = cms.EDAnalyzer('ForwardAnalyzer'
                                , CentralitySrc = cms.InputTag("hiCentrality")
                                , CentralityBinSrc = cms.InputTag("centralityBin","HFtowers")
                                , trackSrc = cms.InputTag("hiGeneralTracks")
                                , vtxCollection_ = cms.InputTag("hiSelectedVertex")
                                )
process.forwardSequence = cms.Sequence(process.fwdana)
                                                                           
process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:1000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)
from CondCore.DBCommon.CondDBSetup_cfi import *
#----------------------------------------------------- replacing conditions
process.es_ascii = cms.ESSource("HcalTextCalibrations",
                                    input = cms.VPSet(
             cms.PSet(
                 object = cms.string('Gains'),
                              file =
                 cms.FileInPath('data/Gains_Runs262834-263614.txt')
                          ),
                      cms.PSet(
                 object = cms.string('LongRecoParams'),
                              file =
                 cms.FileInPath('data/LongRecoParams_Runs262314-263614.txt')
                          ),
                      cms.PSet(
                 object = cms.string('MCParams'),
                              file =
                 cms.FileInPath('data/DumpMCParams_Run211831.txt')
                          )
                 )
                                )
process.es_prefer = cms.ESPrefer('HcalTextCalibrations','es_ascii')
# end replacing conditions
from RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_cfi import zdcreco
zdcreco.digiLabel = cms.InputTag("castorDigis")
from RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_zdc_cfi import zdcreco
zdcreco.digiLabel = cms.InputTag("castorDigis")
#
process.zdcreco.lowGainFrac = 8.6
# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('output_data_rereco.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

# add custom HCAL conditions
process.es_pool = cms.ESSource("PoolDBESSource",
    process.CondDBSetup,
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string("HcalRespCorrsRcd"),
            tag = cms.string("HcalRespCorrs_v5.0_offline")
        )
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    authenticationMethod = cms.untracked.uint32(0)
)

process.es_prefer_es_pool = cms.ESPrefer( "PoolDBESSource", "es_pool" )

# Path and EndPath definitions
process.reconstruction_step = cms.Path(process.zdcreco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
### version with no triggers and no RECO level output, just Tree
process.p = cms.Path(process.zdcreco*
                     process.centralityBin *
                     process.fwdana )
### version with triggers
### process.p = cms.Path(process.zdcreco*
###                      process.hfCoincFilter3 *
###                      process.primaryVertexFilter *
###                      process.clusterCompatibilityFilter *
###                      process.centralityBin *
###                      process.hltMinBias *
###                      process.fwdana )

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)
#process.schedule = cms.Schedule(process.raw2digi_step,process.RECOoutput_step)
#process.schedule = cms.Schedule(process.reconstruction_step,process.RECOoutput_step)
# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
#from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_lowPU

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
#process = customisePostLS1_lowPU(process)

# End of customisation functions

