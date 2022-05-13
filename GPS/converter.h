/**
 * @file Converter.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip> //std::setprecision(8)

void convert_ZDA(std::string &data);
void convert_VTG(std::string &data);
bool convert_RMC(std::string &data, std::string &info); //Recommended Minimum data
void convert_GSV(std::string &data);
void convert_GST(std::string &data);
void convert_GSA(std::string &data);
void convert_GRS(std::string &data);
bool convert_GLL(std::string &data, std::string &info); //Latitude and longitude, with time of position fix and status
bool convert_GGA(std::string &data, std::string &info); //GGA Global positioning system fix data
void convert_GBS(std::string &data);
void convert_DTM(std::string &data);
void convert_UBX_04(std::string &data);
void convert_UBX_03(std::string &data);
void convert_UBX_00(std::string &data);

bool converter(std::string rawData, std::string &convertedData);

std::vector<std::string> splitStr(const std::string &data);
std::string getSystemName(uint id);
std::string getGpsQuality(uint quality);
double convert_DDmm_mm_To_dd_dddd(const std::string &data);
double convert_DDDmm_mm_To_ddd_dddd(const std::string &data);
std::string convertTime(std::string &data);
