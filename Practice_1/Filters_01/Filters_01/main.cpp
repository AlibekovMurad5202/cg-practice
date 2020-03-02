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
#include "TSharpnessFilter1.h"
#include "TSharpnessFilter2.h"
#include "TMotionBlurFilter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string imageName;
    for (int i = 0; i < argc; i++)
      if (!strcmp(argv[i], "-p") && (i + 1 < argc))
        imageName = argv[i + 1];

    QImage image;
    image.load(imageName.c_str());
    /*
    std::cout << "Copying" << std::endl;
    image.save("Images//tmp_cp.png");
    
    std::cout << "Inverting image" << std::endl;
    TInvertFilter *invert = new TInvertFilter();
    QImage inverted_image = invert->calculateNewImagePixMap(image, 0);
    inverted_image.save("Images//tmp_inv.png");
    delete invert;

    std::cout << "Blurring image" << std::endl;
    TBlurFilter *blur = new TBlurFilter();
    QImage blurred_image = blur->calculateNewImagePixMap(image, 0);
    blurred_image.save("Images//tmp_blr.png");
    delete blur;
    
    std::cout << "Gaussian blurring image" << std::endl;
    TGaussianBlurFilter *gaussian_blur = new TGaussianBlurFilter();
    QImage gaussian_blurred_image = gaussian_blur->calculateNewImagePixMap(image, 3);
    gaussian_blurred_image.save("Images//tmp_gblr.png");
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
    
    std::cout << "Sharpness1 filtering image" << std::endl;
    TSharpnessFilter1 *sharpness1 = new TSharpnessFilter1();
    QImage sharpness1_filtered_image = sharpness1->calculateNewImagePixMap(image, 0);
    sharpness1_filtered_image.save("Images//tmp_shrp1.png");
    delete sharpness1;

    std::cout << "Sharpness2 filtering image" << std::endl;
    TSharpnessFilter2 *sharpness2 = new TSharpnessFilter2();
    QImage sharpness2_filtered_image = sharpness2->calculateNewImagePixMap(image, 0);
    sharpness2_filtered_image.save("Images//tmp_shrp2.png");
    delete sharpness2;
    */
    std::cout << "Motion blurring image" << std::endl;
    TMotionBlurFilter *motion_blur = new TMotionBlurFilter();
    QImage motion_blurred_image = motion_blur->calculateNewImagePixMap(image, 
      image.width() > image.height() ? image.height() : image.width());
    motion_blurred_image.save("Images//tmp_mblr.png");
    delete motion_blur;

    return a.exec();
}