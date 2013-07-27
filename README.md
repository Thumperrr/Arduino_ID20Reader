ID20Reader Arduino Library
==========================

## Description
This is a simple, minimalistic library created to simplify the use of the ID12 or ID20 RFID reader for the Arduino.
The library behaves similarly to the Serial library that comes with the Arduino.

## Contact
Emails can be sent to sbhall808(at)hotmail(dot)com with any questions or requests. 
You can also post in the issues on GitHub if you find problems or have general questions.

## Testing
So far this library has only been tested with an Arduino Uno (rev 3.) If you have success with other versions of the arduino, I would very much like to know about it!

## Download and Installation
[Download the library by clicking here](https://github.com/Thumperrr/Arduino_ID20Reader/archive/master.zip).
Unzip the library to any location.
Move the ID20Reader folder into your Arduino Libraries directory.
Begin coding.

Note:
On Mac and Linux, the library folder will be something like `Documents\Arduino\libraries\`
On Windows, it will be something like `My Documents/Arduino/libraries/`

## Example code
```C++
#include <SoftwareSerial.h> // Dependency of ID20Reader. Must include in main file
                            // Due to Arduino software limitations.
#include <ID20Reader.h>

int rx_pin = 9; //Data input pin
int tx_pin = 8; //Unused, but must be defined. (Nothing is sent from the Arduino to the reader.)

ID20Reader rfid(rx_pin, tx_pin); //Create an instance of ID20Reader.

void setup() {
  Serial.begin(9600);
  Serial.println("RFID Reader - Swipe a card ~~~~~");
}

void loop() {
  rfid.read(); //Receive a tag from the reader if available
  
  if(rfid.available()) //a tag has been read
  {
    String code = rfid.get(); //Get the tag
    Serial.println(code); //Print the tag to the serial monitor
  }
}
```
