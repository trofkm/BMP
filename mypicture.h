#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <pixeltable.h>

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


class Bitmap
{

    typedef struct
    {
        BitmapFileHeader bfh;
        BitmapInfoHeader bih;
    } Bmp;


    std::string pathFrom;
public:
    Bmp picture;
    std::unique_ptr<PixelTable> tbl;
    Bitmap(std::string name);
    ~Bitmap();
    unsigned int H()const;
    unsigned int W()const;
    std::string getFilename()const;
    void setFilename(std::string);
    void ToMonochrome(std::pair<int, int>, std::pair<int, int>, std::string = "out.bmp");
    void InverseColors(std::pair<int, int>, std::pair<int, int>, std::string = "out.bmp");
    void DrawVector(std::pair<int, int>, std::pair<int, int>, Rgb, int = 1, std::string = "out.bmp");
    void DrawLine(std::pair<int, int>, std::pair<int, int>, Rgb, std::string = "out.bmp");
    void CutImage(int , std::string = "out.bmp");
    void AddBackground(Rgb, int, std::string ="out.bmp");
    void SaveImage(std::string);
    void SearchWhiteArea(std::string = "out.bmp");
    void CutArea(std::pair<int, int>, std::pair<int, int>, std::string  = "out.bmp");

};

extern std::unique_ptr<Bitmap>bmp;
extern int mode;
extern Rgb color;

#endif // MYPICTURE_H
