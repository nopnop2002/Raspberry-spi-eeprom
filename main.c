/*
  AT25010  cc -o main main.c eeprom.c -lwiringPi -DAT25010
  AT25020  cc -o main main.c eeprom.c -lwiringPi -DAT25020
  AT25040  cc -o main main.c eeprom.c -lwiringPi -DAT25040
  AT25080  cc -o main main.c eeprom.c -lwiringPi -DAT25080
  AT25160  cc -o main main.c eeprom.c -lwiringPi -DAT25160
  AT25320  cc -o main main.c eeprom.c -lwiringPi -DAT25320
  AT25640  cc -o main main.c eeprom.c -lwiringPi -DAT25640
  AT25128  cc -o main main.c eeprom.c -lwiringPi -DAT25128
  AT25256  cc -o main main.c eeprom.c -lwiringPi -DAT25256
  AT25512  cc -o main main.c eeprom.c -lwiringPi -DAT25512

  M95010  cc -o main main.c eeprom.c -lwiringPi -DM95010
  M95020  cc -o main main.c eeprom.c -lwiringPi -DM95020
  M95040  cc -o main main.c eeprom.c -lwiringPi -DM95040
  M95080  cc -o main main.c eeprom.c -lwiringPi -DM95080
  M95160  cc -o main main.c eeprom.c -lwiringPi -DM95160
  M95320  cc -o main main.c eeprom.c -lwiringPi -DM95320
  M95640  cc -o main main.c eeprom.c -lwiringPi -DM95640
  M95128  cc -o main main.c eeprom.c -lwiringPi -DM95128
  M95256  cc -o main main.c eeprom.c -lwiringPi -DM95256
  M95512  cc -o main main.c eeprom.c -lwiringPi -DM95512
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "eeprom.h"

#define GPIO_CS    10
#define SPI_CHANNEL 0 // /dev/spidev0.0
//#define SPI_CHANNEL 1 // /dev/spidev0.1

void dump(char * title, int bits, uint8_t *dt, uint16_t n) {
	int clm = 0;
	uint16_t data;
	uint16_t saddr =0;
	uint16_t eaddr =n-1;

	printf("-------------------- [%s] --------------------\n", title);
	uint16_t addr;
	for (addr = saddr; addr <= eaddr; addr++) {
		data = dt[addr];
		if (clm == 0) {
			printf("%05x: ",addr);
		}

		if (bits == 8)	printf("%02x ",data);
		if (bits == 16) printf("%04x ",data);

		clm++;
		if (bits == 8 && clm == 16) {
			printf("\n");
			clm = 0;
		}
		if (bits == 16 && clm == 8) {
			printf("\n");
			clm = 0;
		}
	}
	printf("-------------------- [%s] --------------------\n", title);
}



int main(int argc, char *argv[])
{
	// set EEPROM memory size
	int eeprom_model = 0;

// ATMEL
#ifdef AT25010
	eeprom_model = 25010;
#endif
#ifdef AT25020
	eeprom_model = 25020;
#endif
#ifdef AT25040
	eeprom_model = 25040;
#endif
#ifdef AT25080
	eeprom_model = 25080;
#endif
#ifdef AT25160
	eeprom_model = 25160;
#endif
#ifdef AT25320
	eeprom_model = 25320;
#endif
#ifdef AT25640
	eeprom_model = 25640;
#endif
#ifdef AT25128
	eeprom_model = 25128;
#endif
#ifdef AT25256
	eeprom_model = 25256;
#endif
#ifdef AT25512
	eeprom_model = 25512;
#endif

// ST Micro
#ifdef M95010
	eeprom_model = 95010;
#endif
#ifdef M95020
	eeprom_model = 95020;
#endif
#ifdef M95040
	eeprom_model = 95040;
#endif
#ifdef M95080
	eeprom_model = 95080;
#endif
#ifdef M95160
	eeprom_model = 95160;
#endif
#ifdef M95320
	eeprom_model = 95320;
#endif
#ifdef M95640
	eeprom_model = 95640;
#endif
#ifdef M95128
	eeprom_model = 95128;
#endif
#ifdef M95256
	eeprom_model = 95256;
#endif

	printf("eeprom_model=%d\n",eeprom_model);
	if (eeprom_model == 0) {
		printf("EEPROM model not found\n");
		return 1;
	}

	// open SPI device
	struct eeprom dev;
	char device[20];
	struct stat st;
	int ret;
	snprintf(device, 19, "/dev/spidev0.%d", SPI_CHANNEL);
	ret = stat(device, &st);
	//printf("%s=%d\n", device,ret);
	if (ret != 0) {
		printf("spi device[%s] not found\n", device);
		return 1;
	}

	// Start SPI with 2MHz
	if (wiringPiSPISetup(SPI_CHANNEL, 2000000) < 0) {
	//if (wiringPiSPISetup(SPI_CHANNEL, 8000000) < 0) {
		printf("wiringPiSPISetup failed:\n");
		return 1;
	}

	uint32_t eeprom_totalBytes = eeprom_open(&dev, SPI_CHANNEL, eeprom_model);
	int16_t lastPage = eeprom_lastPage(&dev);
	uint16_t pageSize = eeprom_pageSize(&dev);
	char *name = eeprom_name(&dev);
	printf("name=%s\n", name);
	printf("eeprom_totalBytes=%d lastPage=%d pageSize=%d\n",eeprom_totalBytes, lastPage, pageSize);

	uint16_t mem_addr;
	uint8_t data;
	uint8_t rdata[128];
	uint16_t i;

	// clear first 64 bytes
	mem_addr = 0;
	for(i=0;i<64;i++) {
		data = 0xff;
		eeprom_writeByte(&dev, mem_addr, data);
		mem_addr++;
	}

	// write first 64 bytes
	mem_addr = 0;
	for(i=0;i<64;i++) {
		data = i;
		eeprom_writeByte(&dev, mem_addr, data);
		mem_addr++;
	}

	// read first 64 bytes
	memset(rdata, 0, sizeof(rdata));
	mem_addr = 0;
	for(i=0;i<64;i++) {
		rdata[i] = eeprom_readByte(&dev, mem_addr);
		mem_addr++;
	}
	char title[64];
	sprintf(title,"address 0-63");
	dump(title, 8, rdata, 64);

	// clear last 64 bytes
	mem_addr = eeprom_totalBytes - 64;
	for(i=0;i<64;i++) {
		data = 0xff;
		eeprom_writeByte(&dev, mem_addr, data);
		mem_addr++;
	}

	// write last 64 bytes
	mem_addr = eeprom_totalBytes - 64;
	for(i=0;i<64;i++) {
		data = 0x3f - i;
		eeprom_writeByte(&dev, mem_addr, data);
		mem_addr++;
	}

	// read last 64 bytes
	memset(rdata, 0, sizeof(rdata));
	mem_addr = eeprom_totalBytes - 64;
	for(i=0;i<64;i++) {
		rdata[i] = eeprom_readByte(&dev, mem_addr);
		mem_addr++;
	}
	sprintf(title,"address %d-%d", eeprom_totalBytes - 64, eeprom_totalBytes);
	dump(title, 8, rdata, 64);

	// write last page
	memset(rdata, 0xff, 128);
	eeprom_writePage(&dev, lastPage, rdata);

	// read last 64 bytes
	memset(rdata, 0, sizeof(rdata));
	mem_addr = eeprom_totalBytes - 64;
	for(i=0;i<64;i++) {
		rdata[i] = eeprom_readByte(&dev, mem_addr);
		mem_addr++;
	}
	sprintf(title,"address %d-%d", eeprom_totalBytes - 64, eeprom_totalBytes);
	dump(title, 8, rdata, 64);
} 
