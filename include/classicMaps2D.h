#pragma once

#include "mapTemplate.h"

// Henon map: T(x, y) = (1 - a*x^2 + y, b*x), classic chaotic parameters a = 1.4, b = 0.3
class HenonMap : public Map2D{
    
    real& alpha_;
    real& beta_;

public:
    explicit HenonMap (real alpha, real beta): 
        Map2D("henonMap",{alpha,  beta}),
        alpha_(params()[0]),
        beta_(params()[1]) {};

    //Relevant phase space
    point xmin() const override {return {real("-2"), real("-0.5")};}
    point xmax() const override {return {real("2"), real("0.5")};}

    //Update iterate and jacobian to reflet the corret implementations for the HenonMap
    point iterate(point x) const override;

    matrix jacobian (point x) const override;

    std::string name() const override{
        return ("Henon Map at (" + alpha_.str() + "," + beta_.str() + ')');
    }
};