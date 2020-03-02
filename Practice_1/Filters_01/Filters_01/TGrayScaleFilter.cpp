#include "TGrayScaleFilter.h"

QImage TGrayScaleFilter::calculateNewImagePixMap(const QImage & image, int radius)
{
  QImage result_image(image);

  for (int x = 0; x < image.width(); x++)
    for (int y = 0; y < image.height(); y++)
    {
      QColor gray_color = image.pixelColor(x, y);
      int red =   gray_color.red();
      int green = gray_color.green();
      int blue =  gray_color.blue();

      int intensity = 0.36 * red + 0.53 * green + 0.11 * blue;
      intensity = clamp<int>(intensity, 255, 0);

      gray_color.setRgb(intensity, intensity, intensity);
      result_image.setPixelColor(x, y, gray_color);
    }

  return result_image;
}
