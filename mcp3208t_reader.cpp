#include "mcp3208t_reader.hpp"

Mcp3208t_reader::Mcp3208t_reader(SPI_HandleTypeDef& hspi,GPIO_TypeDef &nss_port, uint16_t &nss_pin):hspi(&hspi),nss_port(&nss_port),nss_pin(nss_pin){

}

void Mcp3208t_reader::init(){
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
	for(uint8_t i = 0; i < 8; i++){
		channel_config.insert(std::make_pair(static_cast<ADC_CHANNEL>(i), (i+8)<<12));
		receive_port.insert(std::make_pair(static_cast<ADC_CHANNEL>(i),receive_data[i]));
	}
}

void Mcp3208t_reader::update(ADC_CHANNEL adc_channel, uint32_t timeout){
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi,(uint8_t*)&(channel_config.at(adc_channel)), (uint8_t*)&(receive_port.at(adc_channel)), sizeof(receive_port.at(adc_channel)), timeout);
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

uint16_t Mcp3208t_reader::get(ADC_CHANNEL adc_channel){
	return receive_port.at(adc_channel);
}
