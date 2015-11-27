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
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/024A092C-8A94-E511-8DDB-02163E012741.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/08FE7E42-8A94-E511-8943-02163E013523.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/0AF7D4D4-8394-E511-A3DC-02163E014407.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/0E341D60-8394-E511-A884-02163E0125EB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/10C4D720-8A94-E511-B5D4-02163E01229E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/12B9321F-8A94-E511-9DC5-02163E013813.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/141F209E-8394-E511-8F36-02163E014648.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/166DD264-8394-E511-91FB-02163E0143FA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/1886DED9-7D94-E511-AFC3-02163E011BB3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/1C9FDB35-8A94-E511-B43C-02163E0140FA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/1CC507DC-7D94-E511-9029-02163E0129BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/1E0C7101-7E94-E511-B32E-02163E012AD4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/1E774FB5-7B94-E511-9417-02163E011EB6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/20D33741-7C94-E511-8D92-02163E0133F4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/20E0FB7C-8394-E511-AE39-02163E014408.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/22634E3A-8A94-E511-A991-02163E0138A7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/28FAE87C-8394-E511-BEA1-02163E0123FB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/2AEECB1A-8A94-E511-859E-02163E013519.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/2AF8F01D-8A94-E511-82DD-02163E01361E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/2E65C46F-8A94-E511-A3B0-02163E014719.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/30947E4D-8A94-E511-80A1-02163E013904.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3450D097-8394-E511-BDBB-02163E012680.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/348C0121-7E94-E511-9962-02163E0144F4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3661CED9-7B94-E511-B71D-02163E014607.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3860087E-8394-E511-9BB0-02163E011ACA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3862C175-8A94-E511-8FB8-02163E014669.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3CD51D75-8A94-E511-9F74-02163E0133E4.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3E2F6E0F-8A94-E511-8CD7-02163E014191.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/3EA25E8A-8394-E511-B8D4-02163E0118FD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4003FC46-8A94-E511-B537-02163E01395B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4645AA1E-8A94-E511-9E3F-02163E012B9C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/489F5415-7E94-E511-B456-02163E0138E0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/48FAFE35-8A94-E511-8DBF-02163E013470.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4A7B836F-8A94-E511-9327-02163E01436F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4ADD75C7-8394-E511-B68E-02163E0142DB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4C1B232E-8A94-E511-B497-02163E011B2E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4C519427-8A94-E511-B18B-02163E0138B9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4C5C8BAE-7994-E511-9292-02163E0125EB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/4E0B02A0-8394-E511-9E36-02163E014469.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/50157B50-8A94-E511-A894-02163E014663.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/50F3AACB-8394-E511-8B5C-02163E0145C3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/54719E6A-9294-E511-9124-02163E014367.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/5A658EE5-7D94-E511-939D-02163E011807.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/5AA73BDA-7B94-E511-84D8-02163E0146E0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/5AEB1378-8A94-E511-8018-02163E011F3A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/5EE03357-7E94-E511-B3A6-02163E0139BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6033445E-8A94-E511-9ABD-02163E01454C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6066AD26-8A94-E511-8F03-02163E0146A8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/608004E2-7B94-E511-AA64-02163E011E4A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6256A9D1-7D94-E511-A35D-02163E0135E2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/62D59169-8394-E511-9191-02163E0141E6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/62E09E2C-8A94-E511-8704-02163E0143D1.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6460F68E-8A94-E511-A656-02163E0145D6.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/64CC2A2D-7E94-E511-BEE4-02163E011827.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/665EC062-8394-E511-A2DC-02163E01390D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6835351D-8A94-E511-86BF-02163E011D7F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/689EE2E7-8094-E511-BB53-02163E0135C9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/68D29560-8A94-E511-9864-02163E01254F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6CAE770D-8A94-E511-83E4-02163E014268.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/6E61818A-8A94-E511-B868-02163E014367.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/7065B1ED-7D94-E511-A97F-02163E01415B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/707065FB-7E94-E511-9477-02163E014652.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/7252D820-8A94-E511-9993-02163E0129BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/745AB809-8A94-E511-A7F1-02163E01398D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/76588D04-7E94-E511-9E69-02163E01462B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/7685E419-8A94-E511-B378-02163E01390D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/78420B06-7C94-E511-ACEC-02163E0135E2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/7852113C-8A94-E511-A44C-02163E013859.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/7E23E8EA-7D94-E511-807D-02163E0138CF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/805A0C6F-8394-E511-8782-02163E011BC7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/82452F35-8A94-E511-815F-02163E014761.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8418ACD6-7D94-E511-9C17-02163E011B00.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8447E98E-7794-E511-B679-02163E01381C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/84AF82F0-7D94-E511-BFFE-02163E01239A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8617F8E8-7D94-E511-BB89-02163E0123EB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8661A521-8594-E511-8C0C-02163E012BB9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/88ABC9BF-8094-E511-9552-02163E0144A5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8C6CF706-7E94-E511-8597-02163E0141C3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8CD47AEE-7D94-E511-A269-02163E0144D5.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8E22FB2A-8A94-E511-B754-02163E013525.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/8E8A8A58-8394-E511-8758-02163E0134BE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/90CBF9FD-8A94-E511-AE20-02163E0134FE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/90E97ECC-7D94-E511-ADCD-02163E012A39.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/925808FA-7D94-E511-ACE5-02163E013668.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/926E3DE1-9194-E511-A7E1-02163E01367B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9413D126-8A94-E511-A02F-02163E013905.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9483BE0C-7E94-E511-AF10-02163E0140E3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/94EBBCBA-8C94-E511-83FF-02163E0128BD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/96097B68-7E94-E511-87DA-02163E011ACF.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/96C5B181-7C94-E511-B25D-02163E0146E1.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/96FCBD55-8394-E511-A9D4-02163E013904.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9ADEA6EA-8394-E511-A135-02163E0143BA.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9C39058A-8394-E511-A79B-02163E013953.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9E50FCDE-9194-E511-9999-02163E011BC2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/9ED9301A-8A94-E511-80DC-02163E01189F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A0DD26FD-7D94-E511-AE6F-02163E01425D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A2792383-8A94-E511-B1FE-02163E0120D9.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A27CDBDB-7B94-E511-90B9-02163E014367.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A2AFACD6-7C94-E511-A923-02163E014646.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A421DCD7-7D94-E511-9728-02163E013762.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A65B8B30-8A94-E511-BBF6-02163E0141FE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/A80AFFD3-7B94-E511-BA5D-02163E014501.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/AE8AB2DB-7B94-E511-94BD-02163E011BB3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B0E417DC-7D94-E511-B311-02163E0127BE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B0ED0515-8A94-E511-B2D0-02163E0138CC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B44C7D44-8A94-E511-B777-02163E0119A0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B471C135-8A94-E511-AA67-02163E013454.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B4D11621-8A94-E511-BDBE-02163E0120BB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B6683631-8A94-E511-953B-02163E01389C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B6978431-8A94-E511-853B-02163E014682.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B83EEB3F-8A94-E511-B9A9-02163E01191B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/B84C5C25-8A94-E511-8136-02163E011F06.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C27D2A96-8394-E511-9C2B-02163E0119D3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C2B90014-8A94-E511-98F9-02163E01386D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C69AAAFA-7D94-E511-A08A-02163E01375D.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C6D86510-7E94-E511-AA0C-02163E01456B.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C847CC1D-8A94-E511-A653-02163E014655.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C857836F-8A94-E511-AD66-02163E01436F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C8698024-8A94-E511-A183-02163E011F10.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C8DE6EBB-7B94-E511-9196-02163E011893.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/C8F8B304-7E94-E511-A61C-02163E014511.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/CA2FBA60-8394-E511-9B43-02163E013647.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/CA3694CD-7B94-E511-B6B7-02163E014438.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/CABE0D27-8A94-E511-A46A-02163E01282C.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/CC3DA4EE-7D94-E511-AAAD-02163E0136FD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/CC9682D6-7C94-E511-8615-02163E014646.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D0BD03A4-8594-E511-ABFF-02163E014390.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D0BE9750-8A94-E511-822A-02163E0128AE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D2ABC1EE-7D94-E511-8953-02163E0143D3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D40202E7-7D94-E511-B6E2-02163E01443E.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D42129D0-7B94-E511-B5BE-02163E01430A.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D61E1626-8A94-E511-900B-02163E0138D8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D62D405D-8394-E511-8555-02163E01285F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D80A9EDA-7D94-E511-B39B-02163E0138D2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D8751433-8A94-E511-9021-02163E01369F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/D89AB6C0-7B94-E511-A87B-02163E013555.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/DA5A48FC-7D94-E511-A5BB-02163E014719.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/DC48FF95-8394-E511-ADA1-02163E0136F3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/DEAB01E1-8A94-E511-ADA9-02163E0133E1.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/DEEA41F8-7B94-E511-B936-02163E0142B0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E0F0502D-8A94-E511-B36E-02163E014192.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E0F116DE-7B94-E511-8870-02163E0133BB.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E21C7D6B-8394-E511-BCB8-02163E011C36.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E29503EF-7D94-E511-823E-02163E0138FE.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E2E73E0A-8A94-E511-8DC3-02163E0135F8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E4425764-7E94-E511-91BC-02163E012021.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E467C6E4-7D94-E511-B948-02163E011DDC.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E61AAA2B-8A94-E511-9693-02163E0122F0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/E8886F28-8A94-E511-8FBF-02163E011899.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/EC48DC5A-7C94-E511-8FD4-02163E0141E0.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/EE675483-8394-E511-888D-02163E0138A7.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F073CD36-8A94-E511-B3BF-02163E011B1F.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F0A374E1-8594-E511-9A7E-02163E0142B3.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F20C8E1C-8A94-E511-908A-02163E0136E8.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F49EBF3E-8494-E511-B8DB-02163E014732.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F8D630E8-7D94-E511-99C2-02163E014503.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F8E1438D-8394-E511-B12E-02163E0135FD.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F8EAB1DF-8C94-E511-893D-02163E014741.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/F8EF42BF-8A94-E511-9797-02163E014451.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/FAF01811-7E94-E511-8A36-02163E0142D2.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/FC14886C-8394-E511-8D5B-02163E011C36.root',
'/store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/695/00000/FC9B23F2-7B94-E511-9A70-02163E0142C5.root'
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
                                   fileName = cms.string('ForwardAnalyzerRun262695_MinBiasHF1AndExpress.root')
                                   )
                                   
import HLTrigger.HLTfilters.hltHighLevel_cfi                                  
process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBias.HLTPaths = [
        "HLT_HIL1MinimumBiasHF1ANDExpress_v*"
]

process.fwdana = cms.EDAnalyzer('ForwardAnalyzer', 
  #                              l1GtRR=cms.InputTag("GtDigis")
                                )

# process.upcvertexana = cms.EDAnalyzer('UPCVertexAnalyzer',
#                                       vertexCollection=cms.string("offlinePrimaryVerticesWithBS")
#                                       )
# process.whatever = cms.Path(process.hltMinBias * process.your_analyzer)
                                      
process.p = cms.Path(process.hltMinBias*process.fwdana)
#process.p = cms.Path(process.zdcreco*process.fwdana)
#process.p = cms.Path(process.fwdana*process.upcvertexana)