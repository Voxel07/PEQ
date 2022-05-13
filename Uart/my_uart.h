#ifndef MYUART_H
#define MYUART_H

#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <iostream>

#include "uartDefines.h"

class uart
{
private:
    uart_inst_t * m_uart;
    uint8_t m_tx;
    uint8_t m_rx;
    uint32_t m_baudrate;
public:
//Ctor
    uart(uart_inst_t *uart, uint8_t tx, uint8_t rx, long baudrate);
    ~uart();

//Methodes
    void write(const std::string& message) const;
    std::string read()const;
    char readC();
    void setFormat(uint data_bits, uint stop_bits, uart_parity_t parity )const;
};






#endif