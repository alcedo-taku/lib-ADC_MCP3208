#ifndef INC_MCP3208T_READER_HPP_
#define INC_MCP3208T_READER_HPP_
#include <array>
#include "gpio.h"
#include "spi.h"
#include <unordered_map>

/**
 * 各Channelを要素に持つenum class
 * MCP3208のチャンネルの指定に使用
 */
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

/**
 * ADコンバータ MCP3208 から値を読み取るクラス
 */
class Mcp3208t_reader{
private:
	std::unordered_map<ADC_CHANNEL, std::array<uint8_t,3>> channel_config;	//!< ICから値を受け取る変数
	std::unordered_map<ADC_CHANNEL, std::array<uint8_t,3>> receive_port;   	//!< ICに送る変数(値を取得したいChannelが格納)
	SPI_HandleTypeDef* hspi;												//!< 使用するSPIのハンドル
	GPIO_TypeDef* ss_port;													//!< SSピンとして設定したGPIOのPort
	const uint16_t ss_pin;													//!< SSピンとして設定したGPIOのPin
public:
	Mcp3208t_reader(SPI_HandleTypeDef& hspi,GPIO_TypeDef *ss_port, uint16_t ss_pin);
	void init();
	void update(ADC_CHANNEL adc_channel, uint32_t timeout);
	uint16_t get(ADC_CHANNEL adc_channel);
};

#endif //INC_MCP3208T_READER_HPP_
