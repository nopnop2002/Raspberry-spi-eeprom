/*
  at25.c - Library for the SPI Serial EEPROM chip
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "at25.h"


uint16_t eeprom_open(struct eeprom *dev, int16_t channel, int16_t model)
{
	if (model == A010) {
		dev->_totalBytes = 128;
		dev->_addrBits = 7;
		dev->_pageSize = 8;
		dev->_lastPage = 15;
		strcpy(dev->_name, "AT25010");
	} else if (model == A020) {
		dev->_totalBytes = 256;
		dev->_addrBits = 8;
		dev->_pageSize = 8;
		dev->_lastPage = 31;
		strcpy(dev->_name, "AT25020");
	} else if (model == A040) {
		dev->_totalBytes = 512;
		dev->_addrBits = 9;
		dev->_pageSize = 8;
		dev->_lastPage = 63;
		strcpy(dev->_name, "AT25040");
	} else if (model == A080) {
		dev->_totalBytes = 1024;
		dev->_addrBits = 10;
		dev->_pageSize = 32;
		dev->_lastPage = 31;
		strcpy(dev->_name, "AT25080");
	} else if (model == A160) {
		dev->_totalBytes = 2048;
		dev->_addrBits = 11;
		dev->_pageSize = 32;
		dev->_lastPage = 63;
		strcpy(dev->_name, "AT25160");
	} else if (model == A320) {
		dev->_totalBytes = 4096;
		dev->_addrBits = 12;
		dev->_pageSize = 32;
		dev->_lastPage = 127;
		strcpy(dev->_name, "AT25320");
	} else if (model == A640) {
		dev->_totalBytes = 8192;
		dev->_addrBits = 13;
		dev->_pageSize = 32;
		dev->_lastPage = 255;
		strcpy(dev->_name, "AT25640");
	} else if (model == A128) {
		dev->_totalBytes = 16384;
		dev->_addrBits = 14;
		dev->_pageSize = 64;
		dev->_lastPage = 255;
		strcpy(dev->_name, "AT25128");
	} else if (model == A256) {
		dev->_totalBytes = 32768;
		dev->_addrBits = 15;
		dev->_pageSize = 64;
		dev->_lastPage = 511;
		strcpy(dev->_name, "AT25256");
	} else if (model == A512) {
		dev->_totalBytes = 65536;
		dev->_addrBits = 16;
		dev->_pageSize = 128;
		dev->_lastPage = 511;
		strcpy(dev->_name, "AT25512");
	}
	dev->_channel = channel;
	dev->_model = model;
	return dev->_totalBytes;
}

void wait_ready(struct eeprom *dev)
{
	//Wait until device is READY.
	uint8_t data[2];
	while(1) {
		data[0] = AT25_RDSR_CMD;
		data[1] = 0x0;
		int ret=wiringPiSPIDataRW (dev->_channel, data, 2);
		if ((data[1] & 0x01) == 0) break;
		usleep(DELAY_WAIT);
	}
}

void write_enable(struct eeprom *dev)
{
	//printf("write_enable start\n");
	//Wait until device is WRITE ENABLED.
	uint8_t data[2];

	while(1) {
		data[0] = AT25_WREN_CMD;
		int ret=wiringPiSPIDataRW (dev->_channel, data, 1);
		usleep(DELAY_WAIT);

		data[0] = AT25_RDSR_CMD;
		data[1] = 0x0;
		ret=wiringPiSPIDataRW (dev->_channel, data, 2);
		//printf("write_enable data[1]=%x\n",data[1]);
		//if ((data[1] & 0x02) == 0x02) break;
		if (data[1] == 0x02) break;
		usleep(DELAY_WAIT);
	}
}

void eeprom_writeByte(struct eeprom *dev, uint16_t address, uint8_t data)
{
	write_enable(dev);

	uint8_t index;
	uint8_t work[4];
	work[0] = AT25_WRITE_CMD;
	if (dev->_addrBits == 9 && address > 0xff) work[0] = work[0] | 0x8;
if(DEBUG)printf("[write_byte] address=0x%x work[0]=0x%x\n",address, work[0]);

	if (dev->_addrBits < 10) {
		work[1] = (address & 0xFF);			//send LSByte address
		work[2] = data;
		int ret=wiringPiSPIDataRW (dev->_channel, work, 3);
	} else {
		work[1] = (address & 0x0FF00) >> 8;	//send MSByte address first
		work[2] = (address & 0x0FF);		//send LSByte address
		work[3] = data;
		int ret=wiringPiSPIDataRW (dev->_channel, work, 4);
	}

	wait_ready(dev);
}

void eeprom_writePage(struct eeprom *dev, uint16_t pages, uint8_t *data)
{
	write_enable(dev);

	uint8_t index;
	uint8_t *work = (uint8_t *)malloc(128);
	uint16_t address = pages * dev->_pageSize;
	work[0] = AT25_WRITE_CMD;
	if (dev->_addrBits == 9 && address > 0xff) work[0] = work[0] | 0x8;
if(DEBUG)printf("[write_pageSize] address=%x work[0]=%x\n",address, work[0]);

	if (dev->_addrBits < 10) {
		work[1] = (address & 0xFF);		 //send LSByte address
		index = 2;
	} else {
		work[1] = (address & 0x0FF00) >> 8;   //send MSByte address first
		work[2] = (address & 0x0FF);	  //send LSByte address
		index = 3;
	}

if(DEBUG)printf("[write_pageSize] _pageSize=%d\n", dev->_pageSize);
	for (int i=0;i<dev->_pageSize;i++)
		work[index+i] = data[i];
	int ret=wiringPiSPIDataRW (dev->_channel, work, index+dev->_pageSize);
	free (work);

	wait_ready(dev);
}

uint8_t eeprom_readByte(struct eeprom *dev, uint16_t address)
{
	uint8_t work[4];
	work[0] = AT25_READ_CMD;
	if (dev->_addrBits == 9 && address > 0xff) work[0] = work[0] | 0x8;
if(DEBUG)printf("[read_byte] address=0x%x work[0]=0x%x\n",address, work[0]);

	uint8_t data;
	if (dev->_addrBits < 10) {
		work[1] = (address & 0xFF);			//send LSByte address
		work[2] = 0;
		int ret=wiringPiSPIDataRW (dev->_channel, work, 3);
		data = work[2];
	} else {
		work[1] = (address & 0x0FF00) >> 8;	//send MSByte address first
		work[2] = (address & 0x0FF);		//send LSByte address
		work[3] = 0;
		int ret=wiringPiSPIDataRW (dev->_channel, work, 4);
		data = work[3];
	}
	return (data);
}

uint32_t eeprom_totalBytes(struct eeprom *dev)
{
	return dev->_totalBytes;
}

int16_t eeprom_lastPage(struct eeprom *dev)
{
	return dev->_lastPage;
}

uint16_t eeprom_pageSize(struct eeprom *dev)
{
	return dev->_pageSize;
}

char * eeprom_name(struct eeprom *dev)
{
	return dev->_name;
}


