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

// Full Lyapunov spectrum via the Benettin/QR method.
template <size_t dim>
std::array<real, dim> Analyzer<dim>::lyapunovSpectrum(typename Map<dim>::point x0, int N) const{
    using matrix = typename Map<dim>::matrix;
    // Q holds an orthonormal tangent basis: Q[i][k] is component i of basis vector k,
    matrix Q{};
    //Initialiaze the Q as the identity
    for (size_t i = 0; i < dim; i++) Q[i][i] = real("1.0");

    std::array<real, dim> sumLog{};
    for (size_t i = 0; i < dim; i++) sumLog[i] = real("0.0");


    typename Map<dim>::point x = x0;

    for (int n = 0; n < N; n++) {
        matrix J = map_.jacobian(x);

        // Propagate the basis: W = J * Q
        matrix W{};
        for (size_t i = 0; i < dim; i++) {
            for (size_t k = 0; k < dim; k++) {
                real acc = real("0.0");
                for (size_t j = 0; j < dim; j++) {
                    acc += J[i][j] * Q[j][k];
                }
                W[i][k] = acc;
            }
        }

        // Modified Gram-Schmidt QR: re-orthonormalize the columns of W into Q,
        // accumulating the log of each column's residual norm (= R's diagonal).
        for (size_t k = 0; k < dim; k++) {
            std::array<real, dim> v;
            for (size_t i = 0; i < dim; i++) v[i] = W[i][k];

            for (size_t j = 0; j < k; j++) {
                real proj = real("0.0");
                for (size_t i = 0; i < dim; i++) proj += Q[i][j] * v[i];
                for (size_t i = 0; i < dim; i++) v[i] -= proj * Q[i][j];
            }

            real norm = real("0.0");
            for (size_t i = 0; i < dim; i++) norm += v[i] * v[i];
            norm = sqrt(norm);

            for (size_t i = 0; i < dim; i++) Q[i][k] = v[i] / norm;
            sumLog[k] += log(norm);
        }

        x = map_.iterate(x);
    }

    std::array<real, dim> lambda;
    for (size_t i = 0; i < dim; i++){
         lambda[i] = sumLog[i] / N;
    }
    return lambda;
}

//To make sure the methods defined in this cpp are properly called from main
template class Analyzer<1>;
template class Analyzer<2>;