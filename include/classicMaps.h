#include "map.h"
#include <stdexcept>

class DoublingMap : public Map {
public:
    double iterate(double x) const override {
        return std::fmod(2.0 * x, 1.0); 
    }
    double derivative(double /*x*/) const override { 
        return 2.0; 
    }
    std::string name() const override { 
        return "DoublingMap";
    }
    double xmin() const override { 
        return 0.0; 
    }
    double xmax()  const override { 
        return 1.0; 
    }
};

// Logistic map: T(x) = r * x * (1 - x), x in [0,1]

class LogisticMap : public Map {
private:
    //Parameter for the logistic regression
    double r_;
public:
    explicit LogisticMap(double r);
    double iterate(double x) const override{
        return (r_ * x * (1-x));
    }
    double derivative (double x) const override {
        return (r_ * (1 - 2 * x));
    }
    std::string name() const override {
        return ("Logistic Map at " + std::to_string(r_));
    }
    double xmin() const override {
        return 0.0;
    }
    double xmax() const override {
        return 1.0; 
    }
};