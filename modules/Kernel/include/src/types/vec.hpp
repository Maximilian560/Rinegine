#pragma once
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wnested-anon-types"
#endif
namespace Rinegine {
  namespace Kernel {
    template <class type> struct vec2;
    template <class type> struct vec3;
    template <class type> struct vec4;
    template <class type>
    struct vec2 {
      union {
        struct { type x, y; };
        struct { type r, g; };
        struct { type s, t; };
        type data[2];
      };

      inline type& operator[](size_t i) { return data[i]; }
      inline const type& operator[](size_t i) const { return data[i]; }

      inline vec2 operator+(const vec2& v) const { return { x + v.x, y + v.y }; }
      inline vec2 operator-(const vec2& v) const { return { x - v.x, y - v.y }; }
      inline vec2 operator*(const vec2& v) const { return { x * v.x, y * v.y }; }
      inline vec2 operator/(const vec2& v) const { return { x / v.x, y / v.y }; }

      inline vec2 operator+(type scalar) const { return { x + scalar, y + scalar }; }
      inline vec2 operator-(type scalar) const { return { x - scalar, y - scalar }; }
      inline vec2 operator*(type scalar) const { return { x * scalar, y * scalar }; }
      inline vec2 operator/(type scalar) const { return { x / scalar, y / scalar }; }

      inline vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; }
      inline vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; }
      inline vec2& operator*=(const vec2& v) { x *= v.x; y *= v.y; return *this; }
      inline vec2& operator/=(const vec2& v) { x /= v.x; y /= v.y; return *this; }

      inline bool operator==(const vec2& v) const {
        return (x == v.x && y == v.y);
      }
      inline bool operator!=(const vec2& v) const {
        return !(*this == v);
      }
      vec2() : x(0), y(0) {}
      vec2(type _x, type _y) : x(_x), y(_y) {}
      vec2(type scalar) : x(scalar), y(scalar) {}

      vec2(const vec3<type>& v);
      vec2(const vec4<type>& v);

    };
    template <class type>
    struct vec3 {
      union {
        struct { type x, y, z; };
        struct { type r, g, b; };
        struct { type s, t, p; };
        type data[3];
      };

      inline type& operator[](size_t i) { return data[i]; }
      inline const type& operator[](size_t i) const { return data[i]; }

      inline vec3 operator+(const vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }
      inline vec3 operator-(const vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }
      inline vec3 operator*(const vec3& v) const { return { x * v.x, y * v.y, z * v.z }; }
      inline vec3 operator/(const vec3& v) const { return { x / v.x, y / v.y, z / v.z }; }

      inline vec3 operator+(type scalar) const { return { x + scalar, y + scalar, z + scalar }; }
      inline vec3 operator-(type scalar) const { return { x - scalar, y - scalar, z - scalar }; }
      inline vec3 operator*(type scalar) const { return { x * scalar, y * scalar, z * scalar }; }
      inline vec3 operator/(type scalar) const { return { x / scalar, y / scalar, z / scalar }; }

      inline vec3& operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
      inline vec3& operator-=(const vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
      inline vec3& operator*=(const vec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
      inline vec3& operator/=(const vec3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

      inline bool operator==(const vec3& v) const {
        return (x == v.x && y == v.y && z == v.z);
      }
      inline bool operator!=(const vec3& v) const {
        return !(*this == v);
      }
      vec3() : x(0), y(0), z(0) {}
      vec3(type _x, type _y, type _z) : x(_x), y(_y), z(_z) {}
      vec3(type scalar) : x(scalar), y(scalar), z(scalar) {}

      vec3(const vec2<type>& v);
      vec3(const vec4<type>& v);
    };
    template <class type>
    struct vec4 {
      union {
        struct { type x, y, z, w; };
        struct { type r, g, b, a; };
        struct { type s, t, p, q; };
        type data[4];
      };

      inline type& operator[](size_t i) { return data[i]; }
      inline const type& operator[](size_t i) const { return data[i]; }

      inline vec4 operator+(const vec4& v) const { return { x + v.x, y + v.y, z + v.z, w + v.w }; }
      inline vec4 operator-(const vec4& v) const { return { x - v.x, y - v.y, z - v.z, w - v.w }; }
      inline vec4 operator*(const vec4& v) const { return { x * v.x, y * v.y, z * v.z, w * v.w }; }
      inline vec4 operator/(const vec4& v) const { return { x / v.x, y / v.y, z / v.z, w / v.w }; }

      inline vec4 operator+(type scalar) const { return { x + scalar, y + scalar, z + scalar, w + scalar }; }
      inline vec4 operator-(type scalar) const { return { x - scalar, y - scalar, z - scalar, w - scalar }; }
      inline vec4 operator*(type scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
      inline vec4 operator/(type scalar) const { return { x / scalar, y / scalar, z / scalar, w / scalar }; }

      inline vec4& operator+=(const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
      inline vec4& operator-=(const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
      inline vec4& operator*=(const vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
      inline vec4& operator/=(const vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

      inline bool operator==(const vec4& v) const {
        return (x == v.x && y == v.y && z == v.z && w == v.w);
      }
      inline bool operator!=(const vec4& v) const {
        return !(*this == v);
      }
      vec4() : x(0), y(0), z(0), w(0) {}
      vec4(type _x, type _y, type _z, type _w) : x(_x), y(_y), z(_z), w(_w) {}
      vec4(type scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

      vec4(const vec2<type>& v);
      vec4(const vec3<type>& v);
    };
    template <class type> inline vec2<type>::vec2(const vec3<type>& v) : x(v.x), y(v.y) {}
    template <class type> inline vec2<type>::vec2(const vec4<type>& v) : x(v.x), y(v.y) {}

    template <class type> inline vec3<type>::vec3(const vec2<type>& v) : x(v.x), y(v.y), z(0) {}
    template <class type> inline vec3<type>::vec3(const vec4<type>& v) : x(v.x), y(v.y), z(v.z) {}

    template <class type> inline vec4<type>::vec4(const vec2<type>& v) : x(v.x), y(v.y), z(0), w(0) {}
    template <class type> inline vec4<type>::vec4(const vec3<type>& v) : x(v.x), y(v.y), z(v.z), w(0) {}


  }
  using vec2 = Kernel::vec2<float>;
  using vec3 = Kernel::vec3<float>;
  using vec4 = Kernel::vec4<float>;

  using dvec2 = Kernel::vec2<double>;
  using dvec3 = Kernel::vec3<double>;
  using dvec4 = Kernel::vec4<double>;

  using ivec2 = Kernel::vec2<int>;
  using ivec3 = Kernel::vec3<int>;
  using ivec4 = Kernel::vec4<int>;

  using uvec2 = Kernel::vec2<unsigned int>;
  using uvec3 = Kernel::vec3<unsigned int>;
  using uvec4 = Kernel::vec4<unsigned int>;

  using bvec2 = Kernel::vec2<bool>;
  using bvec3 = Kernel::vec3<bool>;
  using bvec4 = Kernel::vec4<bool>;

}

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif