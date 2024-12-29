//
//  Untitled.h
//  OptionValuation
//
//  Created by Williams on 14/11/2024.
//

#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class WeinerProcess {
    
private:
    int nPath,nPathLength;
    double dt;
    double *paths;
    double * x0;
public:
    
    WeinerProcess( const int &nPath_,const int nPathLength_ ,const double &dt_ ) : nPath{nPath_},dt{dt_},nPathLength{nPathLength_} ,x0(new double[nPath_]{0.0}), paths(new double[nPath_*nPathLength_]{0.0}) {
        //
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_real_distribution unif{0.0, 1.0};
        double x;
        //for (auto i=0; i < nDim; i++ ) {
            for (auto j=0; j < nPath; j++) {
                x = x0[j];
                for (auto k=0; k < nPathLength; k++) {
                    paths[nPathLength*j+k] = x + dt * NormalCDFInverse(unif(gen));
                    x = paths[nPathLength*j+k];
                    //std::cout << nPathLength*j+k<< " " <<  paths[nPathLength*j+k] << std::endl;
                }
            }
        //}
        
    }
    
    // Copy Constructor (Deep Copy)
    WeinerProcess(const WeinerProcess& other) :  nPath{other.nPath},nPathLength{other.nPathLength} ,x0(new double[other.nPath]{0}), paths(new double[other.nPath*other.nPathLength]{0}) {
        for (auto i= 0 ; i < nPath; i++) {
            other.x0[i] = other.x0[i];
        }
        for (auto i= 0 ; i < nPathLength*nPath; i++) {
            other.paths[i] = other.paths[i];
        }
        // could use this function from the standard lib
        //std::memcpy(data, other.test, len * sizeof(int)); // Copy data
        std::cout << "Copy Constructor called. Deep copy performed." << std::endl;
    }
    
    
    //Copy assignment
    WeinerProcess& operator=(const WeinerProcess& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        
        //release existing resources
        delete[] paths;
        delete[] x0;
        
        // Allocate new memory and copy data
        nPath = other.nPath;
        nPathLength = other.nPathLength;
        x0 = new double[other.nPath]{0};
        paths = new double[other.nPathLength*other.nPath]{0};
        for (auto i= 0 ; i < nPath; i++) {
            other.x0[i] = other.x0[i];
        }
        for (auto i= 0 ; i < nPathLength*nPath; i++) {
            other.paths[i] = other.paths[i];
        }
        
        std::cout << "Copy Assignment Operator called. Deep copy performed." << std::endl;
        return *this;
    }
    
    
    void printDimension() {
        double time = 0.00;
        std::ofstream file("/Users/Williams/Software/OptionValuation/paths.csv");
        if (!file.is_open()) {
            std::cerr << "Failed to open the file for writing!" << std::endl;
        }
        file << std::fixed << std::setprecision(2);
        //The header is here:::
        file << "t";
        for (auto i = 0; i < nPath; i++) {
            file << ",";
            file << "p" + std::to_string(i);
        }
        file << endl;
        // first line
        file << time;
        for (auto i = 0; i < nPath; i++) {
            file << ",";
            file << x0[i];
        }
        file << endl;
       // first line
       time = time +dt;
       for (auto i = 0; i < nPathLength; i++) {
           file << time;
            for (auto j = 0;  j < nPathLength; j++ ) {
                file << ",";
                file << paths[j*nPathLength + i];
               // cout <<j*nPathLength + i << endl;
            }
           file << endl;
           time = time + dt;
        }
        // Close the file */
        file.close();
        std::cout << "CSV file 'paths.csv' has been generated successfully!" << std::endl;
    }
    
    ~WeinerProcess(){
        delete[] paths;
        delete[] x0;
    }
    
};
