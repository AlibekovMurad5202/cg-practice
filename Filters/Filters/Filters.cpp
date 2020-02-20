#include "Filters.h"

QImage Inversion(QImage& _image)
{
  QImage invertedImage = _image;
  int height = _image.height();
  int width  = _image.width();
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor pixelColor = _image.pixelColor(x, y);
      int r_inverted = 255 - pixelColor.red();
      int g_inverted = 255 - pixelColor.green();
      int b_inverted = 255 - pixelColor.blue();
      QColor invertedColor(r_inverted, g_inverted, b_inverted);
      invertedImage.setPixelColor(x, y, invertedColor);
    }
  return invertedImage;
}

QImage Averaging(QImage& _image)
{
  QImage averagedImage = _image;
  int height = _image.height();
  int width  = _image.width();
  double transformationMatrix[3][3] = { 1./9, 1./9, 1./9,
                                        1./9, 1./9, 1./9,
                                        1./9, 1./9, 1./9 };

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
      QColor pixelColors[3][3];

      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
          int x_position = x - 1 + j;
          if ((x_position < 0) || (x_position >= width))
            x_position = x;

          int y_position = y - 1 + i;
          if ((y_position < 0) || (y_position >= height))
            y_position = y;

          pixelColors[i][j] = _image.pixelColor(x_position, y_position);
        }

      int r_averaged = 0;
      int g_averaged = 0;
      int b_averaged = 0;

      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
          r_averaged += (pixelColors[i][j].red()   * transformationMatrix[i][j]);
          g_averaged += (pixelColors[i][j].green() * transformationMatrix[i][j]);
          b_averaged += (pixelColors[i][j].blue()  * transformationMatrix[i][j]);
        }

      QColor averagedColor(r_averaged, g_averaged, b_averaged);
      averagedImage.setPixelColor(x, y, averagedColor);
    }

  return averagedImage;
}