#include "images.h"
#include <algorithm>


vita2d_font *font10;
vita2d_font *font15;
vita2d_font *font19;
vita2d_font *font20;
vita2d_font *font23;
vita2d_font *font29;
vita2d_font *font40;

void loadTextures() {
    font10 = vita2d_load_font_file("app0:/font.ttf");
    font15 = vita2d_load_font_file("app0:/font.ttf");
    font19 = vita2d_load_font_file("app0:/font.ttf");
    font20 = vita2d_load_font_file("app0:/font.ttf");
    font23 = vita2d_load_font_file("app0:/font.ttf");
    font29 = vita2d_load_font_file("app0:/font.ttf");
    font40 = vita2d_load_font_file("app0:/font.ttf");
}

void deleteTextures() {
    vita2d_free_font(font10);
    vita2d_free_font(font15);
    vita2d_free_font(font19);
    vita2d_free_font(font20);
    vita2d_free_font(font23);
    vita2d_free_font(font29);
    vita2d_free_font(font40);
}

std::string word_wrap(std::string text, unsigned per_line) {
  //http://www.cplusplus.com/forum/beginner/132223/#msg714543
  unsigned line_begin = 0;
  while (line_begin < text.size()) {
    const unsigned ideal_end = line_begin + per_line ;
    unsigned line_end = (ideal_end <= text.size() ? ideal_end : text.size()-1);

    if (line_end == text.size() - 1) {
        ++line_end;
    } else if (std::isspace(text[line_end])) {
      text[line_end] = '\n';
      ++line_end;
    } else {   // backtrack
      unsigned end = line_end;
      while ( end > line_begin && !std::isspace(text[end])) {
        --end;
      }
      if (end != line_begin) {
        line_end = end;
        text[line_end++] = '\n';
      }
      else {
        text.insert(line_end++, 1, '\n');
      }
    }
    line_begin = line_end;
  }
  return text;
}

bool invalidChar (char c)
{
    return !(c>=0 && c<128);
}
void strip_carriage_return(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
}
void strip_new_line(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}