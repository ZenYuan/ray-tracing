#ifndef VEC3_H
#define VEC3_H
#include <initializer_list>

template <size_t N, typename T>
class Vec {
 public:
    T m[N] = {0}; //元素数组
 public:
    Vec() { for(size_t i = 0; i < N; i++) { m[i] = 0; } }
    Vec(const Vec<N, T>& vec) { for(size_t i = 0; i < N; i++) { m[i] = vec.m[i]; } }
    Vec(const std::initializer_list<T>& il) { if(il.size() != N) { return; } int j = 0; for(auto i : il) { m[j++] = i; } }
    Vec& operator=(const Vec<N, T>& vec) { for(size_t i = 0; i < N; i++) { m[i] = vec.m[i]; }  return *this; }
    T& operator[](const int i) { return m[i];}
};

template <typename T>
class Vec<3, T> {
 public:
    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        T m[3];
    };
  public:
    Vec() { for(size_t i = 0; i < 3; i++) { m[i] = 0; } }
    Vec(T x, T y, T z) { m[0] = x; m[1] = y; m[2] = z;}
    Vec(const Vec<3, T>& vec) { for(size_t i = 0; i < 3; i++) { m[i] = vec.m[i]; } }
    Vec(const std::initializer_list<T>& il) { if(il.size() != 3) { return; } int j = 0; for(auto i : il) { m[j++] = i; } }
    Vec& operator=(const Vec<3, T>& vec) { for(size_t i = 0; i < 3; i++) { m[i] = vec.m[i]; }  return *this; }
    T& operator[](const int i) { return m[i];}
};

template <typename T>
using vec3 = Vec<3, T>;
using point = vec3<double>;
using color = vec3<double>;

//utility func
template <typename T>
vec3<T> operator+(vec3<T>& vec, T val) {
    return vec3<T>{vec.x + val, vec.y + val, vec.z + val};
}

template <typename T>
vec3<T> operator-(vec3<T>& vec, T val) {
    return vec3<T>{vec.x - val, vec.y - val, vec.z - val};
}

template <typename T>
vec3<T> operator*(vec3<T>& vec, T val) {
    return vec3<T>{vec.x * val, vec.y * val, vec.z * val};
}

template <typename T>
vec3<T> operator/(vec3<T>& vec, T val) {
    return vec * (1/val);
}

template <typename T>
int dot(vec3<T>& vec_l, vec3<T>& vec_r) {
    return vec_l.x * vec_r.x + vec_l.y * vec_r.y + vec_l.y * vec_r.y;
}

template <typename T>
vec3<T> cross(vec3<T>& vec_l, vec3<T>& vec_r) {
    return
}
#endif
