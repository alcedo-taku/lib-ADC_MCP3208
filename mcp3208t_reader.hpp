#ifndef INC_MCP3208T_READER_HPP_
#define INC_MCP3208T_READER_HPP_
#include <array>
#include "gpio.h"
#include "spi.h"
class Mcp3208t_reader{
private:
	std::array<uint16_t, 8> receive_data;
	std::array<uint16_t, 8> transmit_data;
	const GPIO_TypeDef* nss_port;
	const uint16_t nss_pin;
public:
	Mcp3208t_reader(GPIO_TypeDef &nss_port, uint16_t &nss_pin);
	void init();
	void update();
	void get();
	void update_all();
	void get_all();
};
#endif //INC_MCP3208T_READER_HPP_
