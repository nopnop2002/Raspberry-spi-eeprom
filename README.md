# Raspberry-spi-eeprom

SPI EEPROM Access Library for RaspberryPi

---

# Software requirement

WiringPi Library   

---

# Memory size

## ST Micro   
10 MHz Clock Rate.   
There are several variations in the M95 series.   
4.5 V to 5.5 V for M95xxx   
2.5 V to 5.5 V for M95xxx-W   
1.8 V to 5.5 V for M95xxx-R   

__M95xxx don't work with Raspberry Pi__

|Device|# of Bits|# of Bytes|Byte Address range|Page Size(Byte)|Page Address Range|
|:---|:---|:---|:---|:---|:---|
|M95080|8K|1024|0x00-0x3FF|32|0-31|
|M95160|16K|2048|0x00-0x7FF|32|0-63|
|M95320|32K|4096|0x00-0xFFF|32|0-127|
|M95640|64K|8192|0x00-0x1FFF|32|0-255|
|M95128|128K|16384|0x00-0x3FFF|64|0-127|
|M95256|256K|32768|0x00-0x7FFF|64|0-255|

## ATMEL   

|Device|# of Bits|# of Bytes|Byte Address Range|Page Size(Byte)|Page Address Range|
|:---|:---|:---|:---|:---|:---|
|AT25010|1K|128|0-0x7F|8|0-15|
|AT25020|2K|256|0-0xFF|8|0-31|
|AT25040|4K|512|0-0x1FF|8|0-63|
|AT25080|8K|1024|0-0x3FF|32|0-31|
|AT25160|16K|2048|0-0x7FF|32|0-63|
|AT25320|32K|4096|0-0xFFF|32|0-127|
|AT25640|64K|8192|0-0x1FFF|32|0-255|
|AT25128|128K|16384|0-0x3FFF|64|0-255|
|AT25256|256K|32768|0-0x7FFF|64|0-511|
|AT25512|512K|65536|0-0xFFFF|128|0-511|

---

# Build

## ST Micro   
for M95080   
cc -o main main.c eeprom.c -lwiringPi -DM95080

for M95160   
cc -o main main.c eeprom.c -lwiringPi -DM95160

for M95320   
cc -o main main.c eeprom.c -lwiringPi -DM95320

for M95640   
cc -o main main.c eeprom.c -lwiringPi -DM95640

for M95128   
cc -o main main.c eeprom.c -lwiringPi -DM95128

for M95256   
cc -o main main.c eeprom.c -lwiringPi -DM95256

## ATMEL   
for AT25010   
cc -o main main.c eeprom.c -lwiringPi -DAT25010

for AT25020   
cc -o main main.c eeprom.c -lwiringPi -DAT25020

for AT25040   
cc -o main main.c eeprom.c -lwiringPi -DAT25040

for AT25080   
cc -o main main.c eeprom.c -lwiringPi -DAT25080

for AT25160   
cc -o main main.c eeprom.c -lwiringPi -DAT25160

for AT25320   
cc -o main main.c eeprom.c -lwiringPi -DAT25320

for AT25640   
cc -o main main.c eeprom.c -lwiringPi -DAT25640

for AT25128   
cc -o main main.c eeprom.c -lwiringPi -DAT25128

for AT25256   
cc -o main main.c eeprom.c -lwiringPi -DAT25256

for AT25512   
cc -o main main.c eeprom.c -lwiringPi -DAT25512

---

# stdout
![AT25010](https://user-images.githubusercontent.com/6020549/83345860-a0e17f80-a352-11ea-9515-fe1706c5eafa.jpg)

---

# API

```
// Open device
uint32_t eeprom_open(struct eeprom *dev, int16_t channel, uint32_t model);

// Get EEPROM memory byte size
uint32_t eeprom_totalBytes(struct eeprom *dev);

// Get EEPROM page number
int16_t eeprom_lastPage(struct eeprom *dev);

// Get EEPROM page byte size
uint16_t eeprom_pageSize(struct eeprom *dev);

// Get EEPROM name
char * eeprom_name(struct eeprom *dev);

// Read data from EEPROM
uint8_t eeprom_readByte(struct eeprom *dev, uint16_t address);

// Write data to EEPROM by address
void eeprom_writeByte(struct eeprom *dev, uint16_t address, uint8_t data);

// Write data to EEPROM by page
void eeprom_writePage(struct eeprom *dev, uint16_t pages, uint8_t *data);
```

---

# Wireing

![Raspberry-at25-SPI](https://user-images.githubusercontent.com/6020549/83345856-91623680-a352-11ea-9394-543a0cb01847.jpg)

