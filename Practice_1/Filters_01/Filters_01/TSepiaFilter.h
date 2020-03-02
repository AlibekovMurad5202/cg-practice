#pragma once
#include "TFilter.h"

class TSepiaFilter : public TFilter
{
public:
  TSepiaFilter() {};
  ~TSepiaFilter() {};

  QImage calculateNewImagePixMap(const QImage& image, int radius);
};