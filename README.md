# Cache-Simulator
A Cache Simulator written in C++. The Cache Simulator takes in the following parameters:
1) .txt file - This is a trace file containing reads/write with addresses
2) CACHE_SIZE - The Cache Size in KB
3) SET_ASSOCIATIVITY - n-way set associativity
4) BLOCK_SIZE - Block Size in Bytes
5) REPLACEMENT_POLICY - a) 'l' - Least Reccently Used
For more details please check the cache.sh file.

Steps to run the Simulator:
1) Set your present working directory to "Cache_Simulator"
2) Run the cache.sh file
You can also run a single trace input and get its output on terminal. Following command is an example:
gzip -dc 429.mcf-184B.trace.txt.gz | ./cache 4096 64 64 l

Modifications in cache.sh:
1) Modifications can be made to the parameters of the cache.sh file to change the characteristics of cache. To make it a Direct-mapped Cache you can set the SET_ASSSOCIATIVITY parameter to 1. Similarly, to characterize a fully-associative cache you need to calculate the n-way set associativity depending upon your BLOCK_SIZE and CACHE_SIZE.

Results:-
The results directory has a file "SpecBenchmark_cache_reference.txt" which has the reference results of all the trace inputs provided in the cache.sh file for CACHE_SIZE=128KB, SET_ASSOCIATIVITY=16, BLOCK_SIZE=64 and REPLACEMENT_POLICY='l'. After running the cache.sh, the cache.cpp file will generate a "SpecBenchmark_cache_results.txt" file which contains the generated results and can be used for comparing the miss statistics. 
The numbers in the result file have the following respective meaning:
Number of Misses, Number of Memory Accesses, Number of Read Miss, Number of Read Accesses, Number of Write Miss, Number of Write Accesses






