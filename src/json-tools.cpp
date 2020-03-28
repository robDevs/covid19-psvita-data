#include "json-tools.h"
#include "draw.h"

int jansson_get_max_values(std::string data_string, std::string country, int *cases_confirmed, int *cases_deaths, int *cases_recovered) {
    json_t *root;
    json_error_t error;

    root = json_loads(data_string.c_str(), 0, &error);

    if(!root)
    {
        return -2;
    }

    if(!json_is_object(root))
    {
        json_decref(root);
        return -1;
    }

    int count = 0;

    int max_confirmed = 0;
    int max_deaths = 0;
    int max_recovered = 0;

    json_t *data, *array_data, *confirmed, *deaths, *recovered;

        data = json_object_get(root, country.c_str());
        if(!json_is_array(data))
        {
            json_decref(root);
            return count;
        }

        for(size_t i = 0; i < json_array_size(data); i++) {
            int temp_confirmed = 0;
            int temp_deaths = 0;
            int temp_recovered = 0;

            array_data = json_array_get(data, i);
            confirmed = json_object_get(array_data, "confirmed");
            deaths = json_object_get(array_data, "deaths");
            recovered = json_object_get(array_data, "recovered");

            if(json_is_integer(confirmed)) temp_confirmed = json_integer_value(confirmed);
            if(json_is_integer(deaths)) temp_deaths = json_integer_value(deaths);
            if(json_is_integer(recovered)) temp_recovered = json_integer_value(recovered);

            if(temp_confirmed > max_confirmed) max_confirmed = temp_confirmed;
            if(temp_deaths > max_deaths) max_deaths = temp_deaths;
            if(temp_recovered > max_recovered) max_recovered = temp_recovered;

            count++;
        }

        *cases_confirmed = max_confirmed;
        *cases_deaths = max_deaths;
        *cases_recovered = max_recovered;

    json_decref(root);
    return count;
}

int jansson_get_list(std::string data_string, std::string country, std::vector<case_day> *days) {
    json_t *root;
    json_error_t error;

    root = json_loads(data_string.c_str(), 0, &error);

    if(!root)
    {
        return -2;
    }

    if(!json_is_object(root))
    {
        json_decref(root);
        return -1;
    }

    int count = 0;

    int max_confirmed = 0;
    int max_deaths = 0;
    int max_recovered = 0;

    json_t *data, *array_data, *date, *confirmed, *deaths, *recovered;

        data = json_object_get(root, country.c_str());
        if(!json_is_array(data))
        {
            json_decref(root);
            return count;
        }

        for(size_t i = 0; i < json_array_size(data); i++) {
            int temp_confirmed = 0;
            int temp_deaths = 0;
            int temp_recovered = 0;

            array_data = json_array_get(data, i);
            date = json_object_get(array_data, "date");
            confirmed = json_object_get(array_data, "confirmed");
            deaths = json_object_get(array_data, "deaths");
            recovered = json_object_get(array_data, "recovered");

            if(json_is_integer(confirmed)) temp_confirmed = json_integer_value(confirmed);
            if(json_is_integer(deaths)) temp_deaths = json_integer_value(deaths);
            if(json_is_integer(recovered)) temp_recovered = json_integer_value(recovered);

            case_day new_day;

            if(temp_confirmed > max_confirmed) new_day.confirmed = temp_confirmed;
            if(temp_deaths > max_deaths) new_day.deaths = temp_deaths;
            if(temp_recovered > max_recovered) new_day.recovered = temp_recovered;
            if(json_is_string(date)) new_day.date = json_string_value(date);

            days->push_back(new_day);

            count++;
        }

    json_decref(root);
    return count;
}