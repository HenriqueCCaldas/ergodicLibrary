#pragma once

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <vector>
#include <array>
#include <string>


//Extremely important. Real numbers should be used as real("0.2") and not real r = 0.2. Otherwise we have the same issue as with a double

using real = boost::multiprecision::cpp_bin_float_100;

// base class for all discrete dynamical maps
// use polymorphism in classicMaps.h and .cpp to replace the virtual methods iterate (), derivative and name;
// using const methods to guarantee no member of the class is changed when called

template <size_t dim> class Map{

    public:
    
        using point = std::array<real, dim>;
        using matrix = std::array<std::array<real, dim>, dim>;

        //Phase space bounds [xmin, xmax]
        virtual point xmin() const = 0;
        virtual point xmax() const = 0;

        //Methods, Constructors, etc
        virtual ~Map() = default;

        // Apply the map once: x -> T(x)
        virtual point iterate(point x) const = 0;

        // Jacobian of the map T at x: DT(x)
        virtual matrix jacobian(real x) const = 0;

        // Output Name for output/plots (NOT the hashKey)
        virtual std::string name() const = 0;

        // Identifier built from the map tag_ and parameters_ (e.g. logisticMap4.000000)
        // Not a virtual method as it is ALWAYS derived from tag_ and parameters_
        std::string hashKey() const;

        // Generate an orbit of length n starting from x0
        std::vector<point> orbit(point x0, int n) const;

    protected:
    
        //To change any params in the derived class, use this constructor
        //to have access to the params_ methods from the base class
        Map(std::string tag, std::vector<real> params): tag_(std::move(tag)), params_(std::move(params)) {}
        //The derived classes must have an alias parameter as a member for these parameters stores in the params vector
        std::vector<real>& params() {return params_;}

    private:
        std::string tag_;
        std::vector<real> params_;
};

// Define alias for the 2 first map dimensions

using Map1D = Map<1>;
using Map2D = Map<2>;