#include "include/ergodicAnalyzer.h"


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

std::vector<double> Analyzer::invariantMeasure(double x0, int N, int bins) const {
    std::vector<double> hist(bins, 0.0);
    double low = map_.xmin();
    double high = map_.xmax();
    double x = x0;
    for (int i = 0; i < N; i++) {
        int bin = static_cast<int>((x - low) / (high - low) * bins);
        if (bin >= 0 && bin < bins) hist[bin]++;
        x = map_.iterate(x);
    }
    // normalize
    for (auto& h : hist) h /= N;
    return hist;
}