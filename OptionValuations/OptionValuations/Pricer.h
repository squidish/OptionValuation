//
//  Pricer.h
//  OptionValuation
//
//  Created by Williams on 21/12/2024.
//

#include "Data.h"
#include "InvCDF.h"
#include "WeinerProcess.h"
#include "Instrument.h"
#include <boost/version.hpp>

class Pricer {
private:
    // can make this a pointer
    WeinerProcess mc;
    //create a vector of all the processes
public:
    Pricer() : mc(Data::n,Data::nPathLength,Data::dt) {
        // Extract Boost version components
        int major_version = BOOST_VERSION / 100000;       // Major version
        int minor_version = (BOOST_VERSION / 100) % 1000; // Minor version
        int patch_version = BOOST_VERSION % 100;          // Patch version

        // Print Boost version
        std::cout << "Boost version: "
                  << major_version << "."
                  << minor_version << "."
                  << patch_version << std::endl;
        
    }
    void runsimulation() {
        mc.printDimension();
    }
    
};

