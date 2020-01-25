#include "sdcard.h"

#include <SD.h>
#include "debug.h"
#include "Arduino.h"

const int chipSelect = 4;    

sdcard::sdcard() {}

void sdcard::init() {
  pinMode(10, OUTPUT);
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin()) {
    DBG("%s\r\n","cannot begin");
  }
  DBG("%s\r\n","begin");
}
/*
Sd2Card card;
SdVolume volume;
SdFile root;
*/
void sdcard::info() {
  /*
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present."); 
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch(card.type()) {
  case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
  case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
  case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
  default:
    Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
  
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
  
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  */
}

#include "time.h"
void sdcard::write(const char * filename, const uint8_t * data, const size_t length) {
  File file=SD.open(filename,FILE_WRITE);
  if (!file) {
    DBG("%s:%s\r\n","could not open file",filename);
  } else { 
    DBG("%s:%s\r\n","opened file",filename);
    auto ret=file.write(data,length);
    DBG("wrote %u bytes in %s\r\n",ret,filename);
  }
  file.close();  
}

