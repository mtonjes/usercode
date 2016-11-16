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
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:pPb_MB_RAW.root')
    
    	#'file:USC_261664.root')
        #'root://xrootd.ba.infn.it//store/data/Run2015A/ZeroBias1/RAW/v1/000/247/324/00000/92067870-580D-E511-940D-02163E013891.root')
        'file:/home/belt/wrk/ZDC/2015Data/ZDCTree/Mate/PbPb2015_PromptReco_MinBias2_263005.root')
)

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
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.zdcreco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)
#process.schedule = cms.Schedule(process.raw2digi_step,process.RECOoutput_step)
process.schedule = cms.Schedule(process.reconstruction_step,process.RECOoutput_step)
# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
#from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_lowPU

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
#process = customisePostLS1_lowPU(process)

# End of customisation functions

