#include "TBlurFilter.h"

TBlurFilter::TBlurFilter()
{
  int matrix_size = 2 * matrix_radius + 1;
  weight_matrix = new float[matrix_size * matrix_size];

  for (int i = 0; i < matrix_size; i++)
    for (int j = 0; j < matrix_size; j++)
      weight_matrix[i * matrix_size + j] = 1.0f / (matrix_size * matrix_size);
}
