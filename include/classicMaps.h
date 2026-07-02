#include "map.h"

class DoublingMap : public Map {
public:
    double iterate(double x)    const override { \
        return std::fmod(2.0 * x, 1.0); 
    }
    double derivative(double /*x*/) const override { 
        return 2.0; 
    }
    std::string name()          const override { 
        return "DoublingMap";
    }
    double xmin()               const override { 
        return 0.0; 
    }
    double xmax()               const override { 
        return 1.0; 
    }
};