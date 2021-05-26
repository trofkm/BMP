#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <pixeltable.h>

class MyPicture
{
protected:
    std::string pathFrom;

public:
    MyPicture(std::string name_);
    virtual void ToMonochrome(std::pair<int, int> , std::pair<int, int> , std::string  = "out.bmp") {}
    virtual void DrawVector(std::pair<int, int>, std::pair<int, int> , Rgb , int  = 1, std::string  = "out.bmp") {}
    virtual void DrawLine(std::pair<int, int> , std::pair<int, int> , Rgb , std::string  = "out.bmp") {}
    virtual void InverseColors(std::pair<int, int> , std::pair<int, int> , std::string  = "out.bmp") {}
    virtual void IncreaseImage(int , std::string ="out.bmp"){}
    virtual void AddBackground(Rgb , int , std::string ="out.bmp"){}
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
    std::unique_ptr<PixelTable> tbl;

public:
    Bitmap(std::string name);
    ~Bitmap();
    unsigned int H()const;
    unsigned int W()const;
    std::string getFilename()const;
    void setFilename(std::string);
    void ToMonochrome(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo = "out.bmp") override;
    void InverseColors(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo = "out.bmp") override;
    void DrawVector(std::pair<int, int> p1, std::pair<int, int> p2, Rgb color, int count = 1, std::string nameTo = "out.bmp")override;
    void DrawLine(std::pair<int, int> p1, std::pair<int, int> p2, Rgb color, std::string nameTo = "out.bmp")override;
    void IncreaseImage(int mode, std::string nameTo="out.bmp")override;
    void AddBackground(Rgb color, int mode, std::string nameTo="out.bmp")override;

};

extern std::unique_ptr<Bitmap>bmp;
extern int mode;
extern Rgb color;

#endif // MYPICTURE_H
