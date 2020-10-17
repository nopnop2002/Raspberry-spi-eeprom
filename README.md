# Raspberry-AT25

AT25 series SPI EEPROM Access Library for RaspberryPi

---

# Memory size

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

# Software requirement

WiringPi Library   

---

# Build

for AT25010   
cc -o main main.c at25.c -lwiringPi -DAT25010

for AT25020   
cc -o main main.c at25.c -lwiringPi -DAT25020

for AT25040   
cc -o main main.c at25.c -lwiringPi -DAT25040

for AT25080   
cc -o main main.c at25.c -lwiringPi -DAT25080

for AT25160   
cc -o main main.c at25.c -lwiringPi -DAT25160

for AT25320   
cc -o main main.c at25.c -lwiringPi -DAT25320

for AT25640   
cc -o main main.c at25.c -lwiringPi -DAT25640

for AT25128   
cc -o main main.c at25.c -lwiringPi -DAT25128

for AT25256   
cc -o main main.c at25.c -lwiringPi -DAT25256

for AT25512   
cc -o main main.c at25.c -lwiringPi -DAT25512

---

- AT25010   
![AT25010](https://user-images.githubusercontent.com/6020549/83345860-a0e17f80-a352-11ea-9515-fe1706c5eafa.jpg)

- AT25020   
![AT25020](https://user-images.githubusercontent.com/6020549/83345862-ae970500-a352-11ea-8172-4bde0962ffb7.jpg)

- AT25040   
![AT25040](https://user-images.githubusercontent.com/6020549/83346120-bd7eb700-a354-11ea-912b-c2228e29714c.jpg)

- AT25080   
![AT25080](https://user-images.githubusercontent.com/6020549/83345864-b060c880-a352-11ea-998a-67d2a7bd0e27.jpg)

- AT25160   
![AT25160](https://user-images.githubusercontent.com/6020549/83345868-b22a8c00-a352-11ea-8293-e8196d1663c4.jpg)

- AT25320   
![AT25320](https://user-images.githubusercontent.com/6020549/83345873-b48ce600-a352-11ea-85ea-787d8d4b70e1.jpg)

- AT25640   
![AT25640](https://user-images.githubusercontent.com/6020549/83345861-ad65d800-a352-11ea-90c5-0e6697cebd65.jpg)

- AT25128   
![AT25128](https://user-images.githubusercontent.com/6020549/83345867-b191f580-a352-11ea-8e53-0bab88ba3a4b.jpg)

- AT25256   
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

