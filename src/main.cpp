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

void rgb_split(sil::Image &image)
{
    const int d = 15; // pour le décalade

    sil::Image original = image; // on copie l'image

    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            glm::vec3 color = original.pixel(x, y);

            // décaler le pixel rouge
            if (x + d < width)
                color.r = original.pixel(x + d, y).r;

            // décaler le pixel bleu
            if (x - d >= 0)
                color.b = original.pixel(x - d, y).b;

            // Vert : on garde celui du pixel actuel

            image.pixel(x, y) = color;
        }
    }
}

void draw_disk(sil::Image &image)
{
    int width = image.width();
    int height = image.height();

    int cx = width / 2;
    int cy = height / 2;
    int R = 200;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            if (dx * dx + dy * dy <= R * R)
            {
                image.pixel(x, y) = glm::vec3{1.f, 1.f, 1.f}; // blanc
            }
            else
            {
                image.pixel(x, y) = glm::vec3{0.f, 0.f, 0.f}; // noir
            }
        }
    }
}

void draw_circle(sil::Image &image)
{
    int width = image.width();
    int height = image.height();

    int cx = width / 2;
    int cy = height / 2;

    int R = 200;
    int thickness = 10;

    int Rmin = R - thickness / 2;
    int Rmax = R + thickness / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            int dist2 = dx * dx + dy * dy;

            if (dist2 >= Rmin * Rmin && dist2 <= Rmax * Rmax)
            {
                image.pixel(x, y) = glm::vec3{1.f, 1.f, 1.f}; // blanc
            }
            else
            {
                image.pixel(x, y) = glm::vec3{0.f, 0.f, 0.f}; // noir
            }
        }
    }
}



int main()
{
    // sil::Image image{"images/logo.png"};
    // sil::Image image2{"images/logo.png"};
    // sil::Image image{300,200};
    sil::Image image{500, 500};

    // EXO 1
    // keep_green_only(image);

    // EXO 2
    // negative_image(image);

    // EXO 3
    // random_noise(image);

    // EXO 4
    // rgb_split(image2);

    // EXO 5
    // draw_disk(image);

    // EXO 6
    draw_circle(image);

   


    image.save("output/pouet.png");
    // image2.save("output/pouet.png");
}
