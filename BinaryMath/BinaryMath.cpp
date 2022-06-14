// BinaryMath.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include"TestAdd.hpp"
#include"TestMult.hpp"
#include"TestComp.hpp"

int main()
{   /*
    tst::testMult_guguclass();
    putchar('\n');
    tst::testMult_overflow();
    */

    tst::testcomp_equal();
    tst::testcomp_not_equal();
    tst::testcomp_bigger();
    tst::testcomp_smaller();
    tst::testcomp_not_smaller();
    tst::testcomp_not_bigger();
    getchar();
}
