#!/bin/bash
RUN_NUMBER=$1
mkdir $RUN_NUMBER
echo "Making working files for run " $1
sed -e "s/262811/$RUN_NUMBER/g" crabConfig.py > $RUN_NUMBER/crabConfig.py
sed -e "s/262811/$RUN_NUMBER/g" RunForwardAnalyzer_PbPb2015_all.py > $RUN_NUMBER/RunForwardAnalyzer_PbPb2015_all.py
