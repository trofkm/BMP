#ifndef PIXELTABLE_H
#define PIXELTABLE_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <memory>

#pragma pack(push, 1)
typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack(pop)

class PixelTable
{
private:
    int H;
    int W;
    Rgb **data;
public:
    PixelTable(int x, int y);
    ~PixelTable();

    Rgb *&operator[](int index) const;
    PixelTable &operator*();

};

#endif // PIXELTABLE_H
