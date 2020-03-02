#pragma once
#include "TFilter.h"

class TGrayScaleFilter : public TFilter
{
public:
  TGrayScaleFilter() {};
  ~TGrayScaleFilter() {};

  QImage calculateNewImagePixMap(const QImage& image, int radius);
};