#ifndef _INCLUDES_
#define _INCLUDES_

#include <string.h>
#include <stdbool.h>
#include <psp2/apputil.h>
#include <psp2/display.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ime_dialog.h>
#include <psp2/message_dialog.h>
#include <psp2/ctrl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vita2d.h>

#include <psp2/io/stat.h>
#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

#include <psp2/io/fcntl.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <curl/curl.h>
#include <cmath>

#include <vector>

#include <jansson.h>

struct case_day {
    int confirmed;
    int deaths; 
    int recovered;
    std::string date;
};

#endif