#include "my_uart.h"

#include <sstream>

//Ctor
uart::uart(uart_inst_t *uart, uint8_t tx, uint8_t rx, long baudrate)
:m_uart(uart),m_tx(tx),m_rx(rx),m_baudrate(baudrate)
{
    uart_init(m_uart, m_baudrate);

    // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    // gpio_init(m_tx);
    // gpio_init(m_rx);
    // gpio_set_dir(m_tx, GPIO_OUT);
    // gpio_set_dir(m_rx, GPIO_IN);
    gpio_set_function(m_tx, GPIO_FUNC_UART);
    gpio_set_function(m_rx, GPIO_FUNC_UART);

}

uart::~uart()
{
    uart_deinit(m_uart);
}

void uart::write(const std::string& message) const
{
    if (!uart_is_writable(m_uart)) return;

    uart_puts(m_uart, message.c_str());
}

std::string uart::read() const{

    std::stringstream werte;

    while (uart_is_readable(m_uart))
    {
        werte << uart_getc(m_uart);
    }

    return werte.str();
}
char uart::readC()
{
    // if(uart_is_readable(m_uart)) return 0x7F;
    return uart_getc(m_uart);
}

void uart::setFormat(uint data_bits, uint stop_bits, uart_parity_t parity ) const{
    uart_set_format(m_uart,data_bits,stop_bits,parity);
}

