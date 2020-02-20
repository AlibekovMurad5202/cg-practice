#include <QtCore/QCoreApplication>
#include "Filters.h"
#include "iostream"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QImage image;

  if (!image.load("Images//apples.jpg", "jpg"))
  {
    std::cout << "Image upload failed!";
    return a.exec();
  }

  Inversion(image).save("Images//inverted_apples.jpg", "jpg");
  Averaging(image).save("Images//averaged_apples.jpg", "jpg");

  Inversion(Inversion(image)).save("Images//normal_apples.jpg", "jpg");

  return a.exec();
}