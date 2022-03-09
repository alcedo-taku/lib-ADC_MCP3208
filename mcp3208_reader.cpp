#include <mcp3208_reader.hpp>

/**
 * コンストラクタ
 * @param hspi 使用するSPIのハンドル
 * @param ss_port SSピンとして設定したGPIOのPort
 * @param ss_pin SSピンとして設定したGPIOのPin
 */
MCP3208_reader::MCP3208_reader(
	SPI_HandleTypeDef& hspi,
	GPIO_TypeDef *ss_port,
	uint16_t ss_pin
):
	hspi(&hspi),
	ss_port(ss_port),
	ss_pin(ss_pin)
{
}

/**
 * 初期化関数（MCP3208に送るコマンドを作製）
 */
void MCP3208_reader::init(){
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_SET);
	for(uint8_t i = 0; i < 8; i++){
		/*データシート TABLE 5-2(p.19), FIGURE 6-1(p.22)を参照*/
		std::array<uint8_t,3> transmit_data = { (0b110 | i>>2), (i << 6), 0 };
		channel_config.insert(std::make_pair(static_cast<ADC_CHANNEL>(i), transmit_data));
	}
}

/**
 * ADCICと通信し、指定したChannelの値を更新する関数
 * @param adc_channel 更新したいChannel
 * @param timeout SPI通信のtimeout
 */
void MCP3208_reader::update(ADC_CHANNEL adc_channel, uint32_t timeout){
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi,(uint8_t*)&(channel_config[adc_channel]), (uint8_t*)&(receive_port[adc_channel]), sizeof(receive_port[adc_channel]), timeout);
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_SET);
}

/**
 * 指定したのChannelの値を取得する関数
 * @param adc_channel 取得したいChannel
 * @return uint16_t 指定したのChannelの値
 */
uint16_t MCP3208_reader::get(ADC_CHANNEL adc_channel){
	return static_cast<uint16_t>((receive_port.at(adc_channel)[1]<<8 | receive_port.at(adc_channel)[2])) <<3;
}
