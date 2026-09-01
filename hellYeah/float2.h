#pragma once
#include <cmath>
#include <string>

using namespace std;

class float2 {
public:
    float x;
    float y;

    float2(const float x_ = 0.0, const float y_ = 0.0) {
        x = x_;
        y = y_;
    }

    float2 operator+(const float2& v) const {
        return float2(x + v.x, y + v.y);
    }

    float2 operator-(const float2& v) const {
        return float2(x - v.x, y - v.y);
    }

    float2 operator*(const float s) const {
        return float2(x * s, y * s);
    }

    float2 operator/(const float s) const {
        return float2(x / s, y / s);
    }

    float2 operator-() const {
        return float2(x * -1, y * -1);
    }

    float2 operator+=(const float2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    float cross(const float2& v) const {
        return x * v.y - y * v.x;
    }

    float getLength() const {
        return sqrt(x * x + y * y);
    }

    float2 getNormalized() const {
        float length = getLength();
        return float2(x/length, y/length);
    }

    float2 getNormalized(float length) const {
        return float2(x / length, y / length);
    }

    float2 normalize() {
        float length = getLength();
        x /= length;
        y /= length;
        return *this;
    }

    string getString() const {
        return "(" + to_string(this->x) + ", " + to_string(this->y) + ")";
    }

    //friend std::ostream& operator<<(std::ostream& os, float2* v);
};

//std::ostream& operator<<(std::ostream& os, float2* v) {
//    os << "(" << v->x << ", " << v->y << ")";
//    return os;
//};