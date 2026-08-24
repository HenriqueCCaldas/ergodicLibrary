#include "../include/classicMaps2D.h"
#include "../include/mapTemplate.h"

Map2D::point HenonMap::iterate(point x) const {
    return {real("1") - alpha_ * x[0] * x[0] + x[1], beta_ * x[0]};
}

Map2D::matrix HenonMap::jacobian(point x) const {
    return {{
        {real("-2") * alpha_ * x[0], real("1")},
        {beta_, real("0")}
    }};
}

Map2D::point RulkovMap::iterate(point x) const {
    return{
        (alpha_ / (real("1") + (x[0]*x[0]))) + x[1],
        x[1] - mu_ * (x[0] - sigma_)
    };
}

Map2D::matrix RulkovMap::jacobian(point x) const{
    real denom = real("1") + x[0]*x[0];
    return {{
        {(-real("2")*alpha_*(x[0]/(denom*denom))), real("1")},
        {-mu_, real("1")}
    }};
}

