#include "pixeltable.h"

PixelTable::PixelTable(int x, int y) : H(x), W(y)
{
    data = (Rgb **)malloc(H * sizeof(Rgb *));

    for (int i = 0; i < H; ++i)
    {
        data[i] = (Rgb *)malloc(W * sizeof(Rgb) + (W * 3) % 4);
    }
}
PixelTable::~PixelTable()
{
    for (int i = 0; i < H; ++i)
        free(data[i]);
    free(data);
}
Rgb*& PixelTable::operator[](int index) const
{
    return data[index];
}
PixelTable& PixelTable::operator*()
{
    return *this;
}
