#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/SIMD_op-mult"
/*
 * SIMD‑умножение матриц (слева A [M×K], справа B [K×N]) → result [M×N]
 * Тип данных: float, AVX2 + FMA
 *
 * Параметры:
 *   A      – указатель на элементы левой матрицы (размещение row‑major)
 *   B      – указатель на элементы правой матрицы (размещение row‑major)
 *   result – указатель на массив под результирующую матрицу (row‑major)
 *   M      – число строк в A и в result
 *   K      – число столбцов в A (и строк в B)
 *   N      – число столбцов в B и в result
 */
namespace RG {
  namespace Lock {
    void simd_matrix_mulf(const float* A,
      const float* B,
      float* result,
      size_t M, size_t K, size_t N) {
      const size_t VEC = 8;               // AVX2 работает с 8 float за раз
      const size_t rowSize = N;           // длина строки в B и result

      // 1) Обнуляем result
      for (size_t i = 0; i < M * N; ++i) {
        result[i] = 0.0f;
      }

      // 2) Основной алгоритм: для каждой строки A (i) и блока из 8 колонок B (j..j+7)
      for (size_t i = 0; i < M; ++i) {
        const float* rowA = A + i * K;       // указатель на начало i‑й строки A
        float* rowC = result + i * N;   // указатель на начало i‑й строки result

        // 2a) Блоки по 8 колонок
        for (size_t j = 0; j + VEC <= N; j += VEC) {
          // Вектор‑аккумулятор для 8 элементов результата
          __m256 sum = _mm256_setzero_ps();

          // Суммируем по k: sum += A[i,k] * B[k, j..j+7]
          for (size_t k = 0; k < K; ++k) {
            // Распространяем скаляр A[i,k] на все 8 lane
            __m256 a_vec = _mm256_set1_ps(rowA[k]);
            // Загружаем сразу 8 элементов B[k, j..j+7]
            __m256 b_vec = _mm256_loadu_ps(B + k * rowSize + j);
            // FMA: sum = a_vec * b_vec + sum
            sum = _mm256_fmadd_ps(a_vec, b_vec, sum);
          }
          // Сохраняем 8 результирующих значений в rowC[j..j+7]
          _mm256_storeu_ps(rowC + j, sum);
        }

        // 2b) Обработка «хвоста», если N % 8 != 0
        for (size_t j = (N / VEC) * VEC; j < N; ++j) {
          float acc = 0.0f;
          for (size_t k = 0; k < K; ++k) {
            acc += rowA[k] * B[k * rowSize + j];
          }
          rowC[j] = acc;
        }
      }
    }
    void simd_matrix_muld(const double* A,
      const double* B,
      double* result,
      size_t M, size_t K, size_t N) {
      const size_t VEC = 4;               // AVX2 обрабатывает 4 double за раз (256 бит)
      const size_t rowSize = N;           // длина строки в B и result

      // 1) Обнуляем result
      for (size_t i = 0; i < M * N; ++i) {
        result[i] = 0.0;
      }

      // 2) Основной алгоритм: для каждой строки A (i) и блока из 4 колонок B (j..j+3)
      for (size_t i = 0; i < M; ++i) {
        const double* rowA = A + i * K;       // начало i‑й строки A
        double* rowC = result + i * N;   // начало i‑й строки result

        // 2a) Обработка блоков по 4 колонки
        for (size_t j = 0; j + VEC <= N; j += VEC) {
          // Вектор-аккумулятор для 4 элементов результата
          __m256d sum = _mm256_setzero_pd();

          // Суммируем по k: sum += A[i,k] * B[k, j..j+3]
          for (size_t k = 0; k < K; ++k) {
            // Распространяем скаляр A[i,k] по 4 lane
            __m256d a_vec = _mm256_set1_pd(rowA[k]);
            // Загружаем 4 элемента B[k, j..j+3]
            __m256d b_vec = _mm256_loadu_pd(B + k * rowSize + j);
            // FMA: sum = a_vec * b_vec + sum
            sum = _mm256_fmadd_pd(a_vec, b_vec, sum);
          }
          // Сохраняем 4 результирующих значения
          _mm256_storeu_pd(rowC + j, sum);
        }

        // 2b) Обработка "хвоста" (если N % 4 != 0)
        for (size_t j = (N / VEC) * VEC; j < N; ++j) {
          double acc = 0.0;
          for (size_t k = 0; k < K; ++k) {
            acc += rowA[k] * B[k * rowSize + j];
          }
          rowC[j] = acc;
        }
      }
    }
  }
  inline void SIMD_RG_Matrix_mulf(const RG_Matrix<float>& in_l, const  RG_Matrix<float>& in_r, RG_Matrix<float>& out) {
    Lock::simd_matrix_mulf(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols(), in_r.cols());
  }
  inline void SIMD_RG_Matrix_muld(const RG_Matrix<double>& in_l, const  RG_Matrix<double>& in_r, RG_Matrix<double>& out) {
    Lock::simd_matrix_muld(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols(), in_r.cols());
  }

  inline RG_Matrix<float> SIMD_RG_Matrix_mulf(const RG_Matrix<float>& in_l, const  RG_Matrix<float>& in_r) {
    RG_Matrix<float>out(in_r.cols(), in_l.rows());
    Lock::simd_matrix_mulf(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols(), in_r.cols());
    return out;
  }
  inline RG_Matrix<double> SIMD_RG_Matrix_muld(const RG_Matrix<double>& in_l, const  RG_Matrix<double>& in_r) {
    RG_Matrix<double>out(in_r.cols(), in_l.rows());
    Lock::simd_matrix_muld(in_l.data(), in_r.data(), out.data(), in_l.rows(), in_l.cols(), in_r.cols());
    return out;
  }
}


