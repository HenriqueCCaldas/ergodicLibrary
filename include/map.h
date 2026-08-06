#pragma once
#include <vector>
#include <string>
 
// base class for all discrete dynamical maps
// use polymorphism in classicMaps.h and .cpp to replace the virtual methods iterate (), derivative and name;
// using const methods to guarantee no member of the class is changed when called

class Map {
public:
    virtual ~Map() = default;
 
    // Apply the map once: x -> T(x)
    virtual double iterate(double x) const = 0;
 
    // Derivative of the map at x: DT(x)
    // Used for Lyapunov exponent computation
    virtual double derivative(double x) const = 0;
 
    // Name for output/plots
    virtual std::string name() const = 0;
 
    // Generate an orbit of length n starting from x0
    std::vector<double> orbit(double x0, int n) const;
 
    // Limit Phase space bounds [xmin, xmax] (relevant for histogramming for example)
    virtual double xmin() const = 0;
    virtual double xmax() const = 0;
};