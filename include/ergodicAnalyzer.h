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
    double birkhoffAverage(double x0, int N, const std::function<double(double)>& f) const;
 
    // Birkhoff average convergence: returns vector of running averages
    std::vector<double> birkhoffConvergence(double x0, int N, const std::function<double(double)>& f) const;

    // Maximal Lyapunov exponent in one dimension: (1/N) * sum log|DT(x_n)|
    double lyapunovExponent(double x0, int N) const;

    //Running average of the Lyapunov Exponent
    std::vector<double> lyapunovConvergence(double x0, int N) const;

    // Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
    std::vector<double> trajectoryDivergence(double x0, double delta, int N) const;

    // Invariant measure: histogram of orbit visits over [xmin, xmax]
    // Returns normalized bin counts (approximates the invariant density)
    std::vector<double> invariantMeasure(double x0, int N, int bins) const;
 
private:
    const Map& map_;  // taken as a reference pointing to the memory location of map used in the constructor
};
