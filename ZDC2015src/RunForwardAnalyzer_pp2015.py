import FWCore.ParameterSet.Config as cms
import sys

#if len(sys.argv) > 2:
 #   file=open(sys.argv[2])
  #  outfile=sys.argv[3]

process = cms.Process("Forward")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_hf_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_cfi")
process.load("EventFilter.CastorRawToDigi.CastorRawToDigi_cfi")
process.load("RecoLocalCalo.CastorReco.CastorSimpleReconstructor_cfi")


process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('file:/home/belt/wrk/ZDC/2015Data/ZDCTree/output_data_pp_fixDigi.root')
                            )

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# pp 2015
process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_HLT_ppAt5TeV_v0', '')
# PbPb 2015
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')

# load centrality
#process.HeavyIonGlobalParameters = cms.PSet(
#	centralityVariable = cms.string("HFhits"),
#	nonDefaultGlauberModel = cms.string(""),
#	centralitySrc = cms.InputTag("hiCentrality")
#)

# process.hltbitanalysis = cms.EDAnalyzer("HLTBitAnalyzer",
#                                         ### Trigger objects
#                                         l1GctHFBitCounts                = cms.InputTag("gctDigis"),
#                                         l1GctHFRingSums                 = cms.InputTag("gctDigis"),
#                                         l1GtObjectMapRecord             = cms.InputTag("hltL1GtObjectMap::HLT"),
#                                         l1GtReadoutRecord               = cms.InputTag("gtDigis::RECO"),
#                                         
#                                         l1extramc                       = cms.string('l1extraParticles'),
#                                         l1extramu                       = cms.string('l1extraParticles'),
#                                         hltresults                      = cms.InputTag("TriggerResults::HLT"),
#                                         HLTProcessName                  = cms.string("HLT"),
#                                         UseTFileService                 = cms.untracked.bool(True),
#                                         
#                                         ### Run parameters
#                                         RunParameters = cms.PSet(
#     HistogramFile = cms.untracked.string('hltbitanalysis.root')
#     )
#                                         )##end of HLT

# ###L1 Stuff
# process.GtDigis = cms.EDProducer( "L1GlobalTriggerRawToDigi",
#                                   #DaqGtInputTag = cms.InputTag( "rawDataRepacker" ),
#                                   DaqGtInputTag = cms.InputTag("rawDataCollector"),
#                                   DaqGtFedId = cms.untracked.int32( 813 ),
#                                   ActiveBoardsMask = cms.uint32( 0xffff ),
#                                   UnpackBxInEvent = cms.int32( 5 ),
#                                   Verbosity = cms.untracked.int32( 0 )
#                                   )##END of L1 Stuff

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('ForwardAnalyzerRun_pp_fixDigi.root')
                                   )

process.fwdana = cms.EDAnalyzer('ForwardAnalyzer', 
  #                              l1GtRR=cms.InputTag("GtDigis")
                                )

# process.upcvertexana = cms.EDAnalyzer('UPCVertexAnalyzer',
#                                       vertexCollection=cms.string("offlinePrimaryVerticesWithBS")
#                                       )
                                      
process.p = cms.Path(process.fwdana)
#process.p = cms.Path(process.zdcreco*process.fwdana)
#process.p = cms.Path(process.fwdana*process.upcvertexana)