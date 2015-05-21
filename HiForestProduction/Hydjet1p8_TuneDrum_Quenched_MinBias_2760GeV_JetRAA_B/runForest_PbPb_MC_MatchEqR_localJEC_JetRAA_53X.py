#!/usr/bin/env python2
# Run the foresting configuration on PbPb in CMSSW_5_3_X, using the new HF/Voronoi jets
# Author: Alex Barbieri
# Date: 2013-10-15

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')
process.options = cms.untracked.PSet(
    # wantSummary = cms.untracked.bool(True)
    #SkipEvent = cms.untracked.vstring('ProductNotFound')
)

#####################################################################################
# HiForest labelling info
#####################################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest V3",)
import subprocess
version = subprocess.Popen(["(cd $CMSSW_BASE/src && git describe --tags)"], stdout=subprocess.PIPE, shell=True).stdout.read()
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.untracked.string(version)

#####################################################################################
# Input source
#####################################################################################

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring("/store/user/ginnocen/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/HiMinBias_RECO_26June2014/296b762a3f7ae585942f7234457ce1af/step3_RAW2DIGI_L1Reco_RECO_1000_1_Ajv.root"))

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2))


#####################################################################################
# Load Global Tag, Geometry, etc.
#####################################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

# PbPb 53X MC
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')

from HeavyIonsAnalysis.Configuration.CommonFunctionsLocalDB_cff import *
overrideGT_PbPb2760(process)

process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFtowers"),
    nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
    centralitySrc = cms.InputTag("hiCentrality")
    )

#####################################################################################
# Define tree output
#####################################################################################

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string("HiForest_MinBiasHydjet.root"))

#####################################################################################
# Additional Reconstruction and Analysis: Main Body
#####################################################################################

process.load('HeavyIonsAnalysis.JetAnalysis.jets.HiGenJetsCleaned_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu2CaloJetSequence_PbPb_mc_cff')
# process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs2CaloJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs2PFJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu2PFJetSequence_PbPb_mc_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu3CaloJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs3CaloJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs3PFJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu3PFJetSequence_PbPb_mc_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu4CaloJetSequence_PbPb_mc_cff')
# process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs4CaloJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs4PFJetSequence_PbPb_mc_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu4PFJetSequence_PbPb_mc_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.jets.akPu5CaloJetSequence_PbPb_mc_cff') 
# process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs5CaloJetSequence_PbPb_mc_cff') 
#process.load('HeavyIonsAnalysis.JetAnalysis.jets.akVs5PFJetSequence_PbPb_mc_cff') 

process.load('HeavyIonsAnalysis.JetAnalysis.jets.HiReRecoJets_HI_MatchEqR_cff')


process.jetSequences = cms.Sequence(
                                    process.hiReRecoPFJetsMatchEqRJetRAA +
#                                    process.akPu1CaloJetSequence +
#                                    process.akVs1CaloJetSequence +
#                                    process.akVs1PFJetSequence +
#                                    process.akPu1PFJetSequence +

                                    process.akPu2CaloJetSequence +
#                                    process.akVs2CaloJetSequence +
                                    process.akVs2PFJetSequence +
                                    process.akPu2PFJetSequence +

                                    process.akPu3CaloJetSequence +
                                    process.akVs3CaloJetSequence +
                                    process.akVs3PFJetSequence +
                                    process.akPu3PFJetSequence +

                                    process.akPu4CaloJetSequence +
#                                    process.akVs4CaloJetSequence +
                                    process.akVs4PFJetSequence +
                                    process.akPu4PFJetSequence +
                                    
                                    process.akPu5CaloJetSequence

                                    )

process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_mc_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.HiGenAnalyzer_cfi')

#####################################################################################
# To be cleaned

process.load('HeavyIonsAnalysis.JetAnalysis.ExtraTrackReco_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.TrkAnalyzers_MC_cff')
process.load("HeavyIonsAnalysis.TrackAnalysis.METAnalyzer_cff")
process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
process.load('HeavyIonsAnalysis.JetAnalysis.rechitanalyzer_cfi')
process.rechitAna = cms.Sequence(process.rechitanalyzer+process.pfTowers)
process.pfcandAnalyzer.skipCharged = False
process.pfcandAnalyzer.pfPtMin = 0

#####################################################################################

#########################
# Track Analyzer
#########################
process.anaTrack.qualityStrings = cms.untracked.vstring('highPurity','highPuritySetWithPV')
process.pixelTrack.qualityStrings = cms.untracked.vstring('highPurity','highPuritySetWithPV')
process.hiTracks.cut = cms.string('quality("highPurity")')

# set track collection to iterative tracking
process.anaTrack.trackSrc = cms.InputTag("hiGeneralTracks")

# clusters missing in recodebug - to be resolved
process.anaTrack.doPFMatching = False
process.pixelTrack.doPFMatching = False

#####################
# photons
process.load('HeavyIonsAnalysis.JetAnalysis.EGammaAnalyzers_cff')
process.multiPhotonAnalyzer.GenEventScale = cms.InputTag("generator")
process.multiPhotonAnalyzer.HepMCProducer = cms.InputTag("generator")
process.RandomNumberGeneratorService.multiPhotonAnalyzer = process.RandomNumberGeneratorService.generator.clone()

#####################
# muons
######################
process.load("HeavyIonsAnalysis.MuonAnalysis.hltMuTree_cfi")
process.hltMuTree.doGen = cms.untracked.bool(True)
process.load("RecoHI.HiMuonAlgos.HiRecoMuon_cff")
process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("akVs3PFJets")
process.globalMuons.TrackerCollectionLabel = "hiGeneralTracks"
process.muons.TrackExtractorPSet.inputTrackCollection = "hiGeneralTracks"
process.muons.inputCollectionLabels = ["hiGeneralTracks", "globalMuons", "standAloneMuons:UpdatedAtVtx", "tevMuons:firstHit", "tevMuons:picky", "tevMuons:dyt"]

# HYDJET RECO file didn't have ak2GenJets and ak6GenJets as input, so removed them (add ak2 back in)
# and ran our own hiGenJetsCleaned sequence
process.load('Configuration.StandardSequences.Generator_cff')
from HeavyIonsAnalysis.JetAnalysis.jets.HiGenJetsCleaned_cff import *
process.load('RecoHI.HiJetAlgos.HiGenJets_cff')

process.genStep = cms.Path(process.hiGenParticlesForJets +
                           process.ak2HiGenJets)

process.hiSelectGenJets = cms.Sequence(
 					ak2HiGenJetsCleaned +
 					ak3HiGenJetsCleaned +
 					ak4HiGenJetsCleaned +
 					ak5HiGenJetsCleaned 
)


process.ana_step = cms.Path(process.heavyIon*
                            process.hltanalysis *
#                            process.hltobject *
                            process.hiEvtAnalyzer*
                            process.HiGenParticleAna*
#                            process.hiGenJetsCleaned*
                             process.hiSelectGenJets*
                            process.jetSequences +
                           process.photonStep_withReco +
                            process.pfcandAnalyzer +
                            process.rechitAna +
#temp                            process.hltMuTree +
                            process.HiForest +
                           process.cutsTPForFak +
                            process.cutsTPForEff +
                            process.anaTrack +
                            process.pixelTrack
                            )

process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
process.phltJetHI = cms.Path( process.hltJetHI )
process.pcollisionEventSelection = cms.Path(process.collisionEventSelection)
process.pHBHENoiseFilter = cms.Path( process.HBHENoiseFilter )
process.phfCoincFilter = cms.Path(process.hfCoincFilter )
process.phfCoincFilter3 = cms.Path(process.hfCoincFilter3 )
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter )
process.phltPixelClusterShapeFilter = cms.Path(process.siPixelRecHits*process.hltPixelClusterShapeFilter )
process.phiEcalRecHitSpikeFilter = cms.Path(process.hiEcalRecHitSpikeFilter )

process.pAna = cms.EndPath(process.skimanalysis)

# Customization