#include "../include/classicMaps.h"


//Logistic Map
LogisticMap::LogisticMap(double r){
    if (r > 4 || r < 0){
        throw std::invalid_argument("parameter r must be between 0 and 4.0");
    }
    else r_ = r;
}

