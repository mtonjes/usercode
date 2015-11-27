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


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/046D46EE-9794-E511-BC2A-02163E01394E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/04841ED2-9794-E511-846B-02163E011CD1.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/0A2CF9B2-9794-E511-A7BE-02163E0119EA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/0AD86F08-9894-E511-9EFE-02163E014434.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/18BE08EF-9794-E511-AB9F-02163E0138C6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/1AC0A466-AD94-E511-A7EC-02163E01378D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/1E9182DD-9794-E511-9152-02163E0142BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/2084342F-9094-E511-A696-02163E013526.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/243C16C6-9794-E511-A073-02163E0135FF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/2AAB53A5-9294-E511-892A-02163E011DDC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/2AB9FCE3-9794-E511-8130-02163E01418A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/32F644D4-9794-E511-AE6A-02163E01452E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/3CC1A1A2-9294-E511-B496-02163E0143E9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/3EDE89F0-9794-E511-83C8-02163E0134CB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/425AB3B5-9794-E511-8C04-02163E01194E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/48AC80CC-9794-E511-9ECA-02163E011EF4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/4A2E0286-9294-E511-9BA4-02163E01187F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/4AA9161E-9894-E511-BE7B-02163E01436F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/4AB7CDCC-9794-E511-91CC-02163E0144A5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/4AC3A1DA-9594-E511-9941-02163E01456B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/4EC7A7DE-9794-E511-BAC3-02163E0119FA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/507B2DDF-9794-E511-B749-02163E0144DB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/5210C493-9294-E511-963F-02163E014776.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/547DEEA4-9294-E511-95BC-02163E0136FD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/562A20D3-9794-E511-BEDA-02163E011F2A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/5688AC75-9794-E511-87C0-02163E011D17.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/587739BB-9794-E511-ABCC-02163E013956.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/5ADA60E8-9794-E511-A8BC-02163E011F7E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/5CEB0EE1-9794-E511-B363-02163E013394.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/62BB70F4-9794-E511-AAF1-02163E0123C6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/64253DEE-9794-E511-B167-02163E014575.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/64AC28BA-9594-E511-BA26-02163E01395F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/682094E8-9794-E511-A05F-02163E01373D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/68D1FCE2-9794-E511-B0B2-02163E0125F7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/6C401809-9894-E511-9BEC-02163E014795.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/6EA7B3B9-9794-E511-909A-02163E012680.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/72A2A428-9894-E511-809B-02163E013515.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/72D225E6-9794-E511-B88D-02163E0119EB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/7463AB2A-9094-E511-B464-02163E011C5E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/78314DF0-9794-E511-AC53-02163E011EF7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/7ADD39CE-9794-E511-981C-02163E01233C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/888C97B5-9594-E511-AE85-02163E0142C8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/8A3B6D1D-9894-E511-B41D-02163E01183C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/8C817AB6-9594-E511-B0FE-02163E01440F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/9822BAD1-9794-E511-B992-02163E01476F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/987DC91B-9894-E511-AE5A-02163E012219.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/9AD059B1-9594-E511-BF7A-02163E011C3E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/9C327FB7-9794-E511-A152-02163E011E7B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/A0B418D9-9794-E511-9022-02163E014510.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/A8137FCF-9794-E511-81B4-02163E0135BF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/A8F815B0-9594-E511-B74A-02163E0133AC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/AADFE1D0-9794-E511-851C-02163E013774.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/AEC154CD-9794-E511-A2AD-02163E0146A9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/AEFBE713-9894-E511-BB16-02163E0143DD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/B01518DC-9794-E511-B5D0-02163E01478F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/B43D35B1-9794-E511-A010-02163E014486.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/B6975DCD-9794-E511-99D3-02163E013407.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/BC9C23A9-9594-E511-B2ED-02163E01294C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/C4CB3DBA-9794-E511-9087-02163E011DD8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/C878C7E3-9794-E511-905C-02163E0135B9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/C8FE71B8-9794-E511-A091-02163E01390D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CA8693CB-9794-E511-B62E-02163E01355F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CCDE2313-9894-E511-9B73-02163E0145EC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CE5EF2C2-9794-E511-9D3B-02163E0136F3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CE7F81E5-9794-E511-B696-02163E0137A2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CE8DEA0E-9894-E511-8BFB-02163E0141C3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/CEB9C4CC-9794-E511-A5E6-02163E0134BD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/D0835AC5-9794-E511-8BE3-02163E011FA4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/D297F9D5-9594-E511-A922-02163E011DED.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/D65ED0B9-9794-E511-8235-02163E014223.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/D6EE8AD8-A194-E511-8C4E-02163E011A08.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/D80597BD-9794-E511-9A90-02163E0143C8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/DC70D0DD-9794-E511-8442-02163E014661.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/DE0EC39B-9294-E511-8131-02163E011B89.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/E240BEDD-9794-E511-8142-02163E0143C8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/E27EDE8E-9294-E511-8625-02163E01369F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/E84257BA-9794-E511-9501-02163E014248.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/E8C01677-9894-E511-9668-02163E012034.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/EA0B9C09-9894-E511-8D0D-02163E014756.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/EA237BA1-9594-E511-B9D7-02163E0129BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/EACE71B4-9594-E511-8569-02163E01374B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/EEAC2DE7-9294-E511-8124-02163E0139BF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F014F320-9894-E511-9CCA-02163E013957.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F034A0E5-9794-E511-BD3D-02163E014326.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F4739EF4-9794-E511-A271-02163E0126E5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F4770A8E-9894-E511-95C1-02163E0146F3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F4C984D6-9794-E511-903C-02163E01279D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F4CC0CE7-8D94-E511-AC38-02163E01414A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/F6432FB5-9794-E511-BA81-02163E0138D2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/FA97F306-9894-E511-8DB7-02163E0123EB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/FC0580F6-9794-E511-BAB7-02163E011F9D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/FCB30716-9894-E511-8616-02163E01449D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/FCBF43F1-9794-E511-B812-02163E01463E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/703/00000/FE04BB32-9894-E511-B40A-02163E01361E.root'
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
                                   fileName = cms.string('ForwardAnalyzerRun262703_MinBiasHF1AndExpress_10k.root')
                                   )
                                   
import HLTrigger.HLTfilters.hltHighLevel_cfi                                                                     
process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBias.HLTPaths = [
        "HLT_HIL1MinimumBiasHF1ANDExpress_v*"
]

process.fwdana = cms.EDAnalyzer('ForwardAnalyzer'
)

# process.upcvertexana = cms.EDAnalyzer('UPCVertexAnalyzer',
#                                       vertexCollection=cms.string("offlinePrimaryVerticesWithBS")
#                                       )
# process.whatever = cms.Path(process.hltMinBias * process.your_analyzer)
                                      
process.p = cms.Path(process.hltMinBias*process.fwdana)
#process.p = cms.Path(process.zdcreco*process.fwdana)
#process.p = cms.Path(process.fwdana*process.upcvertexana)