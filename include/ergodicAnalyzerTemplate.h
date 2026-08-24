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
        
        real birkhoffAverage(typename Map<dim>::point x0, int N,
            const std::function< real(typename Map<dim>::point)>& f) const;

        // Birkhoff average convergence: returns vector of running averages
        std::vector<real> birkhoffConvergence(typename Map<dim>::point x0, int N, const std::function<real(typename Map<dim>::point)>& f) const;

        //Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
        std::vector<typename Map<dim>::point> trajectoryDivergence(point x0, int N, point delta) const;

};

