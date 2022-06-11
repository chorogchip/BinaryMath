// BinaryMath.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "Integer.h"

using namespace std;
using namespace bm;

int main()
{   
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            Integer a(i * 7);
            Integer b(j * 13);
            printf("%d + %d = %d\n", i*7, j*13, (a + b).getInt());
        }
    }
    
}
