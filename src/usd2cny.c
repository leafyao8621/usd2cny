#include <curl/curl.h>
#include <string.h>
#include <stdio.h>

static char buf[20000];
static char *buf_end = buf;
static const char *usd = "USD";
static const char *center = "center";

static size_t writefunc(void* in, size_t sz, size_t mb, void* out) {
    size_t len = sz * mb;
    memcpy(buf_end, in, sz * mb);
    buf_end += len;
    *buf_end = 0;
    return sz * mb;
}

int main(void) {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.bankcomm.com/BankCommSite/simple/cn/whpj/queryExchangeResult.do?type=simple");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    char *i = buf;
    for (; i != buf_end && memcmp(i, usd, 3); i++);
    for (int j = 0; j < 5; j++) {
        for (i++; i != buf_end && memcmp(i, center, 6); i++);
    }
    i += 8;
    i[6] = 0;
    puts(i);
}
