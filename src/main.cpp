#include <sil/sil.hpp>
#include <algorithm>
#include <random.hpp>
#include <cmath>
#include <glm/gtx/matrix_transform_2d.hpp>

void only_green(sil::Image &image) // On prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void gray(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float gray = 0.29f * color.r + 0.58f * color.g + 0.11f * color.b;
        color = glm::vec3{gray, gray, gray};
    }
}

void negative(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1 - color.r;
        color.b = 1 - color.b;
        color.g = 1 - color.g;
    }
}

void degraded(sil::Image &image)
{
    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float t = static_cast<float>(x) / (width - 1);

            image.pixel(x, y) = glm::vec3{t, t, t};
        }
    }
}

void mirror(sil::Image &image)
{
    sil::Image original = image;

    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int mx = width - 1 - x;

            image.pixel(x, y) = original.pixel(mx, y);
        }
    }
}

void noise(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        if (true_with_probability(0.1f))
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

    sil::Image original = image;

    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            glm::vec3 color = original.pixel(x, y);

            // on décale le pixel rouge
            if (x + d < width)
                color.r = original.pixel(x + d, y).r;

            // et le bleu
            if (x - d >= 0)
                color.b = original.pixel(x - d, y).b;

            image.pixel(x, y) = color;
        }
    }
}

void disk(sil::Image &image)
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

void circle(sil::Image &image)
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
            int dist = dx * dx + dy * dy;

            if (dist >= Rmin * Rmin && dist <= Rmax * Rmax)
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

void circle_at(sil::Image &image, int cx, int cy, int R, int thickness)
{
    int width = image.width();
    int height = image.height();

    int Rmin = R - thickness / 2;
    int Rmax = R + thickness / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            int d2 = dx * dx + dy * dy;

            if (d2 >= Rmin * Rmin && d2 <= Rmax * Rmax)
            {
                image.pixel(x, y) = glm::vec3{1.f, 1.f, 1.f};
            }
        }
    }
}

void rosace(sil::Image &image)
{
    int width = image.width();
    int height = image.height();

    int cx = width / 2;
    int cy = height / 2;

    int N = 20;  // nb de cercles
    int r = 120; // r de la rosace
    int Rc = 80; // r de chacun des cercles
    int thickness = 4;

    for (int i = 0; i < N; i++)
    {
        float theta = 2.f * M_PI * i / N;

        int x = cx + r * std::cos(theta);
        int y = cy + r * std::sin(theta);

        circle_at(image, x, y, Rc, thickness);
    }
}

void mosaic(sil::Image &image)
{
    sil::Image original = image;

    int w = original.width();
    int h = original.height();

    int cols = 3;
    int rows = 3;

    image = sil::Image{cols * w, rows * h};

    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            int ox = x % w;
            int oy = y % h;

            image.pixel(x, y) = original.pixel(ox, oy);
        }
    }
}

void mosaic_mirror(sil::Image &image)
{
    sil::Image original = image;

    int w = original.width();
    int h = original.height();

    int cols = 5;
    int rows = 4;

    image = sil::Image{cols * w, rows * h};

    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            int ox = x % w;
            int oy = y % h;

            int cell_x = x / w;
            int cell_y = y / h;

            if ((cell_x + cell_y) % 2 == 1)
            {
                ox = w - 1 - ox; // miroir horizontal
            }

            image.pixel(x, y) = original.pixel(ox, oy);
        }
    }
}

void pixelsort(sil::Image &image)
{
    sil::Image original = image;

    int w = image.width();
    int h = image.height();

    for (int y = 0; y < h; y++)
    {
        int shift = 0;

        // pour décaler aléatoirement certaines lignes
        if (true_with_probability(0.08f))
        {
            shift = random_int(-30, 30);
        }

        for (int x = 0; x < w; x++)
        {
            int sx = x + shift;

            if (sx >= 0 && sx < w)
            {
                glm::vec3 color = original.pixel(sx, y);

                // pour un glitch de couleur améatoires 
                if (true_with_probability(0.05f))
                {
                    std::swap(color.r, color.b);
                }

                image.pixel(x, y) = color;
            }
            else
            {
                image.pixel(x, y) = glm::vec3{0.f, 0.f, 0.f};
            }
        }
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{
               glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} +
           center_of_rotation;
}

void vortex(sil::Image &image)
{
    sil::Image original = image;

    int width = image.width();
    int height = image.height();

    glm::vec2 center{
        width / 2.f, height / 2.f};

    float strength = 0.002f; // intensité du vortex

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            glm::vec2 point{x, y};

            float dist = glm::distance(point, center);

            float angle = strength * dist;

            glm::vec2 rotated_point = rotated(point, center, angle);

            int src_x = static_cast<int>(rotated_point.x);
            int src_y = static_cast<int>(rotated_point.y);

            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height)
            {
                image.pixel(x, y) = original.pixel(src_x, src_y);
            }
            else
            {
                image.pixel(x, y) = glm::vec3{0.f, 0.f, 0.f};
            }
        }
    }
}

void convolution(sil::Image &image)
{
    sil::Image original = image;

    int width = image.width();
    int height = image.height();

    // taille du carré
    int c = 1; 

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            glm::vec3 sum{0.f, 0.f, 0.f};
            int count = 0;

            //ensuite on parcourt le voisinnage, 
            for (int dy = -c; dy <= c; dy++)
            {
                for (int dx = -c; dx <= c; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        sum += original.pixel(nx, ny);
                        count++;
                    }
                }
            }

            image.pixel(x, y) = sum / static_cast<float>(count);
        }
    }
}

int main()
{
    sil::Image image{"images/logo.png"};
    // sil::Image image2{"images/logo.png"};
    // sil::Image image{500, 500};

    // EXO 1
    // only_green(image);

    // EXO 2
    // swap(image);

    // EXO 3
    // gray(image);

    // EXO 4
    // negative(image);

    // EXO 5
    // degraded(image);

    // EXO 6
    // mirror(image);

    // EXO 7
    // noise(image);

    // EXO 8
    // rgb_split(image2);

    // EXO 9
    // disk(image);

    // EXO 10
    // circle(image);

    // EXO 11
    // rosace(image);

    // EXO 12
    // mosaic(image);

    // EXO 13
    // mosaic_mirror(image);

    // EXO 14
    // pixelsort(image);

    // EXO 15
    // vortex(image);

    // EXO 16
    convolution(image);

    image.save("output/pouet.png");
    // image2.save("output/pouet.png");
}
