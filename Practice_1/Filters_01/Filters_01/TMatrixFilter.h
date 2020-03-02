#pragma once
#include "TFilter.h"

class TMatrixFilter : public TFilter
{
public:
  float* weight_matrix;
  int matrix_radius;

  explicit TMatrixFilter(int radius = 1) : matrix_radius(radius) {};
  ~TMatrixFilter() {};

  QColor calculateNewPixelColor(const QImage & image, int x, int y, int radius);
  QImage calculateNewImagePixMap(const QImage& image, int radius);
};