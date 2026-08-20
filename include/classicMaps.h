#include "map.h"
#include <stdexcept>

class DoublingMap : public Map {
public:
    explicit DoublingMap() : Map("doublingMap", {}) {}
    //For y 
    real iterate(real x) const override {
        return fmod(2.0 * x, 1.0); 
    }
    real derivative(real /*x*/) const override { 
        return 2.0; 
    }
    std::string name() const override { 
        return "Doubling Map";
    }
    real xmin() const override { 
        return 0.0;
    }
    real xmax()  const override { 
        return 1.0; 
    }
};

// Logistic map: T(x) = r * x * (1 - x), x in [0,1]

class LogisticMap : public Map {
private:
    //alias of the parameter in the base class Map 
    real& r_;
public:
    explicit LogisticMap(real r);
    real iterate(real x) const override{
        return (r_ * x * (1 - x));
    }
    real derivative (real x) const override {
        return (r_ * (1 - 2 * x));
    }
    std::string name() const override {
        return ("Logistic Map at " + r_.str());
    }
    real xmin() const override {
        return 0.0;
    }
    real xmax() const override {
        return 1.0; 
    }
};

class GaussIteratedMap: public Map {
private:
    //alias the parameters from the base class Map
    real& alpha_;
    real& beta_;
public:
    explicit GaussIteratedMap(real alpha, real beta)
    : Map("gaussIterated", {alpha, beta}), 
    alpha_(params()[0]), 
    beta_(params()[1]) {};
    
    real iterate(real x) const override {
        return exp(-alpha_ * x * x) + beta_;
    }
    real derivative(real x) const override {
        return -2.0 * alpha_ * x * exp(-alpha_ * x * x);
    }
    std::string name () const override {
        return "Gauss Iterated Map at (" + alpha_.str() + "," + beta_.str() + ')';
    }
    real xmin() const override {
        return (-1.0);
    }
    real xmax() const override {
        return 1.0; 
    }  
};