#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <pixeltable.h>

class MyPicture
{
protected:
    std::string pathFrom;

public:
    MyPicture(std::string name_);
    virtual void ToMonochrome(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo)=0;
    virtual void DrawVecror(std::pair<int, int> p1, std::pair<int, int> p2)=0;
};


class Bitmap : public MyPicture
{
#pragma pack(push, 1)
    typedef struct
    {
        unsigned short signature;
        unsigned int filesize;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int pixelArrOffset;
    } BitmapFileHeader;
    typedef struct
    {
        unsigned int headerSize;
        unsigned int width;
        unsigned int height;
        unsigned short planes;
        unsigned short bitsPerPixel;
        unsigned int compression;
        unsigned int imageSize;
        unsigned int xPixelsPerMeter;
        unsigned int yPixelsPerMeter;
        unsigned int colorsInColorTable;
        unsigned int importantColorCount;
    } BitmapInfoHeader;
#pragma pack(pop)
    typedef struct
    {
        BitmapFileHeader bfh;
        BitmapInfoHeader bih;
    } Bmp;
    Bmp picture;
    //PixelTable *tbl;
    std::unique_ptr<PixelTable> tbl;

public:
    Bitmap(std::string name);
    ~Bitmap();
    unsigned int H();
    unsigned int W();
    void ToMonochrome(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo = "out.bmp") override;
    void DrawVecror(std::pair<int, int> p1, std::pair<int, int> p2) override;


};

#endif // MYPICTURE_H
