#include "Arduino.h"
#include "MyOneWire.h"


MyOneWire::MyOneWire(uint8_t pin) : pinIO_(pin)
{
	
}

/*** сбросПрисутствие ***/
int MyOneWire::resetPresence()
{
	// инициализация по шине 1-Wire, посылаем сигнал сброса
	pinMode(pinIO_, OUTPUT); // прижимаем шину к 0
	delayMicroseconds(480); // ... на 480мкс
	pinMode(pinIO_, INPUT); // отпускаем к 1
	delayMicroseconds(60); // ... и ждем 15-60мкс заряжаем конденсаторы
						   
	unsigned long int t = micros();
	// получаем ответ присутствия от датчика "0" - 60-240мкс
	while (1)
	{
		if (digitalRead(pinIO_) == LOW)
		{
			if ((micros() - t) > 250)
			{
				return 250;   // выход при зацикливании
			}
		}
		else
		{
			if ((micros() - t) < 60) return -60;
			break;
		}
	}
	while ((micros() - t) < 500); // ждем до конца инициализации

	return 1;
}

/*** Метод отправки данных по шине 1-Wire ***/
void MyOneWire::masterWrite(uint8_t command)
{
	for (int i = 0; i < 8; i++)
	{
		if (((command & 0x01 << i) >> i) == 0x01)
		{
			// если 1 отправляем
			pinMode(pinIO_, OUTPUT);    // прижимаем к 0
			delayMicroseconds(8);      // . . . и держим не дольше 15мкс
			pinMode(pinIO_, INPUT);
			delayMicroseconds(60);     // отпускаем линию до конца тайм-слота 60мкс,
									   // . . . тут идет заряд конденсатора при паразитном питании
		}
		else
		{
			// если 0 отправляем
			pinMode(pinIO_, OUTPUT); // прижимаем к 0
			delayMicroseconds(68);  // . . . и держим от 60мкс до 120мкс
			pinMode(pinIO_, INPUT);
			delayMicroseconds(60);  // отпускаем к 1 и ждем от 1 мкс
		}
	}
}

/*** Метод считывания данных на шине 1-Wire ***/
uint8_t  MyOneWire::masterRead()
{
	uint8_t bit;
	// читаем ответ, прижимаем к 0 на от 1мкс и до < 15мкс слушаем ответ
	delayMicroseconds(60);
	pinMode(pinIO_, OUTPUT);
	delayMicroseconds(4);
	pinMode(pinIO_, INPUT); // отпускаем и до  < 15мкс смотрим ответ - 0 или 1
	delayMicroseconds(4);

	if (digitalRead(pinIO_) == LOW)
	{
		bit = 0x00; // возвращаем 0
	}
	else
	{
		bit = 0x01; // возвращаем 1
	}
	//delayMicroseconds(68);
	return bit;
}