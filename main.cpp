//
//  main.cpp
//  Stream Benchmark
//
//  Created by Sagar Dolas on 28/06/17.
//  Copyright © 2017 Sagar Dolas. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <chrono>


int main(int argc, const char * argv[]) {
    
	// Taking     
    uint64_t N = std::atol(argv[1]) ;
    int K_times = std::atoi(argv[2]) ; 


    // Memory allocation     
    double * a = new double [N] ;
    double * b = new double [N] ;
    double * c = new double [N] ;

    // NUMA initialization 
    for (uint64_t i = 0; i < N; ++i)
    {
    	a[i] = 1.0 ; 
    	b[i] = 1.0 ; 
    	c[i] = 1.0 ; 
    }
    
    // ADD Benchmark
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now() ;  
    for (int i = 0 ; i < K_times ; ++i){

    	for (uint64_t k =0 ; k < N ; ++k){
    		a[k] = b[k] + c[k] ; 
    	}
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() ;  
    double time_spend  =  std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() / 1000000.0 ;
	std::cout << "Time spend for ADD operations is :=" << time_spend << std::endl ;     
    double mem_bnd = (N * 3 * 8) / time_spend  ; 

    std::cout << "Add Operation Memory Bandwidth for :=" <<( N * 3 * sizeof(double) )/ time_spend << std::endl ; 


    // Finding out the average 




 
}
