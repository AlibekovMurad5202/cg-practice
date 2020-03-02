#include "TSobelYFilter.h"

TSobelYFilter::TSobelYFilter()
{
  int matrix_size = 2 * matrix_radius + 1;
  weight_matrix = new float[matrix_size * matrix_size];

  weight_matrix[0] = -1; weight_matrix[1] = 0; weight_matrix[2] = 1;
  weight_matrix[3] = -2; weight_matrix[4] = 0; weight_matrix[5] = 2;
  weight_matrix[6] = -1; weight_matrix[7] = 0; weight_matrix[8] = 1;
}