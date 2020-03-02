#include <QtCore/QCoreApplication>
#include <QImage>
#include "iostream"
#include "TInvertFilter.h"
#include "TBlurFilter.h"
#include "TGaussianBlurFilter.h"
#include "TGrayScaleFilter.h"
#include "TSepiaFilter.h"
#include "TBrightnessFilter.h"
#include "TSobelYFilter.h"
#include "TSobelXFilter.h"
#include "TSharpnessFilter.h"

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

    std::cout << "Graying image" << std::endl;
    TGrayScaleFilter *gray_scale = new TGrayScaleFilter();
    QImage grayed_image = gray_scale->calculateNewImagePixMap(image, 0);
    grayed_image.save("Images//tmp_grs.png");
    delete gray_scale;

    std::cout << "Sepia image" << std::endl;
    TSepiaFilter *sepia = new TSepiaFilter();
    QImage sepia_image = sepia->calculateNewImagePixMap(image, 0);
    sepia_image.save("Images//tmp_sp.png");
    delete sepia;
    
    std::cout << "Brighting image" << std::endl;
    TBrightnessFilter *brightness = new TBrightnessFilter();
    QImage bright_image = brightness->calculateNewImagePixMap(image, 0);
    bright_image.save("Images//tmp_brt.png");
    delete brightness;
    
    std::cout << "Sobel (y) filtering image" << std::endl;
    TSobelYFilter *sobel_y = new TSobelYFilter();
    QImage sobel_y_filtered_image = sobel_y->calculateNewImagePixMap(image, 0);
    sobel_y_filtered_image.save("Images//tmp_sby.png");
    delete sobel_y;

    std::cout << "Sobel (x) filtering image" << std::endl;
    TSobelXFilter *sobel_x = new TSobelXFilter();
    QImage sobel_x_filtered_image = sobel_x->calculateNewImagePixMap(image, 0);
    sobel_x_filtered_image.save("Images//tmp_sbx.png");
    delete sobel_x;
    
    std::cout << "Sharpness filtering image" << std::endl;
    TSharpnessFilter *sharpness = new TSharpnessFilter();
    QImage sharpness_filtered_image = sharpness->calculateNewImagePixMap(image, 0);
    sharpness_filtered_image.save("Images//tmp_shrp.png");
    delete sharpness;
    
    return a.exec();
}