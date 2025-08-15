//#include "differentiator/AAD22.hpp"
#include "Differentiator.hpp"

#include <cmath>
#include <iostream>


AAD22 func_add(AAD22 x, AAD22 y) {
    return  2*x*y + cos(x+y) / exp(x-y) * sin(x*y);
}

double func_double(double x, double y) {
    return 2*x*y + cos(x+y) /  exp(x-y) * sin(x*y);
}

double get_differ(double x, double y) {
    return 0;
}


int main() {

    double x = 20.2926;
    double y = 0.91747;
    std::cout<<"dF/dx \n";
    
    std::cout << "Stencil3: " << Differentiator<WhichD::x, DiffMethod::Stencil3>(&func_double, x, y) << '\n';
    std::cout << "Stencil3Extra: " <<  Differentiator<WhichD::x, DiffMethod::Stencil3Extra>(&func_double, x, y) << '\n';
    std::cout << "Stencil5: " <<  Differentiator<WhichD::x, DiffMethod::Stencil5>(&func_double, x, y) << '\n';
    std::cout << "Stencil5Extra: " << Differentiator<WhichD::x, DiffMethod::Stencil5Extra>(&func_double, x, y) << '\n';
    std::cout << "FwdAAD: " <<  Differentiator<WhichD::x, DiffMethod::FwdAAD>(&func_add, x, y) << '\n';
    std::cout << '\n';

    std::cout<<"dF/dy \n";
    std::cout << "Stencil3: " << Differentiator<WhichD::y, DiffMethod::Stencil3>(&func_double, x, y) << '\n';
    std::cout << "Stencil3Extra: " <<  Differentiator<WhichD::y, DiffMethod::Stencil3Extra>(&func_double, x, y) << '\n';
    std::cout << "Stencil5: " <<  Differentiator<WhichD::y, DiffMethod::Stencil5>(&func_double, x, y) << '\n';
    std::cout << "Stencil5Extra: " << Differentiator<WhichD::y, DiffMethod::Stencil5Extra>(&func_double, x, y) << '\n';
    std::cout << "FwdAAD: " <<  Differentiator<WhichD::y, DiffMethod::FwdAAD>(&func_add, x, y) << '\n';
    std::cout << '\n';

    std::cout<<"dF/dxdx \n";
    std::cout << "Stencil3: " << Differentiator<WhichD::xx, DiffMethod::Stencil3>(&func_double, x, y) << '\n';
    std::cout << "Stencil3Extra: " <<  Differentiator<WhichD::xx, DiffMethod::Stencil3Extra>(&func_double, x, y) << '\n';
    std::cout << "Stencil5: " <<  Differentiator<WhichD::xx, DiffMethod::Stencil5>(&func_double, x, y) << '\n';
    std::cout << "Stencil5Extra: " << Differentiator<WhichD::xx, DiffMethod::Stencil5Extra>(&func_double, x, y) << '\n';
    std::cout << "FwdAAD: " <<  Differentiator<WhichD::xx, DiffMethod::FwdAAD>(&func_add, x, y) << '\n';
    std::cout << '\n';

    std::cout<<"dF/dydy \n";
    std::cout << "Stencil3: " << Differentiator<WhichD::yy, DiffMethod::Stencil3>(&func_double, x, y) << '\n';
    std::cout << "Stencil3Extra: " <<  Differentiator<WhichD::yy, DiffMethod::Stencil3Extra>(&func_double, x, y) << '\n';
    std::cout << "Stencil5: " <<  Differentiator<WhichD::yy, DiffMethod::Stencil5>(&func_double, x, y) << '\n';
    std::cout << "Stencil5Extra: " << Differentiator<WhichD::yy, DiffMethod::Stencil5Extra>(&func_double, x, y) << '\n';
    std::cout << "FwdAAD: " <<  Differentiator<WhichD::yy, DiffMethod::FwdAAD>(&func_add, x, y) << '\n';
    std::cout << '\n';
    

    std::cout<<"dF/dxdy \n";
    std::cout << "Stencil3: " << Differentiator<WhichD::xy, DiffMethod::Stencil3>(&func_double, x, y) << '\n';
    std::cout << "Stencil3Extra: " <<  Differentiator<WhichD::xy, DiffMethod::Stencil3Extra>(&func_double, x, y) << '\n';
    std::cout << "Stencil5: " <<  Differentiator<WhichD::xy, DiffMethod::Stencil5>(&func_double, x, y) << '\n';
    std::cout << "Stencil5Extra: " << Differentiator<WhichD::xy, DiffMethod::Stencil5Extra>(&func_double, x, y) << '\n';
    std::cout << "FwdAAD: " <<  Differentiator<WhichD::xy, DiffMethod::FwdAAD>(&func_add, x, y) << '\n';
    std::cout << '\n';
    
    std::cout << '\n';
}