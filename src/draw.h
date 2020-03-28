#ifndef _DRAW_
#define _DRAW_
#include "includes.h"
#include "controls.h"
#include "images.h"

struct Button{
    std::string name;
    int x;
    int y;
    int w;
    int h;
};

extern void draw_header(std::string header);

extern void draw_line(int x0, int y0, int x1, int y1, unsigned int color);
extern void draw_rect(int x, int y, int w, int h, unsigned int color);
extern void draw_empty_rect(int x, int y, int w, int h, unsigned int color);

#endif