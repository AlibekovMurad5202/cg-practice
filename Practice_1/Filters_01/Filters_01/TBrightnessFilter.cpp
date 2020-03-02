#include "TBrightnessFilter.h"

QImage TBrightnessFilter::calculateNewImagePixMap(const QImage & image, int radius)
{
  QImage result_image(image);

  for (int x = 0; x < image.width(); x++)
    for (int y = 0; y < image.height(); y++)
    {
      QColor color = image.pixelColor(x, y);

      const int coef = 16;
      int bright_red =   clamp<int>(color.red()   + coef, 255, 0);
      int bright_green = clamp<int>(color.green() + coef, 255, 0);
      int bright_blue =  clamp<int>(color.blue()  + coef, 255, 0);

      color.setRgb(bright_red, bright_green, bright_blue);
      result_image.setPixelColor(x, y, color);
    }

  return result_image;
}
