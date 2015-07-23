   grae->SetPoint(0,35,180);
   grae->SetPointError(0,4,4,29.95905,29.95905);
   grae->SetPoint(1,44.5,55.7);
   grae->SetPointError(1,5.5,5.5,7.828377,7.828377);
   grae->SetPoint(2,56.5,16.9);
   grae->SetPointError(2,6.5,6.5,2.625436,2.625436);
   grae->SetPoint(3,71,4.85);
   grae->SetPointError(3,8,8,0.6276957,0.6276957);
   grae->SetPoint(4,89.5,1.42);
   grae->SetPointError(4,10.5,10.5,0.1878054,0.1878054);
   grae->SetPoint(5,112.5,0.364);
   grae->SetPointError(5,12.5,12.5,0.04772427,0.04772427);
   grae->SetPoint(6,141.5,0.0882);
   grae->SetPointError(6,16.5,16.5,0.01103805,0.01103805);
   grae->SetPoint(7,178.5,0.0197);
   grae->SetPointError(7,20.5,20.5,0.002292152,0.002292152);
   grae->SetPoint(8,225,0.00406);
   grae->SetPointError(8,26,26,0.0004822521,0.0004822521);
   grae->SetPoint(9,283.5,0.000735);
   grae->SetPointError(9,32.5,32.5,8.981748e-05,8.981748e-05);
   grae->SetPoint(10,357,0.000114);
   grae->SetPointError(10,41,41,1.442494e-05,1.442494e-05);
   grae->SetPoint(11,449.5,1.41e-05);
   grae->SetPointError(11,51.5,51.5,1.98855e-06,1.98855e-06);
	
SetPointError(Int_t i, Double_t exl, Double_t exh, Double_t eyl, Double_t eyh)  
SetPoint(Int_t i, Double_t x, Double_t y) 
ATLAS pp
point centers: 35, 44.5, 56.5,   71,  89.5,  112.5,  141.5,  178.5,    225,  283.5,    357,  449.5
point errors:   4,  5.5,  6.5,    8,  10.5,   12.5,   16.5,   20.5,     26,   32.5,     41,   51.5
bin edges : 31-39,39-50,50-63,63-79,79-100,100-125,125-158,158-199,199-251,251-316,316-398,398-501
bin errors are symmetrical, so...

Double_t xAxisATLASpp[13] = {31,39,50,63,79,100,125,158,199,251,316,398,501}; 
   TH1F *hATLASppHist = new TH1F("hATLASppHist"," ",100,xAxisATLASpp);
   hATLASppHist->SetMinimum(1.090031e-05);
   hATLASppHist->SetMaximum(230.955);
   hATLASppHist->SetDirectory(0);
   hATLASppHist->SetStats(0);
   hATLASppHist->SetBinContent(0,180);
   hATLASppHist->SetBinError(0,29.95905);
   hATLASppHist->SetBinContent(1,55.7);
   hATLASppHist->SetBinError(1,7.828377);
   hATLASppHist->SetBinContent(2,16.9);
   hATLASppHist->SetBinError(2,2.625436);
   hATLASppHist->SetBinContent(3,4.85);
   hATLASppHist->SetBinError(3,0.6276957);
   hATLASppHist->SetBinContent(4,1.42);
   hATLASppHist->SetBinError(4,10.1878054);
   hATLASppHist->SetBinContent(5,0.364);
   hATLASppHist->SetBinError(5,0.04772427);
   hATLASppHist->SetBinContent(6,0.0882);
   hATLASppHist->SetBinError(6,0.01103805);
   hATLASppHist->SetBinContent(7,0.0197);
   hATLASppHist->SetBinError(7,0.002292152);
   hATLASppHist->SetBinContent(8,0.00406);
   hATLASppHist->SetBinError(8,0.0004822521);
   hATLASppHist->SetBinContent(9,0.000735);
   hATLASppHist->SetBinError(9,8.981748e-05);
   hATLASppHist->SetBinContent(10,0.000114);
   hATLASppHist->SetBinError(10,1.442494e-05);
   hATLASppHist->SetBinContent(11,1.41e-05);
   hATLASppHist->SetBinError(11,1.98855e-06);

