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
                            fileNames = cms.untracked.vstring(
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/0224FD16-9F94-E511-9941-02163E01350C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/02BB03F1-7C94-E511-8E6A-02163E01470D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/0846ACBB-7894-E511-8E34-02163E01462B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/0848D9C0-6C94-E511-812E-02163E01396E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/088F6B29-7194-E511-8476-02163E014456.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/0C78703E-6A94-E511-A8F8-02163E01358E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/0C8C46B4-7894-E511-8F35-02163E014429.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/16421A32-7194-E511-93F4-02163E012776.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/16658E61-7D94-E511-A537-02163E012B63.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/16B45C5A-7694-E511-A6D3-02163E014297.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/26F4EE02-6994-E511-B507-02163E011FE9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/2A56A2E9-5E94-E511-98FE-02163E011ADA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/3008BC32-7194-E511-B317-02163E011C8D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/30C49CF3-7C94-E511-9AA0-02163E012A39.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/3251549D-7894-E511-A1D6-02163E01435B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/36583BA9-7F94-E511-9A6B-02163E014431.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/3C1510EA-6594-E511-997C-02163E012118.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/3E801143-7194-E511-B57D-02163E0135BF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/401EA85C-7194-E511-A402-02163E0136A5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/407A58B7-7894-E511-A717-02163E011822.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/40D5B150-7194-E511-B0D6-02163E0138F6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/4247D6AD-7194-E511-86E4-02163E011EE8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/469C9B41-6A94-E511-86C0-02163E0137E5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/4829C988-6194-E511-BA86-02163E014347.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/483B9561-7D94-E511-BC2A-02163E013945.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/48F7E1C6-7894-E511-A184-02163E0133BB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/509B72E6-6C94-E511-A185-02163E01463E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/5675BDF5-7894-E511-A790-02163E014347.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/56B12AFC-7894-E511-BE67-02163E01452A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/5A796C55-7194-E511-8F50-02163E011BF3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/66FB8498-7D94-E511-8844-02163E014493.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/68A3CAA8-7894-E511-848E-02163E0140E3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/70F392E4-7194-E511-99E1-02163E011E77.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/725C010E-7994-E511-9B0C-02163E014496.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/72A26D89-7894-E511-B18B-02163E011CF2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/76CC3106-7D94-E511-851B-02163E011C3A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/78CBE3E3-7894-E511-9CB0-02163E01451B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/78D8D6C6-5E94-E511-9517-02163E0135BF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/7AA424C3-7894-E511-B1C9-02163E01476D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/7EDB663E-7694-E511-9343-02163E014726.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/8297A0F2-7C94-E511-A2D5-02163E0133BC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/84D04EA6-7694-E511-9F97-02163E0139D9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/86A52A3F-7194-E511-A6B8-02163E012402.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/86D96C5B-7A94-E511-9377-02163E014692.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/88E97006-7D94-E511-89E6-02163E014318.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/8C9CB423-6A94-E511-B8F9-02163E011D94.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/8E40D503-7D94-E511-A8E1-02163E012B63.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/901941FE-7C94-E511-8A8A-02163E01430A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/90E6417E-6194-E511-9485-02163E014136.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/9424B518-7B94-E511-B501-02163E0144EC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/943EF7F3-7A94-E511-8521-02163E011E77.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/94FC0804-7D94-E511-A7C0-02163E013734.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/961ABD16-7D94-E511-8476-02163E014175.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/9693EABA-7894-E511-BDEE-02163E014578.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/984A06A5-7894-E511-B1EA-02163E01364B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/9AB80975-7194-E511-AAED-02163E01443B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/9AC60E74-7D94-E511-AF28-02163E0142DD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/A0048302-7D94-E511-8218-02163E014607.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/A4DACAFB-7F94-E511-AE4C-02163E011E27.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/AAC9C821-7694-E511-BA4F-02163E0126AC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/ACC63D4E-7194-E511-B767-02163E0142A3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/AE00CD46-7194-E511-A0CA-02163E0139D9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B099AD52-7194-E511-85CF-02163E01371A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B09D2910-9394-E511-AE6F-02163E013956.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B20D2FB8-7894-E511-9DBF-02163E0134F6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B2B8613C-7194-E511-AAB4-02163E014759.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B800D014-7D94-E511-AEC3-02163E013408.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B8604FBC-7894-E511-8915-02163E0146D2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/B86520DC-7894-E511-8F10-02163E0143B9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C02ABB14-7994-E511-810A-02163E014255.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C0C0597F-6194-E511-9FC8-02163E011F65.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C291689F-7894-E511-90FB-02163E011DED.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C2C45FCA-7894-E511-9E2B-02163E014540.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C4F186D4-5E94-E511-B62C-02163E0145B9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C4F20F1D-7D94-E511-AC49-02163E014717.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C6F6C143-7194-E511-80A8-02163E01354D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/C856111D-7D94-E511-996F-02163E014717.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/CAE255A4-7894-E511-9C10-02163E012842.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/CC8A964E-8494-E511-AE2D-02163E012061.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/D85D1FBB-7894-E511-8D41-02163E014175.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/DADDC9A7-7894-E511-A771-02163E013399.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/DE09DA03-7D94-E511-9171-02163E012B63.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/E09398B8-7894-E511-9E09-02163E011EF7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/E0F6F223-7D94-E511-86FA-02163E013813.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/E6458CB2-7894-E511-BB75-02163E012085.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/E8BBEAB3-7894-E511-9EB0-02163E0144ED.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/EA3677C8-7894-E511-A63E-02163E01243A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/ECDA9DAB-7894-E511-9F9A-02163E0146CA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/EEB17A1E-7D94-E511-8C37-02163E0122F0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/EECBA713-7D94-E511-846B-02163E011BB3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/F2BA7B58-7194-E511-A4B9-02163E011F25.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/F4594856-6A94-E511-8F02-02163E0145D5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/F8B702A9-7D94-E511-949C-02163E014438.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/F8FEA0DC-7894-E511-86AC-02163E01298B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/694/00000/FEBB7BA3-7894-E511-890D-02163E011BF7.root'
                             )
                            )

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# pp 2015
#process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_HLT_ppAt5TeV_v0', '')
# PbPb 2015
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')

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
                                   fileName = cms.string('ForwardAnalyzerRun262694_MinBiasHIZeroBiasExpress_HF.root')
                                   )
                                   
import HLTrigger.HLTfilters.hltHighLevel_cfi                                  
process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBias.HLTPaths = [
        "HLT_HIL1MinimumBiasHF1ANDExpress_v*"
]
process.hltZB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltZB.HLTPaths = [
        "HLT_HIZeroBias_v1"
]

process.fwdana = cms.EDAnalyzer('ForwardAnalyzer', 
  #                              l1GtRR=cms.InputTag("GtDigis")
                                )

# process.upcvertexana = cms.EDAnalyzer('UPCVertexAnalyzer',
#                                       vertexCollection=cms.string("offlinePrimaryVerticesWithBS")
#                                       )
# process.whatever = cms.Path(process.hltMinBias * process.your_analyzer)
                                      
process.p = cms.Path(process.hltZB*process.fwdana)
#process.p = cms.Path(process.zdcreco*process.fwdana)
#process.p = cms.Path(process.fwdana*process.upcvertexana)