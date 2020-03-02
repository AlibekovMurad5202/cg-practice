#include <QtCore/QCoreApplication>
#include <QImage>
#include "iostream"
#include "TInvertFilter.h"
#include "TBlurFilter.h"
#include "TGaussianBlurFilter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string imageName;
    for (int i = 0; i < argc; i++)
      if (!strcmp(argv[i], "-p") && (i + 1 < argc))
        imageName = argv[i + 1];

    QImage image;
    image.load(imageName.c_str());
    
    std::cout << "Copying" << std::endl;
    image.save("Images//tmp_cp.png");
    
    std::cout << "Inverting image" << std::endl;
    TInvertFilter *invert = new TInvertFilter();
    QImage inverted_image = invert->calculateNewImagePixMap(image, 0);
    inverted_image.save("Images//tmp_inv.png");
    delete invert;

    std::cout << "Bluring image" << std::endl;
    TBlurFilter *blur = new TBlurFilter();
    QImage blured_image = blur->calculateNewImagePixMap(image, 0);
    blured_image.save("Images//tmp_blr.png");
    delete blur;
    
    std::cout << "Gaussian bluring image" << std::endl;
    TGaussianBlurFilter *gaussian_blur = new TGaussianBlurFilter();
    QImage gaussian_blured_image = gaussian_blur->calculateNewImagePixMap(image, 3);
    gaussian_blured_image.save("Images//tmp_gblr.png");
    delete gaussian_blur;

    return a.exec();
}