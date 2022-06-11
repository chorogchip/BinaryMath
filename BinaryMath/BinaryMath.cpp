// BinaryMath.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "Integer.hpp"

using namespace std;
using namespace bm;

typedef Integer<32> myint;

int main()
{   
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            myint a(i * 7);
            myint b(j * 13);
            printf("%d + %d = %d\n", i*7, j*13, (a + b).getInt());
        }
    }
    int arr[] = { 2147483646, 2147483647, -2147483648, -2147483647};
    int brr[] = { -1, 0, 1 };
    
    for (int a : arr) {
        for (int b : brr) {
            myint ia(a);
            myint ib(b);
            printf("%d + %d = %d\n", a, b, (ia + ib).getInt());
            printf("%d - %d = %d\n", a, b, (ia - ib).getInt());
        }
    }

    cout << "\n count plus : " << myint::get_count_plus() << endl;
}
