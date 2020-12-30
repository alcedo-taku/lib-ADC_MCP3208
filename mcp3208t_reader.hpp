#ifndef INC_MCP3208T_READER_HPP_
#define INC_MCP3208T_READER_HPP_
#include <array>

class Mcp3208t_reader{
private:
	std::array<uint16_t, 8> receive_data;
	std::array<uint16_t, 8> transmit_data;
	GPIO_TypeDef* nss_port;
	uint16_t nss_pin;
public:
	Mcp3208t_reader();
	void init();
	void update();
	void get();
	void update_all();
	void get_all();
};
#endif //INC_MCP3208T_READER_HPP_
