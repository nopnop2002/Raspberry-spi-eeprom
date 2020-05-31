# Raspberry-at25

SPI EEPROM Access Library for RaspberryPi

---

# Memory size

|Device|# of Bits|# of Bytes|Page Size(Byte)|Address Range|Block Range|
|:---|:---|:---|:---|:---|:---|
|25010|1K|128|8|0-0x7f|0-15|
|25020|2K|256|8|0-0xff|0-31|
|25040|4K|512|8|0-0x1ff|0-63|
|25080|8K|1024|32|0-0x3ff|0-31|
|25160|16K|2048|32|0-0x7ff|0-63|
|25320|32K|4096|32|0-0xfff|0-127|
|25640|64K|8192|32|0-0x1fff|0-255|
|25128|128K|16384|64|0-0x3fff|0-255|
|25256|256K|32768|64|0-0x7fff|0-511|
|25512|512K|65536|128|0-0x7fff|0-511|

---

# Software requirement

WiringPi Library   

---

# Build

for 25010   
cc -o main main.c at25.c -lwiringPi -DAT25010

for 25020   
cc -o main main.c at25.c -lwiringPi -DAT25020

for 25040   
cc -o main main.c at25.c -lwiringPi -DAT25040

for 25080   
cc -o main main.c at25.c -lwiringPi -DAT25080

for 25160   
cc -o main main.c at25.c -lwiringPi -DAT25160

for 25320   
cc -o main main.c at25.c -lwiringPi -DAT25320

for 25640   
cc -o main main.c at25.c -lwiringPi -DAT25640

for 25128   
cc -o main main.c at25.c -lwiringPi -DAT25128

for 25256   
cc -o main main.c at25.c -lwiringPi -DAT25256

---

- 25010   
![AT25010](https://user-images.githubusercontent.com/6020549/83345860-a0e17f80-a352-11ea-9515-fe1706c5eafa.jpg)

- 25020   
![AT25020](https://user-images.githubusercontent.com/6020549/83345862-ae970500-a352-11ea-8172-4bde0962ffb7.jpg)

- 25040   
![AT25640](https://user-images.githubusercontent.com/6020549/83345861-ad65d800-a352-11ea-90c5-0e6697cebd65.jpg)

- 25080   
![AT25080](https://user-images.githubusercontent.com/6020549/83345864-b060c880-a352-11ea-998a-67d2a7bd0e27.jpg)

- 25160   
![AT25160](https://user-images.githubusercontent.com/6020549/83345868-b22a8c00-a352-11ea-8293-e8196d1663c4.jpg)

- 25320   
![AT25320](https://user-images.githubusercontent.com/6020549/83345873-b48ce600-a352-11ea-85ea-787d8d4b70e1.jpg)

- 25640   
![AT25640](https://user-images.githubusercontent.com/6020549/83345861-ad65d800-a352-11ea-90c5-0e6697cebd65.jpg)

- 25128   
![AT25128](https://user-images.githubusercontent.com/6020549/83345867-b191f580-a352-11ea-8e53-0bab88ba3a4b.jpg)

- 25256   
![AT25256](https://user-images.githubusercontent.com/6020549/83345871-b35bb900-a352-11ea-8b56-d8b23075ac2f.jpg)

---

# API

```
// Open device
uint16_t eeprom_open(struct eeprom *dev, int16_t channel, int16_t model);

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

