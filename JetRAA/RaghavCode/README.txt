Modified to run in the following directory at hepcms-in1.umd.edu
/home/belt/wrk/JetRAA/MatchNtuples/AnalysisPlots/16April2015

Have most of the input files in:
/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/16april

A couple more in:
/net/hisrv0001/home/rkunnawa/WORK/RAA/CMSSW_5_3_20/src/Output
**********************************
Analysis plots set take input from:
/export/d00/scratch/rkunnawa/rootfiles/
With names like:


**********************************
Final plots set:

The files which are input to these below have names like:
/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/NoResidual/PbPb_pp_calopfpt_jetidcut_R0p3_unfold_mcclosure_oppside_trgMC_n20_eta_p20_60GeVCut_akPF_20150415.root

You will have to change the input file names to those mentioned above (since I run them locally on hidsk). 
https://github.com/rkunnawa/RAA/blob/master/RAA_plot.C - to run: $ root -l RAA_plot.C 
DONT compile this! its just to run with all the boolean variables ive setup. will make the MCClosure, individual Spectra, Trigger Combination and RAA plots for a single radii at a time. 

https://github.com/rkunnawa/RAA/blob/master/RAA_plot_Systematics.C - to run: $ root -l RAA_plot_Systematics.C+ 
you can compile this its ok. 
Will make the systematics plots. I need to add the systematics I mentioned above to the class SysData, located here: https://github.com/rkunnawa/RAA/blob/master/Headers/utilities.h#L51 Pawan should have experience with this before since he did this the last time. 

https://github.com/rkunnawa/RAA/blob/master/RAA_plot_finalpaper.C - to runL $ root -l RAA_plot_finalpaper.C+ 
you can compile this. 
This makes the final RAA paper plots which are 
1) Spectra for pp and PbPb with artificial scaling introduced to separate the differner curves. showing data points as filled circles and MC as lines. 
2) Bayesian unfolded RAA for R=0.2, 0.3, 0.4 in the different centrality bins. 
3) RAA as a function of N_part for the different radii. 