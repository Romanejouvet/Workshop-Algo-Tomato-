#include <sil/sil.hpp>
#include <random.hpp>

void keep_green_only(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void negative_image(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1 - color.r;
        color.b = 1 - color.b;
        color.g = 1 - color.g;
    }
}

void random_noise(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        if (true_with_probability(0.5f))
        {

            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);
        }
    }
}

int main()
{
    sil::Image image{"images/logo.png"};
    // sil::Image image{300,200}

    // EXO 1
     //keep_green_only(image);

    // EXO 2
    //negative_image(image);

    // EXO 3
    //random_noise(image);

    // EXO 4 


    image.save("output/pouet.png");
}
