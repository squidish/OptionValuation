//
//  Insturment.h
//  OptionValuation
//
//  Created by Williams on 25/11/2024.
//
#include <iostream>
#include <algorithm>
class Instrument {
    public:
    
    double virtual payoff(double &S_) = 0;
        
};


class Call : public Instrument {
    public:
    double payoff(double &S_, double &K_) {
        return std::max(S_-K_,0.0);
    };
        
};
