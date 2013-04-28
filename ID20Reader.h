/*
 * RFIDReader.h
 * 
 * Class for controlling ID-12 and ID-20 RFID readers.
 * 
 * Pin1 - GND
 * Pin2 - Reset --- Arduino digital pin 2
 * Pin9 - Data (srx) --- Arduino digital pin 9
 * Pin10 - LED w/ 1K series resistor
 * Pin11 - 5V
 *
 * Created: 8/10/2012 6:19:13 PM
 *  Author: Steve
 */ 
#ifndef ID20READER_H
#define ID20READER_H

#include <Arduino.h>
#include "../SoftwareSerial/SoftwareSerial.h"

class ID20Reader
{
public:	
	ID20Reader(uint8_t _rx, uint8_t _tx, long _baud);	
	~ID20Reader() {}
	
	ID20Reader(const ID20Reader&); //prevent copying of this class
	ID20Reader &operator = (const ID20Reader&); //prevent copying of this class
	
	bool available(); //returns true if a code is available in the queue
	String get(); //returns the next code in the queue
	
	void read(); //needs to be called on every loop

private:
    String currentCode;
    bool is_available;
	SoftwareSerial RFIDSerial;
};


#endif /* RFIDREADER_H_ */