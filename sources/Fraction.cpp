
#include "Fraction.hpp"

int INT_MAX = std::numeric_limits<int>::max();
int INT_MIN = std::numeric_limits<int>::min();

//-------------help---------------
int GCD(int a, int b) {
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

void reduce(Fraction &frc) {
    if (frc.a == 0) {
        frc.b = 1; //just to organize
        return;
    }
    if ((frc.a < 0 && frc.b < 0) || (frc.a > 0 && frc.b < 0)) {
        frc.a *= -1;
        frc.b *= -1;
    }
    int gcd = GCD(::abs(frc.a), abs(frc.b));
    frc.a /= gcd;
    frc.b /= gcd;
}

bool check_mul_overflow(int lhs, int rhs) {
    if (rhs > 0) {
        if (lhs > INT_MAX / rhs || lhs < INT_MIN / rhs) {
            return true;
        }
    } else if (rhs < 0) {
        if (rhs == -1) {
            return lhs == INT_MIN;
        }

        if (lhs < INT_MAX / rhs || lhs > INT_MIN / rhs) {
            return true;
        }
    }

    return false;
}

bool check_add_overflow(int lhs, int rhs) {
    //lhs+rhs > inf  -> lhs > inf - rhs
    if (lhs >= 0 && rhs >= 0 && (lhs > INT_MAX - rhs)) {
        return true;
        //lhs+rhs < -inf  -> lhs < -inf - rhs
    } else if (lhs < 0 && rhs < 0 && (lhs < INT_MIN - rhs)) {
        return true;
    }
    return false;
}

//-------------constructor---------------
Fraction::Fraction() : a(0), b(1) {}

Fraction::Fraction(int a, int b) : a(a), b(b) {
    if (b == 0)
        throw invalid_argument("cant divide by zero, constructor");
    reduce(*this);

}

Fraction::Fraction(float f) : a(1), b(1) {
    a *= std::floor(f * 1000);
    b *= 1000;
    reduce(*this);
}

int Fraction::getNumerator() { return a; }

int Fraction::getDenominator() { return b; }



//-------------arithmetic---------------


Fraction operator+(const Fraction &frc1, const Fraction &frc2) {
    if (frc1.a == 0)return frc2;
    if (frc2.a == 0)return frc1;

    int gcd = GCD(abs(frc1.b), abs(frc2.b));


    //use gcd to add
    int lhs = frc1.a * (frc2.b / gcd);
    int rhs = frc2.a * (frc1.b / gcd);

    if (check_mul_overflow(frc1.a, (frc2.b / gcd)) ||
        check_mul_overflow(frc2.a, (frc1.b / gcd))) {
        throw overflow_error("");

    }
    if (check_add_overflow(lhs, rhs)) {
        throw overflow_error("");
    }
    int a = frc1.a * (frc2.b / gcd) + frc2.a * (frc1.b / gcd);
    int b = frc1.b * frc2.b / gcd;

    Fraction temp(a, b);
    reduce(temp);
    return temp;
}

Fraction operator-(const Fraction &frc1, const Fraction &frc2) {
    Fraction cpy(frc2);
    //because min int> max int
    if(cpy.a == INT_MIN) cpy.a = INT_MAX;
    else cpy.a *= -1;
    return frc1 + cpy;
}

Fraction operator*(const Fraction &frc1, const Fraction &frc2) {
    if (frc1.a == 0 || frc2.a == 0) return Fraction();
    if (check_mul_overflow(frc1.a, frc2.a) || check_mul_overflow(frc1.b, frc2.b)) {
        throw overflow_error("");
    }
    Fraction temp(frc1.a * frc2.a, frc1.b * frc2.b);
    reduce(temp);
    return temp;
}

Fraction operator/(const Fraction &frc1, const Fraction &frc2) {
    if (frc2.a == 0 && frc1.a != 0)
        throw runtime_error("cant divide by zero");
    Fraction cpy(frc2);
    int tmp = cpy.a;
    cpy.a = cpy.b;
    cpy.b = tmp;
    return frc1 * cpy;
}

//-------------prefix---------------
Fraction Fraction::operator--() {
    if (check_add_overflow(this->a, -this->b)) {
        throw overflow_error("");
    }
    this->a -= this->b;
    return *this;
}

Fraction Fraction::operator++() {
    if (check_add_overflow(this->a, this->b)) {
        throw overflow_error("");
    }
    this->a += this->b;
    return *this;
}

//-------------postfix---------------

const Fraction Fraction::operator--(int) {
    if (check_add_overflow(this->a, -this->b)) {
        throw overflow_error("");
    }
    Fraction cpy(*this);
    this->a -= this->b;
    return cpy;
}

const Fraction Fraction::operator++(int) {
    if (check_add_overflow(this->a, this->b)) {
        throw overflow_error("");
    }
    Fraction cpy(*this);
    this->a += this->b;
    return cpy;
}



//-------------comparison---------------


bool operator==(const Fraction &frc1, const Fraction &frc2) {
    Fraction cpy1(frc1);
    Fraction cpy2(frc2);
    reduce(cpy1);
    reduce(cpy2);

    return cpy1.a == cpy2.a && cpy1.b == cpy2.b;
}

bool operator!=(const Fraction &frc1, const Fraction &frc2) {
    return !(frc1 == frc2);
}

bool operator<(const Fraction &frc1, const Fraction &frc2) {
    return (1.0 * frc1.a / frc1.b) < (1.0 * frc2.a / frc2.b);
}

bool operator>(const Fraction &frc1, const Fraction &frc2) {
    return (1.0 * frc1.a / frc1.b) > (1.0 * frc2.a / frc2.b);
}

bool operator<=(const Fraction &frc1, const Fraction &frc2) {
    return !(frc1 > frc2);
}

bool operator>=(const Fraction &frc1, const Fraction &frc2) {
    return !(frc1 < frc2);
}

//-------------input,output---------------
ostream &operator<<(ostream &output, const Fraction &frc) {
    output << frc.a << "/" << frc.b;

    return output;
}

istream &operator>>(istream &input, Fraction &frc) {
    int a, b;
    input >> a >> b;
    if (input.fail() || b == 0) {
        throw runtime_error("");
    }
    frc.a = a;
    frc.b = b;
    reduce(frc);
    return input;
}


