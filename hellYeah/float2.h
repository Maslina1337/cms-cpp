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

    bool operator==(const float2& v) {
        return (x == v.x) and (y == v.y);
    }

    bool operator!=(const float2& v) {
        return (x != v.x) and (y != v.y);
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

    static float2 getIntersectionPoint(float2 from1, float2 to1, float2 from2, float2 to2) {
        float2 d1 = to1 - from1;
        float2 d2 = to2 - from2;

        float2 intersection;

        if (d1.x > d1.y) {
            // Using tan for d1.
            float t1 = d1.y / d1.x;

            if (d2.x > d2.y) {
                // Using tan for d2. (Using tan for d1.)
                float t2 = d2.y / d2.x;

                //cout << "J1" << endl << from1.getString() << endl << to1.getString() << endl << from2.getString() << endl << to2.getString() << endl << endl;

                intersection.x = (t2 * from2.x - from2.y - t1 * from1.x + from1.y) / (t2 - t1);
                intersection.y = t1 * (intersection.x - from1.x) + from1.y;
            }
            else {
                // Using ctan for d2. (Using tan for d1.)
                float c2 = d2.x / d2.y;

                //cout << "J2" << endl << from1.getString() << endl << to1.getString() << endl << from2.getString() << endl << to2.getString() << endl << endl;

                intersection.x = (c2 * (t1 * from1.x - from1.y + from2.y) - from2.x) / (c2 * t1 - 1);
                intersection.y = t1 * (intersection.x - from1.x) + from1.y;
            }
        }
        else {
            // Using ctan for d1.
            float c1 = d1.x / d1.y;
            
            if (d2.x > d2.y) {
                // Using tan for d2. (Using ctan for d1)
                float t2 = d2.y / d2.x;

                //cout << "J3" << endl << from1.getString() << endl << to1.getString() << endl << from2.getString() << endl << to2.getString() << endl << endl;

                intersection.x = (c1 * (t2 * from2.x - from2.y + from1.y) - from1.x) / (c1 * t2 - 1);
                intersection.y = t2 * (intersection.x - from2.x) + from2.y;
            }
            else {
                // Using ctan for d2. (Using ctan for d1)
                float c2 = d2.x / d2.y;

                //cout << "J4" << endl << from1.getString() << endl << to1.getString() << endl << from2.getString() << endl << to2.getString() << endl << endl;

                intersection.y = (c2 * from2.y - from2.x - c1 * from1.y + from1.x) / (c2 - c1);
                intersection.x = c1 * (intersection.y - from1.y) + from1.x;
            }
        }

        //cout << intersection.getString() << endl << endl;

        return intersection;
    }
        

    //friend std::ostream& operator<<(std::ostream& os, float2* v);
};

//std::ostream& operator<<(std::ostream& os, float2* v) {
//    os << "(" << v->x << ", " << v->y << ")";
//    return os;
//};