#include "TSharpnessFilter2.h"

TSharpnessFilter2::TSharpnessFilter2()
{
  int matrix_size = 2 * matrix_radius + 1;
  weight_matrix = new float[matrix_size * matrix_size];

  weight_matrix[0] = -1; weight_matrix[1] = -1; weight_matrix[2] = -1;
  weight_matrix[3] = -1; weight_matrix[4] =  9; weight_matrix[5] = -1;
  weight_matrix[6] = -1; weight_matrix[7] = -1; weight_matrix[8] = -1;
}