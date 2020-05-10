#include "Mask.h"

TMask::TMask(const std::string& _filename) {
  std::ifstream file;
  file.open(_filename);
  if (file)
  {
    file >> width >> height;
    int size = width * height;
    weights = new int[size];
    for (int i = 0; i < size; i++)
      file >> weights[i];
    file.close();
  }
}

TMask::TMask(const TMask& _mask) {
  width = _mask.width;
  height = _mask.height;
  int size = width * height;
  weights = new int[size];
  for (int i = 0; i < size; i++)
    weights[i] = _mask[i];
}

TMask::~TMask()
{
  delete[] weights;
}

int TMask::getHeight()
{
  return height;
}

int TMask::getWidth()
{
  return width;
}

int TMask::operator[](int _index)
{
  const int default_weight = 0;
  if ((_index >= 0) && (_index <= height * width))
    return weights[_index];
  return default_weight;
}

const int TMask::operator[](int _index) const
{
  const int default_weight = 0;
  if ((_index >= 0) && (_index <= height * width))
    return weights[_index];
  return default_weight;
}
