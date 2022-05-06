#include "Image.h"
#include "cs225/PNG.h"
#include <cmath>
#include <algorithm>

void Image::darken()
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.l <= 0.1)
            {
                pixel.l = 0;
            }
            else
            {
                pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount)
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.l <= amount)
            {
                pixel.l = 0;
            }
            else
            {
                pixel.l -= amount;
            }
        }
    }
}

void Image::desaturate()
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.s <= 0.1)
            {
                pixel.s = 0;
            }
            else
            {
                pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount)
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.s <= amount)
            {
                pixel.s = 0;
            }
            else
            {
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale()
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::illinify()
{
    int Blue = 216;
    int Orange = 11;
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //Get ref to pixel at x,y
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            //calculates distance from hue to orange val and blue val
            int noWrap = std::abs(pixel.h - Orange);
            int Wrap = std::abs(360 - pixel.h + 11);
            int chgOrange = std::min(noWrap, Wrap);
            int chgBlue = std::abs(pixel.h - Blue);
            if (chgOrange < chgBlue)
            {
                pixel.h = Orange;
            }
            else
            {
                pixel.h = Blue;
            }
            //changes to orange or blue depending on which is closer
        }
    }
}

void Image::lighten()
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.l >= 0.9)
            {
                pixel.l = 1;
            }
            else
            {
                pixel.l += 0.1;
            }
        }
    }
}

void Image::lighten(double amount)
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.l >= (1 - amount))
            {
                pixel.l = 1;
            }
            else
            {
                pixel.l += amount;
            }
        }
    }
}

void Image::rotateColor(double degrees)
{
    if (degrees >= 360)
    { //Truncates numbers above 360 to below 360
        while (degrees >= 360)
        {
            degrees -= 360;
        }
    }
    else if (degrees <= -360)
    { //Truncates numbers below -360 to above -360
        while (degrees <= -360)
            degrees += 360;
    }
    else
    {
        for (unsigned x = 0; x < this->width(); x++)
        {
            for (unsigned y = 0; y < this->height(); y++)
            {
                cs225::HSLAPixel &pixel = this->getPixel(x, y);
                if (pixel.h + degrees >= 360)
                {
                    pixel.h = (pixel.h + degrees) - 360;
                }
                else if (pixel.h + degrees < 0)
                {
                    pixel.h = (pixel.h + degrees) + 360;
                }
                else
                {
                    pixel.h += degrees;
                }
            }
        }
    }
}

void Image::saturate()
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.s >= 0.9)
            {
                pixel.s = 1;
            }
            else
            {
                pixel.s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount)
{
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            if (pixel.s >= (1 - amount))
            {
                pixel.s = 1;
            }
            else
            {
                pixel.s += amount;
            }
        }
    }
}

void Image::scale(double factor)
{
    unsigned w = unsigned(factor * this->width());
    unsigned h = unsigned(factor * this->height());
    scale(w, h);
}

void Image::scale(unsigned w, unsigned h)
{
    double xrat = (double(w) / double(this->width()));
    double yrat = (double(h) / double(this->height()));
    double fact = std::min(double(xrat), double(yrat));

    unsigned newW = unsigned(this->width() * fact);
    unsigned newH = unsigned(this->height() * fact);

    cs225::PNG temp(newW, newH);
    for (unsigned x = 0; x < newW; x++)
    {
        for (unsigned y = 0; y < newH; y++)
        {
            unsigned Xsource = int(std::round(double(x) / double(newW) * double(this->width())));
            unsigned Ysource = int(std::round(double(y) / double(newH) * double(this->height())));
            Xsource = std::min(Xsource, this->width() - 1);
            Ysource = std::min(Ysource, this->height() - 1);
            cs225::HSLAPixel &pixelSrc = this->getPixel(Xsource, Ysource);
            cs225::HSLAPixel &pixelTemp = temp.getPixel(x, y);
            pixelTemp.h = pixelSrc.h;
            pixelTemp.s = pixelSrc.s;
            pixelTemp.l = pixelSrc.l;
            pixelTemp.a = pixelSrc.a;
        }
    }
    this->resize(newW, newH);

    for (unsigned x = 0; x < newW; x++)
    {
        for (unsigned y = 0; y < newH; y++)
        {
            cs225::HSLAPixel &pixelSrc = this->getPixel(x, y);
            cs225::HSLAPixel &pixelTemp = temp.getPixel(x, y);
            pixelSrc.h = pixelTemp.h;
            pixelSrc.s = pixelTemp.s;
            pixelSrc.l = pixelTemp.l;
            pixelSrc.a = pixelTemp.a;
        }
    }
}
