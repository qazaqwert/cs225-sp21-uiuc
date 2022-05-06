#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    max_ = max;
    stickers = std::vector<Image *>();
    coords = std::vector<std::tuple<unsigned, unsigned>>();

    baseCopy = new Image();
    baseCopy->resize(picture.width(), picture.height());
    for (unsigned x = 0; x < picture.width(); x++)
    {
        for (unsigned y = 0; y < picture.height(); y++)
        {
            cs225::HSLAPixel pixelTemp = picture.getPixel(x, y);
            cs225::HSLAPixel &pixelSrc = baseCopy->getPixel(x, y);
            pixelSrc.h = pixelTemp.h;
            pixelSrc.s = pixelTemp.s;
            pixelSrc.l = pixelTemp.l;
            pixelSrc.a = pixelTemp.a;
        }
    }
}

StickerSheet::~StickerSheet()
{
    stickers = std::vector<Image *>();
    coords = std::vector<std::tuple<unsigned, unsigned>>();

    delete baseCopy;
}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other)
{
    max_ = other.max_;
    delete baseCopy;
    stickers = std::vector<Image *>();
    coords = std::vector<std::tuple<unsigned, unsigned>>();
    //put new base image into old base iamge
    baseCopy = new Image();
    baseCopy->resize(other.baseCopy->width(), other.baseCopy->height());
    for (unsigned x = 0; x < other.baseCopy->width(); x++)
    {
        for (unsigned y = 0; y < other.baseCopy->height(); y++)
        {
            cs225::HSLAPixel &pixelTemp = other.baseCopy->getPixel(x, y);
            cs225::HSLAPixel &pixelSrc = baseCopy->getPixel(x, y);

            pixelSrc.h = pixelTemp.h;
            pixelSrc.s = pixelTemp.s;
            pixelSrc.l = pixelTemp.l;
            pixelSrc.a = pixelTemp.a;
        }
    }
    //put new coords into old coords
    for (std::tuple<unsigned, unsigned> pt : other.coords)
    {
        std::tuple<unsigned, unsigned> Adding(std::get<0>(pt), std::get<1>(pt));
        coords.push_back(Adding);
    }
    //put new stickers into old stickers
    for (Image *point : other.stickers)
    {
        stickers.push_back(point);
    }
    return (*this);
}

StickerSheet::StickerSheet(const StickerSheet &other)
{
    max_ = other.max_;
    coords = std::vector<std::tuple<unsigned, unsigned>>();
    stickers = std::vector<Image *>();
    //copy base image

    baseCopy = new Image();
    baseCopy->resize(other.baseCopy->width(), other.baseCopy->height());
    for (unsigned x = 0; x < other.baseCopy->width(); x++)
    {
        for (unsigned y = 0; y < other.baseCopy->height(); y++)
        {
            cs225::HSLAPixel &pixelTemp = other.baseCopy->getPixel(x, y);
            cs225::HSLAPixel &pixelSrc = baseCopy->getPixel(x, y);

            pixelSrc.h = pixelTemp.h;
            pixelSrc.s = pixelTemp.s;
            pixelSrc.l = pixelTemp.l;
            pixelSrc.a = pixelTemp.a;
        }
    }
    //copy coords

    for (std::tuple<unsigned, unsigned> pt : other.coords)
    {
        std::tuple<unsigned, unsigned> Adding(std::get<0>(pt), std::get<1>(pt));
        coords.push_back(Adding);
    }
    //copy stickers

    for (Image *point : other.stickers)
    {
        stickers.push_back(point);
    }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
    //Need to add sticker at lowest possible spot in sticker vector
    //Need to add coords at same indice as sticker vector in coords vector
    if (x < 0)
    {
        return (-1);
    }
    if (y < 0)
    {
        return (-1);
    }
    if (stickers.size() < max_)
    {
        std::tuple<unsigned, unsigned> Adding(x, y);
        coords.push_back(Adding);
        stickers.push_back(&sticker);

        return stickers.size() - 1;
    }
    return (-1);
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    if (max >= max_)
    {
        max_ = max;
    }
    if (max < max_)
    {
        for (unsigned m = max; m <= max_; m++)
        {
            this->removeSticker(max);
        }
        max_ = max;
    }
}

Image *StickerSheet::getSticker(unsigned index)
{
    if (index < 0)
    {
        return (NULL);
    }
    else if (index >= stickers.size())
    {
        return (NULL);
    }
    else
    {
        return stickers[index];
    }
}

void StickerSheet::removeSticker(unsigned index)
{
    if (index >= stickers.size())
    {
        return;
    }
    if (index < 0)
    {
        return;
    }
    {
        stickers.erase(index + stickers.begin());
        coords.erase(index + coords.begin());
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if (index >= stickers.size())
    {
        return (false);
    }
    else if (index < 0)
    {
        return (false);
    }
    else if (stickers[index] == NULL)
    {
        return (false);
    }
    else if (index > max_)
    {
        return (false);
    }
    else
    {
        std::get<1>(coords[index]) = y;
        std::get<0>(coords[index]) = x;
        return (true);
    }
}

Image StickerSheet::render() const
{
    Image final;                                         //make new image
    final.resize(baseCopy->width(), baseCopy->height()); //just set it to initial bounds for now, later gonna have to check if each stickers goes oob

    for (unsigned x = 0; x < baseCopy->width(); x++) //copy over original image to this new final image that is actually getting rendered
    {
        for (unsigned y = 0; y < baseCopy->height(); y++)
        {
            cs225::HSLAPixel &pixelSrc = final.getPixel(x, y);
            cs225::HSLAPixel &pixelTemp = baseCopy->getPixel(x, y);

            pixelSrc.h = pixelTemp.h;
            pixelSrc.s = pixelTemp.s;
            pixelSrc.l = pixelTemp.l;
            pixelSrc.a = pixelTemp.a;
        }
    }
    //go through and find if you need to expand the image borders based on the stickers
    //based? Based on what?
    //Astolfo Monster Cock
    for (unsigned n = 0; n < stickers.size(); n++)
    {
        unsigned why = stickers[n]->height() + std::get<1>(coords[n]);
        unsigned ecks = stickers[n]->width() + std::get<0>(coords[n]);
        if (why > final.height())
        {
            final.resize(final.width(), why);
        }
        if (ecks > final.width())
        {
            final.resize(ecks, final.height());
        }
    }
    for (unsigned n = 0; n < stickers.size(); n++)
    {
        unsigned Ystrt = std::get<1>(coords[n]);
        unsigned Xstrt = std::get<0>(coords[n]);

        for (unsigned x = 0; x < stickers[n]->width(); x++)
        {
            for (unsigned y = 0; y < stickers[n]->height(); y++)
            {
                cs225::HSLAPixel &stix = stickers[n]->getPixel(x, y);
                cs225::HSLAPixel &based = final.getPixel(Xstrt + x, Ystrt + y);

                if (stix.a == 0)
                {
                    continue;
                }
                based.h = stix.h; 
                based.s = stix.s; 
                based.l = stix.l; 
                based.a = stix.a; 
            }
        }
    }
    return (final);
}