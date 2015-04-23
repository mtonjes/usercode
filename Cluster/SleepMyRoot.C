#include <iostream>
#include <stdio.h>
#include <fstream>
#include <fstream>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"
#include "TSystem.h"


  

void SleepMyRoot(Int_t TotalHours=5)
{

  TStopwatch timer;
  timer.Start();

  TDatime date;
  
Int_t TotalMinutes = TotalHours*60;
Int_t TotalSeconds = TotalMinutes*60;
Int_t TotalMilliSeconds = TotalSeconds*1000;

cout<<"Going to take up some CPU with a simple root macro, it is date: "<<date.GetDate()<<", and time: "<<date.GetTime()<<endl;
//cout<<"It is system time: "<<gSystem->Now();

Int_t LoopEnd=10;
Int_t SleepFactor=1000*60*10;
Int_t LoopFactor=(Int_t)(TotalMilliSeconds/SleepFactor);

cout<<"We will run this macro for a total of: "<<TotalMinutes<<" Total Minutes, which is "<<TotalMilliSeconds<<" total milliseconds, and we will sleep for: "<<SleepFactor<<" milliseconds at a time, which means we loop a total of: "<<LoopFactor<<" times."<<endl;

  for(int i=0;i<LoopFactor;i++){
     cout<<"in the loop, i: "<<i<<endl;
     gSystem->Sleep ( SleepFactor );
     TDatime date;
     cout<<"just slept, it's now date: "<<date.GetDate()<<", and time: "<<date.GetTime()<<endl;
  }


}