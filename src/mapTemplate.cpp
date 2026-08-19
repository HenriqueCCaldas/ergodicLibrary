#include "../include/mapTemplate.h"

//specify again what dim is
template <size_t dim>
std::string Map<dim>::hashKey() const {
    
    std::string key = tag_;
    for (real p : params_) key += p.str(2, std::ios_base::fixed)+ "_";
    if(params_.size()!=0){return key.substr(0,key.size()-1);}
    else{return key;}
}

//use typename to guarantee to the compiler that is treats point as a type, not a value. this comes from the header
//Error seen: use the 'typename' keyword to treat nontype "Map<dim>::point [with dim=dim]" as a type in a dependent context
template <size_t dim>
std::vector<typename Map<dim>::point> Map<dim>::orbit(Map<dim>::point x0, int n) const{
    
    std::vector<point> orb;
    //alocate n places to the vector orb
    orb.reserve(n);
    //create current phase point x
    point x = x0;
    for (int i = 0; i< n; i++){
        orb.push_back(x);
        x = iterate(x);
    }
    return orb;
}
