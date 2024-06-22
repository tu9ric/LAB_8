#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <opencv2/opencv.hpp>
#include <openssl/engine.h>
#include <openssl/sha.h>
#include <openssl/evp.h>


size_t hashFunction(const std::string &name);

void enrolled(const std::string &filename, std::unordered_map<size_t, std::string> &voters);

void unenrolled(const std::string &surname, std::unordered_map<size_t, std::string> &voters, int &duplicates);

void calculateSHA256(const cv::Mat& img, unsigned char* md_buf);
#endif