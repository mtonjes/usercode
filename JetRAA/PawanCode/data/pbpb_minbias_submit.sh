#!/bin/bash

if [ $# -eq 0 ]
then
    echo "No input txt file please check"
    exit
fi

name=$1
algname=$2
failed=$3

if [ -z $3 ]
then
    failed=-1
fi


species=pbpb
dataset=data
maxpthat=9999

nFilesTotal=`cat $name | wc -l`
nFilesTotal=$(( nFilesTotal-1 ))
nFilesPerSet=10

echo $name  $nFilesTotal

iFile=0
iJob=0
count=0



while read -r line
do
    infile=$line
#    echo $infile
    if [ $count -le $nFilesPerSet ]
    then
	if [ $count -eq 0 ]
        then
            inputList="$infile"
#            echo  "..... First file in set : " $iJob $inputList $count
        else
            inputList="$inputList,$infile"
#            echo  "..... adding files "  $iJob $inputList  $count
        fi
        count=$((count+1))
    fi
    if [ $count -eq $nFilesPerSet ] || [ $iFile -eq  $nFilesTotal ]
    then
	outfile="JetRAA_${algname}_PbPb_MinBias_Data_${iJob}.root"
        Error="$algname-$iJob.err"
        Output="$algname-$iJob.out"
        Log="$algname-$iJob.log"
#	echo $iJob $outfile $Error $Output $Log
#	echo $iJob $outfile

#	echo $iJob $inputList
#	echo " "	
	cat > tmpfile <<EOF
Universe       = vanilla  
# files will be copied back to this dir
Initialdir     = . 

# run my script
Executable     = run.sh 

+AccountingGroup = "group_cmshi.belt"

Arguments        = $species $algname $dataset $inputList $outfile $maxpthat

# input files. in this case, there are none. 
Input          = /dev/null

# log files
Error          = LOG/$Error
Output         = LOG/$Output
Log            = LOG/$Log

# get the environment (path, etc.)
Getenv         = True

# prefer to run on fast computers
#Rank          = kflops

# only run on 64 bit computers
#Requirements   = Arch == "X86_64"

# should write all output & logs to a local directory

# and then transfer it back to Initialdir on completion
should_transfer_files   = YES
                                                                                                                  
when_to_transfer_output = ON_EXIT                                                 

# specify any extra input files (for example, an orcarc file)

Queue
EOF
	condor_submit tmpfile
	iJob=$((iJob+1))	
	count=0

	if [ $iJob -eq $((failed+1)) ];
	then 
	    exit
	fi

    fi
    iFile=$((iFile+1))

done < $name

echo ""
echo ""
echo "Total # of file : "$nFilesTotal ", files submitted per job : "$nFilesPerSet", # of jobs submitted : " $iJob
echo ""
echo ""
