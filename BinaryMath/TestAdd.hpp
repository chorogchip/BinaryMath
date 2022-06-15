#pragma once
#include<iostream>
#include"Logger.hpp"
#include"Integer.hpp"

namespace tst {

using namespace std;
using namespace bm;

typedef Integer<32> myint;

static void testAdd_guguclass() {
    Logger::start_test("add gugu");
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            myint a(i * 7);
            myint b(j * 13);
            if ((int)(a + b) != (i * 7 + j * 13)) Logger::error(i * 7, j * 13);
        }
    }
    Logger::end_test();
}

static void testAdd_overflow() {
    Logger::start_test("add overflow");
    int arr[] = { 2147483646, 2147483647, -2147483648, -2147483647};
    int brr[] = { -1, 0, 1 };
    for (int a : arr) {
        for (int b : brr) {
            myint ia(a);
            myint ib(b);
            printf("%d + %d = %d\n", a, b, (int)(ia + ib));
            printf("%d - %d = %d\n", a, b, (int)(ia - ib));
            if ((int)(ia + ib) != (a + b)) Logger::error(a, b);
            if ((int)(ia - ib) != (a - b)) Logger::error(a, b);
        }
    }
    Logger::end_test();
}

}