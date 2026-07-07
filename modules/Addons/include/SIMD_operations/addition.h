#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/SIMD_op-add"
namespace RG {
  namespace Lock {
    void simd_matrix_addf(const float* a, const float* b, float* result, size_t rows, size_t cols) {
      const size_t size = rows * cols;
      const size_t VEC = 8;

      size_t i = 0;
      for (; i + VEC <= size; i += VEC) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 sum = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(result + i, sum);
      }

      for (; i < size; ++i) {
        result[i] = a[i] + b[i];
      }
    }

    void simd_matrix_addd(const double* a, const double* b, double* result, size_t rows, size_t cols) {
      const size_t size = rows * cols;
      const size_t VEC = 4;

      size_t i = 0;
      for (; i + VEC <= size; i += VEC) {
        __m256d va = _mm256_loadu_pd(a + i);
        __m256d vb = _mm256_loadu_pd(b + i);
        __m256d sum = _mm256_add_pd(va, vb);
        _mm256_storeu_pd(result + i, sum);
      }

      for (; i < size; ++i) {
        result[i] = a[i] + b[i];
      }
    }
  }
  inline void SIMD_RG_Matrixaddf(const RG_Matrix<float>& in_l, const  RG_Matrix<float>& in_r, RG_Matrix<float>& out) {
    Lock::simd_matrix_addf(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols());
  }
  inline void SIMD_RG_Matrix_addd(const RG_Matrix<double>& in_l, const  RG_Matrix<double>& in_r, RG_Matrix<double>& out) {
    Lock::simd_matrix_addd(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols());
  }

  inline RG_Matrix<float> SIMD_RG_Matrix_addf(const RG_Matrix<float>& in_l, const  RG_Matrix<float>& in_r) {
    RG_Matrix<float>out(in_r.cols(), in_l.rows());
    Lock::simd_matrix_addf(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols());
    return out;
  }
  inline RG_Matrix<double> SIMD_RG_Matrix_addd(const RG_Matrix<double>& in_l, const  RG_Matrix<double>& in_r) {
    RG_Matrix<double>out(in_r.cols(), in_l.rows());
    Lock::simd_matrix_addd(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols());
    return out;
  }
}




