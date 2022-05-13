#include "pico/stdlib.h"
#include <stdlib.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
// #include <iostream>
#include <sstream>
#include<algorithm>
#include <cstring>
#include "Uart/my_uart.h"
#include "GPS/converter.h"

#include "Chrono/PicoChrono.hpp"

#define oneSecond 1000000

void removeCharsFromString( std::string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

int main ()
{
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN,GPIO_OUT);


    //Timer
    PicoChrono timer;

    //GPS
    // uart GPS(uart1,8,9,9600); //dev Port
    uart GPS(uart0,0,1,9600); //final Port
    char data;
    bool was_CR = false;
    std::stringstream GpsData;

    //LoRa
    uart Lora(uart1,4,5,115200);

    Lora.write("at+join\r\n"); //Join LoRa Net.
    sleep_ms(1000); // wait for response;
    std::cout << "Lora DATA: " << Lora.read()<< std::endl;


    std::string LoRaAnswer;
    std::string LoRaMessage = "at+send=lora:2:";
    std::string LoRaPayLoad = "";
    bool dataValid = false;

    std::stringstream asd;
    char chars[] = "\n\r";

    while (true)
    {
        if (timer.hasPassed(10*oneSecond,true)&&dataValid) // send Lora msg every 10s
        {
            // Lora.write("at+send=lora:2:48616c6c6f6f\r\n");
            Lora.write(LoRaMessage.append(string_to_hex(LoRaPayLoad)).append("\r\n"));
            sleep_ms(1000); // wait for response;
            LoRaAnswer = Lora.read();
            removeCharsFromString(LoRaAnswer, chars);
            std::cout << LoRaAnswer <<std::endl;

            if(LoRaAnswer == "ERROR: 86") //error code 86 = no lora net
            {
              Lora.write("at+join\r\n");
            }
            asd.str(std::string());
            asd.clear();
            dataValid = false;
            gpio_put(PICO_DEFAULT_LED_PIN, false);
        }

        data = GPS.readC();

        if(data == '$')
        {
            GpsData.str(std::string()); // Clear sstream
            GpsData.clear();
        }
        else if(data == '\r' || was_CR)
        {
            was_CR = true;
            if (data == '\n')
            {
                was_CR = false;
                if (converter(GpsData.str(), LoRaPayLoad)){
                    dataValid = true;
                    gpio_put(PICO_DEFAULT_LED_PIN, true);
                    std::cout  << LoRaPayLoad << std::endl;
                } // one full line was read
            }
        }
        else
        {
            GpsData << data; // collect Data
            // std::cout << data;
        }
    }
    return 0;
}

