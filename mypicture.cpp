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
        if (y2 >= 0 && y2 < this->picture.bih.height && x2 >= 0 && x2 < this->picture.bih.width)
            (*tbl)[y2][x2] = color;
        while (x1 != x2 || y1 != y2)
        {
            if (y1 >= 0 && y1 < this->picture.bih.height && x1 >= 0 && x1 < this->picture.bih.width)
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

        for (int i = 0; i < picture.bih.height; ++i)
        {
            fwrite((*tbl)[i], 1, w, to);
        }
        fclose(to);
    }



void Bitmap::DrawVector(std::pair<int, int> p1, std::pair<int, int> p2, Rgb color, int count, std::string nameTo){
    if (abs(p1.first - p2.first) <= (abs(p1.second - p2.second)))
    {

        for (int i = 0; i < count; ++i)
        {
            p1.first++;
            p2.first++;
            DrawLine(p1, p2, color,nameTo);
        }
    }
    else
    {

        for (int i = 0; i < count; ++i)
        {
            p1.second++;
            p2.second++;
            DrawLine(p1, p2, color,nameTo);
        }
    }
}
void Bitmap::IncreaseImage(int mode, std::string nameTo)
    {
        FILE *to = fopen(nameTo.c_str(), "wb");
        if (mode == 1)
        {
            this->picture.bih.width = this->picture.bih.width / 2;
            this->picture.bih.height = this->picture.bih.height / 2;
            fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
            for (size_t i = 0; i < picture.bih.height; ++i)
            {
                fwrite((*tbl)[i], 1, w, to);
            }
            fclose(to);
        }
        else if (mode == 2)
        {
            unsigned int heighUntil = this->picture.bih.height;
            this->picture.bih.width = this->picture.bih.width / 2;
            this->picture.bih.height = this->picture.bih.height / 2;
            fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
            for (size_t i = this->picture.bih.height; i < heighUntil; ++i)
            {
                fwrite((*tbl)[i], 1, w, to);
            }
            fclose(to);
        }
        else if (mode == 3)
        {
            unsigned int heighUntil = this->picture.bih.height;
            this->picture.bih.width = this->picture.bih.width / 2;
            this->picture.bih.height = this->picture.bih.height / 2;
            fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
            for (size_t y = this->picture.bih.height; y < heighUntil; ++y)
            {
                for (int i = 0; i < this->picture.bih.width; ++i)
                {
                    (*tbl)[y][i] = (*tbl)[y][i + this->picture.bih.width];
                }
            }

            for (size_t i = this->picture.bih.height; i < heighUntil; ++i)
            {
                fwrite((*tbl)[i], 1, w, to);
            }
            fclose(to);
        }
        else if (mode == 4)
        {
            this->picture.bih.width = this->picture.bih.width / 2;
            this->picture.bih.height = this->picture.bih.height / 2;
            fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
            for (size_t y = 0; y < this->picture.bih.height; ++y)
            {
                for (int i = 0; i < this->picture.bih.width; ++i)
                {
                    (*tbl)[y][i] = (*tbl)[y][i + this->picture.bih.width];
                }
            }

            for (size_t i = 0; i < this->picture.bih.height; ++i)
            {
                fwrite((*tbl)[i], 1, w, to);
            }
            fclose(to);
        }
        else if (mode == 5)
        {
            //unsigned int heighUntil = this->picture.bih.height;
            this->picture.bih.width = this->picture.bih.width / 2;
            this->picture.bih.height = this->picture.bih.height / 2;
            fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
            fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
            unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
            for (size_t y = this->picture.bih.height / 2; y < (this->picture.bih.height + this->picture.bih.height / 2); ++y)
            {
                for (int i = 0; i < (this->picture.bih.width + this->picture.bih.width / 2); ++i)
                {
                    (*tbl)[y][i] = (*tbl)[y][i + this->picture.bih.width / 2];
                }
            }

            for (size_t i = this->picture.bih.height / 2; i < (this->picture.bih.height + this->picture.bih.height / 2); ++i)
            {
                fwrite((*tbl)[i], 1, w, to);
            }
            fclose(to);
        }
    }
    void Bitmap::AddBackground(Rgb color, int mode, std::string nameTo)
    {
        FILE *to = fopen(nameTo.c_str(), "wb");
        this->picture.bih.width = this->picture.bih.width * 2;
        this->picture.bih.height = this->picture.bih.height * 2;
        fwrite(&picture.bfh, 1, sizeof(BitmapFileHeader), to);
        fwrite(&picture.bih, 1, sizeof(BitmapInfoHeader), to);
        auto Bigtbl = std::make_unique<PixelTable>(this->picture.bih.height, this->picture.bih.width);
        unsigned int w = (picture.bih.width) * sizeof(Rgb) + ((picture.bih.width) * 3) % 4;
        if (mode == 5)
        {
            for (int y = 0; y < this->picture.bih.height; ++y)
            {
                for (size_t i = 0; i < this->picture.bih.width; ++i)
                {

                    if (y >= this->picture.bih.height / 4 && i >= this->picture.bih.width / 4 && y < this->picture.bih.height / 4 + this->picture.bih.height / 2 && i < this->picture.bih.width / 2 + this->picture.bih.width / 4)
                        (*Bigtbl)[y][i] = (*tbl)[y - (int)picture.bih.height / 4][i - picture.bih.width / 4];
                    else
                        (*Bigtbl)[y][i] = color;
                }
            }
        }
        else if (mode == 1)
        {
            for (int y = 0; y < this->picture.bih.height; ++y)
            {
                for (size_t i = 0; i < this->picture.bih.width; ++i)
                {

                    if (y < this->picture.bih.height / 2 && i < this->picture.bih.width / 2)
                        (*Bigtbl)[y][i] = (*tbl)[y][i];
                    else
                        (*Bigtbl)[y][i] = color;
                }
            }
        }
        else if (mode == 2)
        {
            for (int y = 0; y < this->picture.bih.height; ++y)
            {
                for (size_t i = 0; i < this->picture.bih.width; ++i)
                {

                    if (y >= this->picture.bih.height / 2 && i < this->picture.bih.width / 2)
                        (*Bigtbl)[y][i] = (*tbl)[y - this->picture.bih.height / 2][i];
                    else
                        (*Bigtbl)[y][i] = color;
                }
            }
        }
        else if (mode == 3)
        {
            for (int y = 0; y < this->picture.bih.height; ++y)
            {
                for (size_t i = 0; i < this->picture.bih.width; ++i)
                {

                    if (y >= this->picture.bih.height / 2 && i >= this->picture.bih.width / 2)
                        (*Bigtbl)[y][i] = (*tbl)[y - this->picture.bih.height / 2][i - this->picture.bih.width / 2];
                    else
                        (*Bigtbl)[y][i] = color;
                }
            }
        }
        else if (mode == 4)
        {
            for (int y = 0; y < this->picture.bih.height; ++y)
            {
                for (size_t i = 0; i < this->picture.bih.width; ++i)
                {

                    if (i >= this->picture.bih.width / 2 && y < this->picture.bih.height / 2 )
                        (*Bigtbl)[y][i] = (*tbl)[y ][i - picture.bih.width / 2];
                    else
                        (*Bigtbl)[y][i] = color;
                }
            }
        }

        for (int i = 0; i < this->picture.bih.height; ++i)
        {
            fwrite((*Bigtbl)[i], 1, w, to);
        }
        fclose(to);
    }
