#include "map.h"
#include <functional>
#include <limits>
#include <cmath>
#include <numeric>
#include <stdexcept>

// The Analyzer class borrows a Map (does not own it) and computes ergodic quantities.
// All methods take observables as function f: R -> R as std::function.

class Analyzer {
public:

    explicit Analyzer(const Map& map) : map_(map) {}
    real birkhoffAverage(real x0, int N, const std::function<real(real)>& f) const;
 
    // Birkhoff average convergence: returns vector of running averages
    std::vector<real> birkhoffConvergence(real x0, int N, const std::function<real(real)>& f) const;

    // Maximal Lyapunov exponent in one dimension: (1/N) * sum log|DT(x_n)|
    real lyapunovExponent(real x0, int N) const;

    //Running average of the Lyapunov Exponent
    std::vector<real> lyapunovExponentConvergence(real x0, int N) const;

    //Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
    std::vector<real> trajectoryDivergence(real x0, int N, real delta) const;

    // Invariant measure: histogram of orbit visits over [xmin, xmax]
    // Returns normalized bin counts (approximates the invariant density)
    std::vector<real> invariantMeasure(real x0, int N, int bins) const;
 
private:
    const Map& map_;  // taken as a reference pointing to the memory location of map used in the constructor
};
