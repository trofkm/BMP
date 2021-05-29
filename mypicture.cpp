#include "mypicture.h"



Bitmap::Bitmap(std::string name) : pathFrom(name)
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
}

unsigned int Bitmap::H()const{
    return this->picture.bih.height;
}
unsigned int Bitmap::W()const{
    return this->picture.bih.width;
}
std::string Bitmap::getFilename()const{
    return pathFrom;
}

void Bitmap::setFilename(std::string newPath){
    pathFrom = newPath;
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

    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;

    for (int y = yFirstPixel; y < yLastPixel + 1; ++y)
    {

        for (int x = xFirstPixel; x < xLastPixel + 1; ++x)
        {
            int sr = ((*tbl)[y][x].r + (*tbl)[y][x].g + (*tbl)[y][x].b) / 3;
            (*tbl)[y][x].r = sr;
            (*tbl)[y][x].g = sr;
            (*tbl)[y][x].b = sr;
        }
    }
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}

void Bitmap::InverseColors(std::pair<int, int> p1, std::pair<int, int> p2, std::string nameTo) {
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
            (*tbl)[k][i].r = 255-(*tbl)[k][i].r;
            (*tbl)[k][i].g = 255-(*tbl)[k][i].g;
            (*tbl)[k][i].b = 255-(*tbl)[k][i].b;
        }
    }
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);

}

void Bitmap::DrawLine(std::pair<int, int> p1, std::pair<int, int> p2, Rgb color, std::string nameTo)
{
    FILE *to = fopen(nameTo.c_str(), "wb");
    fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
    fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
    int x1 = p1.first;
    int x2 = p2.first;
    int y1 = p1.second;
    int y2 = p2.second;

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    if (y2 >= 0 && y2 < picture.bih.height && x2 >= 0 && x2 < picture.bih.width)
        (*tbl)[y2][x2] = color;
    while (x1 != x2 || y1 != y2)
    {
        if (y1 >= 0 && y1 < picture.bih.height && x1 >= 0 && x1 < picture.bih.width)
            (*tbl)[y1][x1] = color;
        int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }

    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}



void Bitmap::DrawVector(std::pair<int, int> p1, std::pair<int, int> p2, Rgb color, int count, std::string nameTo){

    DrawLine(p1, p2, color,nameTo);
    if(count==1)
        return;

    int default1,default2;
    if (abs(p1.first - p2.first) <= (abs(p1.second - p2.second)))
    {
        default1 = p1.first;
        default2 = p2.first;
        for (int i = 0; i < count/2; ++i)
        {
            p1.first++;
            p2.first++;
            DrawLine(p1, p2, color,nameTo);
        }
        p1.first = default1;
        p2.first = default2;
        for(int i = count/2;i<count;++i){
            p1.first--;
            p2.first--;
            DrawLine(p1, p2, color,nameTo);
        }
    }
    else
    {
        default1 = p1.second;
        default2 = p2.second;
        for (int i = 0; i < count/2; ++i)
        {
            p1.second++;
            p2.second++;
            DrawLine(p1, p2, color,nameTo);
        }
        p1.second = default1;
        p2.second = default2;
        for(int i = count/2;i<count;++i){
            p1.second--;
            p2.second--;
            DrawLine(p1, p2, color,nameTo);
        }
    }
}
void Bitmap::CutImage(int mode, std::string nameTo)
{
    FILE *to = fopen(nameTo.c_str(), "wb");
    auto Smalltbl =std::make_unique<PixelTable>(picture.bih.height/2, picture.bih.width/2);
    fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);

    if (mode == 1)
    {
        picture.bih.width = picture.bih.width/2;
        picture.bih.height = picture.bih.height/2;
        for(size_t y = 0;y<picture.bih.height;++y){
            for(size_t x = 0;x<picture.bih.width;++x){
                (*Smalltbl)[y][x] = (*tbl)[y][x];
            }
        }


        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);


    }
    else if (mode == 2)
    {
        unsigned int heighUntil = picture.bih.height-picture.bih.height%2;
        picture.bih.width = picture.bih.width / 2;
        picture.bih.height = picture.bih.height / 2;

        for(size_t y = picture.bih.height;y<heighUntil;++y){
            for(size_t x = 0;x<picture.bih.width;++x){
                (*Smalltbl)[y-picture.bih.height][x] = (*tbl)[y][x];
            }
        }
        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);


    }
    else if (mode == 3)
    {
        unsigned int heighUntil = picture.bih.height-picture.bih.height%2;
        picture.bih.width = picture.bih.width / 2;
        picture.bih.height = picture.bih.height / 2;

        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);

        for (size_t y = picture.bih.height; y < heighUntil; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {
                (*Smalltbl)[y-picture.bih.height][i] = (*tbl)[y][i + picture.bih.width];
            }
        }

    }
    else if (mode == 4)
    {
        picture.bih.width = picture.bih.width / 2;
        picture.bih.height = picture.bih.height / 2;

        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);

        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {
                (*Smalltbl)[y][i] = (*tbl)[y][i + picture.bih.width];
            }
        }

    }
    else if (mode == 5)
    {
        picture.bih.width = picture.bih.width / 2;
        picture.bih.height = picture.bih.height / 2;

        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
        for (size_t y = picture.bih.height / 2; y < (picture.bih.height + picture.bih.height / 2); ++y)
        {
            for (size_t i = picture.bih.width / 2; i < (picture.bih.width + picture.bih.width / 2); ++i)
            {
                (*Smalltbl)[y-picture.bih.height / 2][i-picture.bih.width / 2] = (*tbl)[y][i];
            }
        }



    }
    tbl = std::move(Smalltbl);
    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}
void Bitmap::AddBackground(Rgb color, int mode, std::string nameTo)//Have some errors when using this function more then once
{
    FILE *to = fopen(nameTo.c_str(), "wb");
    picture.bih.width = picture.bih.width * 2;
    picture.bih.height = picture.bih.height * 2;
    fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
    fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
    auto Bigtbl = std::make_unique<PixelTable>(picture.bih.height, picture.bih.width);
    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
    if (mode == 5)
    {
        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {

                if (y >= picture.bih.height / 4 && i >= picture.bih.width / 4 && y <picture.bih.height / 4 + picture.bih.height / 2 && i < picture.bih.width / 2 + picture.bih.width / 4)
                    (*Bigtbl)[y][i] = (*tbl)[y - (int)picture.bih.height / 4][i - picture.bih.width / 4];
                else
                    (*Bigtbl)[y][i] = color;
            }
        }
    }
    else if (mode == 1)
    {
        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {

                if (y < picture.bih.height / 2 && i < picture.bih.width / 2)
                    (*Bigtbl)[y][i] = (*tbl)[y][i];
                else
                    (*Bigtbl)[y][i] = color;
            }
        }
    }
    else if (mode == 2)
    {
        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {

                if (y >= picture.bih.height / 2 && i < picture.bih.width / 2)
                    (*Bigtbl)[y][i] = (*tbl)[y - picture.bih.height / 2][i];
                else
                    (*Bigtbl)[y][i] = color;
            }
        }
    }
    else if (mode == 3)
    {
        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {

                if (y >= picture.bih.height / 2 && i >= picture.bih.width / 2)
                    (*Bigtbl)[y][i] = (*tbl)[y - picture.bih.height / 2][i - picture.bih.width / 2];
                else
                    (*Bigtbl)[y][i] = color;
            }
        }
    }
    else if (mode == 4)
    {
        for (size_t y = 0; y < picture.bih.height; ++y)
        {
            for (size_t i = 0; i < picture.bih.width; ++i)
            {

                if (i >= picture.bih.width / 2 && y < picture.bih.height / 2 )
                    (*Bigtbl)[y][i] = (*tbl)[y ][i - picture.bih.width / 2];
                else
                    (*Bigtbl)[y][i] = color;
            }
        }
    }

    tbl = std::move(Bigtbl);
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}

void Bitmap::SaveImage(std::string savePath){
    FILE *to = fopen(savePath.c_str(), "wb");
    fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
    fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
    unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
    for (size_t i = 0; i < picture.bih.height; ++i)
    {
        fwrite((*tbl)[i], 1, w, to);
    }
    fclose(to);
}


std::unique_ptr<Bitmap>bmp;
int mode;
Rgb color;
