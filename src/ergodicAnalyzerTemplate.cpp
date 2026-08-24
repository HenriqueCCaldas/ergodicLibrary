#include "../include/ergodicAnalyzerTemplate.h"


template <size_t dim> typename Map<dim>::point Analyzer<dim>::birkhoffAverage(typename Map<dim>::point x0, int N,
    const std::function< typename Map<dim>::point(typename Map<dim>::point)>& f) const{

}
// Birkhoff average convergence: returns vector of running averages
template <size_t dim>
std::vector<typename Map<dim>::point> birkhoffConvergence(typename Map<dim>::point x0, int N, 
    const std::function<typename Map<dim>::point(typename Map<dim>::point)>& f) const;

//Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
template <size_t dim>
std::vector<typename Map<dim>::point> trajectoryDivergence(typename Map<dim>::point x0, int N,
    typename Map<dim> point delta) const;