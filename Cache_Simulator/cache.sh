#!/bin/bash
#Use this file to run the cache simulator in batch mode

#Define CACHE_SIZE in KBs
CACHE_SIZE=128
#Define n-way SET_ASSOCIATIVITY
SET_ASSOCIATIVITY=2048
#Define BLOCK_SIZE in Bytes
BLOCK_SIZE=64
#Define REPLACEMENT_POLICY
#'l' - Least Recently Used
#'r' - Random Replacement
REPLACEMENT_POLICY='l'

rm -rf Executables/cache
rm -rf Results/SpecBenchmark_cache_results.txt
g++ -o Executables/cache Code_Files/cache.cpp


gzip -dc Test_Files/400.perlbench-41B.trace.txt.gz             | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/401.bzip2-226B.trace.txt.gz                | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/403.gcc-16B.trace.txt.gz                   | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/410.bwaves-1963B.trace.txt.gz              | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/416.gamess-875B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/429.mcf-184B.trace.txt.gz                  | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/433.milc-127B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/435.gromacs-111B.trace.txt.gz              | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/436.cactusADM-1804B.trace.txt.gz           | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/437.leslie3d-134B.trace.txt.gz             | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/444.namd-120B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/445.gobmk-17B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/447.dealII-3B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/450.soplex-247B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/453.povray-887B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/454.calculix-104B.trace.txt.gz             | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/456.hmmer-191B.trace.txt.gz                | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/458.sjeng-1088B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/459.GemsFDTD-1169B.trace.txt.gz            | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/462.libquantum-1343B.trace.txt.gz          | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/464.h264ref-30B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/465.tonto-1769B.trace.txt.gz               | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/470.lbm-1274B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/471.omnetpp-188B.trace.txt.gz              | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/473.astar-153B.trace.txt.gz                | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/481.wrf-1170B.trace.txt.gz                 | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/482.sphinx3-1100B.trace.txt.gz             | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
gzip -dc Test_Files/483.xalancbmk-127B.trace.txt.gz            | ./Executables/cache $CACHE_SIZE $SET_ASSOCIATIVITY $BLOCK_SIZE $REPLACEMENT_POLICY
