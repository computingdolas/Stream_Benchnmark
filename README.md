# Stream_Benchnmark for NUMA Machine @ intel Processor - 3.2Ghz
This stream specifically desisgned for NUMA machine. This stream benchmark does not measure memory bandwidth, but can be freely adapted to it. It supports NUMA memory allocation. It currently supports four types of Analysis

1. Memory Bandwidth Limited - ADD Operations
2. Compute Bound - ADD Operations
3. Random Access - ADD Operations
4. Random Access and Compute Bound - ADD Operations

# Compilation
g++ -std=c++11 -fopenmp -O3 filename -o name_executable

# Execution 
numactl --physcpubind=0,1,2,3 --localalloc ./name_of_executable  number_of_iterations  memory_Mbytes

# Energy Consumption 
Stream benchmark can also be used to measure energy consumption of processing cores using perf tool by using following command only on linux system 
sudo perf stat -a -e "power/energy-cores/" ./<name of executable>
