#include "../include/ergodicAnalyzer.h"



// Time average
double Analyzer::birkhoffAverage(double x0, int N, const std::function<double(double)>& f) const {
    double sum = 0.0;
    double x = x0;
    // Birkhoff average: (1/N) * sum_{n=0}^{N-1} f(T^n x0)
    for (int i = 0; i < N; i++) {
        sum += f(x);
        x = map_.iterate(x);
    }
    return sum / N;
}

std::vector<double> Analyzer::birkhoffConvergence(double x0, int N, const std::function<double(double)>& f) const {
    std::vector<double> running;
    running.reserve(N);
    double sum = 0.0;
    double x = x0;
    for (int i = 0; i < N; i++) {
        sum += f(x);
        running.push_back(sum / (i + 1));
        x = map_.iterate(x);
    }
    return running;
}
//Lyapunov Exponent at N
double Analyzer::lyapunovExponent(double x0, int N) const {
    double sum = 0.0;
    double x = x0;
    for (int i = 0; i < N; i++) {
        double d = std::abs(map_.derivative(x));
        if (d > 0) sum += std::log(d);
        x = map_.iterate(x);
    }
    return sum / N;
}
//Running Lyapunov Exponent
std::vector<double> Analyzer::lyapunovExponentConvergence(double x0, int N) const {
    std::vector<double> running;
    running.reserve(N);
    double sum = 0.0;
    double x = x0;
    for (int i = 0; i < N; i++) {
        double d = std::abs(map_.derivative(x));
        if (d > 0) sum += std::log(d);
        running.push_back(sum / (i + 1));
        x = map_.iterate(x);
    }
    return running;
}

//
std::vector<double> Analyzer::trajectoryDivergence(double x0, int N, double delta) const {
    std::vector<double> logSeparation;
    //Alocate N places for trajectory divergence
    logSeparation.reserve(N);
    double x = x0;
    double y = x0 + delta;
    for (int i = 0; i < N; i++) {
        double separation = std::abs(x - y);
        //use quite_Nan in case sep = 0 
            if (separation > 0){
                logSeparation.push_back(std::log(separation));
            }
            else {
                logSeparation.push_back(std::numeric_limits<double>::quiet_NaN());
            }   
        x = map_.iterate(x);
        y = map_.iterate(y);
    }
    return logSeparation;
}

std::vector<double> Analyzer::invariantMeasure(double x0, int N, int bins) const {
    std::vector<double> hist(bins, 0.0);
    double low = map_.xmin();
    double high = map_.xmax();
    double x = x0;
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