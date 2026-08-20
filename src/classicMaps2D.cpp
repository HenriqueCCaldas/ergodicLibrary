#include "../include/classicMaps2D.h"

HenonMap::point HenonMap::iterate(point x) const {
    return {real("1") - alpha_ * x[0] * x[0] + x[1], beta_ * x[0]};
}

HenonMap::matrix HenonMap::jacobian(point x) const {
    return {{
        {real("-2") * alpha_ * x[0], real("1")},
        {beta_, real("0")}
    }};
}

