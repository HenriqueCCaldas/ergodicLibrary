#include "../include/ergodicAnalyzer.h"



// Time average
real Analyzer::birkhoffAverage(real x0, int N, const std::function<real(real)>& f) const {
    real sum = 0.0;
    real x = x0;
    // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
    for (int i = 0; i < N; i++) {
        sum += f(x);
        x = map_.iterate(x);
    }
    return sum / N;
}

std::vector<real> Analyzer::birkhoffConvergence(real x0, int N, const std::function<real(real)>& f) const {
    std::vector<real> running;
    running.reserve(N);
    real sum = 0.0;
    real x = x0;
    for (int i = 0; i < N; i++) {
        sum += f(x);
        running.push_back(sum / (i + 1));
        x = map_.iterate(x);
    }
    return running;
}
//Lyapunov Exponent at N
real Analyzer::lyapunovExponent(real x0, int N) const {
    real sum = 0.0;
    real x = x0;
    for (int i = 0; i < N; i++) {
        real d = abs(map_.derivative(x));
        if (d > 0) sum += log(d);
        x = map_.iterate(x);
    }
    return sum / N;
}
//Running Lyapunov Exponent
std::vector<real> Analyzer::lyapunovExponentConvergence(real x0, int N) const {
    std::vector<real> running;
    running.reserve(N);
    real sum = 0.0;
    real x = x0;
    for (int i = 0; i < N; i++) {
        real d = abs(map_.derivative(x));
        if (d > 0) sum += log(d);
        running.push_back(sum / (i + 1));
        x = map_.iterate(x);
    }
    return running;
}

//
std::vector<real> Analyzer::trajectoryDivergence(real x0, int N, real delta) const {
    std::vector<real> logSeparation;
    //Alocate N places for trajectory divergence
    logSeparation.reserve(N);
    real x = x0;
    real y = x0 + delta;
    for (int i = 0; i < N; i++) {
        real separation = abs(x - y);
        //use quite_Nan in case sep = 0 
            if (separation > 0){
                logSeparation.push_back(log(separation));
            }
            else {
                logSeparation.push_back(std::numeric_limits<real>::quiet_NaN());
            }   
        x = map_.iterate(x);
        y = map_.iterate(y);
    }
    return logSeparation;
}

std::vector<real> Analyzer::invariantMeasure(real x0, int N, int bins) const {
    std::vector<real> hist(bins, 0.0);
    real low = map_.xmin();
    real high = map_.xmax();
    real x = x0;
    for (int i = 0; i < N; i++) {
        //retrieve the index of the bin the each iteration of the map
        //use static cast to convert to integer
        int bin = static_cast<int>((x - low) / (high - low) * bins);
        if (bin >= 0 && bin < bins) {
            hist[bin]++;
        }
        x = map_.iterate(x);
    }
    //normalize to account for iterations
    for (auto& h : hist) {
        h /= N;
    }
    return hist;
}