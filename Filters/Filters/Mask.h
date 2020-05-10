#pragma once

#include "fstream"

class TMask {
private:
  int  width;
  int  height;
  int* weights;

public:
  TMask(const std::string& _filename);
  TMask(const TMask& _mask);
  ~TMask();

  int getHeight();
  int getWidth();

  int operator[] (int _index);
  const int operator[] (int _index) const;
};
