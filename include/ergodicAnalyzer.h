#pragma once
#include "map.h"
#include <functional>
#include <vector>
 
// Analyzer borrows a Map (does not own it) and computes ergodic quantities.
// All methods take observables f: R -> R as std::function.

class Analyzer {
public:
    // Takes a reference — Analyzer does not own the map
    explicit Analyzer(const Map& map) : map_(map) {}
 
    // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
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
 
    // Autocorrelation: C(n) = <f o T^n * f> - <f>^2
    std::vector<double> autocorrelation(double x0, int N, int maxLag,
                           const std::function<double(double)>& f) const;
 
private:
    const Map& map_;  // reference — not owned
};