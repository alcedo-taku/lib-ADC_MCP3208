#include "mcp3208t_reader.hpp"

Mcp3208t_reader::Mcp3208t_reader(GPIO_TypeDef &nss_port, uint16_t &nss_pin):nss_port(&nss_port),nss_pin(nss_pin){

}

