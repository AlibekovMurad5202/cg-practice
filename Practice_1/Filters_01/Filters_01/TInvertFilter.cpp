#include "TInvertFilter.h"

QImage TInvertFilter::calculateNewImagePixMap(const QImage& image, int radius)
{
  QImage result_image(image);

  for (int x = 0; x < image.width(); x++)
    for (int y = 0; y < image.height(); y++)
    {
      QColor inverted_color = image.pixelColor(x, y);
      inverted_color.setRgb(255 - inverted_color.red(),
                            255 - inverted_color.green(),
                            255 - inverted_color.blue() );
      result_image.setPixelColor(x, y, inverted_color);
    }

  return result_image;
}