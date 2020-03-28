#ifndef _CURL_TOOLS
#define _CURL_TOOLS

#include "includes.h"
#include "draw.h"

struct stringcurl {
  char *ptr;
  size_t len;
};

extern std::string progress_string;

extern int progress_func_string(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
extern void init_string(struct stringcurl *s);

extern size_t writefunc(void *ptr, size_t size, size_t nmemb, struct stringcurl *s);

extern size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);

extern size_t write_data_to_disk(void *ptr, size_t size, size_t nmemb, void *stream);

extern std::string curl_get_string(std::string url);

extern void netInit();

extern void netTerm();

extern void httpInit();

extern void httpTerm();


#endif