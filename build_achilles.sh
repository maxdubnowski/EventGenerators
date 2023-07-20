#!/bin/bash                                                                                                                                

BASE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]:-${(%):-%x}}" )" && pwd )"

# MicroBooNE                                                                                                                                                                                            
source /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh

# SBND                                                                                                                                                                                                 
#source /cvmfs/sbnd.opensciencegrid.org/products/sbnd/setup_sbnd.sh                                                                                                                                      
#DUNE                                                                                                                                                                                                   
#source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh                                                                                                                                      
setup root v6_22_08b -q e20:p383b:prof
setup lhapdf v5_9_1k -q e17:debug
setup log4cpp v1_1_3a -q e17:debug
setup pdfsets v5_9_1b
setup gdb v8_1
setup git v2_15_1
setup cmake v3_14_3
setup hdf5 v1_12_0b -q e20:prof 

git clone https://github.com/AchillesGen/Achilles
cd Achilles
git checkout 6ff810ad7e3fa5daa5f94d7f5c52a93070664433

mkdir build && cd build
cmake .. -DENABLE_BSM=OFF -DUSE_ROOT=ON
make -j4

export LD_LIBRARY_PATH=/cvmfs/larsoft.opensciencegrid.org/products/gcc/v9_3_0/Linux64bit+3.10-2.17/lib64/:$LD_LIBRARY_PATH

cd $BASE_DIR
