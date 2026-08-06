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
    auto logistic4 = std::make_unique<LogisticMap>(4.0);

    // Alpha set tp 4.9 and sweeping between beta from -1 to 0 is chaotic
    // Fixed point at x0 = 0: simplest, Lyapunov < 0
    auto gauss_fixed   = std::make_unique <GaussIteratedMap>(4.9,  0.0);

    // Period 8 at x0= -0.58: periodic, Lyapunov = 0
    auto gauss_period  = std::make_unique<GaussIteratedMap>(4.9, -0.58);

    // Chaotic for x0= -0.5: — Lyapunov > 0
    auto gauss_chaotic = std::make_unique<GaussIteratedMap>(6.2, -0.5);
    
    //Create a hash map for these test maps;
    std::unordered_map<std::string, Map*> availableMaps = {
        {doubling->name(), doubling.get()}, {logistic4->name(), logistic4.get()} ,
        {gauss_fixed->name(), gauss_fixed.get()}, {gauss_chaotic->name(), gauss_chaotic.get()},
        {gauss_period->name(), gauss_period.get()}
    };

    for (const auto& [name, map]: availableMaps){
        std:: cout << "\nMap: " << name << std::endl;
        
        //Initial condition 
        double x0 = 0.2;
        //Create the first initial orbital points from x0
        auto entryOrbit = map->orbit(x0,100);
        std::cout << "First 100 iterates from x0 = " << std::to_string(x0) << std::endl;
        for (double x: entryOrbit){
            std::cout << "  " << x << std::endl;
        }
    
        
        //Initializes the analyzer, by borrowing the map (taking its memory reference)
        Analyzer analyzer(*map);  // borrows, does not own   
        
        //Use the identify function as the observable function
        auto f = [](double x) { return x;};
 
        //Use the methods deriving from the analyzer and 
        
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