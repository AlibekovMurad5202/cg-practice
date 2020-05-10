#include "Filters.h"

QImage MatrixFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = _image.height();
  int width = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      result.setPixelColor(x, y, this->calculateNewPixelColor(_image, x, y));
  return result;
}

QColor MatrixFilter::calculateNewPixelColor(const QImage& _image, int x, int y) 
{
  double result_red   = 0;
  double result_green = 0;
  double result_blue  = 0;
  int height = _image.height();
  int width  = _image.width();
  int diam   = m_radius * 2 + 1;

  for (int j = -m_radius; j <= m_radius; j++)
    for (int i = -m_radius; i <= m_radius; i++) {
      int idx = (j + m_radius) * diam + (i + m_radius);
      QColor color = _image.pixelColor(clamp<int>(x + i, 0, width  - 1),
                                       clamp<int>(y + j, 0, height - 1));
      result_red   += int(color.red()   * weight_matrix[idx]);
      result_green += int(color.green() * weight_matrix[idx]);
      result_blue  += int(color.blue()  * weight_matrix[idx]);
    }
  return QColor(clamp<int>(result_red,   0, 255),
                clamp<int>(result_green, 0, 255),
                clamp<int>(result_blue,  0, 255));
}

QImage TInvertFilter::calculateNewImagePixMap(const QImage& _image)
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor color = _image.pixelColor(x, y);
      color.setRgb(255 - color.red(), 
                   255 - color.green(), 
                   255 - color.blue());
      result.setPixelColor(x, y, color);
    }
  return result;
}

QImage TGrayScaleFilter::calculateNewImagePixMap(const QImage& _image)
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor grey_color = _image.pixelColor(x, y);
      int intensity = INTENSITY_INT(grey_color);
      grey_color.setRgb(intensity, intensity, intensity);
      result.setPixelColor(x, y, grey_color);
    }
  return result;
}

QImage TSepiaFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor sepia_color = _image.pixelColor(x, y);
      int intensity = INTENSITY_INT(sepia_color);
      sepia_color.setRgb(clamp<int>(intensity + sepia_scale * 2, 0, 255),
                         clamp<int>(intensity + sepia_scale / 2, 0, 255),
                         clamp<int>(intensity - sepia_scale,     0, 255));
      result.setPixelColor(x, y, sepia_color);
    }
  return result;
}

QImage TBrightnessFilter::calculateNewImagePixMap(const QImage& _image)
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor brightness_color = _image.pixelColor(x, y);
      brightness_color.setRgb(clamp<int>(brightness_color.red()   + brightness_scale, 0, 255),
                              clamp<int>(brightness_color.green() + brightness_scale, 0, 255),
                              clamp<int>(brightness_color.blue()  + brightness_scale, 0, 255));
      result.setPixelColor(x, y, brightness_color);
    }
  return result;
}

QImage TMedianFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();
  int diam = 2 * radius + 1;
  int size = diam * diam;
  int* indexes = new int[size];
  double* weight_matrix = new double[size];
  QColor* colors = new QColor[size];

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      for (int j = -radius; j <= radius; j++)
        for (int i = -radius; i <= radius; i++)
        {
          QColor color = _image.pixelColor(clamp<int>(x + i, 0, width - 1),
                                           clamp<int>(y + j, 0, height - 1));
          int idx = (j + radius) * diam + (i + radius);
          indexes[idx] = idx;
          colors[idx]  = color;
          weight_matrix[idx]  = INTENSITY_DOUBLE(color);
        }

      for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
          if (weight_matrix[j] > weight_matrix[j + 1])
          {
            SWAP_DOUBLE(weight_matrix[j], weight_matrix[j + 1]);
            SWAP_INT(indexes[j], indexes[j + 1]);
          }
      QColor median_color = colors[indexes[size / 2]];
      result.setPixelColor(x, y, median_color);
    }
  delete[] indexes;
  delete[] weight_matrix;
  delete[] colors;
  return result;
}

QImage TRotationFilter::calculateNewImagePixMap(const QImage& _image) 
{
  int height = _image.height();
  int width  = _image.width();
  QImage result(width, height, QImage::Format_RGB32);

  for (double y_result = 0; y_result < height; y_result++)
    for (double x_result = 0; x_result < width; x_result++)
    {
      int x = int(x_rotation_center
               + (x_result - x_rotation_center) * cos(angle)
               - (y_result - y_rotation_center) * sin(angle));

      int y = int(y_rotation_center
               + (x_result - x_rotation_center) * sin(angle)
               + (y_result - y_rotation_center) * cos(angle));

      QColor color;
      if ((x < 0) || (y < 0) || (x > width - 1) || (y > height - 1))
        color = QColor(0, 0, 0);
      else
        color = _image.pixelColor(x, y);
      result.setPixelColor(x_result, y_result, color);
    }

  return result;
}

void TGaussianBlurFilter::createGaussianWeightMatrix()
{
  const unsigned int size = 2 * m_radius + 1;
  weight_matrix = new double[size * size];
  double norm = 0;

  for (int i = -m_radius; i <= m_radius; i++)
    for (int j = -m_radius; j <= m_radius; j++) 
    {
      int idx = (i + m_radius) * size + (j + m_radius);
      weight_matrix[idx] = exp(-(double)(i * i + j * j) / (2 * sigma * sigma));
      norm += weight_matrix[idx];
    }

  for (int i = -m_radius; i <= m_radius; i++)
    for (int j = -m_radius; j <= m_radius; j++)
    {
      int idx = (i + m_radius) * size + (j + m_radius);
      weight_matrix[idx] /= norm;
    }
  return;
}

QColor TSobelYFilter::calculateNewPixelColor(const QImage& _image, int _x, int _y)
{
  int height = _image.height();
  int width  = _image.width();
  int diam = m_radius * 2 + 1;

  int x_result_red = 0;
  int x_result_green = 0;
  int x_result_blue = 0;

  int y_result_red = 0;
  int y_result_green = 0;
  int y_result_blue = 0;

  for (int j = -m_radius; j <= m_radius; j++)
    for (int i = -m_radius; i <= m_radius; i++) 
    {
      int x_idx = (j + m_radius) * diam + (i + m_radius);
      QColor x_color = _image.pixelColor(clamp<int>(_x + i, 0, width - 1),
                                         clamp<int>(_y + j, 0, height - 1));
      x_result_red   += x_color.red()   * weight_matrix[x_idx];
      x_result_green += x_color.green() * weight_matrix[x_idx];
      x_result_blue  += x_color.blue()  * weight_matrix[x_idx];

      int y_idx = (i + m_radius) * diam + (j + m_radius);
      QColor y_color = _image.pixelColor(clamp<int>(_x + j, 0, width - 1),
                                         clamp<int>(_y + i, 0, height - 1));
      y_result_red   += y_color.red()   * weight_matrix[y_idx];
      y_result_green += y_color.green() * weight_matrix[y_idx];
      y_result_blue  += y_color.blue()  * weight_matrix[y_idx];
    }

  int result_red   = (int)sqrt(x_result_red   * x_result_red   + y_result_red   * y_result_red);
  int result_green = (int)sqrt(x_result_green * x_result_green + y_result_green * y_result_green);
  int result_blue  = (int)sqrt(x_result_blue  * x_result_blue  + y_result_blue  * y_result_blue);
  QColor gradient(clamp<int>(result_red,   0, 255),
                  clamp<int>(result_green, 0, 255),
                  clamp<int>(result_blue,  0, 255));
  return gradient;
}

QImage TSobelYFilter::calculateNewImagePixMap(const QImage& _image)
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      result.setPixelColor(x, y, calculateNewPixelColor(_image, x, y));
  return result;
}

QColor TSobelXFilter::calculateNewPixelColor(const QImage& _image, int _x, int _y)
{
  int height = _image.height();
  int width  = _image.width();
  int diam = m_radius * 2 + 1;

  int x_result_red   = 0;
  int x_result_green = 0;
  int x_result_blue  = 0;

  int y_result_red   = 0;
  int y_result_green = 0;
  int y_result_blue  = 0;

  for (int j = -m_radius; j <= m_radius; j++)
    for (int i = -m_radius; i <= m_radius; i++)
    {
      int x_idx = (j + m_radius) * diam + (i + m_radius);
      QColor x_color = _image.pixelColor(clamp<int>(_x + i, 0, width  - 1),
                                         clamp<int>(_y + j, 0, height - 1));
      x_result_red   += x_color.red()   * weight_matrix[x_idx];
      x_result_green += x_color.green() * weight_matrix[x_idx];
      x_result_blue  += x_color.blue()  * weight_matrix[x_idx];

      int y_idx = (i + m_radius) * diam + (j + m_radius);
      QColor y_color = _image.pixelColor(clamp<int>(_x + j, 0, width - 1),
                                         clamp<int>(_y + i, 0, height - 1));
      y_result_red   += y_color.red()   * weight_matrix[y_idx];
      y_result_green += y_color.green() * weight_matrix[y_idx];
      y_result_blue  += y_color.blue()  * weight_matrix[y_idx];
    }

  int result_red   = (int)sqrt(x_result_red   * x_result_red   + y_result_red   * y_result_red);
  int result_green = (int)sqrt(x_result_green * x_result_green + y_result_green * y_result_green);
  int result_blue  = (int)sqrt(x_result_blue  * x_result_blue  + y_result_blue  * y_result_blue);
  QColor gradient(clamp<int>(result_red, 0, 255),
                  clamp<int>(result_green, 0, 255),
                  clamp<int>(result_blue, 0, 255));
  return gradient;
}

QImage TSobelXFilter::calculateNewImagePixMap(const QImage& _image)
{
  QImage result(_image);
  int height = _image.height();
  int width = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      result.setPixelColor(x, y, calculateNewPixelColor(_image, x, y));
  return result;
}

QImage TVerticalWaveFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y_result = 0; y_result < height; y_result++)
    for (int x_result = 0; x_result < width; x_result++)
    {
      int x = clamp<int>((int)(x_result + 10 * sin(2. * M_PI * x_result / 30.)), 0, width - 1);
      int y = y_result;      
      QColor color = _image.pixelColor(x, y);
      result.setPixelColor(x_result, y_result, color);
    }
  return result;
}

QImage THorizontalWaveFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y_result = 0; y_result < height; y_result++)
    for (int x_result = 0; x_result < width; x_result++)
    {
      int x = clamp<int>((int)(x_result + 20 * sin(2. * M_PI * y_result / 60.)), 0, width - 1);
      int y = y_result;
      QColor color = _image.pixelColor(x, y);
      result.setPixelColor(x_result, y_result, color);
    }
  return result;
}

QImage TGlassFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = result.height();
  int width  = result.width();

  for (int y_result = 0; y_result < height; y_result++)
    for (int x_result = 0; x_result < width; x_result++)
    {
      int x = clamp<int>((int)(x_result + ((std::rand() % 8) * .1 - .5) * 10.), 0, width  - 1);
      int y = clamp<int>((int)(y_result + ((std::rand() % 8) * .1 - .5) * 10.), 0, height - 1);
      QColor color = _image.pixelColor(x, y);
      result.setPixelColor(x_result, y_result, color);
    }
  return result;
}

QImage TGrayWorldFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  double sum_red   = 0.;
  double sum_green = 0.;
  double sum_blue  = 0.;

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor color = _image.pixelColor(x, y);
      sum_red   += (double)color.red();
      sum_green += (double)color.green();
      sum_blue  += (double)color.blue();
    }

  double average_red   = sum_red   / (height * width);
  double average_green = sum_green / (height * width);
  double average_blue  = sum_blue  / (height * width);
  double average = (average_red + average_green + average_blue) / 3.;

  double red_scale   = average / average_red;
  double green_scale = average / average_green;
  double blue_scale  = average / average_blue;

  for (int y_result = 0; y_result < height; y_result++)
    for (int x_result = 0; x_result < width; x_result++)
    {
      QColor color = _image.pixelColor(x_result, y_result);
      int result_red   = clamp<int>((int)(color.red()   * red_scale),   0, 255);
      int result_green = clamp<int>((int)(color.green() * green_scale), 0, 255);
      int result_blue  = clamp<int>((int)(color.blue()  * blue_scale),  0, 255);
      QColor result_color(result_red, result_green, result_blue);
      result.setPixelColor(x_result, y_result, result_color);
    }
  return result;
}

QImage TDilationFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();
  int mask_height = mask.getHeight();
  int mask_width  = mask.getWidth();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor max_color(0, 0, 0);
      double max_intensity = 0.;
      for (int j = -mask_height / 2; j <= mask_height / 2; j++)
        for (int i = -mask_width / 2; i <= mask_width / 2; i++)
        {
          if (mask[(i + mask_height / 2) * mask_width + (j + mask_width / 2)])
          {
            QColor color = _image.pixelColor(clamp<int>(x + j, 0, width  - 1),
                                             clamp<int>(y + i, 0, height - 1));
            double intensity = INTENSITY_DOUBLE(color);
            if (intensity > max_intensity)
            {
              max_color = color;
              max_intensity = intensity;
            }
          }
        }
      result.setPixelColor(x, y, max_color);
    }
  return result;
}

QImage TErosionFilter::calculateNewImagePixMap(const QImage& _image) 
{
  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();
  int mask_height = mask.getHeight();
  int mask_width  = mask.getWidth();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor min_color(255, 255, 255);
      float min_intensity = 255.;
      for (int j = -mask_height / 2; j <= mask_height / 2; j++)
        for (int i = -mask_width / 2; i <= mask_width / 2; i++)
        {
          if (mask[(i + mask_height / 2) * mask_width + (j + mask_width / 2)])
          {
            QColor color = _image.pixelColor(clamp<int>(x + j, 0, width  - 1),
                                             clamp<int>(y + i, 0, height - 1));
            double intensity = INTENSITY_DOUBLE(color);
            if (intensity < min_intensity)
            {
              min_color = color;
              min_intensity = intensity;
            }
          }
        }
      result.setPixelColor(x, y, min_color);
    }
  return result;
}

QImage TOpeningFilter::calculateNewImagePixMap(const QImage& _image) 
{
  TErosionFilter erosion_filter(mask);
  QImage result = erosion_filter.calculateNewImagePixMap(_image);
  TDilationFilter dilation_filter(mask);
  return dilation_filter.calculateNewImagePixMap(result);
}

QImage TClosingFilter::calculateNewImagePixMap(const QImage& _image) 
{
  TDilationFilter dilation_filter(mask);
  QImage result = dilation_filter.calculateNewImagePixMap(_image);
  TErosionFilter erosion_filter(mask);
  return erosion_filter.calculateNewImagePixMap(result);
}

QImage TGradFilter::calculateNewImagePixMap(const QImage& _image) 
{
  TDilationFilter dilation_filter(mask);
  QImage dilation_image = dilation_filter.calculateNewImagePixMap(_image);
  TErosionFilter erosion_filter(mask);
  QImage erosion_image = erosion_filter.calculateNewImagePixMap(_image);

  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor dilation_color = dilation_image.pixelColor(x, y);
      QColor erosion_color  =  erosion_image.pixelColor(x, y);
      int result_red   = clamp<int>(dilation_color.red()   - erosion_color.red(),   0, 255);
      int result_green = clamp<int>(dilation_color.green() - erosion_color.green(), 0, 255);
      int result_blue  = clamp<int>(dilation_color.blue()  - erosion_color.blue(),  0, 255);
      QColor result_color(result_red, result_green, result_blue);
      result.setPixelColor(x, y, result_color);
    }
  return result;
}

QImage TTopHatFilter::calculateNewImagePixMap(const QImage& _image) 
{
  TOpeningFilter opening(mask);
  QImage opening_image = opening.calculateNewImagePixMap(_image);

  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor color = _image.pixelColor(x, y);
      QColor opening_color = opening_image.pixelColor(x, y);
      int result_red   = clamp<int>(color.red()   - opening_color.red(),   0, 255);
      int result_green = clamp<int>(color.green() - opening_color.green(), 0, 255);
      int result_blue  = clamp<int>(color.blue()  - opening_color.blue(),  0, 255);
      QColor result_color(result_red, result_green, result_blue);
      result.setPixelColor(x, y, result_color);
    }
  return result;
}

QImage TBlackHatFilter::calculateNewImagePixMap(const QImage& _image) 
{
  TClosingFilter closing(mask);
  QImage closing_picture = closing.calculateNewImagePixMap(_image);

  QImage result(_image);
  int height = _image.height();
  int width  = _image.width();

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor color = _image.pixelColor(x, y);
      QColor closing_color = closing_picture.pixelColor(x, y);
      int result_red   = clamp<int>(closing_color.red()   - color.red(),   0, 255);
      int result_green = clamp<int>(closing_color.green() - color.green(), 0, 255);
      int result_blue  = clamp<int>(closing_color.blue()  - color.blue(),  0, 255);
      QColor result_color(result_red, result_green, result_blue);
      result.setPixelColor(x, y, result_color);
    }
  return result;
};