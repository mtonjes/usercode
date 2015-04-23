**********************************
INTRODUCTION:
**********************************
Modified to run in the following directory at hepcms-in1.umd.edu
/home/belt/wrk/JetRAA/MatchNtuples/AnalysisPlots/16April2015

Have most of the input files in:
UMD: /data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/16april (all but matched ntuples)
UMD: /data/users/belt/JetRAA/MatchNtuples (for matched ntuples)
MIT: /export/d00/scratch/rkunnawa/rootfiles/RAA/apil16 (all but matched ntuples)
MIT: /export/d00/scratch/rkunnawa/rootfiles (matched ntuples)

A couple more files can be found (if you are missing them in):
/net/hisrv0001/home/rkunnawa/WORK/RAA/CMSSW_5_3_20/src/Output
--> Note that some macros have booleans and don't actually run code which takes other files you may be mising

Don't forget to pick up Raghav's full Headers directory from github and point to it when running. His code assumes:
../../Output
../../Plots
Marguerite's code assumes:
Output/
Plots/

github areas:
https://github.com/rkunnawa/RAA
https://github.com/mtonjes/usercode/tree/master/JetRAA
https://github.com/obaron/CMScode/tree/master/drawfiles

**********************************
We do not expect you to run this step yourself as it requires condor jobs:
--> Take input from:
/export/d00/scratch/rkunnawa/rootfiles/
(produced with Raghav's code https://github.com/rkunnawa/RAA/RAA_calo_pf_JetCorrelation_v2.C)
With names like:
PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150331.root
PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150331.root
pp_MC_calo_pf_jet_correlation_deltaR_0p2_ak3_20150331.root
pp_Data_calo_pf_jet_correlation_deltaR_0p2_ak3_20150331.root

--> Cuts included in these root files:
jet |eta|<2
jet pT>30 (Calo and PF)
supernova/pileup removal
pHBHEFilter (not MC)
pCollisionEventSelection (PbPb data & MC)
pACollisionEventSelection (pp data & MC)
match is done with akPu3CaloJets no matter the radius of the PF jets (akPu2Calo and akPu4Calo not available in data hiForest)
**********************************

Can run some of Marguerite's JetID studies:
root -l https://github.com/mtonjes/usercode/tree/master/JetRAA/RAA_plot_jetidvariables_cutPass_jet55.C+
root -l https://github.com/mtonjes/usercode/tree/master/JetRAA/eMaxCutGen_study.C+


1) Next for analysis, run this code from Raghav to get the spectra including cuts from the matched and unmatched trees (we colloquially call them ntuples):
root -l https://github.com/rkunnawa/RAA/blob/master/RAA_plot_yetkinCutEfficiency_pp.C+
root -l https://github.com/rkunnawa/RAA/blob/master/RAA_plot_yetkinCutEfficiency.C+
--> Note when I (Marguerite) run this code, I get empty canvases but the histograms and pdfs are usually ok.
--> run for each radius

Output looks like:
/export/d00/scratch/rkunnawa/rootfiles/RAA/apil16/
PbPb_CutEfficiency_YetkinCuts_matched_slantedlinecalopfpt_addingunmatched_exclusionhighertriggers_eMaxSumcand_A_R0p3.root
Pp_CutEfficiency_YetkinCuts_matched_slantedlinecalopfpt_addingunmatched_exclusionhighertriggers_eMaxSumcand_A_R0p3.root
--> CutA is included in these root files above (only on eMax/sumCand(!PFElectron))
--> Note that histograms are made without cuts should one prefer to pick those up

Can make plots from Marguerite's code on it:
root -l https://github.com/mtonjes/usercode/tree/master/JetRAA/RAA_plot_CutA_BasicPlots.C+
Later version from Owen:
root -l https://github.com/obaron/CMScode/blob/master/drawfiles/RAA_plot_CutA_BasicPlots.C+

--> Download and install RooUnfold http://hepunx.rl.ac.uk/~adye/software/unfold/RooUnfold.html (RooUnfold-1.1.1)
--> Make sure you have a running ROOT environment (5_3_20 and above on SL6)
untar (see directions at the RooUnfold site)
make
--> Have in your .rootlogon.C the following line pointing to your compiled library:
gSystem->Load("/afs/cern.ch/work/r/rkunnawa/WORK/RAA/CMSSW_5_3_18/src/Headers/RooUnfold-1.1.1/libRooUnfold.so");

2) Next, run data driven unfolding (Raghav code) - this fixes error bars after unfolding 
--> run for each radius
root -l https://github.com/rkunnawa/RAA/blob/master/RAA_dataDrivenUnfoldingErrorCheck.C+
outputs: PbPb_R3_pp_R3_n20_eta_p20_unfoldingCut_60_data_driven_correction_akPuPF_20150417.root
NOTE: this file has pp residual data-driven JEC applied (currently April 17th 12:20am this is disfavored): PbPb_R3_pp_withresiduals_R3_n20_eta_p20_unfoldingCut_60_data_driven_correction_akPuPF_20150417.root

You will need for the RAA_analyze.C code these files (I don't know which macro makes them):
/net/hisrv0001/home/belt/wrk/JetRAA/matchAnalysis/raghav_files/PbPb_MC_calo_pf_jet_correlation_mcclosure_histograms_deltaR_0p2_akPu*_20150413.root
/net/hisrv0001/home/belt/wrk/JetRAA/matchAnalysis/raghav_files/pp_MC_calo_pf_jet_correlation_deltaR_0p2_ak*_20150412.root

3) Then run actual unfolding and RAA calculation (need input files above with "CutEfficiency" and "data_driven_correction")
root -l https://github.com/rkunnawa/RAA/blob/master/RAA_analyze.C+
--> run for each radius

This outputs files as shown below
**********************************
Final plots set:

The files which are input to these below have names like:
/export/d00/scratch/rkunnawa/rootfiles/RAA/apil16/PbPb_pp_calopfpt_jetidcut_R0p3_unfold_mcclosure_oppside_trgMC_n20_eta_p20_60GeVCut_akPF_20150417.root
/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/april16/PbPb_pp_calopfpt_jetidcut_R0p3_unfold_mcclosure_oppside_trgMC_n20_eta_p20_60GeVCut_akPF_20150417.root

--> run for each radius
You will have to change the input file names to those mentioned above (since I run them locally on hidsk). 
https://github.com/rkunnawa/RAA/blob/master/RAA_plot.C - to run: $ root -l RAA_plot.C 
DONT compile this! its just to run with all the boolean variables ive setup. will make the MCClosure, individual Spectra, Trigger Combination and RAA plots for a single radii at a time. 

--> run for each radius
https://github.com/rkunnawa/RAA/blob/master/RAA_plot_Systematics.C - to run: $ root -l RAA_plot_Systematics.C
(I couldn't get it to work compiled - Marguerite)
Will make the systematics plots. I need to add the systematics I mentioned above to the class SysData, located here: https://github.com/rkunnawa/RAA/blob/master/Headers/utilities.h#L51 Pawan should have experience with this before since he did this the last time. 

https://github.com/rkunnawa/RAA/blob/master/RAA_plot_finalpaper.C - to runL $ root -l RAA_plot_finalpaper.C+ 
you can compile this. 
This makes the final RAA paper plots which are 
1) Spectra for pp and PbPb with artificial scaling introduced to separate the differner curves. showing data points as filled circles and MC as lines. 
2) Bayesian unfolded RAA for R=0.2, 0.3, 0.4 in the different centrality bins. 
3) RAA as a function of N_part for the different radii. 
--> Note, Marguerite and Owen have modified versions of this to (Marguerite's) look prettier and (Owen's) draw fine binned response matrix.
https://github.com/mtonjes/usercode/blob/master/JetRAA/RaghavCode/RAA_plot_finalpaper.C+

--> run for each radius
Power Law Fit comparison for pp and PbPb unfolded spectra:
https://github.com/mtonjes/usercode/blob/master/JetRAA/RAA_plot_PowerLaw.C
root -l RAA_plot_PowerLaw.C

https://github.com/rkunnawa/RAA/blob/master/RAA_NEWcomparisonwithPAS.C  $ root -l RAA_NEWcomparisonwithPAS.C+
