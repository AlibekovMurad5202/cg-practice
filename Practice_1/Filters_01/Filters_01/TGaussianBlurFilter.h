#pragma once
#include "TMatrixFilter.h"

class TGaussianBlurFilter : public TMatrixFilter
{
public:
  TGaussianBlurFilter();
  ~TGaussianBlurFilter() {};

  void createGaussianWeightMatrix(int matrix_radius, int sigma);
};