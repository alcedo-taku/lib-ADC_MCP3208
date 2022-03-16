#include <mcp3208.hpp>

namespace mcp3208{

/**
 * コンストラクタ
 * @param hspi 使用するSPIのハンドル
 * @param ss_port SSピンとして設定したGPIOのPort
 * @param ss_pin SSピンとして設定したGPIOのPin
 */
MCP3208::MCP3208(
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
void MCP3208::init(){
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_SET);
	for(uint8_t i = 0; i < 8; i++){
		/*データシート TABLE 5-2(p.19), FIGURE 6-1(p.22)を参照*/
		transmit_data[i] = { (0b110 | i>>2), (i << 6), 0 };
	}
}

/**
 * ADCICと通信し、指定したChannelの値を更新する関数
 * @param adc_channel 更新したいChannel
 * @param timeout SPI通信のtimeout
 */
void MCP3208::update(Channel adc_channel, uint32_t timeout){
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi,(uint8_t*)&(transmit_data[(uint8_t)adc_channel]), (uint8_t*)&(receive_data[(uint8_t)adc_channel]), sizeof(receive_data[(uint8_t)adc_channel]), timeout);
	HAL_GPIO_WritePin(ss_port, ss_pin, GPIO_PIN_SET);
}

/**
 * ADCICと通信し、すべてのChannelの値を更新する関数
 * @param timeout SPI通信のtimeout
 */
void MCP3208::update(uint32_t timeout){
	for(uint8_t i = 0; i < 8; i++){
		update( (Channel)i, timeout );
	}
}

/**
 * 指定したのChannelの値を取得する関数
 * @param adc_channel 取得したいChannel
 * @return uint16_t 指定したのChannelの値
 */
uint16_t MCP3208::get(Channel adc_channel){
	return (uint16_t)(receive_data[(uint8_t)adc_channel][1]<<8 | receive_data[(uint8_t)adc_channel][2]) <<3;
}

/**
 * すべてのChannelの値(unordered_map)を取得する関数
 * @return std::array<uint16_t,8> すべてのChannelの値を含む配列
 */
std::array<uint16_t,8> MCP3208::get(){
	std::array<uint16_t,8> receive_data;
	for(uint8_t i = 0; i < 8; i++){
		receive_data[i] = get( (Channel)i );
	}
	return receive_data;
}

} // namespace mcp3208
