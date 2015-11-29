import FWCore.ParameterSet.Config as cms

# Give the process a name
process = cms.Process("ZDC")

process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')


#process.load("IORawData.HcalTBInputService.HcalTBSource_cfi")
## Tell the process which files to use as the sourdce
#process.source.fileNames = cms.untracked.vstring('file:/afs/cern.ch/user/q/qwang/public/ForZDC/USC_262267.root')
#process.source.streams = cms.untracked.vstring(
#        'HCAL_Trigger',
#        'HCAL_SlowData',
#        'HCAL_DCC690',
#        'HCAL_DCC691',
#        'HCAL_DCC692',
#        'HCAL_DCC693',
#)
#process.source = cms.Source ("PoolSource",
#                                     fileNames = cms.untracked.vstring
#                             ("file:/afs/cern.ch/user/q/qwang/work/ZDC/Pedestal_incl_ZDC/USC_261946.root")
#                             ("root://xrootd.unl.edu//store/user/vzhukova/HYDGET_PERIPHERAL_batch1/HYDGET_PERIPHERAL_RECO_batch1/4ff4724d400594a837d493abb590edd3/Hydget_periph_101_1_kH6.root")
#                             ("/store/user/vzhukova/HYDGET_PERIPHERAL_batch1_version2/HYDGET_PERIPHERAL_RECODEBUG_batch1/4ff4724d400594a837d493abb590edd3/Hydget_periph_101_1_GbM.root")
#                            )

process.source = cms.Source ("NewEventStreamFileReader",
                             fileNames = cms.untracked.vstring(
                                     '/store/t0streamer/Data/HIPhysicsMinBiasUPC/000/262/811/run262811_ls0003_streamHIPhysicsMinBiasUPC_StorageManager.dat',
                             )
                            )

#for i in open("flist.streamer811").read().split("\n"):
#        if i != '':
#                process.source.fileNames.append(i)

# tell the process to only run over 100 events (-1 would mean run over
#  everything
process.maxEvents = cms.untracked.PSet(
                input = cms.untracked.int32 (-1)
)

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltZB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltZB.HLTPaths = [
        "HLT_HIZeroBias_v1"
]

#process.load('EventFilter.CastorRawToDigi.CastorRawToDigi_cfi')
process.castorDigis.InputLabel = cms.InputTag("rawDataRepacker")

process.p = cms.Path(process.hltZB * process.castorDigis);
# Tell the process what filename to use to save the output
process.Out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('p')),
                               fileName = cms.untracked.string ("ZeroBias811.root"),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep ZDCDataFramesSorted_castorDigis_*_*',
                                                                     ),
                              )


process.end = cms.EndPath(process.Out)
