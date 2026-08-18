#include "../include/classicMaps.h"


//Logistic Map
LogisticMap::LogisticMap(real r): Map("logisticMap", {r}), r_(params()[0]){
    //Throw exception in case parameter is out of bounds
    if (r > 4 || r < 0){
        throw std::invalid_argument("parameter r must be between 0 and 4.0");
    }
}
