#include <Headers/plot.h>

void eMaxCutGen_study(){

  TH1::SetDefaultSumw2();
  

   TFile * fData = TFile::Open("/export/d00/scratch/rkunnawa/rootfiles/PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150320.root");
   TTree * Data_matched = (TTree*)fData->Get("matchedJets");
   TTree * Data_unmatched = (TTree*)fData->Get("unmatchedPFJets");

  TFile * fMC = TFile::Open("/export/d00/scratch/rkunnawa/rootfiles/PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150326.root");
  TTree * MC_matched = (TTree*)fMC->Get("matchedJets");
  TTree * MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");

  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_rej","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_keep","",1000,-40,10);
  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0 = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt_pfrefOverpfpt","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_pfrefOverpfpt_rej","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_pfrefOverpfpt_keep","",1000,0,10);
  
  // this cut is: 
  
  // 1 - Data, 2 - MC
  Float_t pfpt_1, pfpt_2;
  Float_t pfrefpt_2;
  Float_t calopt_1, calopt_2;
  Float_t eMax_1, eMax_2;
  Float_t chMax_1, chMax_2;
  Float_t chSum_1, chSum_2;
  Float_t phSum_1, phSum_2;
  Float_t neSum_1, neSum_2;
  Float_t muSum_1, muSum_2;
  Int_t jet55_1, jet65_1, jet80_1;
  Int_t jet55_p_1, jet65_p_1, jet80_p_1;
  Int_t jet55_2, jet65_2, jet80_2;
  Int_t jet55_p_2, jet65_p_2, jet80_p_2;

  Data_matched->SetBranchAddress("calopt",&calopt_1);
  Data_matched->SetBranchAddress("pfpt",&pfpt_1);
  Data_matched->SetBranchAddress("eMax",&eMax_1);
  Data_matched->SetBranchAddress("chMax",&chMax_1);
  Data_matched->SetBranchAddress("chSum",&chSum_1);
  Data_matched->SetBranchAddress("phSum",&phSum_1);
  Data_matched->SetBranchAddress("neSum",&neSum_1);
  Data_matched->SetBranchAddress("muSum",&muSum_1);
  Data_matched->SetBranchAddress("jet55",&jet55_1);
  Data_matched->SetBranchAddress("jet65",&jet65_1);
  Data_matched->SetBranchAddress("jet80",&jet80_1);
  Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
  Data_unmatched->SetBranchAddress("eMax",&eMax_1);
  Data_unmatched->SetBranchAddress("chMax",&chMax_1);
  Data_unmatched->SetBranchAddress("chSum",&chSum_1);
  Data_unmatched->SetBranchAddress("phSum",&phSum_1);
  Data_unmatched->SetBranchAddress("neSum",&neSum_1);
  Data_unmatched->SetBranchAddress("muSum",&muSum_1);
  Data_unmatched->SetBranchAddress("jet55",&jet55_1);
  Data_unmatched->SetBranchAddress("jet65",&jet65_1);
  Data_unmatched->SetBranchAddress("jet80",&jet80_1);
  Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("chSum",&chSum_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
  
  MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
  MC_unmatched->SetBranchAddress("eMax",&eMax_2);
  MC_unmatched->SetBranchAddress("chMax",&chMax_2);
  MC_unmatched->SetBranchAddress("chSum",&chSum_2);
  MC_unmatched->SetBranchAddress("phSum",&phSum_2);
  MC_unmatched->SetBranchAddress("neSum",&neSum_2);
  MC_unmatched->SetBranchAddress("muSum",&muSum_2);
  MC_unmatched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_unmatched->SetBranchAddress("jet55",&jet55_2);
  MC_unmatched->SetBranchAddress("jet65",&jet65_2);
  MC_unmatched->SetBranchAddress("jet80",&jet80_2);
  
  
  // data loop
//   long entries = Data_matched->GetEntries();
//   //entries = 1;
//   cout<<"matched Data ntuple "<<endl;
//   
//   for(long nentry = 0; nentry < entries; ++nentry ){
// 
//     if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
//     Data_matched->GetEntry(nentry);
//     
//     Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
//     
//     if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 ) {
//       
//       hData_Jet55_noCut->Fill(pfpt_1, jet55_p_1);
//       
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) )
// 	hData_Jet55_CutA->Fill(pfpt_1, jet55_p_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85 ) 
// 	hData_Jet55_CutA->Fill(pfpt_1, jet55_p_1);
//       
//       // if(eMax_1/pfpt_1 < (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet55_CutB->Fill(pfpt_1);
// 
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand > (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7))  )
// 	hData_Jet55_CutA_rej->Fill(pfpt_1, jet55_p_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85 )
// 	hData_Jet55_CutA_rej->Fill(pfpt_1, jet55_p_1);
//       
//       // if(eMax_1/pfpt_1 > (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet55_CutB_rej->Fill(pfpt_1);
//       
//     }
//     
//     if(jet65_1 == 1 && jet80_1 == 0 ) {
//       
//       hData_Jet65_noCut->Fill(pfpt_1);
//       
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)))
// 	hData_Jet65_CutA->Fill(pfpt_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85 ) 
// 	hData_Jet65_CutA->Fill(pfpt_1);
//       
//       // if(eMax_1/pfpt_1 < (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet65_CutB->Fill(pfpt_1);
//     
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand > (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) )
// 	hData_Jet65_CutA_rej->Fill(pfpt_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85)
// 	hData_Jet65_CutA_rej->Fill(pfpt_1);
// 
//       // if(eMax_1/pfpt_1 > (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet65_CutB_rej->Fill(pfpt_1);
// 
//     }
// 
//     if(jet80_1 == 1) {
//     
//       hData_Jet80_noCut->Fill(pfpt_1);
// 
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7) ) )
// 	hData_Jet80_CutA->Fill(pfpt_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85) 
// 	hData_Jet80_CutA->Fill(pfpt_1);
// 
//       // if(eMax_1/pfpt_1 < (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet80_CutB->Fill(pfpt_1);
//     
//       if(eMax_1/Sumcand < 0.9 && ( eMax_1/Sumcand > (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7) ) )
// 	hData_Jet80_CutA_rej->Fill(pfpt_1);
//       if(eMax_1/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85)
// 	hData_Jet80_CutA_rej->Fill(pfpt_1);
// 
//       // if(eMax_1/pfpt_1 > (22/15 * (Float_t)calopt_1/pfpt_1 - 11/15)) 
//       // 	hData_Jet80_CutB_rej->Fill(pfpt_1);
//       
//     }
//     
//   }// data ntuple loop
// 
//   // data unmatched loop:
//   entries = Data_unmatched->GetEntries();
//   //entries = 1;
//   cout<<"Unmatched Data ntuple "<<endl;
//   for(long nentry = 0; nentry < entries; ++nentry ){
// 
//     if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
//     Data_unmatched->GetEntry(nentry);
//     
//     Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
// 
//     if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 ) {
//     
//       hData_unmatched_Jet55_noCut->Fill(pfpt_1, jet55_p_1);
// 
//       if(eMax_1/Sumcand < 0.05 ) hData_unmatched_Jet55_CutA->Fill(pfpt_1, jet55_p_1);
//       else hData_unmatched_Jet55_CutA_rej->Fill(pfpt_1, jet55_p_1);
//       
//     }
// 
//     if(jet65_1 == 1 && jet80_1 == 0 ) {
// 
//       hData_unmatched_Jet65_noCut->Fill(pfpt_1);
// 
//       if(eMax_1/Sumcand < 0.05 ) hData_unmatched_Jet65_CutA->Fill(pfpt_1);
//       else hData_unmatched_Jet65_CutA_rej->Fill(pfpt_1);
//       
//     }
// 
//     if(jet80_1 == 1) {
//     
//       hData_unmatched_Jet80_noCut->Fill(pfpt_1);
// 
//       if(eMax_1/Sumcand < 0.05  ) hData_unmatched_Jet80_CutA->Fill(pfpt_1);
//       else hData_unmatched_Jet80_CutA_rej->Fill(pfpt_1);
//       
//     }
//     
//   }// data ntuple loop



 long nentries = MC_matched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at matched MC ntuple "<<endl;
  for(long nentry = 0; nentry < nentries; ++nentry){

    if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
    MC_matched->GetEntry(nentry);
    
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    Float_t ratioGenPF = pfrefpt_2/pfpt_2;
    hMC_AllTrig_noCut_pfrefOverpfpt->Fill(ratioGenPF);
    if(pfrefpt_2>0){
     hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Fill(ratioGenPF);
    }
// all triggers
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF); 
   		}
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) ){
   		hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.85 && eMax_2/Sumcand > 0.9){
    	hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
    	if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF);  
   		}
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand > (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) ){
   		hMC_AllTrig_CutA_pfrefOverpfpt_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
// jet55 !jet65 !jet80
   
//     if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
//       
//       hMC_Jet55_noCut->Fill(pfpt_2);
// 
//    if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) hGood->Fill();
//    if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) ) hGood->Fill();
//    if(calopt_2/pfpt_2 > 0.85 && eMax_2/Sumcand > 0.9) hGood->Fill();
//   
// 	hMC_Jet55_CutA->Fill(pfpt_2);
//       if(eMax_2/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85) 
// 	hMC_Jet55_CutA->Fill(pfpt_2);
// 
//       // if(eMax_2/pfpt_2 < (22/15 * (Float_t)calopt_2/pfpt_2 - 11/15)) 
//       // 	hMC_Jet55_CutB->Fill(pfpt_2);
// 
//     }
// 
// // jet65 !jet80 
//     if(jet65_2 == 1 && jet80_2 == 0){
//       
//       hMC_Jet65_noCut->Fill(pfpt_2);
// 
//       if(eMax_2/Sumcand < 0.9 && ( eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7) ) )
// 	hMC_Jet65_CutA->Fill(pfpt_2);
//       if(eMax_2/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85) 
// 	hMC_Jet65_CutA->Fill(pfpt_2);
// 
//       // if(eMax_2/pfpt_2 < (22/15 * (Float_t)calopt_2/pfpt_2 - 11/15)) 
//       // 	hMC_Jet65_CutB->Fill(pfpt_2);
// 
//     }
// 
//     
//     if(jet80_2 == 1){
//       
//       hMC_Jet80_noCut->Fill(pfpt_2);
// 
//       if(eMax_2/Sumcand < 0.9 && ( eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7) )  )
// 	hMC_Jet80_CutA->Fill(pfpt_2);
//       if(eMax_2/Sumcand >=0.9 && calopt_1/pfpt_1 > 0.85 ) 
// 	hMC_Jet80_CutA->Fill(pfpt_2);
// 
//       // if(eMax_2/pfpt_2 < (22/15 * (Float_t)calopt_2/pfpt_2 - 11/15)) 
//       // 	hMC_Jet80_CutB->Fill(pfpt_2);
// 
//     }
    
    
  }// mc ntuple loop


  long entries = MC_unmatched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at unmatched MC ntuple"<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){

    if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
    MC_unmatched->GetEntry(nentry);
    
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
//cout<<"not going to add anything here, just testing for now..."<<endl;
//     if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
//       
//       hMC_unmatched_Jet55_noCut->Fill(pfpt_2);
//       if(eMax_2/Sumcand < 0.05  ) hMC_unmatched_Jet55_CutA->Fill(pfpt_2);
//       //else hMC_unmatched_Jet55_CutA_rej->Fill(pfpt_2);
//       
//     }
// 
//     
//     if(jet65_2 == 1 && jet80_2 == 0){
//       
//       hMC_unmatched_Jet65_noCut->Fill(pfpt_2);
//       if(eMax_2/Sumcand < 0.05  ) hMC_unmatched_Jet65_CutA->Fill(pfpt_2);
//       //else hMC_unmatched_Jet65_CutA_rej->Fill(pfpt_2);
//       
//     }
// 
//     
//     if(jet80_2 == 1){
//       
//       hMC_unmatched_Jet80_noCut->Fill(pfpt_2);
//       if(eMax_2/Sumcand < 0.05 ) hMC_unmatched_Jet80_CutA->Fill(pfpt_2);
//       //else hMC_unmatched_Jet80_CutA_rej->Fill(pfpt_2);
//       
//     }
    
    
  }// mc unmatched  ntuple loop
  


  TFile fout("PbPb_MCGenStudy_YetkinCuts_matched_slantedlinecalopfpt_addingunmatched_exclusionhighertriggers_eMaxSumcand_A.root","RECREATE");
   hMC_AllTrig_noCut_pfrefOverpfpt->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_rej->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_keep->Write();
   hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Write();

  // add the unmatched histograms to the matched ones to get the final cut efficiency
  TCanvas * cGenJetMC = new TCanvas("cGenJetMC","",800,600);
  cGenJetMC->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt->SetXTitle("GenJet p_{T}/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt=hMC_AllTrig_noCut_pfrefOverpfpt->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt: "<<hMC_AllTrig_noCut_pfrefOverpfpt->GetEntries()<<endl;;
  
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->SetMarkerColor(kRed);
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_rej=hMC_AllTrig_CutA_pfrefOverpfpt_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_rej->GetEntries()<<endl;;
    
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->SetMarkerColor(kGreen);
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_keep=hMC_AllTrig_CutA_pfrefOverpfpt_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_full = myLegend(0.2,0.6,0.2,0.8);
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt,Form("Matched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt),"pl");
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_keep,Form("Matched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_keep),"pl");
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_rej,Form("Matched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_rej),"pl");
      LpfrefOverpfpt_full->SetTextSize(0.03);
      LpfrefOverpfpt_full->Draw();
      
  cGenJetMC->SaveAs("hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_fullrange.pdf","RECREATE");

  TCanvas * cGenJetMC_pfrefptgt0 = new TCanvas("cGenJetMC_pfrefptgt0","",800,600);
  cGenJetMC_pfrefptgt0->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetXTitle("GenJet p_{T}/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0=hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0: "<<hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->SetMarkerColor(kRed);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej=hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->SetMarkerColor(kGreen);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep=hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt = myLegend(0.4,0.7,0.4,0.9);
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0,Form("Matched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0),"pl");
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep,Form("Matched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep),"pl");
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej,Form("Matched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej),"pl");
      LpfrefOverpfpt->SetTextSize(0.03);
      LpfrefOverpfpt->Draw();
      
  cGenJetMC_pfrefptgt0->SaveAs("hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_pfrefptgt0.pdf","RECREATE");
}
