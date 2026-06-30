#pragma once
#include "map.h"
#include <functional>
#include <cmath>
#include <numeric>
#include <stdexcept>

// Analyzer borrows a Map (does not own it) and computes ergodic quantities.
// All methods take observables f: R -> R as std::function.

class Analyzer {
public:
    explicit Analyzer(const Map& map) : map_(map) {}
 

    double birkhoffAverage(double x0, int N,
                           const std::function<double(double)>& f) const;
 
    // Birkhoff average convergence: returns vector of running averages
    std::vector<double> birkhoffConvergence(double x0, int N,
                           const std::function<double(double)>& f) const;
 
    // Maximal Lyapunov exponent: (1/N) * sum log|DT(x_n)|
    double lyapunovExponent(double x0, int N) const;
 
    // Invariant measure: histogram of orbit visits over [xmin, xmax]
    // Returns normalized bin counts (approximates the invariant density)
    std::vector<double> invariantMeasure(double x0, int N, int bins) const;
 
 
private:
    const Map& map_;  // reference — not owned
};