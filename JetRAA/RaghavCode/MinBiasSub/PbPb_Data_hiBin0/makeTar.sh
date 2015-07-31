#!/bin/bash

root -l <<EOF
.L RAA_read_data_pbpb_JetID_hiBin0.C++
.q
EOF

rm jetRAA_run_PbPb_Data_hiBin0.tar
tar -zcvf jetRAA_run_PbPb_Data_hiBin0.tar jetRAA_PbPb_*.txt RAA_read_*.*
