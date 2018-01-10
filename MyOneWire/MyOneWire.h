/*

*/

#pragma once
typedef unsigned char uint8_t;

enum  command {
	SEARCH_ROM        = 0xF0,
	READ_ROM          = 0x33,
	MATCH_ROM         = 0x55,
	SKIP_ROM          = 0xCC,
	ALARM_SEARCH      = 0xEC,

	CONVERT_T         = 0x44,
	READ_SCRATCHPAD   = 0xBE,
	WRITE_SCRATCHPAD  = 0x4E,
	COPY_SCRATCHPAD   = 0x48,
	RECALL_E2         = 0xB8,
	READ_POWER_SUPPLY = 0xB4
};

class MyOneWire 
{
private:
	const uint8_t pinIO_;        // пин с которым работаем

public:
	MyOneWire(uint8_t);

	int resetPresence();        // инициализаци¤ (сброс - присутствие)
	void masterWrite(uint8_t);  // отправляем данные побайтно 8 бит 
	uint8_t masterRead();       // принимаем данные побитно, начиная с младшего
};
