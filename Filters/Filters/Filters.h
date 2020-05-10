#pragma once

#include "includes.h"

class Filter {
public:
  Filter() {}
  ~Filter() {}

  virtual QImage calculateNewImagePixMap(const QImage& _image) = 0;
};

class MatrixFilter : public Filter {
protected:
  double* weight_matrix;
  int m_radius;
  QColor calculateNewPixelColor(const QImage& _image, int _x, int _y);

public:
  MatrixFilter(int _radius = 1, float* _vector = nullptr) : m_radius(_radius) {}
  ~MatrixFilter() { if (weight_matrix != nullptr) delete[] weight_matrix; }

  QImage calculateNewImagePixMap(const QImage& _image);
};


class TInvertFilter : public Filter {
protected:
  int radius;

public:
  TInvertFilter(int _radius = 1) : radius(_radius) {}
  ~TInvertFilter() {}

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TGrayScaleFilter : public Filter {
public:
  TGrayScaleFilter() {};
  ~TGrayScaleFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TSepiaFilter : public Filter {
private:
  const int sepia_scale = 40;

public:
  TSepiaFilter() {};
  ~TSepiaFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TBrightnessFilter : public Filter {
private:
  const int brightness_scale = 16;

public:
  TBrightnessFilter() {};
  ~TBrightnessFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TMedianFilter : public Filter {
protected:
  int radius;
  double* weight_matrix;

public:
  TMedianFilter(int _imageRadius = 1) : radius(_imageRadius) {};
  ~TMedianFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TMaximumFilter : public Filter {
protected:
  int radius;
  double* weight_matrix;

public:
  TMaximumFilter(int _imageRadius = 1) : radius(_imageRadius) {};
  ~TMaximumFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TMinimumFilter : public Filter {
protected:
  int radius;
  double* weight_matrix;

public:
  TMinimumFilter(int _imageRadius = 1) : radius(_imageRadius) {};
  ~TMinimumFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TRotationFilter : public Filter {
protected:
  double angle;
  int x_rotation_center;
  int y_rotation_center;

public:
  TRotationFilter(double _degrees = 90., int _x0 = 0, int _y0 = 0)
    : x_rotation_center(_x0), y_rotation_center(_y0), angle(_degrees / 180 * M_PI) {}
  ~TRotationFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class THorizontalShiftFilter : public Filter {
protected:
  double shift;

public:
  THorizontalShiftFilter(double _shift = 50.)
    : shift(_shift) {}
  ~THorizontalShiftFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TVerticalShiftFilter : public Filter {
protected:
  double shift;

public:
  TVerticalShiftFilter(double _shift = 50.)
    : shift(_shift) {}
  ~TVerticalShiftFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TBlurFilter : public MatrixFilter {
public:
  TBlurFilter(int _radius = 1) : MatrixFilter(_radius) 
  {
    int size = 2 * m_radius + 1;
    weight_matrix = new double[size * size];
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        weight_matrix[i * size + j] = 1. / (size * size);
  }
  ~TBlurFilter() {}
};

class TGaussianBlurFilter : public MatrixFilter {
protected:
  double sigma;

public:
  TGaussianBlurFilter(int _radius = 3, double _sigma = 2) 
    : MatrixFilter(_radius), sigma(_sigma) { createGaussianWeightMatrix(); }

  void createGaussianWeightMatrix();
};

class TSobelYFilter : public MatrixFilter {
protected:
  QColor calculateNewPixelColor(const QImage& _image, int _x, int _y);

public:
  TSobelYFilter() : MatrixFilter(1) 
  {
    weight_matrix = new double[9];
    weight_matrix[0] = -1.; weight_matrix[1] = 0.; weight_matrix[2] = 1.;
    weight_matrix[3] = -2.; weight_matrix[4] = 0.; weight_matrix[5] = 2.;
    weight_matrix[6] = -1.; weight_matrix[7] = 0.; weight_matrix[8] = 1.;
  };
  ~TSobelYFilter() {}

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TSobelXFilter : public MatrixFilter {
protected:
  QColor calculateNewPixelColor(const QImage& _image, int _x, int _y);

public:
  TSobelXFilter() : MatrixFilter(1)
  {
    weight_matrix = new double[9];
    weight_matrix[0] = -1.; weight_matrix[1] = -2.; weight_matrix[2] = -1.;
    weight_matrix[3] =  0.; weight_matrix[4] =  0.; weight_matrix[5] =  0.;
    weight_matrix[6] =  1.; weight_matrix[7] =  2.; weight_matrix[8] =  1.;
  };
  ~TSobelXFilter() {}

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TSharpnessIncreaseFilter : public MatrixFilter {
public:
  TSharpnessIncreaseFilter() : MatrixFilter(1) 
  {
    weight_matrix = new double[9];
    weight_matrix[0] =  0.; weight_matrix[1] = -1.; weight_matrix[2] =  0.;
    weight_matrix[3] = -1.; weight_matrix[4] =  5.; weight_matrix[5] = -1.;
    weight_matrix[6] =  0.; weight_matrix[7] = -1.; weight_matrix[8] =  0.;
  }
  ~TSharpnessIncreaseFilter() {}
};

class TMotionBlurFilter : public MatrixFilter {
public:
  TMotionBlurFilter(int radius = 1) : MatrixFilter(radius) 
  {
    int diam = radius * 2 + 1;
    weight_matrix = new double[diam * diam];
    for (int i = 0; i < diam; i++)
      for (int j = 0; j < diam; j++)
        if (i == j) weight_matrix[i * diam + j] = 1. / diam;
        else weight_matrix[i * diam + j] = 0.;
  }
  ~TMotionBlurFilter() {}
};

class TSharpnessFilter : public MatrixFilter {
public:
  TSharpnessFilter() : MatrixFilter(1) 
  {
    weight_matrix = new double[9];
    weight_matrix[0] = -1.; weight_matrix[1] = -1.; weight_matrix[2] = -1.;
    weight_matrix[3] = -1.; weight_matrix[4] =  9.; weight_matrix[5] = -1.;
    weight_matrix[6] = -1.; weight_matrix[7] = -1.; weight_matrix[8] = -1.;
  }
  ~TSharpnessFilter() {}
};

class TVerticalWaveFilter : public Filter {
public:
  TVerticalWaveFilter() {};
  ~TVerticalWaveFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class THorizontalWaveFilter : public Filter {
public:
  THorizontalWaveFilter() {};
  ~THorizontalWaveFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TLinearCorrectionFilter : public Filter {
public:
  TLinearCorrectionFilter() {};
  ~TLinearCorrectionFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TGammaCorrectionFilter : public Filter {
protected:
  double gamma;
  double coef;

public:
  TGammaCorrectionFilter(double _coef = 1, double _gamma = 1)
  : coef(_coef), gamma(_gamma) {};
  ~TGammaCorrectionFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TPerfectReflectorFilter : public Filter {
public:
  TPerfectReflectorFilter() {};
  ~TPerfectReflectorFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TGlassFilter : public Filter {
public:
  TGlassFilter() {};
  ~TGlassFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TLuminousEdgesFilter : public Filter {
public:
  TLuminousEdgesFilter() {};
  ~TLuminousEdgesFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TGrayWorldFilter : public Filter {
public:
  TGrayWorldFilter() {};
  ~TGrayWorldFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TMorphologicalOperation : public Filter {
protected:
  TMask mask;

public:
  TMorphologicalOperation(TMask _mask) : mask(_mask) {};
  ~TMorphologicalOperation() {};
};

class TDilationFilter : public TMorphologicalOperation {
public:
  TDilationFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TDilationFilter() { };

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TErosionFilter : public TMorphologicalOperation {
public:
  TErosionFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TErosionFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TOpeningFilter : public TMorphologicalOperation {
public:
  TOpeningFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TOpeningFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TClosingFilter : public TMorphologicalOperation {
public:
  TClosingFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TClosingFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TGradFilter : public TMorphologicalOperation {
public:
  TGradFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TGradFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TTopHatFilter : public TMorphologicalOperation {
public:
  TTopHatFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TTopHatFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};

class TBlackHatFilter : public TMorphologicalOperation {
public:
  TBlackHatFilter(TMask _mask) : TMorphologicalOperation(_mask) {};
  ~TBlackHatFilter() {};

  QImage calculateNewImagePixMap(const QImage& _image);
};