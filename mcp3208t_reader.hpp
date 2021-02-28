#ifndef INC_MCP3208T_READER_HPP_
#define INC_MCP3208T_READER_HPP_
#include <array>
#include "gpio.h"
#include "spi.h"
#include <unordered_map>

	enum class ADC_CHANNEL:uint8_t{
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
	std::unordered_map<ADC_CHANNEL, std::array<uint8_t,3>> channel_config;
	std::unordered_map<ADC_CHANNEL, std::array<uint8_t,3>> receive_port;
	std::array<std::array<uint8_t,3>, 8> receive_data;
	std::array<std::array<uint8_t,3>, 8> transmit_data;
	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* nss_port;
	const uint16_t nss_pin;
public:
	Mcp3208t_reader(SPI_HandleTypeDef& hspi,GPIO_TypeDef *nss_port, uint16_t nss_pin);
	void init();
	void update(ADC_CHANNEL adc_channel, uint32_t timeout);
	uint16_t get(ADC_CHANNEL adc_channel);
};
#endif //INC_MCP3208T_READER_HPP_
