#include <iomanip>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
//print lp
template<typename T>
std::ostream& operator<<(std::ostream &os, const CGAL::Quadratic_program<T> &lp) {
    os << "minimize:\n";
    bool before = false;
    for(int j=0; j<lp.get_n(); j++) {
        T val = *(lp.get_c()+j);
        if(val != 0) {
            if(before)
                os << " + ";
            os << val << " * x" << j;
            before = true;
        }
    }
    if(lp.get_c0() != 0) {
        os << " + " << lp.get_c0();
    }
    os << std::endl << "where\n";
    for(int i=0; i<lp.get_m(); i++) {
        for(int j=0; j<lp.get_n(); j++) {
            os << std::setw(4) << *(*(lp.get_a()+j)+i);
        }
        os << std::setw(4) << "|";
        auto rel = *(lp.get_r()+i);
        os << std::setw(4) << ((rel == CGAL::SMALLER) ? "<=" : ((rel == CGAL::LARGER) ? ">=" : "==")) << " ";
        os << *(lp.get_b()+i);
        os << std::endl;
    }
    return os;
}
