#include "mypicture.h"

MyPicture::MyPicture(std::string name_) : pathFrom(name_)
{
}



Bitmap::Bitmap(std::string name) : MyPicture(name)
{
    FILE *from = fopen(pathFrom.c_str(), "rb");
    fread(&picture.bfh, 1, sizeof(BitmapFileHeader), from);
    fread(&picture.bih, 1, sizeof(BitmapInfoHeader), from);
    unsigned int H = picture.bih.height;
    unsigned int W = picture.bih.width;
    tbl = std::make_unique<PixelTable>(H,W);

    for (size_t i = 0; i < H; ++i)
    {
        fread((*tbl)[i], 1, W * sizeof(Rgb) + (W * sizeof(Rgb)) % 4, from);//Changed 3 to sizeof(Rgb)
    }
    fclose(from);
}
Bitmap::~Bitmap()
{
    //delete tbl;
    //fclose(from);
    //fclose(to);
}

unsigned int Bitmap::H(){
    return this->picture.bih.height;
}
unsigned int Bitmap::W(){
    return this->picture.bih.width;
}

void Bitmap::ToMonochrome(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo)
{
    FILE *to = fopen(nameTo.c_str(), "wb");
    fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
    fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);

    int xFirstPixel = std::min(p1.first, p2.first);
    int xLastPixel = std::max(p1.first, p2.first);

    int yFirstPixel = std::min(p1.second, p2.second);
    int yLastPixel = std::max(p1.second, p2.second);
    std::cout << xFirstPixel << "-" << yFirstPixel << std::endl;
    std::cout<<xLastPixel<<"-"<<yLastPixel<<std::endl;
    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;

    for (int i = xFirstPixel; i < xLastPixel + 1; ++i)//It doesn't work
    {

        for (int k = yFirstPixel; k < yLastPixel + 1; ++k)
        {
            std::cout<<i<<"-"<<k<<std::endl;
            int sr = ((*tbl)[i][k].r + (*tbl)[i][k].g + (*tbl)[i][k].b) / 3;
            if (sr < 96)
            {
                 (*tbl)[k][i].r = 0;
                 (*tbl)[k][i].g = 0;
                 (*tbl)[k][i].b = 0;
            }
            else
            {
                (*tbl)[k][i].r = 255;
                (*tbl)[k][i].g = 255;
                (*tbl)[k][i].b = 255;
            }
        }
    }
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}
void Bitmap::DrawVecror(std::pair<int, int> p1, std::pair<int, int> p2){}//First fix ToMonochrome
