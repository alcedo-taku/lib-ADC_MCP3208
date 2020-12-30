#include "mcp3208t_reader.hpp"

Mcp3208t_reader::Mcp3208t_reader(GPIO_TypeDef &nss_port, uint16_t &nss_pin):nss_port(&nss_port),nss_pin(nss_pin){

}

void Mcp3208t_reader::init(){
	HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

void Mcp3208t_reader::update(){

}
