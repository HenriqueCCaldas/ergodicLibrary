#include <iostream>
#include <fstream>
#include "include/map.h"
#include "include/ergodicAnalyzer.h"
#include "include/classicMaps.h"

void writeCSV(const std::string& path, const std::vector<double>& data) {
    std::ofstream f("DATA_DIR" + path);
    for (int i = 0; i < (int)data.size(); i++)
        f << i << "," << data[i] << "\n";
}
 
int main() {
    // --- Module 1: Map + Orbit ---
    auto doubling = std::make_unique<DoublingMap>();
 
    std::cout << "Map: " << doubling->name() << "\n";
    auto orb = doubling->orbit(0.2, 10);
    std::cout << "First 10 iterates from x0=0.2:\n";
    for (double x : orb) std::cout << "  " << x << "\n";
 
    // --- Module 2: Birkhoff average ---
    Analyzer analyzer(*doubling);  // borrows, does not own
    auto f = [](double x) { return x; };  // identity observable
 
    auto convergence = analyzer.birkhoffConvergence(0.2, 10000, f);
    writeCSV("birkhoff_convergence.csv", convergence);
    std::cout << "\nBirkhoff average (N=10000): "
              << convergence.back() << " (expect ~0.5)\n";
 
    // --- Module 3: Invariant measure ---
    auto measure = analyzer.invariantMeasure(0.2, 1000000, 100);
    writeCSV("invariant_measure.csv", measure);
    std::cout << "Invariant measure written to data/invariant_measure.csv\n";
 
    // Compare Lyapunov across maps
    std::cout << "\nLyapunov exponents:\n";
    std::cout << "  " << doubling->name() << ": "
    << analyzer.lyapunovExponent(0.2, 100000) << "\n";
    return 0;
}