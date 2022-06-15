#pragma once
#include<iostream>
#include"Logger.hpp"
#include"Integer.hpp"

namespace tst {

using namespace std;
using namespace bm;

typedef Integer<32> myint;

static void testMult_guguclass() {
    Logger::start_test("multiply gugu");
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            myint a(i);
            myint b(j);
           if ((int)(a * b) != (i * j)) Logger::error(i, j);
        }
    }
    Logger::end_test();
}

static void testMult_overflow() {
    Logger::start_test("multiply overflow");
    int arr[] = { 2147483646, 2147483647, -2147483648, -2147483647};
    int brr[] = { -1, 0, 1 };
    for (int a : arr) {
        for (int b : brr) {
            myint ia(a);
            myint ib(b);
            if ((int)(ia * ib) != (a * b)) Logger::error(a, b);
        }
    }
    Logger::end_test();
}

};