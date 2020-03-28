#include "draw.h"
#include <psp2/kernel/processmgr.h>
#include <psp2/rtc.h>

#include "vita-keyboard.h"
#include "curl-tools.h"

void draw_header(std::string header) {
    SceDateTime time;
    sceRtcGetCurrentClockLocalTime(&time);

    std::string am_pm;

    std::string time_string = "";
    int time_hour = sceRtcGetHour(&time);
    if(time_hour > 12) {
        time_hour -= 12;
        am_pm = " PM";
    }
    else {
        am_pm = " AM";
    }
    if(time_hour == 0)
        time_hour = 12;
    int time_minute = sceRtcGetMinute(&time);
    time_string += std::to_string(time_hour);
    time_string += ":";
    if(time_minute < 10) time_string += "0";
    time_string += std::to_string(time_minute);
    time_string += am_pm;
    
    vita2d_draw_rectangle(0, 0, 960, 44, RGBA8(36,41,46,255));
    vita2d_font_draw_textf(font20, 20, 22+(vita2d_font_text_height(font20, 20.0f, header.c_str()) / 4), RGBA8(255,255,255,255), 20.0f, "%s", header.c_str());

    vita2d_font_draw_textf(font20, 960-(vita2d_font_text_width(font20, 20.0f, time_string.c_str())) - 20, 22+(vita2d_font_text_height(font20, 20.0f, header.c_str()) / 4), RGBA8(255,255,255,255), 20.0f, "%s", time_string.c_str());
}

void draw_line(int x0, int y0, int x1, int y1, unsigned int color) {
    vita2d_draw_line(x0, y0, x1, y1, color);
}

void draw_rect(int x, int y, int w, int h, unsigned int color) {
    vita2d_draw_rectangle(x, y, w, h, color);
}

void draw_empty_rect(int x, int y, int w, int h, unsigned int color) {
    vita2d_draw_line(x, y, x + w, y, color);
    vita2d_draw_line(x, y, x, y + h, color);
    vita2d_draw_line(x, y + h, x + w, y + h, color);
    vita2d_draw_line(x + w, y, x + w, y + h, color);
}