#ifndef INC_MCP3208T_READER_HPP_
#define INC_MCP3208T_READER_HPP_
#include <array>
#include "gpio.h"
#include "spi.h"
#include <map>

	enum class ADC_CHANNEL{
		CH_0,
		CH_1,
		CH_2,
		CH_3,
		CH_4,
		CH_5,
		CH_6,
		CH_7
	};

class Mcp3208t_reader{
private:
	std::map<ADC_CHANNEL, uint16_t> channel_config;

	std::array<uint16_t, 8> receive_data;
	std::array<uint16_t, 8> transmit_data;
	GPIO_TypeDef* nss_port;
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
