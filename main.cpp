#include<iostream>
#include<vector>

using namespace std;

class vec3 {
public:
    float x, y, z;

    vec3 () = default;
    vec3 (float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Print () const {
        cout << "x = " << this->x << ", y = " << this->y << ", z = " << this->z << endl;
    }

    vec3 operator- (vec3 vec) const {
        vec3 res;
        res.x = this->x - vec.x;
        res.y = this->y - vec.y;
        res.z = this->z - vec.z;
        return res;
    }
};

vec3 cross (vec3 a, vec3 b) {
    vec3 res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;

    return res;
}

float dot (vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float triangle_intersection(const vec3& orig, const vec3& dir, const vec3& v0, const vec3& v1, const vec3& v2) {
    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;
    // Вычисление вектора нормали к плоскости
    vec3 pvec = cross(dir, e2);
    float det = dot(e1, pvec);

    // Луч параллелен плоскости
    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }

    float inv_det = 1 / det;
    vec3 tvec = orig - v0;
    float u = dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }

    vec3 qvec = cross(tvec, e1);
    float v = dot(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    return dot(e2, qvec) * inv_det;
}

int main () {
    vec3 v0(0, 3, 0);
    vec3 v1(0, 0, 3);
    vec3 v2(0, -3, 0);
    vec3 orig(3, 0, 0);
    vec3 dir(-3, 0, 1);

    cout << triangle_intersection(orig, dir, v0, v1, v2) << endl;
}