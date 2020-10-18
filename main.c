/*
  AT25010  cc -o main main.c at25.c -lwiringPi -DAT25010
  AT25020  cc -o main main.c at25.c -lwiringPi -DAT25020
  AT25040  cc -o main main.c at25.c -lwiringPi -DAT25040
  AT25080  cc -o main main.c at25.c -lwiringPi -DAT25080
  AT25160  cc -o main main.c at25.c -lwiringPi -DAT25160
  AT25320  cc -o main main.c at25.c -lwiringPi -DAT25320
  AT25640  cc -o main main.c at25.c -lwiringPi -DAT25640
  AT25128  cc -o main main.c at25.c -lwiringPi -DAT25128
  AT25256  cc -o main main.c at25.c -lwiringPi -DAT25256
  AT25512  cc -o main main.c at25.c -lwiringPi -DAT25512

  M25010  cc -o main main.c at25.c -lwiringPi -DM25010
  M25020  cc -o main main.c at25.c -lwiringPi -DM25020
  M25040  cc -o main main.c at25.c -lwiringPi -DM25040
  M25080  cc -o main main.c at25.c -lwiringPi -DM25080
  M25160  cc -o main main.c at25.c -lwiringPi -DM25160
  M25320  cc -o main main.c at25.c -lwiringPi -DM25320
  M25640  cc -o main main.c at25.c -lwiringPi -DM25640
  M25128  cc -o main main.c at25.c -lwiringPi -DM25128
  M25256  cc -o main main.c at25.c -lwiringPi -DM25256
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "at25.h"

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
#ifdef AT25010
	eeprom_model = A010;
#endif
#ifdef AT25020
	eeprom_model = A020;
#endif
#ifdef AT25040
	eeprom_model = A040;
#endif
#ifdef AT25080
	eeprom_model = A080;
#endif
#ifdef AT25160
	eeprom_model = A160;
#endif
#ifdef AT25320
	eeprom_model = A320;
#endif
#ifdef AT25640
	eeprom_model = A640;
#endif
#ifdef AT25128
	eeprom_model = A128;
#endif
#ifdef AT25256
	eeprom_model = A256;
#endif
#ifdef AT25512
	eeprom_model = A512;
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
