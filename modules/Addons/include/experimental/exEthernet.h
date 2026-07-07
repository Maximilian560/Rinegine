#pragma once

#include <curl/curl.h>


size_t write_func(void* ptr, size_t size, size_t nmemb, void* stream){
  size_t written = fwrite(ptr,size,nmemb,stream);
  return written;
}

CURLcode RG_DownloadFrom(string url,string fileName){
  CURL* crl curl_easy_init();
  FILE* file = fopen(fileName,"wb");
  curl_easy_setopt(crl,CURLOPT_URL,url.c_str());
  //curl_easy_setopt(crl,CURLOPT_FILE,file);
  curl_easy_setopt(crl, CURLOPT_WRITEFUNCTION,write_func)
  curl_easy_setopt(crl, CURLOPT_WRITEDATA,file);

  CURLcode res = curl_easy_perform(crl);
  curl_easy_cleanup(crl);
  fclose(file);
  return res;
}