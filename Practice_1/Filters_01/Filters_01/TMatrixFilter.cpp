#include "TMatrixFilter.h"

QColor TMatrixFilter::calculateNewPixelColor(const QImage & image, int x, int y, int radius)
{
  int returnR = 0;
  int returnG = 0;
  int returnB = 0;
  int matrix_size = 2 * radius + 1;
  for (int i = -matrix_radius; i <= matrix_radius; i++)
    for (int j = -matrix_radius; j <= matrix_radius; j++)
    {
      int index = (i + matrix_radius) * matrix_size + (j + matrix_radius);
      QColor color = image.pixelColor(clamp<int>(x + j, image.width() - 1, 0),
                                      clamp<int>(y + i, image.height() - 1, 0));
      returnR += color.red()   * weight_matrix[index];
      returnG += color.green() * weight_matrix[index];
      returnB += color.blue()  * weight_matrix[index];
    }
  return QColor(clamp<int>(returnR, 255, 0),
                clamp<int>(returnG, 255, 0), 
                clamp<int>(returnB, 255, 0));
}

QImage TMatrixFilter::calculateNewImagePixMap(const QImage& image, int radius)
{
  QImage result_image(image);

  for (int x = 0; x < image.width(); x++)
    for (int y = 0; y < image.height(); y++)
    {
      QColor new_color = calculateNewPixelColor(image, x, y, radius);
      result_image.setPixelColor(x, y, new_color);
    }

  return result_image;
}