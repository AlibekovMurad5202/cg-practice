#include "TSharpnessFilter.h"

TSharpnessFilter::TSharpnessFilter()
{
  int matrix_size = 2 * matrix_radius + 1;
  weight_matrix = new float[matrix_size * matrix_size];

  weight_matrix[0] =  0; weight_matrix[1] = -1; weight_matrix[2] =  0;
  weight_matrix[3] = -1; weight_matrix[4] =  5; weight_matrix[5] = -1;
  weight_matrix[6] =  0; weight_matrix[7] = -1; weight_matrix[8] =  0;
}