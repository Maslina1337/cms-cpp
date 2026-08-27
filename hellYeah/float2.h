#pragma once
#include <cmath>

class float2 {
public:
    float x;
    float y;
    float length;

    float2(const float x_ = 0.0, const float y_ = 0.0) {
        x = x_;
        y = y_;
        length = 0.0f;
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

    float calculateLength() {
        length = sqrt(x * x + y * y);
        return length;
    }

    float2 getNormalized() {
        length = sqrt(x * x + y * y);
        return float2(x/length, y/length);
    }

    float2 getNormalized(float length) {
        return float2(x / length, y / length);
    }
};