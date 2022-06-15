#pragma once
#include"TestAdd.hpp"
#include"TestMult.hpp"
#include"TestComp.hpp"

int main() {
    
    /*
    tst::testAdd_guguclass();
    tst::testAdd_overflow();
    */
    /*
    tst::testcomp_equal();
    tst::testcomp_not_equal();
    tst::testcomp_bigger();
    tst::testcomp_smaller();
    tst::testcomp_not_smaller();
    tst::testcomp_not_bigger();
    */

    tst::testMult_guguclass();
    tst::testMult_overflow();


    printf("test completed\n");
    char c = getchar();
}
