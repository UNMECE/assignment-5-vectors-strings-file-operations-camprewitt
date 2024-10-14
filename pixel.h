#ifndef PIXEL_H
#define PIXEL_H

struct _pixel
{
  float r;  //values r, g, and b will fall btween 0 <= 1.0
  float g;
  float b;
  int x;    //x and y are the positions of the pixel on the plane
  int y;
};

typedef struct _pixel Pixel;

#endif 