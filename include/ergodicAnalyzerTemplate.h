#include "mapTemplate.h"
#include <functional>
#include <limits>
#include <cmath>
#include <numeric>
#include <stdexcept>

template <size_t dim> class Analyzer{
    private:
        const Map<dim>& map_;
        
    public:

        explicit Analyzer(const Map<dim>& map): map_(map){};
        
        typename Map<dim>::point birkhoffAverage(typename Map<dim>::point x0, int N,
            const std::function< typename Map<dim>::point(typename Map<dim>::point)>& f) const;

        // Birkhoff average convergence: returns vector of running averages
        std::vector<typename Map<dim>::point> birkhoffConvergence(point x0, int N, const std::function<point(point)>& f) const;

        //Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
        std::vector<typename Map<dim>::point> trajectoryDivergence(point x0, int N, point delta) const;

};