#include "../include/ergodicAnalyzerTemplate.h"
#include "../include/mapTemplate.h"


template <size_t dim>
real Analyzer<dim>::birkhoffAverage(typename Map<dim>::point x0, int N,
    const std::function< real(typename Map<dim>::point)>& f) const{
//Copy what is already defined for 1D in ergodicAnalyzer.cpp
        real sum = real("0.0");
        typename Map<dim>::point x = x0;
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
        typename Map<dim>::point x = x0;
        // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
        for (int i = 0; i < N; i++) {
            sum += f(x);
            running.push_back(sum / (i+1));
            x = map_.iterate(x);
        }
        return running;
}

//Trajectory divergence: log|x_n - y_n| for two orbits starting delta apart (x0, x0+delta).
template <size_t dim>
std::vector<real> Analyzer<dim>::trajectoryDivergence(typename Map<dim>::point x0, int N,
    typename Map<dim>::point delta) const{
        std::vector<real> logseparation;
        logseparation.reserve(N);
        typename Map<dim>::point x = x0;
        typename Map<dim>::point y = x0;
        for (size_t i = 0; i < dim; i++){
            y[i] += delta[i];
        }
        for (int i = 0; i < N; i++){
            real aux = real("0");
            for (size_t j = 0; j < dim; j++){
                aux += abs(x[j]-y[j])*abs(x[j]-y[j]);
            }
            if (aux > 0){
                aux = sqrt(aux);
                logseparation.push_back(log(aux));
            }
            else{
                logseparation.push_back(std::numeric_limits<real>::quiet_NaN());
            }            
            x = map_.iterate(x);
            y = map_.iterate(y);
        }
        return logseparation;
};

//To make sure the methods defined in this cpp are properly called from main
template class Analyzer<1>;
template class Analyzer<2>;