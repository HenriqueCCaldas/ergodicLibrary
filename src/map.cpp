#include "../include/map.h"

// Identifier built from the map's tag and parameters (e.g. logisticMap4.000000)
std::string Map::hashKey() const {
    std::string key = tag_;
    for (real p : params_) key += p.str(2, std::ios_base::fixed)+ "_";
    return key;
}

// Generate an orbit of length n starting from x0
std::vector<real> Map::orbit(real x0, int n) const{
    std::vector <real> orb;
    //alocate n places to the vector orb
    orb.reserve(n);
    //create current phase point x
    real x = x0;
    for (int i = 0; i< n; i++){
        orb.push_back(x);
        x = iterate(x);
    }
    return orb;
}