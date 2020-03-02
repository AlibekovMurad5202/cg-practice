#include "TSepiaFilter.h"

QImage TSepiaFilter::calculateNewImagePixMap(const QImage & image, int radius)
{
  QImage result_image(image);

  for (int x = 0; x < image.width(); x++)
    for (int y = 0; y < image.height(); y++)
    {
      QColor color = image.pixelColor(x, y);

      int intensity = 0.36 * color.red() + 0.53 * color.green() + 0.11 * color.blue();
      const int coef = 40;
      int sepia_red = clamp<int>(intensity + 2 * coef, 255, 0);
      int sepia_green = clamp<int>(intensity + 0.5 * coef, 255, 0);
      int sepia_blue = clamp<int>(intensity - coef, 255, 0);

      color.setRgb(sepia_red, sepia_green, sepia_blue);
      result_image.setPixelColor(x, y, color);
    }

  return result_image;
}
