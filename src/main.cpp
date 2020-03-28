/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include "includes.h"
#include "curl-tools.h"
#include "draw.h"
#include "controls.h"
#include "vita-keyboard.h"
#include "json-tools.h"

/*
 * Symbol of the image.png file
 */

int main()
{   
    netInit(); // init net and then http
	httpInit();

	vita2d_init();
	vita2d_set_clear_color(RGBA8(255, 255, 255, 255));

    loadTextures();

    init_keys();

    bool done = false;

    std::string json_data_string = curl_get_string("https://pomber.github.io/covid19/timeseries.json");

    int cases_confirmed = 0; 
    int cases_deaths = 0;
    int cases_recovered = 0;

    std::string country_name = "US";

    country_name = vita_keyboard_get("Enter Country Name", "", 100, 0);

    int days = jansson_get_max_values(json_data_string, country_name, &cases_confirmed, &cases_deaths, &cases_recovered);
    
    std::vector<case_day> case_days;

    days = jansson_get_list(json_data_string, country_name, &case_days);
	while (!done) {
        update_keys();

        if(cross_released) done = true;

        if(start_released) {
            while(!case_days.empty()) case_days.pop_back();

            cases_confirmed = 0; 
            cases_deaths = 0;
            cases_recovered = 0;
            
            country_name = vita_keyboard_get("Enter Country Name", "", 100, 0);
            days = jansson_get_max_values(json_data_string, country_name, &cases_confirmed, &cases_deaths, &cases_recovered);
            days = jansson_get_list(json_data_string, country_name, &case_days);
        }

		vita2d_start_drawing();
		vita2d_clear_screen();

		draw_header("PSVITA Covid19 Data | START = Search new Country | X = quit");

        vita2d_font_draw_textf(font20, 10, 70, RGBA8(0,0,0,255), 20, "Country: %s\nConfirmed: %d\nDeaths: %d\nRecovered: %d\nDays Since 2020-1-22: %d", country_name.c_str(), cases_confirmed, cases_deaths, cases_recovered, days);

        draw_empty_rect(960 - vita2d_font_text_width(font20, 20, "Data Source: https://github.com/pomber/covid19"), 44, vita2d_font_text_width(font20, 20, "Data Source: https://github.com/pomber/covid19"), 130, RGBA8(0,0,0,255));

        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "KEY"), 70, RGBA8(0,0,0,255), 20, "KEY");
        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "BLACK: Confirmed cases"), 90, RGBA8(0,0,0,255), 20, "BLACK: Confirmed cases");
        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "RED: Deaths"), 110, RGBA8(255,0,0,255), 20, "RED: Deaths");
        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "GREEN: Recovered"), 130, RGBA8(0,255,0,255), 20, "GREEN: Recovered");
        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "Time searies starts at 2020-1-22"), 150, RGBA8(0,0,0,255), 20, "Time series starts at 2020-1-22");
        vita2d_font_draw_text(font20, 960 - vita2d_font_text_width(font20, 20, "Data Source: https://github.com/pomber/covid19"), 170, RGBA8(0,0,0,255), 20, "Data Source: https://github.com/pomber/covid19");

        vita2d_font_draw_text(font20, 960 / 2 - vita2d_font_text_width(font20, 20, "(Logarithmic Scale)") / 2, 544/2, RGBA8(0,0,0,255), 20, "(Logarithmic Scale)");

        int start_y = 544 - 30;
        int start_x = 100;
        double height = log10((double) cases_confirmed) * 24;

        draw_line(start_x, start_y, start_x, 544/2, RGBA8(0,0,0,255));
        draw_line(start_x, start_y, start_x + 216*4, start_y, RGBA8(0,0,0,255));
        vita2d_font_draw_text(font15, 0, 544 / 2, RGBA8(0,0,0,255), 15, "Y = log(N)");
        vita2d_font_draw_text(font15, start_x + 200*4, start_y + 25, RGBA8(0,0,0,255), 15, "X = days");

        double marker = 10.00;
        for(int i = 0; i < 8; i++) {
            double marker_height = log10(marker) * 24;
            draw_line(0, start_y - marker_height, start_x + 10, start_y - marker_height, RGBA8(0,0,0,255));
            vita2d_font_draw_textf(font15, 0, start_y - marker_height - 2, RGBA8(0,0,0,255), 15, "%.0f", marker);
            marker *= 10;
        }

        for(int i = 0; i < 200; i += 10) {
            int marker_x = i*4;
            draw_line(start_x + marker_x, start_y, start_x + marker_x, start_y + 10, RGBA8(0,0,0,255));
            vita2d_font_draw_textf(font15, start_x + marker_x - 5, start_y + 25, RGBA8(0,0,0,255), 15, "%d", i);
        }

        int curr_x = start_x;
        //int curr_y = start_y;
        for(unsigned int i = 0; i < days; i++) {
           double height = 0;
           if(case_days.at(i).confirmed > 0) height = log10((double) case_days.at(i).confirmed) * 24;
           draw_rect(curr_x, start_y - height, 4, height, RGBA8(0,0,0,255));
           if(case_days.at(i).deaths > case_days.at(i).recovered) {
              height = 0;
              if(case_days.at(i).deaths > 0) height = log10((double) case_days.at(i).deaths) * 24;
              draw_rect(curr_x, start_y - height, 4, height, RGBA8(255,0,0,255));
              
              height = 0;
              if(case_days.at(i).recovered > 0) height = log10((double) case_days.at(i).recovered) * 24;
              draw_rect(curr_x, start_y - height, 4, height, RGBA8(0,255,0,255));
           }
           else {
              height = 0;
              if(case_days.at(i).recovered > 0) height = log10((double) case_days.at(i).recovered) * 24;
              draw_rect(curr_x, start_y - height, 4, height, RGBA8(0,255,0,255));

              height = 0;
              if(case_days.at(i).deaths > 0) height = log10((double) case_days.at(i).deaths) * 24;
              draw_rect(curr_x, start_y - height, 4, height, RGBA8(255,0,0,255));
           }
           curr_x += 4;
        }

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	/*
	 * vita2d_fini() waits until the GPU has finished rendering,
	 * then we can free the assets freely.
	 */
	vita2d_fini();
    deleteTextures();
	sceKernelExitProcess(0);
	return 0;
}