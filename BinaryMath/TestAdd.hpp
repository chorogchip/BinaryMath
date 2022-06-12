#pragma once
#include<iostream>
#include"Integer.hpp"

namespace tst {

using namespace std;
using namespace bm;

typedef Integer<32> myint;

static void testAdd_guguclass() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            myint a(i * 7);
            myint b(j * 13);
            printf("%d + %d = %d\n", i * 7, j * 13, (int)(a + b));
        }
    }
    cout << "\ncount plus : " << myint::get_count_plus() << endl;
}

static void testAdd_overflow() {
    int arr[] = { 2147483646, 2147483647, -2147483648, -2147483647};
    int brr[] = { -1, 0, 1 };
    for (int a : arr) {
        for (int b : brr) {
            myint ia(a);
            myint ib(b);
            printf("%d + %d = %d\n", a, b, (int)(ia + ib));
            printf("%d - %d = %d\n", a, b, (int)(ia - ib));
        }
    }
    cout << "\ncount plus : " << myint::get_count_plus() << endl;
}

}