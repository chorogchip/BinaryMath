#pragma once
#include<iostream>
#include"Integer.hpp"

namespace tst {

using namespace std;
using namespace bm;

typedef Integer<32> myint;

static void testcomp_equal() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a == b) != (i == j))
                printf("error equal : %d %d\n", i, j);
        }
}
static void testcomp_not_equal() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a != b) != (i != j))
                printf("error not equal : %d %d\n", i, j);
        }
}
static void testcomp_bigger() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a < b) != (i < j))
                printf("error bigger : %d %d\n", i, j);
        }
}
static void testcomp_smaller() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a > b) != (i > j))
                printf("error smaller : %d %d\n", i, j);
        }
}
static void testcomp_not_smaller() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a <= b) != (i <= j))
                printf("error not smaller : %d %d\n", i, j);
        }
}
static void testcomp_not_bigger() {
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a >= b) != (i >= j))
                printf("error not bigger : %d %d\n", i, j);
        }
}
}