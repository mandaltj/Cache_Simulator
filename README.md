# Cache-Simulator
A Cache Simulator written in C++. The Cache Simulator takes in the following parameters:
1) .txt file - This is a trace file containing reads/write with addresses
2) CACHE_SIZE - The Cache Size in KB
3) SET_ASSOCIATIVITY - n-way set associativity
4) BLOCK_SIZE - Block Size in Bytes
5) REPLACEMENT_POLICY - a) 'l' - Least Reccently Used

Steps to run the Simulator:
1) Set your present working directory to "Cache_Simulator"
2) Run the cache.sh file

Modifications in cache.sh:
1) Modifications can be made to the parameters of the cache.sh file to change the characteristics of cache

Results:-
The results directory has a file "SpecBenchmark_cache_reference.txt" which has the reference results of all the trace inputs provided in the cache.sh file. After running the cache.sh, the cache.cpp file will generate a "SpecBenchmark_cache_results.txt" file which contains the generated results and can be used for comparision.

