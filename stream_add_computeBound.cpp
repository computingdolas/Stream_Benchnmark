//
//  main.cpp
//  Stream Benchmark
//
//  Created by Sagar Dolas on 28/06/17.
//  Copyright © 2017 Sagar Dolas. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <omp.h>
#include <string>
#include <vector>
#include <math.h>


int main(int argc, const char * argv[]) {
    
	// Taking the input parameter 
    int K_times = std::atoi(argv[1]) ; 
    double input_bytes = std::stod(argv[2]) ; 
    int N_bytes = 24 ; 

    double global_time = 0.0	 ; 
    uint64_t N = (input_bytes * 1e+06) / N_bytes ; 
    std::cout << "The length of array is :=" << N << " doubles" << std::endl ; 
    std::cout <<"The input memory in megabytes are :="<< input_bytes <<" MegaBytes"<< std::endl ; 
    std::cout <<"The number of iterations performed will be :=" << K_times<< std::endl ; 
    std::cout << "NUMA aware memory allocation taking place"<<std::endl ; 
    

    // Memory allocation     
    double * a = new double [N] ;
    double * b = new double [N] ;
    double * c = new double [N] ;

    // std::vector<double> a(N) ; 
    // std::vector<double> b(N) ; 
    // std::vector<double> c(N) ; 
    // std::vector<uint64_t> r(N) ; 

    // NUMA initialization ... / first touch principle 
    #pragma omp parallel for schedule(static) shared(a,b,c,N) num_threads(16)
    for (uint64_t i = 0; i < N; ++i)
    {
    	a[i] = 0.0 ; 
    	b[i] = i ; 
    	c[i] = i ; 
    }
    
    // ADD Benchmark ... unit stride access 
    for (int i = 0 ; i < K_times ; ++i){
    	#pragma omp parallel shared(a,b,c,N) num_threads(16)
    	{
    		double wtime = omp_get_wtime() ; 
    		#pragma omp for schedule(static) 
    		for (uint64_t k = 0 ; k < N ; ++k){
                	//a[k] = exp(-1.0 * (sin(b[k]) + cos(c[k]))) ; 
    				a[k] = b[k] + c[k] ; 
    		}
    		wtime = omp_get_wtime() - wtime ; 
    		#pragma omp master 
    		 	global_time += wtime ; 
    	}
    }

    std::cout << "Time spend for unit stride ADD operation is :=" << global_time / (double) K_times  <<" seconds "<< std::endl ;     

}
