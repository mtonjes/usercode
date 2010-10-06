import FWCore.ParameterSet.Config as cms
process = cms.Process('ReRECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/L1Reco_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('DQMOffline/Configuration/DQMOffline_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("HLTrigger.HLTfilters.hltLevel1GTSeed_cfi")
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.9 $'),
    annotation = cms.untracked.string('rereco nevts:2000'),
    name = cms.untracked.string('PyReleaseValidation')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True) 
)
# Input source
process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring( 'file:/filename.root', 'file:filename2.root'
    )
)
readFiles = cms.untracked.vstring()
readFiles.extend( (
        '/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/FEBC2543-E1AF-DF11-8F12-003048D2C108.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/F8E589FD-EAAF-DF11-8077-001617C3B5F4.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/F469317E-D4AF-DF11-960C-001D09F251CC.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/F25EC571-DCAF-DF11-A00B-001617C3B6DE.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/E8CBC7C2-E9AF-DF11-B88D-001D09F24DDA.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/E6D9DF74-DCAF-DF11-A3E3-001617C3B710.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/E0A80510-DFAF-DF11-9503-001D09F24D8A.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/DA9D6184-D4AF-DF11-9B06-001D09F24489.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/CEA2361D-E6AF-DF11-8502-000423D996C8.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/CC3C9D02-E9AF-DF11-94BE-003048F1BF66.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/C88E0DBC-E9AF-DF11-B82B-0019B9F72F97.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/C80B4B67-D9AF-DF11-9CAB-0030487A1884.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/C0C50905-E9AF-DF11-A69B-003048F1BF68.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/AEB4DE3D-C7AF-DF11-8FBD-0030487C5CFA.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/AE3B12E8-D5AF-DF11-A0F4-0030487C8CBE.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/9AA5CC6F-EDAF-DF11-8D41-0030487C7392.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/9626D2B3-D1AF-DF11-955A-0030487CD77E.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/949F97B3-D1AF-DF11-BD87-0030487A3232.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/8CE8D71F-DAAF-DF11-BC38-001D09F2462D.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/885150B0-16B0-DF11-8242-001D09F2462D.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/82F0730A-D8AF-DF11-AA3F-0030487CD700.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/748F6D71-DCAF-DF11-A8B7-000423D996C8.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/62B7F844-C7AF-DF11-8C58-00304879FBB2.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/58A73011-D8AF-DF11-8AD9-000423D987E0.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/58485CA7-CFAF-DF11-86C8-001617E30E28.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/547CAE5F-E5AF-DF11-A3B5-001617DC1F70.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/4EA9D7E6-CCAF-DF11-8679-0030486730C6.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/4C3DEEE9-D0AF-DF11-AB40-0030487A18F2.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/4A61921F-DAAF-DF11-95F4-003048D373AE.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/481F0CE3-CCAF-DF11-9816-0030487CD184.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/42D653E5-CCAF-DF11-9ACC-001D09F297EF.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/4069F294-CFAF-DF11-8DF9-003048F01E88.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/38BF3120-DAAF-DF11-8569-001D09F2905B.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/264AE78C-EEAF-DF11-BFC2-0030487A18D8.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/24FBE756-EDAF-DF11-8800-003048D37514.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/22159209-D3AF-DF11-8CC8-001D09F23A20.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/18C415E8-D5AF-DF11-8D34-0030487A322E.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/18C38066-EDAF-DF11-9DD4-001D09F24664.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/16B1BE6B-DCAF-DF11-8F76-0030487CD76A.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/1229D186-E0AF-DF11-9871-0030487D05B0.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/10123AB4-D1AF-DF11-984D-003048F118AC.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/0CD1CF97-CFAF-DF11-BE54-001617E30CC8.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/0C2D3492-E7AF-DF11-B9D5-001D09F295A1.root',
'/store/data/Run2010A/MinimumBias/RECO/v4/000/143/827/044DEE1F-CEAF-DF11-B3A5-001D09F25041.root'
) )
process.source = cms.Source("PoolSource",
     fileNames = readFiles
)
#process.source.inputCommands = cms.untracked.vstring("keep *", "drop *_MEtoEDMConverter_*_*", "drop L1GlobalTriggerObjectMapRecord_hltL1GtObjectMap__HLT")

process.FEVT = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('ZdcTime_ReReco_143827_1kev.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    )
)
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1UseL1TriggerObjectMaps = cms.bool(False)
process.hltLevel1GTSeed.L1NrBxInEvent = cms.int32(1)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39)')

process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

process.ns = cms.EDFilter("FilterOutScraping",
                              applyfilter = cms.untracked.bool(True),
                              debugOn = cms.untracked.bool(True),
                              numtrack = cms.untracked.uint32(10),
                              thresh = cms.untracked.double(0.25)
)

process.pVF = cms.EDFilter("GoodVertexFilter",
			      vertexCollection = cms.InputTag('offlinePrimaryVertices'),
			      minimumNDOF = cms.uint32(4) ,
			      maxAbsZ = cms.double(15),	
			      maxd0 = cms.double(2)	

)
# Other statements
#3_3_6 GlobalTag for reReco
#process.GlobalTag.globaltag = 'GR09_R_V5::All'
#3_4_1 GlobalTag fore reReco
process.GlobalTag.globaltag = "GR_R_38X_V9::All"

# process.raw2digi_step = cms.Path(process.RawToDigi)
# process.L1GtObjectMap_step = cms.Path(process.hltL1GtObjectMap)
# process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.zdcreco)
# process.dqmoffline_step = cms.Path(process.DQMOffline)
process.endjob_step = cms.Path(process.endOfProcess)
process.p = cms.Path(process.hltLevel1GTSeed*process.hltPhysicsDeclared*process.pVF*process.ns)
process.out_step = cms.EndPath(process.FEVT)

process.schedule = cms.Schedule(process.p,process.reconstruction_step,process.endjob_step,process.out_step)
