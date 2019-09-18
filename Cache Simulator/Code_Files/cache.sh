#Use this file to run the cache simulator in batch mode

#Define CACHE_SIZE in KBs
CACHE_SIZE = 128
#Define n-way SET_ASSOCIATIVITY
SET_ASSOCIATIVITY = 16
#Define BLOCK_SIZE in Bytes
BLOCK_SIZE = 64
#Define REPLACEMENT_POLICY
#'l' - Least Recently Used
#'r' - Random Replacement
REPLACEMENT_POLICY = 'l'

rm -rf Executables/cache

g++ -o Executables/cache Code_Files/cache.cpp

gzip -dc 400.perlbench-41B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 401.bzip2-226B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 403.gcc-16B.trace.text.gz						| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 410.bwaves-1963B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 416.gamess-875B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 429.mcf-184B.trace.text.gz						| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 433.milc-127B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 435.gromacs-111B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 436.cactusADM-1804B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 437.leslie3d-134B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 444.namd-120B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 445.gobmk-17B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 447.dealII-3B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 450.soplex-247B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 453.povray-887B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 454.calculix-104B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 456.hmmer-191B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 458.sjeng-1088B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 459.GemsFDTD-1169B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 462.libquantum-1343.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 464.h264ref-30B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 465.tonto-1769B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 470.lbm-1274B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 471.omnetpp-188B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 473.astar-153B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 481.wrf-1170B.trace.text.gz					| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 482.sphinx3-1100B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
gzip -dc 483.xalancbmk-127B.trace.text.gz				| ./Executables/cache CACHE_SIZE SET_ASSOCIATIVITY BLOCK_SIZE REPLACEMENT_POLICY
