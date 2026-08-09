#include "../include/map.h"

// Identifier built from the map's tag and parameters (e.g. logisticMap4.000000)
std::string Map::hashKey() const {
    std::string key = tag_;
    for (double p : params_) key += std::to_string(p);
    return key;
}

// Generate an orbit of length n starting from x0
std::vector<double> Map::orbit(double x0, int n) const{
    std::vector <double> orb;
    //alocate n places to the vector orb
    orb.reserve(n);
    //create current phase point x
    double x = x0;
    for (int i = 0; i< n; i++){
        orb.push_back(x);
        x = iterate(x);
    }
    return orb;
}