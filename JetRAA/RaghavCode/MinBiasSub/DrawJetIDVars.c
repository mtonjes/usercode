  cTriggerCombination->SaveAs(Form("Plots/TriggerCombination_YetkinCuts_R0p%d.pdf",radius),"RECREATE");
//#if 0
  TCanvas * cchMaxJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet55_keep[i] = new TCanvas(Form("cchMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet55_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet55_keep[i]->Print("base");
    hMC_chMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet55_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_chMaxJtpt_jet55_keep[i]=hMC_chMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet55_keep[i]>0){
       hMC_chMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet55_keep[i]=hData_chMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet55_keep[i]>0){
      if(nMC_chMaxJtpt_jet55_keep[i]<=0){
        hData_chMaxJtpt_jet55_keep[i]->Print("base");
        hData_chMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet55_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet55_keep[i] = new TCanvas(Form("ceMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet55_keep[i]->Print("base");
    hMC_eMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet55_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_eMaxJtpt_jet55_keep[i]=hMC_eMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet55_keep[i]>0){
       hMC_eMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet55_keep[i]=hData_eMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet55_keep[i]>0){
      if(nMC_eMaxJtpt_jet55_keep[i]<=0){
        hData_eMaxJtpt_jet55_keep[i]->Print("base");
        hData_eMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet55_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet55_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet55_keep[i] = new TCanvas(Form("cphMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet55_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet55_keep[i]->Print("base");
    hMC_phMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet55_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_phMaxJtpt_jet55_keep[i]=hMC_phMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet55_keep[i]>0){
       hMC_phMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet55_keep[i]=hData_phMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet55_keep[i]>0){
      if(nMC_phMaxJtpt_jet55_keep[i]<=0){
        hData_phMaxJtpt_jet55_keep[i]->Print("base");
        hData_phMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet55_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet55_keep[i] = new TCanvas(Form("cneMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet55_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet55_keep[i]->Print("base");
    hMC_neMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet55_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_neMaxJtpt_jet55_keep[i]=hMC_neMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet55_keep[i]>0){
       hMC_neMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet55_keep[i]=hData_neMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet55_keep[i]>0){
      if(nMC_neMaxJtpt_jet55_keep[i]<=0){
        hData_neMaxJtpt_jet55_keep[i]->Print("base");
        hData_neMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet55_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet55_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet55_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet55_keep[i]->Print("base");
    hMC_muMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet55_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_muMaxJtpt_jet55_keep[i]=hMC_muMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet55_keep[i]>0){
       hMC_muMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet55_keep[i]=hData_muMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet55_keep[i]>0){
      if(nMC_muMaxJtpt_jet55_keep[i]<=0){
        hData_muMaxJtpt_jet55_keep[i]->Print("base");
        hData_muMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet55_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet55_keep[i] = new TCanvas(Form("cchSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet55_keep[i]->SetLogy();
    hMC_chSumJtpt_jet55_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet55_keep[i]->Print("base");
    hMC_chSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet55_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_chSumJtpt_jet55_keep[i]=hMC_chSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet55_keep[i]>0){
       hMC_chSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet55_keep[i]=hData_chSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet55_keep[i]>0){
      if(nMC_chSumJtpt_jet55_keep[i]<=0){
        hData_chSumJtpt_jet55_keep[i]->Print("base");
        hData_chSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet55_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet55_keep[i] = new TCanvas(Form("ceSumJtpt_jet55_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet55_keep[i]->SetLogy();
    hMC_eSumJtpt_jet55_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet55_keep[i]->Print("base");
    hMC_eSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet55_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_eSumJtpt_jet55_keep[i]=hMC_eSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet55_keep[i]>0){
       hMC_eSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet55_keep[i]=hData_eSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet55_keep[i]>0){
      if(nMC_eSumJtpt_jet55_keep[i]<=0){
        hData_eSumJtpt_jet55_keep[i]->Print("base");
        hData_eSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet55_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet55_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet55_keep[i] = new TCanvas(Form("cphSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet55_keep[i]->SetLogy();
    hMC_phSumJtpt_jet55_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet55_keep[i]->Print("base");
    hMC_phSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet55_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_phSumJtpt_jet55_keep[i]=hMC_phSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet55_keep[i]>0){
       hMC_phSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet55_keep[i]=hData_phSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet55_keep[i]>0){
      if(nMC_phSumJtpt_jet55_keep[i]<=0){
        hData_phSumJtpt_jet55_keep[i]->Print("base");
        hData_phSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet55_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet55_keep[i] = new TCanvas(Form("cneSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet55_keep[i]->SetLogy();
    hMC_neSumJtpt_jet55_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet55_keep[i]->Print("base");
    hMC_neSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet55_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_neSumJtpt_jet55_keep[i]=hMC_neSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet55_keep[i]>0){
       hMC_neSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet55_keep[i]=hData_neSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet55_keep[i]>0){
      if(nMC_neSumJtpt_jet55_keep[i]<=0){
        hData_neSumJtpt_jet55_keep[i]->Print("base");
        hData_neSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet55_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet55_keep[i] = new TCanvas(Form("cmuSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet55_keep[i]->SetLogy();
    hMC_muSumJtpt_jet55_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet55_keep[i]->Print("base");
    hMC_muSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet55_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_muSumJtpt_jet55_keep[i]=hMC_muSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet55_keep[i]>0){
       hMC_muSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet55_keep[i]=hData_muSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet55_keep[i]>0){
      if(nMC_muSumJtpt_jet55_keep[i]<=0){
        hData_muSumJtpt_jet55_keep[i]->Print("base");
        hData_muSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet55_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet55_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet55_rej[i] = new TCanvas(Form("cchMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet55_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet55_rej[i]->Print("base");
    hMC_chMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet55_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_chMaxJtpt_jet55_rej[i]=hMC_chMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet55_rej[i]>0){
       hMC_chMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet55_rej[i]=hData_chMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet55_rej[i]>0){
      if(nMC_chMaxJtpt_jet55_rej[i]<=0){
        hData_chMaxJtpt_jet55_rej[i]->Print("base");
        hData_chMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet55_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet55_rej[i] = new TCanvas(Form("ceMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet55_rej[i]->Print("base");
    hMC_eMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet55_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_eMaxJtpt_jet55_rej[i]=hMC_eMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet55_rej[i]>0){
       hMC_eMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet55_rej[i]=hData_eMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet55_rej[i]>0){
      if(nMC_eMaxJtpt_jet55_rej[i]<=0){
        hData_eMaxJtpt_jet55_rej[i]->Print("base");
        hData_eMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet55_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet55_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet55_rej[i] = new TCanvas(Form("cphMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet55_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet55_rej[i]->Print("base");
    hMC_phMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet55_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_phMaxJtpt_jet55_rej[i]=hMC_phMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet55_rej[i]>0){
       hMC_phMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet55_rej[i]=hData_phMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet55_rej[i]>0){
      if(nMC_phMaxJtpt_jet55_rej[i]<=0){
        hData_phMaxJtpt_jet55_rej[i]->Print("base");
        hData_phMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet55_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet55_rej[i] = new TCanvas(Form("cneMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet55_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet55_rej[i]->Print("base");
    hMC_neMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet55_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_neMaxJtpt_jet55_rej[i]=hMC_neMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet55_rej[i]>0){
       hMC_neMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet55_rej[i]=hData_neMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet55_rej[i]>0){
      if(nMC_neMaxJtpt_jet55_rej[i]<=0){
        hData_neMaxJtpt_jet55_rej[i]->Print("base");
        hData_neMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet55_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet55_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet55_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet55_rej[i]->Print("base");
    hMC_muMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet55_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_muMaxJtpt_jet55_rej[i]=hMC_muMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet55_rej[i]>0){
       hMC_muMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet55_rej[i]=hData_muMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet55_rej[i]>0){
      if(nMC_muMaxJtpt_jet55_rej[i]<=0){
        hData_muMaxJtpt_jet55_rej[i]->Print("base");
        hData_muMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet55_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet55_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet55_rej[i] = new TCanvas(Form("cchSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet55_rej[i]->SetLogy();
    hMC_chSumJtpt_jet55_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet55_rej[i]->Print("base");
    hMC_chSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet55_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_chSumJtpt_jet55_rej[i]=hMC_chSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet55_rej[i]>0){
       hMC_chSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet55_rej[i]=hData_chSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet55_rej[i]>0){
      if(nMC_chSumJtpt_jet55_rej[i]<=0){
        hData_chSumJtpt_jet55_rej[i]->Print("base");
        hData_chSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet55_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet55_rej[i] = new TCanvas(Form("ceSumJtpt_jet55_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet55_rej[i]->SetLogy();
    hMC_eSumJtpt_jet55_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet55_rej[i]->Print("base");
    hMC_eSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet55_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_eSumJtpt_jet55_rej[i]=hMC_eSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet55_rej[i]>0){
       hMC_eSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet55_rej[i]=hData_eSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet55_rej[i]>0){
      if(nMC_eSumJtpt_jet55_rej[i]<=0){
        hData_eSumJtpt_jet55_rej[i]->Print("base");
        hData_eSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet55_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet55_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet55_rej[i] = new TCanvas(Form("cphSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet55_rej[i]->SetLogy();
    hMC_phSumJtpt_jet55_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet55_rej[i]->Print("base");
    hMC_phSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet55_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_phSumJtpt_jet55_rej[i]=hMC_phSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet55_rej[i]>0){
       hMC_phSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet55_rej[i]=hData_phSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet55_rej[i]>0){
      if(nMC_phSumJtpt_jet55_rej[i]<=0){
        hData_phSumJtpt_jet55_rej[i]->Print("base");
        hData_phSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet55_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet55_rej[i] = new TCanvas(Form("cneSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet55_rej[i]->SetLogy();
    hMC_neSumJtpt_jet55_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet55_rej[i]->Print("base");
    hMC_neSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet55_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_neSumJtpt_jet55_rej[i]=hMC_neSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet55_rej[i]>0){
       hMC_neSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet55_rej[i]=hData_neSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet55_rej[i]>0){
      if(nMC_neSumJtpt_jet55_rej[i]<=0){
        hData_neSumJtpt_jet55_rej[i]->Print("base");
        hData_neSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet55_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet55_rej[i] = new TCanvas(Form("cmuSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet55_rej[i]->SetLogy();
    hMC_muSumJtpt_jet55_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet55_rej[i]->Print("base");
    hMC_muSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet55_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_muSumJtpt_jet55_rej[i]=hMC_muSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet55_rej[i]>0){
       hMC_muSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet55_rej[i]=hData_muSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet55_rej[i]>0){
      if(nMC_muSumJtpt_jet55_rej[i]<=0){
        hData_muSumJtpt_jet55_rej[i]->Print("base");
        hData_muSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet55_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  } 
//#endif
  TCanvas * cchMaxJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_keep[i] = new TCanvas(Form("cchMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_keep[i]->Print("base");
    hMC_chMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_chMaxJtpt_jet65_keep[i]=hMC_chMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet65_keep[i]>0){
       hMC_chMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet65_keep[i]=hData_chMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet65_keep[i]>0){
      if(nMC_chMaxJtpt_jet65_keep[i]<=0){
        hData_chMaxJtpt_jet65_keep[i]->Print("base");
        hData_chMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet65_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_keep[i] = new TCanvas(Form("ceMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_keep[i]->Print("base");
    hMC_eMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_eMaxJtpt_jet65_keep[i]=hMC_eMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet65_keep[i]>0){
       hMC_eMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet65_keep[i]=hData_eMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet65_keep[i]>0){
      if(nMC_eMaxJtpt_jet65_keep[i]<=0){
        hData_eMaxJtpt_jet65_keep[i]->Print("base");
        hData_eMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet65_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_keep[i] = new TCanvas(Form("cphMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_keep[i]->Print("base");
    hMC_phMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_phMaxJtpt_jet65_keep[i]=hMC_phMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet65_keep[i]>0){
       hMC_phMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet65_keep[i]=hData_phMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet65_keep[i]>0){
      if(nMC_phMaxJtpt_jet65_keep[i]<=0){
        hData_phMaxJtpt_jet65_keep[i]->Print("base");
        hData_phMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet65_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_keep[i] = new TCanvas(Form("cneMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_keep[i]->Print("base");
    hMC_neMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_neMaxJtpt_jet65_keep[i]=hMC_neMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet65_keep[i]>0){
       hMC_neMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet65_keep[i]=hData_neMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet65_keep[i]>0){
      if(nMC_neMaxJtpt_jet65_keep[i]<=0){
        hData_neMaxJtpt_jet65_keep[i]->Print("base");
        hData_neMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet65_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_keep[i]->Print("base");
    hMC_muMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_muMaxJtpt_jet65_keep[i]=hMC_muMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet65_keep[i]>0){
       hMC_muMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet65_keep[i]=hData_muMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet65_keep[i]>0){
      if(nMC_muMaxJtpt_jet65_keep[i]<=0){
        hData_muMaxJtpt_jet65_keep[i]->Print("base");
        hData_muMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet65_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet65_keep[i] = new TCanvas(Form("cchSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet65_keep[i]->SetLogy();
    hMC_chSumJtpt_jet65_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet65_keep[i]->Print("base");
    hMC_chSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet65_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_chSumJtpt_jet65_keep[i]=hMC_chSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet65_keep[i]>0){
       hMC_chSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet65_keep[i]=hData_chSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet65_keep[i]>0){
      if(nMC_chSumJtpt_jet65_keep[i]<=0){
        hData_chSumJtpt_jet65_keep[i]->Print("base");
        hData_chSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet65_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_keep[i] = new TCanvas(Form("ceSumJtpt_jet65_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet65_keep[i]->SetLogy();
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_keep[i]->Print("base");
    hMC_eSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_eSumJtpt_jet65_keep[i]=hMC_eSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet65_keep[i]>0){
       hMC_eSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet65_keep[i]=hData_eSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet65_keep[i]>0){
      if(nMC_eSumJtpt_jet65_keep[i]<=0){
        hData_eSumJtpt_jet65_keep[i]->Print("base");
        hData_eSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet65_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_keep[i] = new TCanvas(Form("cphSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet65_keep[i]->SetLogy();
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_keep[i]->Print("base");
    hMC_phSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_phSumJtpt_jet65_keep[i]=hMC_phSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet65_keep[i]>0){
       hMC_phSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet65_keep[i]=hData_phSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet65_keep[i]>0){
      if(nMC_phSumJtpt_jet65_keep[i]<=0){
        hData_phSumJtpt_jet65_keep[i]->Print("base");
        hData_phSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet65_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_keep[i] = new TCanvas(Form("cneSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet65_keep[i]->SetLogy();
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_keep[i]->Print("base");
    hMC_neSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_neSumJtpt_jet65_keep[i]=hMC_neSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet65_keep[i]>0){
       hMC_neSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet65_keep[i]=hData_neSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet65_keep[i]>0){
      if(nMC_neSumJtpt_jet65_keep[i]<=0){
        hData_neSumJtpt_jet65_keep[i]->Print("base");
        hData_neSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet65_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_keep[i] = new TCanvas(Form("cmuSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_keep[i]->SetLogy();
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_keep[i]->Print("base");
    hMC_muSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_muSumJtpt_jet65_keep[i]=hMC_muSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet65_keep[i]>0){
       hMC_muSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet65_keep[i]=hData_muSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet65_keep[i]>0){
      if(nMC_muSumJtpt_jet65_keep[i]<=0){
        hData_muSumJtpt_jet65_keep[i]->Print("base");
        hData_muSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet65_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet65_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_rej[i] = new TCanvas(Form("cchMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_rej[i]->Print("base");
    hMC_chMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_chMaxJtpt_jet65_rej[i]=hMC_chMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet65_rej[i]>0){
       hMC_chMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet65_rej[i]=hData_chMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet65_rej[i]>0){
      if(nMC_chMaxJtpt_jet65_rej[i]<=0){
        hData_chMaxJtpt_jet65_rej[i]->Print("base");
        hData_chMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet65_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_rej[i] = new TCanvas(Form("ceMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_rej[i]->Print("base");
    hMC_eMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_eMaxJtpt_jet65_rej[i]=hMC_eMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet65_rej[i]>0){
       hMC_eMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet65_rej[i]=hData_eMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet65_rej[i]>0){
      if(nMC_eMaxJtpt_jet65_rej[i]<=0){
        hData_eMaxJtpt_jet65_rej[i]->Print("base");
        hData_eMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet65_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_rej[i] = new TCanvas(Form("cphMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_rej[i]->Print("base");
    hMC_phMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_phMaxJtpt_jet65_rej[i]=hMC_phMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet65_rej[i]>0){
       hMC_phMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet65_rej[i]=hData_phMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet65_rej[i]>0){
      if(nMC_phMaxJtpt_jet65_rej[i]<=0){
        hData_phMaxJtpt_jet65_rej[i]->Print("base");
        hData_phMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet65_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_rej[i] = new TCanvas(Form("cneMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_rej[i]->Print("base");
    hMC_neMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_neMaxJtpt_jet65_rej[i]=hMC_neMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet65_rej[i]>0){
       hMC_neMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet65_rej[i]=hData_neMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet65_rej[i]>0){
      if(nMC_neMaxJtpt_jet65_rej[i]<=0){
        hData_neMaxJtpt_jet65_rej[i]->Print("base");
        hData_neMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet65_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_rej[i]->Print("base");
    hMC_muMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_muMaxJtpt_jet65_rej[i]=hMC_muMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet65_rej[i]>0){
       hMC_muMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet65_rej[i]=hData_muMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet65_rej[i]>0){
      if(nMC_muMaxJtpt_jet65_rej[i]<=0){
        hData_muMaxJtpt_jet65_rej[i]->Print("base");
        hData_muMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet65_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet65_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet65_rej[i] = new TCanvas(Form("cchSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet65_rej[i]->SetLogy();
    hMC_chSumJtpt_jet65_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet65_rej[i]->Print("base");
    hMC_chSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet65_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_chSumJtpt_jet65_rej[i]=hMC_chSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet65_rej[i]>0){
       hMC_chSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet65_rej[i]=hData_chSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet65_rej[i]>0){
      if(nMC_chSumJtpt_jet65_rej[i]<=0){
        hData_chSumJtpt_jet65_rej[i]->Print("base");
        hData_chSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet65_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_rej[i] = new TCanvas(Form("ceSumJtpt_jet65_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet65_rej[i]->SetLogy();
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_rej[i]->Print("base");
    hMC_eSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_eSumJtpt_jet65_rej[i]=hMC_eSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet65_rej[i]>0){
       hMC_eSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet65_rej[i]=hData_eSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet65_rej[i]>0){
      if(nMC_eSumJtpt_jet65_rej[i]<=0){
        hData_eSumJtpt_jet65_rej[i]->Print("base");
        hData_eSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet65_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_rej[i] = new TCanvas(Form("cphSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet65_rej[i]->SetLogy();
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_rej[i]->Print("base");
    hMC_phSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_phSumJtpt_jet65_rej[i]=hMC_phSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet65_rej[i]>0){
       hMC_phSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet65_rej[i]=hData_phSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet65_rej[i]>0){
      if(nMC_phSumJtpt_jet65_rej[i]<=0){
        hData_phSumJtpt_jet65_rej[i]->Print("base");
        hData_phSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet65_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_rej[i] = new TCanvas(Form("cneSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet65_rej[i]->SetLogy();
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_rej[i]->Print("base");
    hMC_neSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_neSumJtpt_jet65_rej[i]=hMC_neSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet65_rej[i]>0){
       hMC_neSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet65_rej[i]=hData_neSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet65_rej[i]>0){
      if(nMC_neSumJtpt_jet65_rej[i]<=0){
        hData_neSumJtpt_jet65_rej[i]->Print("base");
        hData_neSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet65_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_rej[i] = new TCanvas(Form("cmuSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_rej[i]->SetLogy();
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_rej[i]->Print("base");
    hMC_muSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_muSumJtpt_jet65_rej[i]=hMC_muSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet65_rej[i]>0){
       hMC_muSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet65_rej[i]=hData_muSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet65_rej[i]>0){
      if(nMC_muSumJtpt_jet65_rej[i]<=0){
        hData_muSumJtpt_jet65_rej[i]->Print("base");
        hData_muSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet65_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }  

// plot jet80
  TCanvas * cchMaxJtpt_jet80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet80_keep[i] = new TCanvas(Form("cchMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet80_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet80_keep[i]->Print("base");
    hMC_chMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet80_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_chMaxJtpt_jet80_keep[i]=hMC_chMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet80_keep[i]>0){
       hMC_chMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet80_keep[i]=hData_chMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet80_keep[i]>0){
      if(nMC_chMaxJtpt_jet80_keep[i]<=0){
        hData_chMaxJtpt_jet80_keep[i]->Print("base");
        hData_chMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet80_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet80_keep[i] = new TCanvas(Form("ceMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet80_keep[i]->Print("base");
    hMC_eMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet80_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_eMaxJtpt_jet80_keep[i]=hMC_eMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet80_keep[i]>0){
       hMC_eMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet80_keep[i]=hData_eMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet80_keep[i]>0){
      if(nMC_eMaxJtpt_jet80_keep[i]<=0){
        hData_eMaxJtpt_jet80_keep[i]->Print("base");
        hData_eMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet80_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet80_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet80_keep[i] = new TCanvas(Form("cphMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet80_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet80_keep[i]->Print("base");
    hMC_phMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet80_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_phMaxJtpt_jet80_keep[i]=hMC_phMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet80_keep[i]>0){
       hMC_phMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet80_keep[i]=hData_phMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet80_keep[i]>0){
      if(nMC_phMaxJtpt_jet80_keep[i]<=0){
        hData_phMaxJtpt_jet80_keep[i]->Print("base");
        hData_phMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet80_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet80_keep[i] = new TCanvas(Form("cneMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet80_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet80_keep[i]->Print("base");
    hMC_neMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet80_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_neMaxJtpt_jet80_keep[i]=hMC_neMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet80_keep[i]>0){
       hMC_neMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet80_keep[i]=hData_neMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet80_keep[i]>0){
      if(nMC_neMaxJtpt_jet80_keep[i]<=0){
        hData_neMaxJtpt_jet80_keep[i]->Print("base");
        hData_neMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet80_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet80_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet80_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet80_keep[i]->Print("base");
    hMC_muMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet80_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_muMaxJtpt_jet80_keep[i]=hMC_muMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet80_keep[i]>0){
       hMC_muMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet80_keep[i]=hData_muMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet80_keep[i]>0){
      if(nMC_muMaxJtpt_jet80_keep[i]<=0){
        hData_muMaxJtpt_jet80_keep[i]->Print("base");
        hData_muMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet80_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet80_keep[i] = new TCanvas(Form("cchSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet80_keep[i]->SetLogy();
    hMC_chSumJtpt_jet80_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet80_keep[i]->Print("base");
    hMC_chSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet80_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_chSumJtpt_jet80_keep[i]=hMC_chSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet80_keep[i]>0){
       hMC_chSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet80_keep[i]=hData_chSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet80_keep[i]>0){
      if(nMC_chSumJtpt_jet80_keep[i]<=0){
        hData_chSumJtpt_jet80_keep[i]->Print("base");
        hData_chSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet80_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet80_keep[i] = new TCanvas(Form("ceSumJtpt_jet80_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet80_keep[i]->SetLogy();
    hMC_eSumJtpt_jet80_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet80_keep[i]->Print("base");
    hMC_eSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet80_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_eSumJtpt_jet80_keep[i]=hMC_eSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet80_keep[i]>0){
       hMC_eSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet80_keep[i]=hData_eSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet80_keep[i]>0){
      if(nMC_eSumJtpt_jet80_keep[i]<=0){
        hData_eSumJtpt_jet80_keep[i]->Print("base");
        hData_eSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet80_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet80_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet80_keep[i] = new TCanvas(Form("cphSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet80_keep[i]->SetLogy();
    hMC_phSumJtpt_jet80_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet80_keep[i]->Print("base");
    hMC_phSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet80_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_phSumJtpt_jet80_keep[i]=hMC_phSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet80_keep[i]>0){
       hMC_phSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet80_keep[i]=hData_phSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet80_keep[i]>0){
      if(nMC_phSumJtpt_jet80_keep[i]<=0){
        hData_phSumJtpt_jet80_keep[i]->Print("base");
        hData_phSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet80_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet80_keep[i] = new TCanvas(Form("cneSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet80_keep[i]->SetLogy();
    hMC_neSumJtpt_jet80_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet80_keep[i]->Print("base");
    hMC_neSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet80_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_neSumJtpt_jet80_keep[i]=hMC_neSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet80_keep[i]>0){
       hMC_neSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet80_keep[i]=hData_neSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet80_keep[i]>0){
      if(nMC_neSumJtpt_jet80_keep[i]<=0){
        hData_neSumJtpt_jet80_keep[i]->Print("base");
        hData_neSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet80_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet80_keep[i] = new TCanvas(Form("cmuSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet80_keep[i]->SetLogy();
    hMC_muSumJtpt_jet80_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet80_keep[i]->Print("base");
    hMC_muSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet80_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_muSumJtpt_jet80_keep[i]=hMC_muSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet80_keep[i]>0){
       hMC_muSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet80_keep[i]=hData_muSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet80_keep[i]>0){
      if(nMC_muSumJtpt_jet80_keep[i]<=0){
        hData_muSumJtpt_jet80_keep[i]->Print("base");
        hData_muSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet80_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet80_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet80_rej[i] = new TCanvas(Form("cchMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet80_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet80_rej[i]->Print("base");
    hMC_chMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet80_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_chMaxJtpt_jet80_rej[i]=hMC_chMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet80_rej[i]>0){
       hMC_chMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet80_rej[i]=hData_chMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet80_rej[i]>0){
      if(nMC_chMaxJtpt_jet80_rej[i]<=0){
        hData_chMaxJtpt_jet80_rej[i]->Print("base");
        hData_chMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet80_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet80_rej[i] = new TCanvas(Form("ceMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet80_rej[i]->Print("base");
    hMC_eMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet80_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_eMaxJtpt_jet80_rej[i]=hMC_eMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet80_rej[i]>0){
       hMC_eMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet80_rej[i]=hData_eMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet80_rej[i]>0){
      if(nMC_eMaxJtpt_jet80_rej[i]<=0){
        hData_eMaxJtpt_jet80_rej[i]->Print("base");
        hData_eMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet80_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet80_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet80_rej[i] = new TCanvas(Form("cphMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet80_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet80_rej[i]->Print("base");
    hMC_phMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet80_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_phMaxJtpt_jet80_rej[i]=hMC_phMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet80_rej[i]>0){
       hMC_phMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet80_rej[i]=hData_phMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet80_rej[i]>0){
      if(nMC_phMaxJtpt_jet80_rej[i]<=0){
        hData_phMaxJtpt_jet80_rej[i]->Print("base");
        hData_phMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet80_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet80_rej[i] = new TCanvas(Form("cneMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet80_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet80_rej[i]->Print("base");
    hMC_neMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet80_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_neMaxJtpt_jet80_rej[i]=hMC_neMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet80_rej[i]>0){
       hMC_neMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet80_rej[i]=hData_neMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet80_rej[i]>0){
      if(nMC_neMaxJtpt_jet80_rej[i]<=0){
        hData_neMaxJtpt_jet80_rej[i]->Print("base");
        hData_neMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet80_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet80_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet80_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet80_rej[i]->Print("base");
    hMC_muMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet80_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_muMaxJtpt_jet80_rej[i]=hMC_muMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet80_rej[i]>0){
       hMC_muMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet80_rej[i]=hData_muMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet80_rej[i]>0){
      if(nMC_muMaxJtpt_jet80_rej[i]<=0){
        hData_muMaxJtpt_jet80_rej[i]->Print("base");
        hData_muMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet80_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet80_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet80_rej[i] = new TCanvas(Form("cchSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet80_rej[i]->SetLogy();
    hMC_chSumJtpt_jet80_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet80_rej[i]->Print("base");
    hMC_chSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet80_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_chSumJtpt_jet80_rej[i]=hMC_chSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet80_rej[i]>0){
       hMC_chSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet80_rej[i]=hData_chSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet80_rej[i]>0){
      if(nMC_chSumJtpt_jet80_rej[i]<=0){
        hData_chSumJtpt_jet80_rej[i]->Print("base");
        hData_chSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet80_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet80_rej[i] = new TCanvas(Form("ceSumJtpt_jet80_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet80_rej[i]->SetLogy();
    hMC_eSumJtpt_jet80_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet80_rej[i]->Print("base");
    hMC_eSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet80_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_eSumJtpt_jet80_rej[i]=hMC_eSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet80_rej[i]>0){
       hMC_eSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet80_rej[i]=hData_eSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet80_rej[i]>0){
      if(nMC_eSumJtpt_jet80_rej[i]<=0){
        hData_eSumJtpt_jet80_rej[i]->Print("base");
        hData_eSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet80_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet80_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet80_rej[i] = new TCanvas(Form("cphSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet80_rej[i]->SetLogy();
    hMC_phSumJtpt_jet80_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet80_rej[i]->Print("base");
    hMC_phSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet80_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_phSumJtpt_jet80_rej[i]=hMC_phSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet80_rej[i]>0){
       hMC_phSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet80_rej[i]=hData_phSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet80_rej[i]>0){
      if(nMC_phSumJtpt_jet80_rej[i]<=0){
        hData_phSumJtpt_jet80_rej[i]->Print("base");
        hData_phSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet80_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet80_rej[i] = new TCanvas(Form("cneSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet80_rej[i]->SetLogy();
    hMC_neSumJtpt_jet80_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet80_rej[i]->Print("base");
    hMC_neSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet80_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_neSumJtpt_jet80_rej[i]=hMC_neSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet80_rej[i]>0){
       hMC_neSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet80_rej[i]=hData_neSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet80_rej[i]>0){
      if(nMC_neSumJtpt_jet80_rej[i]<=0){
        hData_neSumJtpt_jet80_rej[i]->Print("base");
        hData_neSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet80_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet80_rej[i] = new TCanvas(Form("cmuSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet80_rej[i]->SetLogy();
    hMC_muSumJtpt_jet80_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet80_rej[i]->Print("base");
    hMC_muSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet80_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_muSumJtpt_jet80_rej[i]=hMC_muSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet80_rej[i]>0){
       hMC_muSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet80_rej[i]=hData_muSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet80_rej[i]>0){
      if(nMC_muSumJtpt_jet80_rej[i]<=0){
        hData_muSumJtpt_jet80_rej[i]->Print("base");
        hData_muSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet80_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
  TCanvas * ctrkMaxJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet55_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet55_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet55_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet55_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
    nMC_trkMaxJtpt_jet55_keep[i]=hMC_trkMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet55_keep[i]>0){
       hMC_trkMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet55_keep[i]=hData_trkMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet55_keep[i]>0){
      if(nMC_trkMaxJtpt_jet55_keep[i]<=0){
        hData_trkMaxJtpt_jet55_keep[i]->Print("base");
        hData_trkMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet55_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));      
        hData_trkMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_jet55_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_jet55_keep[i] = new TCanvas(Form("ctrkSumJtpt_jet55_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_jet55_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet55_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet55_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet55_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet55_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
//     nMC_trkSumJtpt_jet55_keep[i]=hMC_trkSumJtpt_jet55_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet55_keep[i]>0){
//        hMC_trkSumJtpt_jet55_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet55_keep[i]=hData_trkSumJtpt_jet55_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet55_keep[i]>0){
//       if(nMC_trkSumJtpt_jet55_keep[i]<=0){
//         hData_trkSumJtpt_jet55_keep[i]->Print("base");
//         hData_trkSumJtpt_jet55_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet55_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));      
//         hData_trkSumJtpt_jet55_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet55_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet55_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet55_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/trkSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
  TCanvas * ctrkMaxJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet65_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet65_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet65_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet65_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));
    nMC_trkMaxJtpt_jet65_keep[i]=hMC_trkMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet65_keep[i]>0){
       hMC_trkMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet65_keep[i]=hData_trkMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet65_keep[i]>0){
      if(nMC_trkMaxJtpt_jet65_keep[i]<=0){
        hData_trkMaxJtpt_jet65_keep[i]->Print("base");
        hData_trkMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet65_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));      
        hData_trkMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_jet65_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_jet65_keep[i] = new TCanvas(Form("ctrkSumJtpt_jet65_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_jet65_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet65_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet65_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet65_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet65_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));
//     nMC_trkSumJtpt_jet65_keep[i]=hMC_trkSumJtpt_jet65_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet65_keep[i]>0){
//        hMC_trkSumJtpt_jet65_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet65_keep[i]=hData_trkSumJtpt_jet65_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet65_keep[i]>0){
//       if(nMC_trkSumJtpt_jet65_keep[i]<=0){
//         hData_trkSumJtpt_jet65_keep[i]->Print("base");
//         hData_trkSumJtpt_jet65_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet65_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));      
//         hData_trkSumJtpt_jet65_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet65_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet65_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet65_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/trkSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
  TCanvas * ctrkMaxJtpt_80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_80_keep[i] = new TCanvas(Form("ctrkMaxJtpt_80_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_80_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet80_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet80_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet80_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));
    nMC_trkMaxJtpt_jet80_keep[i]=hMC_trkMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet80_keep[i]>0){
       hMC_trkMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet80_keep[i]=hData_trkMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet80_keep[i]>0){
      if(nMC_trkMaxJtpt_jet80_keep[i]<=0){
        hData_trkMaxJtpt_jet80_keep[i]->Print("base");
        hData_trkMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet80_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));      
        hData_trkMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_80_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_80_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_80_keep[i] = new TCanvas(Form("ctrkSumJtpt_80_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_80_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet80_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet80_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet80_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet80_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));
//     nMC_trkSumJtpt_jet80_keep[i]=hMC_trkSumJtpt_jet80_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet80_keep[i]>0){
//        hMC_trkSumJtpt_jet80_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet80_keep[i]=hData_trkSumJtpt_jet80_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet80_keep[i]>0){
//       if(nMC_trkSumJtpt_jet80_keep[i]<=0){
//         hData_trkSumJtpt_jet80_keep[i]->Print("base");
//         hData_trkSumJtpt_jet80_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet80_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));      
//         hData_trkSumJtpt_jet80_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet80_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet80_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet80_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_80_keep[i]->SaveAs(Form("Plots/trkSumJtpt_80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   } 
  TCanvas * ctrkMaxJtpt_Matched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Matched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_Matched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_Matched_keep[i]->Print("base");
    hMC_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, pass CutA ",radius));
    nMC_trkMaxJtpt_Matched_keep[i]=hMC_trkMaxJtpt_Matched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_Matched_keep[i]>0){
       hMC_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_Matched_keep[i]=hData_trkMaxJtpt_Matched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_Matched_keep[i]>0){
      if(nMC_trkMaxJtpt_Matched_keep[i]<=0){
        hData_trkMaxJtpt_Matched_keep[i]->Print("base");
        hData_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, matched pass CutA ",radius));      
        hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_Matched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_Matched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

  TCanvas * ctrkMaxJtpt_jet55_Matched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet55_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_Matched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet55_Matched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet55_Matched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, matched pass CutA ",radius));
    nMC_trkMaxJtpt_jet55_Matched_keep[i]=hMC_trkMaxJtpt_jet55_Matched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet55_Matched_keep[i]>0){
       hMC_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet55_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_Matched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet55_Matched_keep[i]=hData_trkMaxJtpt_jet55_Matched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet55_Matched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet55_Matched_keep[i]<=0){
        hData_trkMaxJtpt_jet55_Matched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet55_Matched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet55_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, matched pass CutA ",radius));      
        hData_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet55_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet55_Matched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet55_Matched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet55_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_jet65_Matched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet65_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_Matched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet65_Matched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet65_Matched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, matched pass CutA ",radius));
    nMC_trkMaxJtpt_jet65_Matched_keep[i]=hMC_trkMaxJtpt_jet65_Matched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet65_Matched_keep[i]>0){
       hMC_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet65_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_Matched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet65_Matched_keep[i]=hData_trkMaxJtpt_jet65_Matched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet65_Matched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet65_Matched_keep[i]<=0){
        hData_trkMaxJtpt_jet65_Matched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet65_Matched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet65_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, matched pass CutA ",radius));      
        hData_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet65_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet65_Matched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet65_Matched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet65_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_jet80_Matched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet80_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet80_Matched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet80_Matched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet80_Matched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, matched pass CutA ",radius));
    nMC_trkMaxJtpt_jet80_Matched_keep[i]=hMC_trkMaxJtpt_jet80_Matched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet80_Matched_keep[i]>0){
       hMC_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet80_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_Matched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet80_Matched_keep[i]=hData_trkMaxJtpt_jet80_Matched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet80_Matched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet80_Matched_keep[i]<=0){
        hData_trkMaxJtpt_jet80_Matched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet80_Matched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet80_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, matched pass CutA ",radius));      
        hData_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet80_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet80_Matched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet80_Matched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet80_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet80_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_Unmatched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Unmatched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_Unmatched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_Unmatched_keep[i]->Print("base");
    hMC_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, pass CutA ",radius));
    nMC_trkMaxJtpt_Unmatched_keep[i]=hMC_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_Unmatched_keep[i]>0){
       hMC_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_Unmatched_keep[i]=hData_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_Unmatched_keep[i]>0){
      if(nMC_trkMaxJtpt_Unmatched_keep[i]<=0){
        hData_trkMaxJtpt_Unmatched_keep[i]->Print("base");
        hData_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, Unmatched pass CutA ",radius));      
        hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_Unmatched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_Unmatched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

  TCanvas * ctrkMaxJtpt_jet55_Unmatched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet55_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_Unmatched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet55_Unmatched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
    nMC_trkMaxJtpt_jet55_Unmatched_keep[i]=hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet55_Unmatched_keep[i]>0){
       hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet55_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet55_Unmatched_keep[i]=hData_trkMaxJtpt_jet55_Unmatched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet55_Unmatched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet55_Unmatched_keep[i]<=0){
        hData_trkMaxJtpt_jet55_Unmatched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, Unmatched pass CutA ",radius));      
        hData_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet55_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet55_Unmatched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet55_Unmatched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet55_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_jet65_Unmatched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet65_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_Unmatched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet65_Unmatched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, Unmatched pass CutA ",radius));
    nMC_trkMaxJtpt_jet65_Unmatched_keep[i]=hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet65_Unmatched_keep[i]>0){
       hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet65_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet65_Unmatched_keep[i]=hData_trkMaxJtpt_jet65_Unmatched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet65_Unmatched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet65_Unmatched_keep[i]<=0){
        hData_trkMaxJtpt_jet65_Unmatched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, Unmatched pass CutA ",radius));      
        hData_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet65_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet65_Unmatched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet65_Unmatched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet65_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_jet80_Unmatched_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet80_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet80_Unmatched_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet80_Unmatched_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, unmatched pass CutA ",radius));
    nMC_trkMaxJtpt_jet80_Unmatched_keep[i]=hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet80_Unmatched_keep[i]>0){
       hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet80_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet80_Unmatched_keep[i]=hData_trkMaxJtpt_jet80_Unmatched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet80_Unmatched_keep[i]>0){
      if(nMC_trkMaxJtpt_jet80_Unmatched_keep[i]<=0){
        hData_trkMaxJtpt_jet80_Unmatched_keep[i]->Print("base");
        hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, unmatched pass CutA ",radius));      
        hData_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet80_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet80_Unmatched_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet80_Unmatched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet80_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet80_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ctrkMaxJtpt_Matched_NoTrig_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_Matched_NoTrig_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Matched_NoTrig_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_Matched_NoTrig_keep[i]->SetLogy();
    hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->Print("base");
    hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), pass CutA ",radius));
    nMC_trkMaxJtpt_Matched_NoTrig_keep[i]=hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_Matched_NoTrig_keep[i]>0){
       hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_Matched_NoTrig_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Matched_NoTrig_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_Matched_keep[i]=hData_trkMaxJtpt_Matched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_Matched_keep[i]>0){
      if(nMC_trkMaxJtpt_Matched_keep[i]<=0){
        hData_trkMaxJtpt_Matched_keep[i]->Print("base");
        hData_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), matched pass CutA ",radius));      
        hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_Matched_NoTrig_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_Matched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_Matched_NoTrig_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Matched_NoTrig_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
   TCanvas * ctrkMaxJtpt_Unmatched_NoTrig_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_Unmatched_NoTrig_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Unmatched_NoTrig_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_Unmatched_NoTrig_keep[i]->SetLogy();
    hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->Print("base");
    hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), pass CutA ",radius));
    nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]=hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]>0){
       hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_Unmatched_keep[i]=hData_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_Unmatched_keep[i]>0){
      if(nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]<=0){
        hData_trkMaxJtpt_Unmatched_keep[i]->Print("base");
        hData_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), Unmatched pass CutA ",radius));      
        hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_Unmatched_NoTrig_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_Unmatched_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_Unmatched_NoTrig_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Unmatched_NoTrig_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }   