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
#include "converter.h"
#define DEBUG false
/**
 * @brief GSV GNSS Satellites in View
 * $GPGSV,NoMsg,MsgNo,NoSv,{,sv,elv,az,cno}*cs
 * Sample Data: $GPGSV,2,1,05,01,31,273,40,04,29,273,41,11,51,280,32,24,00,039,*71
 * @param data
 */
void convert_GPGSV(std::string &data){

    std::vector<std::string> arr = splitStr(data);
    std::stringstream sstr;

    uint msg_cnt = std::stoi(arr.at(1));
    uint msg_nr = std::stoi(arr.at(2));
    uint sat_cnt = std::stoi(arr.at(3));
    // uint satArr[sat_cnt][4];

    // uint8_t ctr = 4;
    // for (size_t i = 0; i < sat_cnt; i++)
    // {
    //    for (size_t j = 0; j < 4; j+=1)
    //     {
    //         satArr[i][j]= std::stoi(arr.at(ctr+j));
    //         ctr+=4;
    //     }
    // }
    // uint id = std::stoi(arr.at(arr.size()-1));
    // uint id = arr.size();
    // std::string system = getSystemName(std::stoi(arr.at(arr.size()-1)));

    std::cout << "Message: " << msg_nr << "/" << msg_cnt << " Sataliten: " << sat_cnt <<std::endl;
}

/**
 * @brief GSV GNSS Satellites in View
 * $GPGSV,NoMsg,MsgNo,NoSv,{,sv,elv,az,cno}*cs
 * Sample Data: $GPGSV,2,1,05,01,31,273,40,04,29,273,41,11,51,280,32,24,00,039,*71
 * @param data
 */
void convert_GLGSV(std::string &data){

    std::vector<std::string> arr = splitStr(data);
    uint msg_cnt = std::stoi(arr.at(1));
    uint msg_nr = std::stoi(arr.at(2));
    uint sat_cnt = std::stoi(arr.at(3));
    uint sat_nr = std::stoi(arr.at(4));


    std::cout << "Message: " << msg_nr << "/" << msg_cnt << " Satalit: "<<sat_nr << "/" << sat_cnt <<std::endl;
}

/**
 * @brief ZDA Time and Date
 * Message Info 0xF0 0x08 9
 * Message Structure: $GPZDA,hhmmss.ss,day,month,year,ltzh,ltzn*cs
 * Sample Data: $GPZDA,154517.00,12,10,2014,00,00*60
 */
void convert_ZDA(std::string &data)
{
    std::vector<std::string> arr = splitStr(data);

    std::string utcTime = convertTime(arr.at(1)); //hhmmss.ss
    uint day = std::stoi(arr.at(2));
    uint month = std::stoi(arr.at(3));
    uint year = std::stoi(arr.at(4));

    std::cout << day << "-" << month << "-" << year << std::endl;
}

/**
 * @brief VTG Course over ground and Ground speed
 * $GPVTG,cogt,T,cogm,M,sog,N,kph,K,mode*cs
 * Sample Data: $GPVTG,69.74,T,,M,1.060,N,1.963,K,A*0B
 */
void convert_VTG(std::string &data){
    //don´t care
}

/**
 * @brief RMC Recommended Minimum data
 * $GPRMC,hhmmss,status,latitude,N,longitude,E,spd,cog,ddmmyy,mv,mvE,mode*cs
 * Sample Data: $GPRMC,134342.00,A,5217.01648,N,00950.17995,E,0.401,,121014,,,A*74
 * SRC https://docs.novatel.com/OEM7/Content/Logs/GPRMC.htm
 * @param data
 */
bool convert_RMC(std::string &data, std::string &info)
{
    std::vector<std::string> arr = splitStr(data);
    std::stringstream sstr;

    // std::string utcTime = convertTime(arr.at(1)); //hhmmss.ss
    bool positionValid;
    double latitude; // (DDmm.mm)
    std::string latitude_direction;
    double longitude; // (DDDmm.mm)
    std::string longitude_direction;

    try
    {
        latitude = convert_DDmm_mm_To_dd_dddd(arr.at(3)); // (DDmm.mm)
        latitude_direction = arr.at(4);
        longitude = convert_DDDmm_mm_To_ddd_dddd(arr.at(5)); // (DDDmm.mm)
        longitude_direction = arr.at(6);
        positionValid = arr.at(2) == "A" ? true: false;

    }
    catch(const std::exception& e)
    {
        std::cout<<"! Fuck ! " << e.what() <<std::endl;
        return false;
    }

    if(!positionValid) return false;


        sstr << std::setprecision(8) << latitude << latitude_direction << "|" << longitude << longitude_direction;
        info = sstr.str();
        return true;
}

/**
 * @brief GST GNSS Pseudo Range Error Statistics
 * $GPGST,hhmmss.ss,range_rms,std_major,std_minor,hdg,std_lat,std_long,std_alt*cs
 * Sample Data: $GPGST,130903.22,0.0000,,,,3750000,3750000,3750000*5E
 * @param data
 */
void convert_GST(std::string &data){
    data.at(1);

}

/**
 * @brief GSA GNSS DOP and Active Satellites Streubreite der Messwerte
 * $GNGSA $GPGSA,Smode,FS{,sv},PDOP,HDOP,VDOP*cs
 * Sample Data: $GPGSA,A,1,01,04,11,,,,,,,,,,99.99,99.99,1.00*04
 * https://docs.novatel.com/OEM7/Content/Logs/GPGSA.htm?Highlight=GPGSA
 * @param data
 */
void convert_GSA(std::string &data)
{

}

/**
 * @brief GRS GNSS Range Residuals
 * $GPGRS,hhmmss.ss, mode {,residual}*cs
 * Sample Data: GPGRS,125910.00,1,0.0,0.1,-278,0.0,,,,,,,,*7F
 */

void convert_GRS(std::string &data){
    data.at(1);
}

/**
 * @brief GLL Latitude and longitude, with time of position fix and status
 * &GNGLL $GPGLL,Latitude,N,Longitude,E,hhmmss.ss,Valid,Mode*cs
 * Sample Data: $GPGLL,5217.01989,N,00950.20011,E,125204.00,A,A*6F
 * https://docs.novatel.com/OEM7/Content/Logs/GPGLL.htm?Highlight=GNGLL
 * @param data
 * RAW DATA: GNGLL,,,,,214240.00,V,N*55
 */
bool convert_GLL(std::string &data, std::string &info)
{
    std::vector<std::string> arr = splitStr(data);
    std::stringstream sstr;

    double latitude;
    std::string latitude_direction;
    double longitude;
    std::string longitude_direction;
    bool dataValid;

   try
   {
        latitude = convert_DDmm_mm_To_dd_dddd(arr.at(1)); // (DDmm.mm)
        latitude_direction = arr.at(2);
        longitude = convert_DDDmm_mm_To_ddd_dddd(arr.at(3)); // (DDDmm.mm)
        longitude_direction = arr.at(4);
        dataValid = arr.at(6) == "A" ? true : false;
   }
   catch(const std::exception& e)
   {
       std::cout<<"! Fuck ! " << e.what() <<std::endl;
       return false;
   }

    if(!dataValid) return false;

    sstr << std::setprecision(8)<< latitude << latitude_direction << "|" << longitude << longitude_direction;
    info = sstr.str();

    return true;

}

/**
 * @brief GGA Global positioning system fix data
 * $GPGGA,hhmmss.ss,Latitude,N,Longitude,E,FS,NoSV,HDOP,msl,m,Altref,m,DiffAge,DiffStation*cs
 * Sample Data: $GPGGA,124141.00,5217.02743,N,00950.20920,E,1,05,8.12,51.8,M,46.2,M,,*6B
 * https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm?Highlight=GPGGA
 * @param data
 */
bool convert_GGA(std::string &data, std::string &info)
{
    std::vector<std::string> arr= splitStr(data);
    std::stringstream sstr;


    double latitude; // (DDmm.mm)
    std::string latitude_direction;
    double longitude; // (DDDmm.mm)
    std::string longitude_direction;
    double altitude;

    try
    {
        latitude = convert_DDmm_mm_To_dd_dddd(arr.at(2)); // (DDmm.mm)
        latitude_direction = arr.at(3);
        longitude = convert_DDDmm_mm_To_ddd_dddd(arr.at(4)); // (DDDmm.mm)
        longitude_direction = arr.at(5);
        altitude = std::stod(arr.at(9));

    }
    catch(const std::exception& e)
    {
        std::cout <<"! Fuck ! "<< e.what() <<std::endl;
        return false;
    }

    sstr << std::setprecision(8) << latitude << latitude_direction << "|" << longitude << longitude_direction << "|" << altitude;
    info = sstr.str();
    return true;
}

/**
 * @brief GBS GNSS Satellite Fault Detection
 * $GPGBS,hhmmss.ss,errlat,errlon,erralt,svid,prob,bias,stddev*cs
 * Sample Data: $GPGBS,122333.00,4.0,5.2,11.2,,,,*72
 */
void convert_GBS(std::string &data){
    data.at(1);
}

/**
 * @brief DTM Datum Reference
 * $GPDTM,LLL,LSD,lat,N/S,lon,E/W,alt,RRR*cs
 * Sample Data: $GPDTM,W84,,0.0,N,0.0,E,0.0,W84*6F
 * @param data
 */
void convert_DTM(std::string &data){
    data.at(1);
}

/**
 * @brief UBX 04 Time of Day and Clock Information
 * Zu Beginn ist die Zeit 10 Sekunden vor Mitternacht und das Datum der 12. Januar 36. Zehn Sekunden stäter springt das Datum auf den 6. Januar 80. Nach weiteren 33 Sekunden ist die Uhrzeit richtig; kurz darauf erst das Datum.
 * $PUBX,04,hhmmss.ss,ddmmyy,UTC_TOW,UTC_WNO,LEAP_SEC,Clk_B,Clk_D,PG,*cs
 * Sample Data: $PUBX,04,235950.00,120136,604790.00,65535,15D,0,0.000,21*59
 * @param data
 */
void convert_UBX_04(std::string &data){
    data.at(1);
}

/**
 * @brief UBX 03 Satellite Status
 * $PUBX,03,GT{,SVID,s,AZM,EL,SN,LK},*cs
 * Sample Data: $PUBX,03,09,7,U,316,16,22,000,8,U,286,25,20,000,19,U,285,29,33,007,21,-,069,54,19,000,22,-,162,32,,000,26,-,030,07,23,000,27,U,290,60,32,003,29,-,105,01,,000,30,-,343,05,20,000*32
 * @param data
 */
void convert_UBX_03(std::string &data){
    data.at(1);
}

/**
 * @brief UBX 00 Lat/Long Position Data
 * $PUBX,00,hhmmss.ss,Latitude,N,Longitude,E,AltRef,NavStat,Hacc,Vacc,SOG,COG,Vvel,ageC,HDOP,VDOP,TDOP,GU,RU,DR,*cs
 * Sample Data: $PUBX,00,081121.00,3619.34208,N,03909.49586,W,7462.062,NF,5303303,3750002,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*05
 * @param data
 */
void convert_UBX_00(std::string &data){
    data.at(1);
}

bool converter(std::string rawdata, std::string &convertedData)
{
    std::string type;

    try
    {
        type = rawdata.substr(0,5);
    }
    catch(const std::out_of_range & e)
    {
        std::cout << e.what() <<std::endl;
        return false;
    }


    if (DEBUG)
    {
        std::cout << type << std::endl;
        return false;
    }
    else
    {
        std::cout <<"RAW DATA: " << rawdata <<std::endl;

        if(type == "GPGSV")
        {
            // convertedData = convert_GPGSV(rawdata);
            return false;
        }
        else if (type == "GLGSV")
        {
            // convertedData = convert_GLGSV(rawdata);
            return false;
        }
        else if (type == "GNGLL" || type == "GPGLL")
        {
            return convert_GLL(rawdata, convertedData);
        }
        else if (type == "GNVTG")
        {
            //dont´t care
            return false;
        }
        else if (type == "GNGGA" || type == "GPGGA")
        {
            return convert_GGA(rawdata, convertedData);
        }
        else if (type == "GNGSA")
        {
            // don´t care
            return false;
        }
        else if (type == "GNRMC" || type == "GPRMC")
        {
            return convert_RMC(rawdata, convertedData);
        }
        else if (type == "GNZDA" || type == "GPZDA")
        {
            // convertedData = convert_ZDA(rawdata);
            return false;
        }
        else{
            std::cout << "unknown: " << type << std::endl;
            convertedData = "unknown";
            return false;
        }
    }
}

std::vector<std::string> splitStr(const std::string &data)
{
    std::stringstream stream(data);

    std::string token;
    std::vector<std::string> arr;

    int i = 0;
    while(std::getline(stream, token, ','))
    {
       arr.push_back(token);
       i++;
    }

    return arr;
}

std::string getSystemName(uint id){

    switch (id)
    {
    case 1: return "GPS";
    case 2: return "GLONASS";
    case 3: return "Galileo";
    case 4: return "BDS ";
    case 5: return "QZSS";
    case 6: return "NavIC";

    default: return "unknown";
    }
}

/*
    https://www.siretta.com/2019/01/gps-latitude-longitude-conversion-guide/
*/
double convert_DDmm_mm_To_dd_dddd(const std::string &data)
{
    int len = data.size();
    std::cout << len << " convertdd: " << data << std::endl;

    double dd =  std::stoi(data.substr(0,2));
    double dddd = std::stof(data.substr(2,len-3))/ 60;
    return dd+dddd;
}

double convert_DDDmm_mm_To_ddd_dddd(const std::string &data)
{
    int len = data.size();
    std::cout<< len  << "convertddd: " << data << std::endl;

    double ddd =  std::stoi(data.substr(0,3));
    double dddd = std::stod(data.substr(3,len-3))/60;
    return ddd+dddd;
}

/*
    https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm?Highlight=GPGGA#GPSQualityIndicators
*/
std::string getGpsQuality(uint quality){
    switch (quality)
        {
        case 0: return "Fix not available or invalid";
        case 1: return "Single point";
        case 2: return "Pseudorange differential";
        case 4: return "RTK fixed ambiguity solution";
        case 5: return "RTK floating ambiguity solution ";
        case 6: return "Dead reckoning mode";
        case 7: return "Manual input mode (fixed position)";
        case 8: return "Simulator mode";
        case 9: return "WAAS(SBAS)";
        default: return "unknown";
        }
}

std::string convertTime(std::string &data){

    std::stringstream stream;
    uint h = std::stoi(data.substr(0,2));
    uint m= std::stoi(data.substr(2,2));
    uint s= std::stoi(data.substr(4,2));
    uint ds= std::stoi(data.substr(7,2));

    stream << h <<":" << m << "" << s << "-" << ds;

    return stream.str();
}