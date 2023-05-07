#include "doctest.h"

#include <stdexcept>
#include "sources/Fraction.hpp"
#include <unistd.h>


TEST_CASE("+ operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) + Fraction(a2, b2), Fraction(a1 * b2 + a2 * b1, b1 * b2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);
        Fraction ans(7, 3);
        CHECK_EQ(a + b, ans);
        CHECK_EQ(a + b, b + a);

    }
    SUBCASE("Testing fraction and float") {
        Fraction a(5, 3), b(14, 21);
        float f = 2.421;
        Fraction ans(12263, 3000);
        Fraction ans2(9263, 3000);
        CHECK_EQ(a + f, ans);
        CHECK_EQ(b + f, ans2);

    }
    SUBCASE("Testing with zero") {
        Fraction a(5, 3);
        CHECK_EQ(a + 0, a);
        CHECK_EQ(0 + a, a);
        CHECK_EQ(a + Fraction(0, 1), a);

    }

}

TEST_CASE("- operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;
            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) - Fraction(a2, b2), Fraction(a1 * b2 - a2 * b1, b1 * b2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);

        Fraction ans(1, 1);
        Fraction ans2(-1, 1);

        CHECK_EQ(a - b, ans);
        CHECK_EQ(b - a, ans2);

    }
    SUBCASE("Testing fraction and float") {
        Fraction a(5, 3), b(14, 21);
        float f = 2.5;

        Fraction ans(-5, 6);
        Fraction ans2(-11, 6);

        CHECK_EQ(a - f, ans);
        CHECK_EQ(b - f, ans2);

    }
    SUBCASE("Testing with zero") {
        Fraction a(5, 3);
        CHECK_EQ(a - 0, a);
        CHECK_EQ(a - Fraction(), a);
    }
}

TEST_CASE("* operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) * Fraction(a2, b2), Fraction(a1 * a2, b1 * b2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);

        Fraction ans(10, 9);

        CHECK_EQ(a * b, ans);
        CHECK_EQ(a * b, b * a);
    }
    SUBCASE("Testing fraction and float") {
        Fraction a(5, 3), b(14, 21);
        float f = 2.5;

        Fraction ans(25, 6);
        Fraction ans2(5, 3);

        CHECK_EQ(a * f, ans);
        CHECK_EQ(f * b, ans2);
    }
    SUBCASE("Testing with zero") {
        Fraction a(5, 3), b(14, 21);
        CHECK_EQ(a * Fraction(), Fraction());
        CHECK_EQ(Fraction() * b, Fraction());
    }
}

TEST_CASE("/ operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0, or divide with 0
            if (b1 == 0 || b2 == 0 || a2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) / Fraction(a2, b2), Fraction(a1 * b2, b1 * a2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);

        Fraction ans(5, 2);
        Fraction ans2(2, 5);

        CHECK_EQ(a / b, ans);
        CHECK_EQ(b / a, ans2);
    }
    SUBCASE("Testing fraction and float") {
        Fraction a(5, 3), b(14, 21);
        float f = 2.5;

        Fraction ans(3, 2);
        Fraction ans2(4, 15);

        CHECK_EQ(f / a, ans);
        CHECK_EQ(b / f, ans2);
    }
    SUBCASE("Cant divide by zero") {
        SUBCASE("Testing make fraction witch is zero") {
            CHECK_NOTHROW(Fraction(0, 123));
            CHECK_THROWS(Fraction(0, 0));
            CHECK_THROWS(Fraction(123, 0));
        }
        SUBCASE("Testing divide by zero as fraction") {
            Fraction f1(12, 13);
            Fraction f2(0, 12);
            Fraction f3(0, 13);
            CHECK_THROWS(f1 / f2);
            CHECK_THROWS(f2 / f3);
        }
        SUBCASE("Testing divide by zero as float") {
            Fraction f1(12, 13);
            Fraction f2(0, 12);
            CHECK_THROWS(f1 / 0);
            CHECK_THROWS(f2 / 0);
        }
    }
}

TEST_CASE("== operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) == Fraction(a2, b2), (1.0 * a1 / b1) == (1.0 * a2 / b2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);
        Fraction c(93, 6), d(31, 2);
        Fraction e(4, 3), f(4, 3);

        CHECK_FALSE(a == b);
        CHECK(c == d);
        CHECK(e == f);
        CHECK(Fraction(-4, 2) == Fraction(8, -4));
        CHECK_FALSE(Fraction(2, 2) == Fraction(2, -2));

    }
    SUBCASE("Testing fraction and float") {
        CHECK_FALSE(Fraction(5, 2) == -2.5);
        CHECK(2.5 == Fraction(5, 2));
        CHECK(15.5 == Fraction(93, 6));
    }
}

TEST_CASE(">= operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) >= Fraction(a2, b2), (1.0 * a1 / b1) >= (1.0 * a2 / b2));
        }
    }
    SUBCASE("Testing two fraction") {
        Fraction a(5, 3), b(14, 21);
        Fraction c(93, 6), d(31, 2);
        Fraction e(4, 3), f(4, 3);

        CHECK(a >= b);
        CHECK(c >= d);
        CHECK(e >= f);
        CHECK(Fraction(-4, 2) >= Fraction(8, -4));
        CHECK(Fraction(2, 2) >= Fraction(2, -2));
        CHECK_FALSE(Fraction(-4, 2) >= Fraction(2, -2));

    }
    SUBCASE("Testing fraction and float") {
        CHECK_FALSE(Fraction(5, 2) == -2.5);
        CHECK(2.501 >= Fraction(5, 2));
        CHECK_FALSE(-15.5 >= Fraction(93, 6));
    }
}


TEST_CASE("<= operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) <= Fraction(a2, b2), (1.0 * a1 / b1) <= (1.0 * a2 / b2));
        }
    }
    SUBCASE("Testing two fraction") {
        CHECK(Fraction(5, 2) <= Fraction(6, 2));
        CHECK(Fraction(5, 2) <= Fraction(5, 2));
        CHECK(Fraction(5, -2) <= Fraction(-2, -5));
        CHECK(Fraction(-10, 2) <= Fraction(5, 2));
        CHECK(Fraction(-2, -2) <= Fraction(-5, -2));
        CHECK(Fraction(-2, -2) <= Fraction(5, 2));
    }
    SUBCASE("Testing fraction and float") {
        CHECK(Fraction(-10, 2) <= 2.5);
        CHECK(Fraction(-2, -2) <= 2.5);
        CHECK(Fraction(2, -2) <= 0.5);
        CHECK(Fraction(-2, 2) <= 0.5);
        CHECK_FALSE(Fraction(-2, -2) <= 0.5);
    }
}


TEST_CASE("< operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) < Fraction(a2, b2), (1.0 * a1 / b1) < (1.0 * a2 / b2));
        }
    }
    SUBCASE("Testing two fraction") {
        CHECK(Fraction(10000, 10001) < Fraction(1, 1));
        CHECK(Fraction(-10001, 10001) < Fraction(1, 1));
        CHECK_FALSE(Fraction(10001, 10001) < Fraction(1, 1));
        CHECK(Fraction(-5, 2) < Fraction(-2, 5));
        CHECK(Fraction(5, -2) < Fraction(-2, -5));
        CHECK(Fraction(5, -2) < Fraction(-2, 5));

    }
    SUBCASE("Testing fraction and float") {
        CHECK(0.999 < Fraction(1, 1));
        CHECK(0.999 < Fraction(2, 2));
        CHECK(-0.001 < Fraction(0, 2));
        CHECK(Fraction(5, 2) < 2.501);
        CHECK_FALSE(Fraction(5, 2) < 2.500);
        CHECK_FALSE(Fraction(6, 2) < 2.999);
    }
}


TEST_CASE("> operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            int a2 = (rand() % (999 - (-999) + 1)) + -999;
            int b2 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0 || b2 == 0) continue;
            CHECK_EQ(Fraction(a1, b1) > Fraction(a2, b2), (1.0 * a1 / b1) > (1.0 * a2 / b2));
        }
    }
    SUBCASE("Testing two fraction") {
        CHECK_FALSE(Fraction(10000, 10001) > Fraction(1, 1));
        CHECK_FALSE(Fraction(-10001, 10001) > Fraction(1, 1));
        CHECK_FALSE(Fraction(10001, 10001) > Fraction(1, 1));
        CHECK_FALSE(Fraction(-5, 2) > Fraction(-2, 5));
        CHECK_FALSE(Fraction(5, -2) > Fraction(-2, -5));
        CHECK_FALSE(Fraction(5, -2) > Fraction(-2, 5));

    }
    SUBCASE("Testing fraction and float") {
        CHECK_FALSE(0.999 > Fraction(1, 1));
        CHECK_FALSE(0.999 > Fraction(2, 2));
        CHECK_FALSE(-0.001 > Fraction(0, 2));
        CHECK_FALSE(Fraction(5, 2) > 2.501);
        CHECK_FALSE(Fraction(5, 2) > 2.500);
        CHECK(Fraction(6, 2) > 2.999);
    }
}


TEST_CASE("++ operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0) continue;
            CHECK_EQ(++Fraction(a1, b1), Fraction(a1 + b1, b1));
        }
    }
    SUBCASE("Testing prefix") {
        Fraction a(12, 41);
        Fraction ans(12, 41);
        Fraction ans2(12 + (41 * 2), 41);
        CHECK_NE(ans, ++a);
        CHECK_EQ(ans2, ++a);
    }
    SUBCASE("Testing postfix") {
        Fraction a(12, 41);
        Fraction ans(12, 41);
        Fraction ans2(12 + (41 * 2), 41);
        CHECK_EQ(ans, a++);
        CHECK_NE(ans2, a++);

    }
}

TEST_CASE("-- operator") {
    SUBCASE("Testing with loop") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < 10000; ++i) {
            int a1 = (rand() % (999 - (-999) + 1)) + -999;
            int b1 = (rand() % (999 - (-999) + 1)) + -999;

            //so won't make fraction that divide 0
            if (b1 == 0) continue;
            CHECK_EQ(--Fraction(a1, b1), Fraction(a1 - b1, b1));
        }
    }
    SUBCASE("Testing prefix") {
        Fraction a(12, 41);
        Fraction ans(12, 41);
        Fraction ans2(12 - (41 * 2), 41);
        CHECK_NE(ans, --a);
        CHECK_EQ(ans2, --a);
    }
    SUBCASE("Testing postfix") {
        Fraction a(12, 41);
        Fraction ans(12, 41);
        Fraction ans2(12 - (41 * 2), 41);
        CHECK_EQ(ans, a--);
        CHECK_NE(ans2, a--);

    }
}
TEST_CASE("test precision") {
    CHECK_FALSE(Fraction(5, 2) > 2.501);
    CHECK(Fraction(5, 2) < 2.501);
    CHECK_FALSE(Fraction(5, 2) == 2.501);

    CHECK_FALSE(Fraction(5, 2) > 2.5001);
    CHECK_FALSE(Fraction(5, 2) < 2.5001);
    CHECK(Fraction(5, 2) == 2.5001);

    CHECK(Fraction(5, 2) > 2.4999);
    CHECK_FALSE(Fraction(5, 2) < 2.4999);
    CHECK_FALSE(Fraction(5, 2) == 2.4999);

}

TEST_CASE("input/output operator") {
    SUBCASE("Testing output") {
        Fraction a(0, 1);
        cout << "Test of output:" << endl << a << endl << (a + 2.12314 + a * 1.21 - 2) << endl << a / (a + 1.312)
             << endl;

    }
    // block the testing
    SUBCASE("Testing input") {
//        Fraction a(0, 1);
//        cout << "please enter two integer" << endl;
//        cin >>  a;
//        cout << a << endl;


    }
}
