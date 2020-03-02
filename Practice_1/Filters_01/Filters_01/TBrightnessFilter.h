#pragma once
#include "TFilter.h"

class TBrightnessFilter : TFilter
{
public:
  TBrightnessFilter() {};
  ~TBrightnessFilter() {};

  QImage calculateNewImagePixMap(const QImage& image, int radius);
};