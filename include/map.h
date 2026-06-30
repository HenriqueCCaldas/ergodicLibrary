#pragma once
#include <vector>
#include <string>
 
// Base class for all discrete dynamical maps
// polymorphism should replace the methods iterate () and derivative
class Map {
public:
    virtual ~Map() = default;
 
    // Apply the map once: x -> T(x)
    virtual double iterate(double x) const = 0;
 
    // Derivative of the map at x: DT(x)
    // Used for Lyapunov exponent computation
    virtual double derivative(double x) const = 0;
 
    // Human-readable name for output/plots
    virtual std::string name() const = 0;
 
    // Generate an orbit of length n starting from x0
    std::vector<double> orbit(double x0, int n) const;
 
    // Phase space bounds [xmin, xmax] for histogramming
    virtual double xmin() const = 0;
    virtual double xmax() const = 0;
};