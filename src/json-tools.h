#ifndef _JSON_TOOLS_
#define _JSON_TOOLS_

#include "includes.h"

extern int jansson_get_max_values(std::string data_string, std::string country, int *cases_confirmed, int *cases_deaths, int *cases_recovered);
extern int jansson_get_list(std::string data_string, std::string country, std::vector<case_day> *days);

#endif