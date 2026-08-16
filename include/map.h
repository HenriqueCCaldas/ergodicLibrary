#pragma once
#include <vector>
#include <string>
 
// base class for all discrete dynamical maps
// use polymorphism in classicMaps.h and .cpp to replace the virtual methods iterate (), derivative and name;
// using const methods to guarantee no member of the class is changed when called

class Map {
public:
    //Phase space bounds [xmin, xmax]
    virtual double xmin() const = 0;
    virtual double xmax() const = 0;

    //Methods, Constructors, etc

    virtual ~Map() = default;

    // Apply the map once: x -> T(x)
    virtual double iterate(double x) const = 0;

    // Derivative of the map at x: DT(x)
    // Used for Lyapunov exponent computation
    virtual double derivative(double x) const = 0;

    // Output Name for output/plots (NOT the hashKey)
    virtual std::string name() const = 0;

    // Identifier built from the map tag_ and parameters_ (e.g. logisticMap4.000000)
    // Not a virtual method as it is ALWAYS derived from tag_ and parameters_
    std::string hashKey() const;

    // Generate an orbit of length n starting from x0
    std::vector<double> orbit(double x0, int n) const;

protected:
    //To change any params in the derived class, use this constructor 
    //to have access to the params_ methods from the base class
    Map(std::string tag, std::vector<double> params): tag_(std::move(tag)), params_(std::move(params)) {}
    //The derived classes must have an alias parameter as a member for these parameters stores in the params vector
    std::vector<double>& params() {return params_;}
private:
    std::string tag_;
    std::vector<double> params_;
};