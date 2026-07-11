#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel {
    unsigned char b, g, r;
};

struct Image {
    Header header;
    vector<Pixel> pixels;
};

Image readImage(const string& filename) {
    Image img;
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return img;
    }
    file.read((char*)&img.header.idLength,        1);
    file.read((char*)&img.header.colorMapType,    1);
    file.read((char*)&img.header.dataTypeCode,    1);
    file.read((char*)&img.header.colorMapOrigin,  2);
    file.read((char*)&img.header.colorMapLength,  2);
    file.read((char*)&img.header.colorMapDepth,   1);
    file.read((char*)&img.header.xOrigin,         2);
    file.read((char*)&img.header.yOrigin,         2);
    file.read((char*)&img.header.width,           2);
    file.read((char*)&img.header.height,          2);
    file.read((char*)&img.header.bitsPerPixel,    1);
    file.read((char*)&img.header.imageDescriptor, 1);

    int numPixels = img.header.width * img.header.height;
    img.pixels.resize(numPixels);
    for (int i = 0; i < numPixels; i++) {
        file.read((char*)&img.pixels[i].b, 1);
        file.read((char*)&img.pixels[i].g, 1);
        file.read((char*)&img.pixels[i].r, 1);
    }
    file.close();
    return img;
}

void writeImage(const Image& img, const string& filename) {
    ofstream file(filename, ios::binary);
    file.write((char*)&img.header.idLength,        1);
    file.write((char*)&img.header.colorMapType,    1);
    file.write((char*)&img.header.dataTypeCode,    1);
    file.write((char*)&img.header.colorMapOrigin,  2);
    file.write((char*)&img.header.colorMapLength,  2);
    file.write((char*)&img.header.colorMapDepth,   1);
    file.write((char*)&img.header.xOrigin,         2);
    file.write((char*)&img.header.yOrigin,         2);
    file.write((char*)&img.header.width,           2);
    file.write((char*)&img.header.height,          2);
    file.write((char*)&img.header.bitsPerPixel,    1);
    file.write((char*)&img.header.imageDescriptor, 1);

    for (int i = 0; i < (int)img.pixels.size(); i++) {
        file.write((char*)&img.pixels[i].b, 1);
        file.write((char*)&img.pixels[i].g, 1);
        file.write((char*)&img.pixels[i].r, 1);
    }
    file.close();
}

unsigned char clamp(int value) {
    if (value < 0)   return 0;
    if (value > 255) return 255;
    return (unsigned char)value;
}

Image multiply(const Image& top, const Image& bottom) {
    Image result = top;
    for (int i = 0; i < (int)top.pixels.size(); i++) {
        result.pixels[i].r = (unsigned char)((top.pixels[i].r / 255.0f) * (bottom.pixels[i].r / 255.0f) * 255.0f + 0.5f);
        result.pixels[i].g = (unsigned char)((top.pixels[i].g / 255.0f) * (bottom.pixels[i].g / 255.0f) * 255.0f + 0.5f);
        result.pixels[i].b = (unsigned char)((top.pixels[i].b / 255.0f) * (bottom.pixels[i].b / 255.0f) * 255.0f + 0.5f);
    }
    return result;
}

Image subtract(const Image& top, const Image& bottom) {
    Image result = top;
    for (int i = 0; i < (int)top.pixels.size(); i++) {
        result.pixels[i].r = clamp((int)top.pixels[i].r - (int)bottom.pixels[i].r);
        result.pixels[i].g = clamp((int)top.pixels[i].g - (int)bottom.pixels[i].g);
        result.pixels[i].b = clamp((int)top.pixels[i].b - (int)bottom.pixels[i].b);
    }
    return result;
}

Image screen(const Image& top, const Image& bottom) {
    Image result = top;
    for (int i = 0; i < (int)top.pixels.size(); i++) {
        float nr = top.pixels[i].r / 255.0f;
        float ng = top.pixels[i].g / 255.0f;
        float nb = top.pixels[i].b / 255.0f;
        float br = bottom.pixels[i].r / 255.0f;
        float bg = bottom.pixels[i].g / 255.0f;
        float bb = bottom.pixels[i].b / 255.0f;
        result.pixels[i].r = (unsigned char)((1.0f - (1.0f - nr) * (1.0f - br)) * 255.0f + 0.5f);
        result.pixels[i].g = (unsigned char)((1.0f - (1.0f - ng) * (1.0f - bg)) * 255.0f + 0.5f);
        result.pixels[i].b = (unsigned char)((1.0f - (1.0f - nb) * (1.0f - bb)) * 255.0f + 0.5f);
    }
    return result;
}

Image overlay(const Image& top, const Image& bottom) {
    Image result = top;
    for (int i = 0; i < (int)top.pixels.size(); i++) {
        float nr = top.pixels[i].r / 255.0f;
        float ng = top.pixels[i].g / 255.0f;
        float nb = top.pixels[i].b / 255.0f;
        float br = bottom.pixels[i].r / 255.0f;
        float bg = bottom.pixels[i].g / 255.0f;
        float bb = bottom.pixels[i].b / 255.0f;

        if (br <= 0.5f)
            result.pixels[i].r = (unsigned char)(2.0f * nr * br * 255.0f + 0.5f);
        else
            result.pixels[i].r = (unsigned char)((1.0f - 2.0f * (1.0f - nr) * (1.0f - br)) * 255.0f + 0.5f);

        if (bg <= 0.5f)
            result.pixels[i].g = (unsigned char)(2.0f * ng * bg * 255.0f + 0.5f);
        else
            result.pixels[i].g = (unsigned char)((1.0f - 2.0f * (1.0f - ng) * (1.0f - bg)) * 255.0f + 0.5f);

        if (bb <= 0.5f)
            result.pixels[i].b = (unsigned char)(2.0f * nb * bb * 255.0f + 0.5f);
        else
            result.pixels[i].b = (unsigned char)((1.0f - 2.0f * (1.0f - nb) * (1.0f - bb)) * 255.0f + 0.5f);
    }
    return result;
}

Image addChannel(const Image& img, int addR, int addG, int addB) {
    Image result = img;
    for (int i = 0; i < (int)img.pixels.size(); i++) {
        result.pixels[i].r = clamp((int)img.pixels[i].r + addR);
        result.pixels[i].g = clamp((int)img.pixels[i].g + addG);
        result.pixels[i].b = clamp((int)img.pixels[i].b + addB);
    }
    return result;
}

Image scaleChannel(const Image& img, int scaleR, int scaleG, int scaleB) {
    Image result = img;
    for (int i = 0; i < (int)img.pixels.size(); i++) {
        result.pixels[i].r = clamp((int)img.pixels[i].r * scaleR);
        result.pixels[i].g = clamp((int)img.pixels[i].g * scaleG);
        result.pixels[i].b = clamp((int)img.pixels[i].b * scaleB);
    }
    return result;
}

Image flip(const Image& img) {
    Image result = img;
    int n = img.pixels.size();
    for (int i = 0; i < n; i++)
        result.pixels[i] = img.pixels[n - 1 - i];
    return result;
}

int main() {
    {
        Image layer1   = readImage("input/layer1.tga");
        Image pattern1 = readImage("input/pattern1.tga");
        Image result   = multiply(layer1, pattern1);
        writeImage(result, "output/part1.tga");
    }
    {
        Image layer2 = readImage("input/layer2.tga");
        Image car    = readImage("input/car.tga");
        Image result = subtract(car, layer2);
        writeImage(result, "output/part2.tga");
    }
    {
        Image layer1   = readImage("input/layer1.tga");
        Image pattern2 = readImage("input/pattern2.tga");
        Image text     = readImage("input/text.tga");
        Image temp     = multiply(layer1, pattern2);
        Image result   = screen(temp, text);
        writeImage(result, "output/part3.tga");
    }
    {
        Image layer2   = readImage("input/layer2.tga");
        Image circles  = readImage("input/circles.tga");
        Image pattern2 = readImage("input/pattern2.tga");
        Image temp     = multiply(layer2, circles);
        Image result   = subtract(temp, pattern2);
        writeImage(result, "output/part4.tga");
    }
    {
        Image layer1   = readImage("input/layer1.tga");
        Image pattern1 = readImage("input/pattern1.tga");
        Image result   = overlay(layer1, pattern1);
        writeImage(result, "output/part5.tga");
    }
    {
        Image car    = readImage("input/car.tga");
        Image result = addChannel(car, 0, 200, 0);
        writeImage(result, "output/part6.tga");
    }
    {
        Image car    = readImage("input/car.tga");
        Image result = scaleChannel(car, 4, 1, 0);
        writeImage(result, "output/part7.tga");
    }
    {
        Image car = readImage("input/car.tga");
        Image r = car, g = car, b = car;
        for (int i = 0; i < (int)car.pixels.size(); i++) {
            r.pixels[i].r = car.pixels[i].r;
            r.pixels[i].g = car.pixels[i].r;
            r.pixels[i].b = car.pixels[i].r;
            g.pixels[i].r = car.pixels[i].g;
            g.pixels[i].g = car.pixels[i].g;
            g.pixels[i].b = car.pixels[i].g;
            b.pixels[i].r = car.pixels[i].b;
            b.pixels[i].g = car.pixels[i].b;
            b.pixels[i].b = car.pixels[i].b;
        }
        writeImage(r, "output/part8_r.tga");
        writeImage(g, "output/part8_g.tga");
        writeImage(b, "output/part8_b.tga");
    }
    {
        Image layerR = readImage("input/layer_red.tga");
        Image layerG = readImage("input/layer_green.tga");
        Image layerB = readImage("input/layer_blue.tga");
        Image result = layerR;
        for (int i = 0; i < (int)result.pixels.size(); i++) {
            result.pixels[i].r = layerR.pixels[i].r;
            result.pixels[i].g = layerG.pixels[i].g;
            result.pixels[i].b = layerB.pixels[i].b;
        }
        writeImage(result, "output/part9.tga");
    }
    {
        Image text2  = readImage("input/text2.tga");
        Image result = flip(text2);
        writeImage(result, "output/part10.tga");
    }

    return 0;
}
