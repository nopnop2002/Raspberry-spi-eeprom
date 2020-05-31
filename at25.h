/*
  at25.h - Library for the SPI Serial EEPROM chip
*/
#ifndef _AT25_H_
#define _AT25_H_

#define AT25_WREN_CMD           0x06        /* Set Write Enable Latch */
#define AT25_WRDI_CMD           0x04        /* Reset Write Enable Latch */
#define AT25_RDSR_CMD           0x05        /* Read Status Register */
#define AT25_WRSR_CMD           0x01        /* Write Status Register */
#define AT25_READ_CMD           0x03        /* Read Data from Memory Array */
#define AT25_WRITE_CMD          0x02        /* Write Data to Memory Array */
 
#define DELAY_WAIT    1
#define	DEBUG	0

#define UNUSED(a) ((void)(a))

// ATMEL
#define A010        10
#define A020        20
#define A040        40
#define A080        80
#define A160        160
#define A320        320
#define A640        640
#define A128        128
#define A256        256
#define A512        512

// STM
#define M010        110
#define M020        120
#define M040        140
#define M080        180
#define M160        1160
#define M320        1320
#define M640        1640
#define M128        1128
#define M256        1256
#define M512        1512


struct eeprom
{
    int16_t _channel;
    int16_t _model;
    uint32_t _totalBytes;    // eeprom memory size
    int16_t _addrBits;        // number of address bit
    int16_t _pageSize;        // bytes per page
    int16_t _lastPage;        // last page
	char 	_name[16];
};

uint16_t eeprom_open(struct eeprom *dev, int16_t channel, int16_t model);
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

