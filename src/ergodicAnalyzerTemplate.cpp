#include "../include/ergodicAnalyzerTemplate.h"
#include "../include/mapTemplate.h"


template <size_t dim>
real Analyzer<dim>::birkhoffAverage(typename Map<dim>::point x0, int N,
    const std::function< real(typename Map<dim>::point)>& f) const{
//Copy what is already defined for 1D in ergodicAnalyzer.cpp
        real sum = real("0.0");
        real x = x0;
        // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
        for (int i = 0; i < N; i++) {
            sum += f(x);
            x = map_.iterate(x);
        }
        return sum / N;
}
// Birkhoff average convergence: returns vector of running averages
template <size_t dim>
std::vector<real> Analyzer<dim>::birkhoffConvergence(typename Map<dim>::point x0, int N, const std::function<real(typename Map<dim>::point)>& f) const{
        std::vector<real> running;
        running.reserve(N);
        real sum = real("0.0");
        real x = x0;
        // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
        for (int i = 0; i < N; i++) {
            sum += f(x);
            running.append(x);
            x = map_.iterate(x);
        }
        return sum / N;
}

//Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
template <size_t dim>
std::vector<typename Map<dim>::point> trajectoryDivergence(typename Map<dim>::point x0, int N,
    typename Map<dim> point delta) const;