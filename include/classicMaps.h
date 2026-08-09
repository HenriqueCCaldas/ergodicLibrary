#include "map.h"
#include <stdexcept>

class DoublingMap : public Map {
public:
    explicit DoublingMap() : Map("doublingMap", {}) {}
    //For y 
    double iterate(double x) const override {
        return std::fmod(2.0 * x, 1.0); 
    }
    double derivative(double /*x*/) const override { 
        return 2.0; 
    }
    std::string name() const override { 
        return "Doubling Map";
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
    //Parameter for the logistic regression, aliased into Map::params_
    double& r_;
public:
    explicit LogisticMap(double r);
    double iterate(double x) const override{
        return (r_ * x * (1 - x));
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

class GaussIteratedMap: public Map {
private:
    // aliased into Map::params_
    double& alpha_;
    double& beta_;
public:
    explicit GaussIteratedMap(double alpha, double beta)
    : Map("gaussIterated", {alpha, beta}), alpha_(params()[0]), beta_(params()[1]) {};
    
        double iterate(double x) const override {
        return std::exp(-alpha_ * x * x) + beta_;
    }
    double derivative(double x) const override {
        return -2.0 * alpha_ * x * std::exp(-alpha_ * x * x);
    }
    std::string name () const override {
        return "Gauss Iterated Map at (" + std::to_string(alpha_) + "," + std::to_string(beta_) + ')';
    }
    double xmin() const override {
        return (-1.0);
    }
    double xmax() const override {
        return 1.0; 
    }  
};