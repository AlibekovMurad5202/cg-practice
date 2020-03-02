#include "TMotionBlurFilter.h"

TMotionBlurFilter::TMotionBlurFilter() : TMatrixFilter(matrix_radius)
{
  int matrix_size = 2 * matrix_radius + 1;
  
  weight_matrix = new float[matrix_size * matrix_size];

  for (int i = 0; i < matrix_size; i++)
    for (int j = 0; j < matrix_size; j++)
      if (i == j) weight_matrix[i * matrix_size + j] = 1.0f / matrix_size;
      else weight_matrix[i * matrix_size + j] = .0f;
}
