#
import FWCore.ParameterSet.Config as cms

process = cms.Process('ReRECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.load('Configuration/StandardSequences/GeometryExtended_cff')
#process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
#process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
#process.load('Configuration/StandardSequences/L1Reco_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
#process.load('DQMOffline/Configuration/DQMOffline_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True) 
)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( 
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_100_1_v9O.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_101_1_Bok.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_102_1_shj.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_103_1_eZa.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_104_1_1f4.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_105_1_kRB.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_106_1_oQb.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_107_1_4im.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_108_1_zk2.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_109_1_rkb.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_10_1_As3.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_110_1_Svi.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_111_1_qyM.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_112_1_jF8.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_113_1_zjQ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_114_1_Gae.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_115_1_cSY.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_116_1_ItW.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_117_1_AHE.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_118_1_KPc.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_119_1_z7Y.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_11_1_Cwm.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_120_1_yRX.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_121_1_mgB.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_122_1_2jC.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_123_1_rL1.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_124_1_KJz.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_125_1_jGO.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_126_1_nkA.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_127_1_r4n.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_128_1_i63.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_129_1_jrM.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_12_1_qPH.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_130_1_HHL.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_131_1_HUh.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_132_1_TaB.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_133_1_JML.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_134_1_yKa.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_135_1_dcp.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_136_1_Ag1.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_137_1_2NY.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_138_1_Ci8.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_139_1_zo0.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_13_1_uhY.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_140_1_2DZ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_141_1_9TA.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_142_1_4QW.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_143_1_bKH.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_144_1_30O.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_14_1_xZ0.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_15_1_Qs1.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_16_1_Wam.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_17_1_XX4.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_18_1_6jd.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_19_1_te4.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_1_1_TeQ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_20_1_pLb.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_21_1_rAm.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_22_1_zlp.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_23_1_hTQ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_24_1_xmP.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_25_1_INa.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_26_1_fCx.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_27_1_32H.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_28_1_cH9.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_29_1_PQ6.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_2_1_scu.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_30_1_4It.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_31_1_qNU.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_32_1_sO7.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_33_1_T9o.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_34_1_Roz.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_35_1_Qgs.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_36_1_HsE.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_37_1_CsK.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_38_1_AS4.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_39_1_ViD.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_3_1_5PD.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_40_1_xOZ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_41_1_NMF.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_42_1_bVT.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_43_1_zhN.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_44_1_qGI.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_45_1_T86.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_46_1_0hS.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_47_1_lRC.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_48_1_cbP.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_49_1_FHm.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_4_1_Nld.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_50_1_Hl2.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_51_1_5ug.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_52_1_Q3d.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_53_1_9OO.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_54_1_SO5.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_55_1_pMi.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_56_1_wQV.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_57_1_s9D.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_58_1_x9F.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_59_1_ItG.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_5_1_YWP.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_60_1_Kpk.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_61_1_air.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_62_1_OKQ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_63_1_OeU.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_64_1_Wli.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_65_1_WtT.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_66_1_xOw.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_67_1_m1D.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_68_1_tbQ.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_69_1_rtc.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_6_1_a4p.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_70_1_lCE.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_71_1_NU1.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_72_1_P3F.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_73_1_U4W.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_74_1_ygg.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_75_1_2Hv.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_76_1_vab.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_77_1_7f5.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_78_1_hmI.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_79_1_upa.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_7_1_jET.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_80_1_oM9.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_81_1_EDx.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_82_1_Q9U.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_83_1_uTW.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_84_1_SIw.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_85_1_UN1.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_86_1_min.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_87_1_zG0.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_88_1_JZc.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_89_1_uEF.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_8_1_Twr.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_90_1_APT.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_91_1_4sA.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_92_1_uev.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_93_1_lFK.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_94_1_dmq.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_95_1_JMy.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_96_1_EdM.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_97_1_Q2e.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_98_1_EVm.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_99_1_Kk6.root',
'rfio:/castor/cern.ch/cms/store/caf/user/yilmaz/HIRun2010_ExpressPhysics_Run150476_RECO_v0/HLT_HIMinBiasHF_9_1_pcL.root'
)
)


# Other statements
process.GlobalTag.globaltag = 'GR_R_39X_V1::All'

process.endjob_step = cms.Path(process.endOfProcess)

process.es_prefer_GlobalTag = cms.ESPrefer('PoolDBESSource','GlobalTag')
process.prefer("GlobalTag")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('150476/html/PbPb_YetkinSkim_AllEvents_ZDCana_150476.root')
)
#    counterbir = cms.string('BothSides_CollisionEvents'),
#    HLTTag = cms.InputTag("TriggerResults::HLT"),

process.demo = cms.EDAnalyzer('MargueriteZDCAnalyzer',
    RunNo = cms.untracked.int32(150476),
    baseHtmlDir = cms.untracked.string('150476/html/'),
    printHTML = cms.untracked.bool(True),
    printZDCHTML = cms.untracked.bool(True)
)

process.p = cms.Path(process.zdcreco*process.demo)
cms.Schedule(process.p,process.endjob_step)
