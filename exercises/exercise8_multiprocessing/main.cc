#include <iostream>
#include <vector>
#include <thread>
#include <string>

#include "harm.h"

int main(int argc,char** argv){

    int nthreads = 1;
    int nterms = 1e8;

    for(int i=0;i<argc;i++){
        std::string arg = argv[i];

        if(arg=="-threads" && i+1<argc)
            nthreads = std::stoi(argv[i+1]);

        if(arg=="-terms" && i+1<argc)
            nterms = std::stoi(argv[i+1]);
    }

    std::vector<data> params(nthreads);

    for(int i=0;i<nthreads;i++){
        params[i].a = 1 + nterms/nthreads*i;
        params[i].b = 1 + nterms/nthreads*(i+1);
    }

    params.back().b = nterms+1;

    std::vector<std::thread> threads;

    for(int i=0;i<nthreads;i++){
        threads.emplace_back(harm,std::ref(params[i]));
    }

    for(auto& thread : threads)
        thread.join();

    double total=0;
    for(auto& p : params)
        total+=p.sum;

    std::cout<<"Harmonic sum = "<<total<<std::endl;
}