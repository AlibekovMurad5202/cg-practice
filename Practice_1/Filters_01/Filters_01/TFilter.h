#pragma once
#include <QImage>

class TFilter
{
public:
  TFilter() {};
  ~TFilter() {};

  virtual QImage calculateNewImagePixMap(const QImage& image, int radius) = 0;
};

template<typename T>
T clamp(T value, int max, int min)
{
  if (value > max)
    return max;
  if (value < min)
    return min;

  return value;
}