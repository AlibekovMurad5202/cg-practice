#include <QtCore/QCoreApplication>
#include <QImage>

#include "Filters.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QImage image;
    std::string image_path;

    INFO("Prepare input data");
    for (int i = 0; i < argc; i++)
      if (!strcmp(argv[i], "-i") && (i + 1 < argc))
        image_path = argv[i + 1];
    if (image.load(QString(image_path.c_str())))
      INFO("Image loaded");
    else
    {
      ERROR("Failed to load image");
      return app.exec();
    }
    std::cout << std::endl;

    
    INFO("Saving image");
    if (image.save("Results//copy_image.jpg"))
      RESULT("Result image was saved to [ Results/copy_image.jpg ]");
    else
      ERROR("Failed to save image");
    std::cout << std::endl;


    INFO("Applying the filter \"Invertion\"");
    TInvertFilter* invertion_filter = new TInvertFilter();
    QImage inverted_image = invertion_filter->calculateNewImagePixMap(image);
    if (inverted_image.save("Results//inverted_image.jpg"))
      RESULT("Result image was saved to [ Results/inverted_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete invertion_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Gray Scale\"");
    TGrayScaleFilter* gray_scale_filter = new TGrayScaleFilter();
    QImage gray_scale_image = gray_scale_filter->calculateNewImagePixMap(image);
    if (gray_scale_image.save("Results//gray_scale_image.jpg"))
      RESULT("Result image was saved to [ Results/gray_scale_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete gray_scale_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Sepia\"");
    TSepiaFilter* sepia_filter = new TSepiaFilter();
    QImage sepia_image = sepia_filter->calculateNewImagePixMap(image);
    if (sepia_image.save("Results//sepia_image.jpg"))
      RESULT("Result image was saved to [ Results/sepia_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete sepia_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Brightness\"");
    TBrightnessFilter* brightness_filter = new TBrightnessFilter();
    QImage brightness_image = brightness_filter->calculateNewImagePixMap(image);
    if (brightness_image.save("Results//brightness_image.jpg"))
      RESULT("Result image was saved to [ Results/brightness_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete brightness_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Median\"");
    TMedianFilter* median_filter = new TMedianFilter();
    QImage median_image = median_filter->calculateNewImagePixMap(image);
    if (median_image.save("Results//median_image.jpg"))
      RESULT("Result image was saved to [ Results/median_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete median_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Maximum\"");
    TMaximumFilter* maximum_filter = new TMaximumFilter();
    QImage maximum_image = maximum_filter->calculateNewImagePixMap(image);
    if (maximum_image.save("Results//maximum_image.jpg"))
      RESULT("Result image was saved to [ Results/maximum_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete maximum_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Minimum\"");
    TMinimumFilter* minimum_filter = new TMinimumFilter();
    QImage minimum_image = minimum_filter->calculateNewImagePixMap(image);
    if (minimum_image.save("Results//minimum_image.jpg"))
      RESULT("Result image was saved to [ Results/minimum_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete minimum_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Rotation\"");
    TRotationFilter* rotation_filter = new TRotationFilter(30., 0, 0);
    QImage rotated_image = rotation_filter->calculateNewImagePixMap(image);
    if (rotated_image.save("Results//rotated_image.jpg"))
      RESULT("Result image was saved to [ Results/rotated_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete rotation_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Vertical Shift\"");
    TVerticalShiftFilter* vshift_filter = new TVerticalShiftFilter(50.);
    QImage vshift_image = vshift_filter->calculateNewImagePixMap(image);
    if (vshift_image.save("Results//vshift_image.jpg"))
      RESULT("Result image was saved to [ Results/vshift_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete vshift_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Horizontal Shift\"");
    THorizontalShiftFilter* hshift_filter = new THorizontalShiftFilter(50.);
    QImage hshift_image = hshift_filter->calculateNewImagePixMap(image);
    if (hshift_image.save("Results//hshift_image.jpg"))
      RESULT("Result image was saved to [ Results/hshift_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete hshift_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Blur\"");
    TBlurFilter* blur_filter = new TBlurFilter();
    QImage blured_image = blur_filter->calculateNewImagePixMap(image);
    if (blured_image.save("Results//blured_image.jpg"))
      RESULT("Result image was saved to [ Results/blured_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete blur_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Gaussian Blur\"");
    TGaussianBlurFilter* gblur_filter = new TGaussianBlurFilter();
    QImage gblured_image = gblur_filter->calculateNewImagePixMap(image);
    if (gblured_image.save("Results//gblured_image.jpg"))
      RESULT("Result image was saved to [ Results/gblured_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete gblur_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Sobel's Filter (on the Y axis)\"");
    TSobelYFilter* sobel_x_filter = new TSobelYFilter();
    QImage sobel_x_image = sobel_x_filter->calculateNewImagePixMap(image);
    if (sobel_x_image.save("Results//sobel_x_image.jpg"))
      RESULT("Result image was saved to [ Results/sobel_x_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete sobel_x_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Sobel's Filter (on the X axis)\"");
    TSobelXFilter* sobel_y_filter = new TSobelXFilter();
    QImage sobel_y_image = sobel_y_filter->calculateNewImagePixMap(image);
    if (sobel_y_image.save("Results//sobel_y_image.jpg"))
      RESULT("Result image was saved to [ Results/sobel_y_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete sobel_y_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Sharpness Increase\"");
    TSharpnessIncreaseFilter* sharp_inc_filter = new TSharpnessIncreaseFilter();
    QImage sharp_inc_image = sharp_inc_filter->calculateNewImagePixMap(image);
    if (sharp_inc_image.save("Results//sharp_inc_image.jpg"))
      RESULT("Result image was saved to [ Results/sharp_inc_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete sharp_inc_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Motion Blur\"");
    TMotionBlurFilter* motion_blur_filter = new TMotionBlurFilter();
    QImage mblur_image = motion_blur_filter->calculateNewImagePixMap(image);
    if (mblur_image.save("Results//mblur_image.jpg"))
      RESULT("Result image was saved to [ Results/mblur_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete motion_blur_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Sharpness\"");
    TSharpnessFilter* sharpness_filter = new TSharpnessFilter();
    QImage sharp_image = sharpness_filter->calculateNewImagePixMap(image);
    if (sharp_image.save("Results//sharp_image.jpg"))
      RESULT("Result image was saved to [ Results/sharp_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete sharpness_filter;
    std::cout << std::endl;

    
    INFO("Applying the filter \"Vertical Waves\"");
    TVerticalWaveFilter* vwave_filter = new TVerticalWaveFilter();
    QImage vwave_image = vwave_filter->calculateNewImagePixMap(image);
    if (vwave_image.save("Results//vwave_image.jpg"))
      RESULT("Result image was saved to [ Results/vwave_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete vwave_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Horizontal Waves\"");
    THorizontalWaveFilter* hwave_filter = new THorizontalWaveFilter();
    QImage hwave_image = hwave_filter->calculateNewImagePixMap(image);
    if (hwave_image.save("Results//hwave_image.jpg"))
      RESULT("Result image was saved to [ Results/hwave_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete hwave_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Linear Correction\"");
    TLinearCorrectionFilter* lin_corr_filter = new TLinearCorrectionFilter();
    QImage lin_corr_image = lin_corr_filter->calculateNewImagePixMap(image);
    if (lin_corr_image.save("Results//lin_corr_image.jpg"))
      RESULT("Result image was saved to [ Results/lin_corr_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete lin_corr_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Gamma Correction\"");
    TGammaCorrectionFilter* gamma_corr_filter = new TGammaCorrectionFilter(1.1, 1.1);
    QImage gamma_corr_image = gamma_corr_filter->calculateNewImagePixMap(image);
    if (gamma_corr_image.save("Results//gamma_corr_image.jpg"))
      RESULT("Result image was saved to [ Results/gamma_corr_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete gamma_corr_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Perfect Reflector\"");
    TPerfectReflectorFilter* p_refl_filter = new TPerfectReflectorFilter();
    QImage p_refl_image = p_refl_filter->calculateNewImagePixMap(image);
    if (p_refl_image.save("Results//p_refl_image.jpg"))
      RESULT("Result image was saved to [ Results/p_refl_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete p_refl_filter;
    std::cout << std::endl;

    
    INFO("Applying the filter \"Glass\"");
    TGlassFilter* glass_filter = new TGlassFilter();
    QImage glass_image = glass_filter->calculateNewImagePixMap(image);
    if (glass_image.save("Results//glass_image.jpg"))
      RESULT("Result image was saved to [ Results/glass_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete glass_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Luminous Edges\"");
    TLuminousEdgesFilter* lumin_edges_filter = new TLuminousEdgesFilter();
    QImage lumin_edges_image = lumin_edges_filter->calculateNewImagePixMap(image);
    if (lumin_edges_image.save("Results//lumin_edges_image.jpg"))
      RESULT("Result image was saved to [ Results/lumin_edges_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete lumin_edges_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Gray World\"");
    TGrayWorldFilter* gray_world_filter = new TGrayWorldFilter();
    QImage gray_world_image = gray_world_filter->calculateNewImagePixMap(image);
    if (gray_world_image.save("Results//gray_world_image.jpg"))
      RESULT("Result image was saved to [ Results/gray_world_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete gray_world_filter;
    std::cout << std::endl;


    std::string mask_filename;
    std::cout << "By default, the mask [ default_morphological_mask.msk ] will be used." << std::endl;
    std::cout << "Do you want to change mask? [y/n] ";
    char answer;
    std::cin >> answer;
    if (answer == 'n')
      mask_filename = "Resources//masks//default_morphological_mask.msk";
    else if (answer == 'y')
    {
      std::cout << "Enter name of file with new mask";
      std::cout << "(with path, if *.msk isn't located in current directory)." << std::endl;
      std::cout << "Path: ";
      std::cin  >> mask_filename;
    }
    else
    {
      std::cout << "What did I do to you, to suffer like this?" << std::endl;
      ERROR("The programm burst into tears");
      return app.exec();
    }


    TMask mask(mask_filename);
    std::cout << std::endl;
    INFO("The mask [ " << mask_filename << " ] will be used.");
    std::cout << std::endl;


    INFO("Applying the filter \"Dilation\"");
    TDilationFilter* dilation_filter = new TDilationFilter(mask);
    QImage dilation_image = dilation_filter->calculateNewImagePixMap(image);
    if (dilation_image.save("Results//dilation_image.jpg"))
      RESULT("Result image was saved to [ Results/gray_world_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete dilation_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Erosion\"");
    TErosionFilter* erosion_filter = new TErosionFilter(mask);
    QImage erosion_image = erosion_filter->calculateNewImagePixMap(image);
    if (erosion_image.save("Results//erosion_image.jpg"))
      RESULT("Result image was saved to [ Results/erosion_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete erosion_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Opening\"");
    TOpeningFilter* opening_filter = new TOpeningFilter(mask);
    QImage opening_image = opening_filter->calculateNewImagePixMap(image);
    if (opening_image.save("Results//opening_image.jpg"))
      RESULT("Result image was saved to [ Results/opening_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete opening_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Closing\"");
    TClosingFilter* closing_filter = new TClosingFilter(mask);
    QImage closing_image = closing_filter->calculateNewImagePixMap(image);
    if (closing_image.save("Results//closing_image.jpg"))
      RESULT("Result image was saved to [ Results/closing_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete closing_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Grad\"");
    TGradFilter* grad_filter = new TGradFilter(mask);
    QImage grad_image = grad_filter->calculateNewImagePixMap(image);
    if (grad_image.save("Results//grad_image.jpg"))
      RESULT("Result image was saved to [ Results/grad_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete grad_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Top Hat\"");
    TTopHatFilter* top_hat_filter = new TTopHatFilter(mask);
    QImage top_hat_image = top_hat_filter->calculateNewImagePixMap(image);
    if (top_hat_image.save("Results//top_hat_image.jpg"))
      RESULT("Result image was saved to [ Results/top_hat_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete top_hat_filter;
    std::cout << std::endl;


    INFO("Applying the filter \"Black Hat\"");
    TBlackHatFilter* black_hat_filter = new TBlackHatFilter(mask);
    QImage black_hat_image = black_hat_filter->calculateNewImagePixMap(image);
    if (black_hat_image.save("Results//black_hat_image.jpg"))
      RESULT("Result image was saved to [ Results/black_hat_image.jpg ]");
    else
      ERROR("Failed to save image");
    delete black_hat_filter;
    std::cout << std::endl;
    

    INFO("All filters were applied to the image [ " << image_path << " ]");
    INFO("All result images were saved in the directory [ Results ]");

    return app.exec();
}