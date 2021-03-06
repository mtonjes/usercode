#!/bin/bash

# run this with $ source raa_condor_submit.sh NJobs NFilesPerJob
# PbPb data: source raa_pbpb_data_condor_submit.sh 181 5

counter=0
incrementer=1

destination=/mnt/hadoop/cms/store/user/belt/rootfiles/JetRAA/July30/PbPb_Data_hiBin0
filelist=jetRAA_PbPb_data_forest.txt

nFiles=`wc -l < $filelist`
tardir=`pwd`
radius=3

echo "nFiles in list: $nFiles"
while [ $counter -lt $1 ]
do
    echo $counter >> Submitted
    
    Error="akPu$radius-PbPbData-$endfile.err"
    Output="akPu$radius-PbPbData-$endfile.out"
    Log="akPu$radius-PbPbData-$endfile.log"
    
    startfile=$(( $counter * $2 ))
    endfile=$(( ($counter + 1) * $2 ))
    if [ $endfile -gt $nFiles ]; then
        let endfile=$nFiles
        let counter=$1
    fi

    outfile="PbPb_Data_histograms_FromForest_JetID_hiBin0_akPu${radius}_20_eta_20_${endfile}.root"
    
    # Condor submit file
    cat > subfile <<EOF

Universe       = vanilla
Environment = "HOSTNAME=$HOSTNAME"
# files will be copied back to this dir
# Initialdir     = .
#tell condor where my grid certificate it
#x509userproxy=/tmp/x509up_u2142
# run my script
Executable     = raa_pbpb_data_condor_run.sh
+AccountingGroup = "group_cmshi.belt"
#+IsMadgraph = 1
Arguments      = $startfile $endfile $radius $outfile
# input files. in this case, there are none.
Input          = /dev/null
# log files
Error          = /export/d00/scratch/belt/JetRAA/30July/PbPb_Data_hiBin0/LOG/$Error
Output         = /export/d00/scratch/belt/JetRAA/30July/PbPb_Data_hiBin0/LOG/$Output
Log            = /export/d00/scratch/belt/JetRAA/30July/PbPb_Data_hiBin0/LOG/$Log
# get the environment (path, etc.)
Getenv         = True
# prefer to run on fast computers
Rank           = kflops
# only run on 64 bit computers
Requirements   = Arch == "X86_64"
transfer_input_files = $tardir/jetRAA_run_PbPb_Data_hiBin0.tar
# should write all output & logs to a local directory
# and then transfer it back to Initialdir on completion
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT
# specify any extra input files (for example, an orcarc file)
Queue
EOF

    # submit the job
    echo "submitting condor_run.sh $startfile $endfile to $destination ..." 
    condor_submit subfile
    counter=$(($counter + 1))
done
