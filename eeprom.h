/*
  eeprom.h - Library for the SPI Serial EEPROM chip
*/
#ifndef _EEPROM_H_
#define _EEPROM_H_

#define EEPROM_WREN_CMD           0x06        /* Set Write Enable Latch */
#define EEPROM_WRDI_CMD           0x04        /* Reset Write Enable Latch */
#define EEPROM_RDSR_CMD           0x05        /* Read Status Register */
#define EEPROM_WRSR_CMD           0x01        /* Write Status Register */
#define EEPROM_READ_CMD           0x03        /* Read Data from Memory Array */
#define EEPROM_WRITE_CMD          0x02        /* Write Data to Memory Array */
 
#define DELAY_WAIT    1
#define	DEBUG	0

#define UNUSED(a) ((void)(a))

struct eeprom
{
	int16_t _channel;
	uint32_t _model;
	uint32_t _totalBytes;     // eeprom memory size
	int16_t _addrBits;        // number of address bit
	int16_t _pageSize;        // bytes per page
	int16_t _lastPage;        // last page
	char 	_name[16];
};

uint32_t eeprom_open(struct eeprom *dev, int16_t channel, uint32_t model);
void write_register(struct eeprom *dev, uint8_t cmd);
uint8_t read_register(struct eeprom *dev);
void wait_ready(struct eeprom *dev);
void write_enable(struct eeprom *dev);
uint8_t eeprom_readStatus(struct eeprom *dev);
void eeprom_writeStatus(struct eeprom *dev, uint8_t status);
void eeprom_writeByte(struct eeprom *dev, uint16_t address, uint8_t data);
void eeprom_writePage(struct eeprom *dev, uint16_t pages, uint8_t *data);
uint8_t eeprom_readByte(struct eeprom *dev, uint16_t address);
uint32_t eeprom_totalBytes(struct eeprom *dev);
int16_t eeprom_lastPage(struct eeprom *dev);
uint16_t eeprom_pageSize(struct eeprom *dev);
char * eeprom_name(struct eeprom *dev);

#endif

