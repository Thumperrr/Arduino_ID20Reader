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