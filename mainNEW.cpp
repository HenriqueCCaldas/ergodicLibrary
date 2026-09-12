#include <iostream>
#include <fstream>
#include <filesystem>
#include "include/mapTemplate.h"
#include "include/classicMaps2D.h"
#include "include/ergodicAnalyzerTemplate.h"

template <size_t dim>
void writeTrajectoryCSV(const std::string& path, const std::vector<typename Map<dim>::point>& orbit) {
    std::filesystem::path fullPath = std::string(DATA_DIR) + path;
    std::filesystem::create_directories(fullPath.parent_path());
    std::ofstream f(fullPath);

    f << "n";
    for (size_t d = 0; d < dim; d++) f << ",x" << d;
    f << "\n";

    for (size_t i = 0; i < orbit.size(); i++) {
        f << i;
        for (size_t d = 0; d < dim; d++) f << "," << orbit[i][d];
        f << "\n";
    }
}

int main() {
    // Rulkov map: T(x,y) = (alpha/(1+x^2) + y, y - mu*(x - sigma))
    RulkovMap rulkov(real("4.1"), real("0.001"), real("-0.02"));
    Analyzer2D analyzer(rulkov);

    Map2D::point x0 = {real("-1.0"), real("-2.5")};
    int N = 100;

    // Observable: project onto the x-coordinate (f : point -> real)
    std::function<real(Map2D::point)> f = [](Map2D::point p) { return p[0];};

    real avg = analyzer.birkhoffAverage(x0, N, f);
    std::cout << "birkhoffAverage(x-coordinate, N=" << N << ") = " << avg << std::endl;

    auto convergence = analyzer.birkhoffConvergence(x0, N, f);
    std::cout << "birkhoffConvergence: first value = " << convergence.front()
              << ", last value = " << convergence.back() << std::endl;
    std::cout << "  (last value should match birkhoffAverage above)" << std::endl;

    // Perturb x0 by a tiny amount in the x-coordinate and track divergence
    Map2D::point delta = {std::numeric_limits<real>::epsilon(), real("0.0")};
    //Map2D::point delta = {real("0.0"), real("0.0")};
    auto divergence = analyzer.trajectoryDivergence(x0, N, delta);
    std::cout << "trajectoryDivergence: first value = " << divergence.front()
              << ", last value = " << divergence.back() << std::endl;

    auto trajectory = rulkov.orbit(x0, N);
    writeTrajectoryCSV<2>(rulkov.hashKey() + "/trajectory.csv", trajectory);
    std::cout << "Wrote trajectory to " << rulkov.hashKey() << "/trajectory.csv" << std::endl;

    return 0;
}
