#include "mcp3208t_reader.hpp"

/**
 * コンストラクタ
 * @param hspi SPI番号
 * @param nss_port SSピンのPort 
 * @param nss_pin SSピンのPin
 */
Mcp3208t_reader::Mcp3208t_reader(SPI_HandleTypeDef& hspi,GPIO_TypeDef *nss_port, uint16_t nss_pin):hspi(&hspi),nss_port(nss_port),nss_pin(nss_pin){

}

/**
 * 初期化関数
 */
void Mcp3208t_reader::init(){
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
	for(uint8_t i = 0; i < 8; i++){
		transmit_data[i][0] = 0b110 | i>>2;
		transmit_data[i][1] = i << 6;
		transmit_data[i][2] = 0;
		channel_config.insert(std::make_pair(static_cast<ADC_CHANNEL>(i), transmit_data[i]));
			receive_port.insert(std::make_pair(static_cast<ADC_CHANNEL>(i),receive_data[i]));
	}
}

/**
 * ADCICと通信し、指定したChannelの値を更新する関数
 * @param adc_channel 更新したいChannel
 * @param timeout SPI通信のtimeout
 */
void Mcp3208t_reader::update(ADC_CHANNEL adc_channel, uint32_t timeout){
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi,(uint8_t*)&(channel_config[adc_channel]), (uint8_t*)&(receive_port[adc_channel]), sizeof(receive_port[adc_channel]), timeout);
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

/**
 * 指定したのChannelの値を取得する関数
 * @param adc_channel 取得したいChannel
 * @return uint16_t 指定したのChannelの値
 */
uint16_t Mcp3208t_reader::get(ADC_CHANNEL adc_channel){
	return static_cast<uint16_t>((receive_port.at(adc_channel)[1]<<8 | receive_port.at(adc_channel)[2]))<<3;
}
