# Auto generated configuration file
# using: 
# Revision: 1.381.2.13 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/python/SingleElectronE120EHCAL_cfi.py -s GEN,SIM,DIGI --conditions auto:mc --datatier GEN-SIM-DIGI --eventcontent RAWSIM -n 1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('DIGI')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('SimG4CMS.Forward.zdcGeometryXML_cfi')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration/StandardSequences/Sim_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)


# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')


# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet()

process.generator = cms.EDProducer("FlatRandomEGunProducer",
    PGunParameters = cms.PSet(
        PartID = cms.vint32(2112),
        MinEta = cms.double(8.0),
        MaxEta = cms.double(9.0),
        MinPhi = cms.double(-3.14159265359), ## in radians
        MaxPhi = cms.double(3.14159265359),
        MinE = cms.double(99.99),
        MaxE = cms.double(100.01)
    ),
    Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts

    psethack = cms.string('single neutron E 100'),
    AddAntiParticle = cms.bool(False),
    firstRun = cms.untracked.uint32(1)
)

process.ProductionFilterSequence = cms.Sequence(process.generator)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.13 $'),
    annotation = cms.untracked.string('Configuration/Generator/python/SingleElectronE120EHCAL_cfi.py nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('ZDCPG_DIGI.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-DIGI')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Special settings
process.g4SimHits.UseMagneticField = cms.bool(False)
process.g4SimHits.Physics.DefaultCutValue = cms.double(10.)
process.g4SimHits.Generator.MinEtaCut = cms.double(-9.0)
process.g4SimHits.Generator.MaxEtaCut =  cms.double(9.0)
process.g4SimHits.Watchers = cms.VPSet(cms.PSet(
    type = cms.string('ZdcTestAnalysis'),
    ZdcTestAnalysis = cms.PSet(
        Verbosity = cms.int32(0),
		StepNtupleFlag = cms.int32(0),
        EventNtupleFlag = cms.int32(0),
        StepNtupleFileName = cms.string('stepNtuple.root'),
        EventNtupleFileName = cms.string('eventNtuple.root')
	)   	
))
process.g4SimHits.ZdcSD.UseShowerLibrary = cms.bool(True)
process.g4SimHits.StackingAction.MaxTrackTime = cms.double(10000.)
process.g4SimHits.CaloSD.TmaxHit = cms.double(10000.)




# Path and EndPath definitions
#process.generation_step = cms.Path(process.pgen)
process.generation_step = cms.Path(process.ProductionFilterSequence+process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

##Keep ZDC Digis
process.RAWSIMoutput.outputCommands += ['drop *_*_*_*']
process.RAWSIMoutput.outputCommands += ['keep PCaloHits_g4SimHits_ZDCHITS_*']
process.RAWSIMoutput.outputCommands += ['keep recoGenParticles_genParticles_*_*']
process.RAWSIMoutput.outputCommands += ['keep ints_genParticles_*_*']
process.RAWSIMoutput.outputCommands += ['keep edmHepMCProduct_generator_*_*']
process.RAWSIMoutput.outputCommands += ['keep ZDCDataFramesSorted_simHcalUnsuppressedDigis_*_*']
