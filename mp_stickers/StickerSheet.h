/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
#include <tuple>
class StickerSheet
{
public:
    StickerSheet(const Image &picture, unsigned max);

    ~StickerSheet();

    StickerSheet(const StickerSheet &other);

    int addSticker(Image &sticker, unsigned x, unsigned y);

    void changeMaxStickers(unsigned max);

    Image *getSticker(unsigned index);

    const StickerSheet &operator=(const StickerSheet &other);

    void removeSticker(unsigned index);

    Image render() const;

    bool translate(unsigned index, unsigned x, unsigned y);

private:
    std::vector<std::tuple<unsigned, unsigned>> coords;
    std::vector<Image *> stickers;
    Image * baseCopy;
    unsigned max_;
};