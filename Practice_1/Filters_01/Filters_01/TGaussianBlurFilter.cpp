#include "TGaussianBlurFilter.h"

TGaussianBlurFilter::TGaussianBlurFilter() : TMatrixFilter(3)
{
  createGaussianWeightMatrix(3, 2);
}

void TGaussianBlurFilter::createGaussianWeightMatrix(int matrix_radius, int sigma)
{
  const unsigned matrix_size = 2 * matrix_radius + 1;
  float norm = 0;
  weight_matrix = new float[matrix_size * matrix_size];

  for (int i = -matrix_radius; i <= matrix_radius; i++)
    for (int j = -matrix_radius; j <= matrix_radius; j++)
    {
      int index = (i + matrix_radius) * matrix_size + (j + matrix_radius);
      weight_matrix[index] = exp(-(i * i + j * j) / (sigma * sigma));
      //norm = norm + (1.0f / (2 * 3.1415926 * sigma * sigma)) * exp(-(i * i + j * j) / (2 * sigma * sigma));
      norm += weight_matrix[index];
    }
  
  for (int i = 0; i < matrix_size; i++)
    for (int j = 0; j < matrix_size; j++)
      weight_matrix[i * matrix_size + j] /= norm;

}