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
#include <random>


int main(int argc, const char * argv[]) {
    
	// Taking the input parameter 
    int K_times = std::atoi(argv[1]) ; 
    double input_bytes = std::stod(argv[2]) ; 
    int N_bytes = 32 ; 

    double global_time = 0.0	 ; 
    uint64_t N = (input_bytes * 1e+06) / N_bytes ; 
    
    std::cout << "The length of array is :=" << N << " doubles" << std::endl ; 
    std::cout <<"The input memory in megabytes are :="<< input_bytes <<" MegaBytes"<< std::endl ; 
    std::cout <<"The number of iterations performed will be :=" << K_times<< std::endl ; 
    std::cout << "NUMA aware memory allocation taking place"<<std::endl ; 
    
    std::vector<uint64_t> r(N) ; 
    std::vector<uint64_t> empty ; 
    for (uint64_t i = 0 ; i < N ; ++i){
		r[i] = i ; 
    }
    std::random_shuffle(r.begin(),r.end()) ; 

    // Memory allocation     
    double * a = new double [N] ;
    double * b = new double [N] ;
    double * c = new double [N] ;
    uint64_t *random = new uint64_t[N] ; 

    // NUMA initialization ... / first touch principle 
    #pragma omp parallel for schedule(static) shared(a,b,c,N) num_threads(8)
    for (uint64_t i = 0; i < N; ++i)
    {
    	a[i] = 1.0 ; 
    	b[i] = 1.0 ; 
    	c[i] = 1.0 ; 
    	random[i] = r[i] ; 
    }
    
    std::cout << "Deleting the random std::vector " << std::endl ; 
    r.swap(empty) ; 
    std::cout << "The size of random vector is :=" << r.size() << std::endl ;

    // ADD Benchmark ... Unit Stride Random Access 
    for (int i = 0 ; i < K_times ; ++i){
    	#pragma omp parallel shared(a,b,c,random,N) num_threads(8)
    	{
    		double wtime = omp_get_wtime() ; 
    		#pragma omp for schedule(static) 
    		for (uint64_t k =0 ; k < N ; ++k){                
                	a[random[k]] = sin(b[random[k]]) + sin(c[random[k]]) ; 
    		}
    		wtime = omp_get_wtime() - wtime ; 
    		#pragma omp master 
    		 	global_time += wtime ; 
    	}
    }
    std::cout << "Time spend for unit stride ADD operation is :=" << global_time / (double) K_times  <<" seconds "<< std::endl ;     
 }
