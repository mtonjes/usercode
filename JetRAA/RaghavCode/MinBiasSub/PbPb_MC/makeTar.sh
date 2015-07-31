#!/bin/bash

root -l <<EOF
.L RAA_read_mc_pbpb_JetID.C++
.q
EOF

rm jetRAA_run_PbPb_MC.tar
tar -zcvf jetRAA_run_PbPb_MC.tar jetRAA_PbPb_*.txt RAA_read_*.* weights.root data_mc_cent_vz_weight.root weights_pbpb_*.root
