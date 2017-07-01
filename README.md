# Stream_Benchnmark for Msc thesis
This stream specifically desisgned for NUMA machine. This stream benchmark does not measure memory bandwidth, but can be freely adapted to it. It supports NUMA memory allocation.

# Compilation
g++ -std=c++11 -fopenmp -O3 filename -o name_executable

# Execution 
numactl --physcpubind=0,1,2,3 --localalloc ./name_of_executable number_of_iterations memory_Mbytes
