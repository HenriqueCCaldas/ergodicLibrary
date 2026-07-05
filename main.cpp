#include <iostream>
#include <fstream>
#include <unordered_map>
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

    //Initialize both the Doubling and the Logistic Map
    auto doubling = std::make_unique<DoublingMap>();
    auto logistic = std::make_unique<LogisticMap>(4.0);
    //Create a hash map for these
    std::unordered_map<std::string, Map*> availableMaps = {
        {doubling->name(), doubling.get()}, {logistic->name(), logistic.get()}
    };
 
    for (const auto& [name, map]: availableMaps){
        std:: cout << "\nMap: " << name << std::endl;
        double x0 = 0.3123432643253452;
        auto entryOrbit = map->orbit(x0,100);
        std::cout << "First 100 iterates from x0 = " << std::to_string(x0) << std::endl;
        for (double x: entryOrbit){
            std::cout << "  " << x << std::endl;
        }
    
        Analyzer analyzer(*map);  // borrows, does not own
        auto f = [](double x) { return x;};  // identity observable
 
        auto convergence = analyzer.birkhoffConvergence(x0, 10000, f);
        writeCSV(name + "/birkhoff_convergence.csv", convergence);
        std::cout << "Birkhoff average (N=10000): " << convergence.back()<<std::endl;
 
    
        auto measure = analyzer.invariantMeasure(x0, 1000000, 100);
        writeCSV(name +"/invariant_measure.csv", measure);
 
        //printout the Lyapunov exponent for the doubling map
        std::cout << "Lyapunov exponent for "<< name << ": " << analyzer.lyapunovExponent(0.2, 100000) << std::endl << std::endl;
    }
    return 0;
}