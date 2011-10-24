import FWCore.ParameterSet.Config as cms

maxEvents=-1

process = cms.Process("HFfilter")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.HFLongShortFilt = cms.EDFilter("HFLongShortFilter")
process.pFilt = cms.Path(process.HFLongShortFilt)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

# using a local test file here
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring("file:/data/users/belt/PbPb_data/HICorePhysics/HICorePromptv3_151353_EE0FFA35-30F2-DF11-9F88-0030486730C6.root"),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxEvents) )

process.GlobalTag.globaltag ='GR_R_44_V6::All'

#To write out events which fail (therefore having the HFLongShortFlag in at least one RecHit
# use SelectEvents = cms.vstring('pFilt')

process.output = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('MBT_HICore_EE0FFA35_GoodHFLongShort.root'),
    SelectEvents = cms.untracked.PSet(
                SelectEvents = cms.vstring('!pFilt')
    ),
    outputCommands = cms.untracked.vstring('drop *',
      'keep *_hbhereco_*_*',
      'keep *_horeco_*_*',
      'keep *_hfreco_*_*',
      'keep *_ecalRecHit_*_*',
      'keep CaloTowersSorted_*_*_*', 
      'keep *_caloTowers_*_*',
      'keep HcalNoiseSummary_*_*_*',
      'keep *_iterativeConePu5CaloJets_*_*',
      'keep *Centrality_*_*_*',
      'keep *Trigger*_*_*_*'
    )
)

#process.RECOoutput_step = cms.EndPath(process.output)

process.endProcess_step = cms.Path(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.output)