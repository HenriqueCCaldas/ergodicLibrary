#include <iostream>
#include <fstream>
#include "include/map.h"
#include "include/ergodicAnalyzer.h"
#include "include/classicMaps.h"

void writeCSV(const std::string& path, const std::vector<double>& data) {
    std::filesystem::path fullPath = std::string(DATA_DIR) + path;
    std::filesystem::create_directories(fullPath.parent_path());
    std::ofstream f(fullPath);
    for (int i = 0; i < (int)data.size(); i++)
        f << i << "," << data[i] << "\n";
}
 
int main() {

    auto doubling = std::make_unique<DoublingMap>();
 
    std::cout << "Map: " << doubling->name() << std::endl;
    auto orb = doubling->orbit(0.2, 10);
    std::cout << "First 10 iterates from x0=0.2: " << std::endl;
    for (double x : orb) std::cout << "  " << x << std::endl;
 
    
    Analyzer analyzer(*doubling);  // borrows, does not own
    auto f = [](double x) { return x; };  // identity observable
 
    auto convergence = analyzer.birkhoffConvergence(0.2, 10000, f);
    writeCSV("doublingMap/birkhoff_convergence.csv", convergence);
    std::cout << "Birkhoff average (N=10000): " << convergence.back() << " (expect ~0.5)" << std::endl;
 
    
    auto measure = analyzer.invariantMeasure(0.2, 1000000, 100);
    writeCSV("doublingMap/invariant_measure.csv", measure);
    std::cout << "Invariant measure written to :" << DATA_DIR << std::endl;
 
    //printout the Lyapunov exponent for the doubling map
    std::cout << "Lyapunov exponent for "<< doubling->name() << ": " << analyzer.lyapunovExponent(0.2, 100000) << std::endl;

    return 0;
}