#pragma once
#include "TFilter.h"

class TInvertFilter : public TFilter
{
public:
  TInvertFilter() {};
  ~TInvertFilter() {};

  QImage calculateNewImagePixMap(const QImage& image, int radius);
};