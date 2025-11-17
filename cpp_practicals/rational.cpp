#include <numeric>
#include <iostream>
#include <cstdint>
// Maybe use safe int

bool is_overflow_add(int a, int b) {
    if (b > 0) {
        return a > std::numeric_limits<int32_t>::max() - b;
    } else {
        return a < std::numeric_limits<int32_t>::min() - b;
    }
}

int safe_add(int a, int b) {
    if (is_overflow_add(a, b)) {
        throw std::overflow_error("Overflow in addition");
    }
    return a + b;
}

class Rational {
public:
    Rational();
    Rational(int, int);
    int num() const;
    int denom() const;
    float value() const;
    Rational operator+(Rational);
    Rational& operator+=(Rational);
    Rational operator*(int);
    Rational& operator*=(int);
    Rational operator/(int);
    Rational& operator/=(int);

    friend std::istream& operator>>(std::istream& in, Rational& r);
private:
    int m_num = 0;
    int m_denom = 1;
    float m_val = 0;
    void self_cancelling();
};
Rational::Rational() {}
Rational::Rational(int num, int denom) {
    m_num = num;
    m_denom = denom;
    self_cancelling();
}
int Rational::num() const {
    return m_num;
}
int Rational::denom() const {
    return m_denom;
}
float Rational::value() const {
    return m_val;
}
void Rational::self_cancelling() {
    int gcd = std::gcd(m_num, m_denom);
    m_num /= gcd;
    m_denom /= gcd;
    m_val = (float)m_num / (float)m_denom;
}
Rational Rational::operator+(Rational b) {
    Rational res = *this;
    res += b;
    return res;
}
Rational& Rational::operator+=(Rational b) {
    int new_num = m_num*b.denom() + b.num()*m_denom;
    int new_denom = m_denom * b.denom();
    m_num = new_num;
    m_denom = new_denom;
    self_cancelling();
    return *this;
}
Rational Rational::operator*(int b) {
    Rational res = *this;
    return res *= b;
}
Rational& Rational::operator*=(int b) {
    m_num = m_num*b;
    self_cancelling();
    return *this;
}
Rational Rational::operator/(int b) {
    Rational res = *this;
    return res/=b;
}
Rational& Rational::operator/=(int b) {
    m_denom = m_denom*b;
    self_cancelling();
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.num() << "/" << r.denom() << "(" << r.value() << ")";
    return os;
}

std::istream& operator>>(std::istream& in, Rational& r) {
    int num, denom;
    char sep;
    in >> num >> sep >> denom;
    if (in && sep == '/') {
        r.m_num = num;
        r.m_denom = denom;
        r.self_cancelling();
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

int main(void) {
    Rational a(10,3);
    std::cout << "a = " << a.num() << "/" << a.denom() << " = " << a.value() << std::endl;
    std::cout << "Default output: " << a << std::endl;
    a /= 5;
    Rational b(3,4);
    a += b*3;
    std::cout << "a = " << a.num() << "/" << a.denom() << " = " << a.value() << std::endl;
    std::cout << "Default output: " << a << std::endl;
    
    
    Rational c;
    std::cout << "Input c: ";
    std::cin >> c;
    std::cout << "Default output for c: " << c << std::endl;
    return 1;
}