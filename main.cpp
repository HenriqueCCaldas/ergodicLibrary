#include <iostream>
#include <fstream>
#include <unordered_map>
#include "include/map.h"
#include "include/ergodicAnalyzer.h"
#include "include/classicMaps.h"

void writeCSV(const std::string& path, const std::vector<real>& data) {
    std::filesystem::path fullPath = std::string(DATA_DIR) + path;
    std::filesystem::create_directories(fullPath.parent_path());
    std::ofstream f(fullPath);
    for (int i = 0; i < (int)data.size(); i++)
        f << i << "," << data[i] << "\n";
}
 
int main() {

    //Initialize both the Doubling and the Logistic Map
    auto doubling = std::make_unique<DoublingMap>();

    auto logistic4 = std::make_unique<LogisticMap>(real("4.0"));
    // Alpha set tp 4.9 and sweeping between beta from -1 to 0 is chaotic
    // Fixed point at x0 = 0: simplest, Lyapunov < 0
    auto gauss_fixed   = std::make_unique <GaussIteratedMap>(real("4.9"),  real("0.0"));

    // Period 8 at x0= -0.58: periodic, Lyapunov = 0
    auto gauss_period  = std::make_unique<GaussIteratedMap>(real("4.9"), real("-0.58"));

    // Chaotic for x0= -0.5: — Lyapunov > 0
    auto gauss_chaotic = std::make_unique<GaussIteratedMap>(real("6.2"), real("-0.5"));
    
    //Create a hash map for these test maps;
    std::unordered_map<std::string, Map*> availableMaps = {
        {doubling->hashKey(), doubling.get()},
        {logistic4->hashKey(), logistic4.get()} ,
        {gauss_fixed->hashKey(), gauss_fixed.get()},
        {gauss_chaotic->hashKey(), gauss_chaotic.get()},
        {gauss_period->hashKey(), gauss_period.get()}
    };

    for (const auto& [hash, map]: availableMaps){
        std:: cout << "\nMap: " << map->name() << std::endl;
        
        //Initial condition
        // Constructed from a string so cpp_bin_float_100's own parser rounds it
        // to ~100 decimal digits, instead of inheriting a double literal's ~16
        // digit rounding (which would reproduce the double-precision collapse
        // at n~53 regardless of how much precision `real` has downstream).
        real x0("0.2");
        //Create the first initial orbital points from x0
        auto entryOrbit = map->orbit(x0,100);
        std::cout << "First 100 iterates from x0 = " << x0.str() << std::endl;
        for (real x: entryOrbit){
            std::cout << "  " << x << std::endl;
        }
    
        
        //Initializes the analyzer, by borrowing the map (taking its memory reference)
        Analyzer analyzer(*map);  // borrows, does not own   
        
        //Use the identify function as the observable function
        auto f = [](real x) { return x;};
 
        //Define the number of map iterations N

        int N = 60;
        
        auto convergence = analyzer.birkhoffConvergence(x0, N, f);
        writeCSV(hash + "/birkhoff_convergence.csv", convergence);
        std::cout << "Birkhoff average (N=10000): " << convergence.back()<<std::endl;
 
    
        auto measure = analyzer.invariantMeasure(x0, N, 100);
        writeCSV(hash +"/invariant_measure.csv", measure);

        auto lyapConvergence = analyzer.lyapunovExponentConvergence(x0, N);
        writeCSV(hash + "/lyapunov_convergence.csv", lyapConvergence);

        // Perturb x0 by a few ULPs and track how fast the two orbits separate.
        // For the Doubling map this reproduces the floating-point error growth
        // described in the README: separation ~ 2^n * epsilon, saturating once
        // n ~ 52 (real's mantissa width) makes the perturbation O(1).
        real delta = std::numeric_limits<real>::epsilon();
        auto divergence = analyzer.trajectoryDivergence(x0,N, delta);
        writeCSV(hash + "/trajectory_divergence.csv", divergence);

        //printout the Lyapunov exponent for the doubling map
        std::cout << "Lyapunov exponent for "<< map->name() << ": " << analyzer.lyapunovExponent(0.2, N) << std::endl << std::endl;
    }
    return 0;
}