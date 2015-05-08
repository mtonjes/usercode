#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
source /osg/app/cmssoft/cms/cmsset_default.sh


cd /net/hisrv0001/home/pawan/Validation/CMSSW_7_1_1/src/
eval `scramv1 runtime -sh`
cd -

species=$1
algname=$2
dataset=$3
infile=$4
outfile=$5
max=$6

#root -l -b -q /net/hisrv0001/home/pawan/Validation/CMSSW_7_1_1/src/JetRaa/CondorPbPb_Data.C+\(\"$type\",\"$infile\",\"$outfile\"\)

root -l -b -q /net/hisrv0001/home/belt/wrk/JetRAA/PawanNtuple/jetmatch_MinBias.C+\(\"$species\",\"$algname\",\"$dataset\",\"$infile\",\"$outfile\",$max\)

# PbPb Data
#scp $outfile hidsk0001:/export/d00/scratch/pawan/condorfiles/pbpb/ntuples/DATA

mv $outfile /mnt/hadoop/cms/store/user/belt/ntuples/$dataset/$species/

rm -f $outfile

echo "Done!"

