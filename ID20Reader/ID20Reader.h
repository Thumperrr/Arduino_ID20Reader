/*
The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.


    Created by Thumperrr
    http://github.com/Thumperrr
*/

#ifndef ID20READER_H
#define ID20READER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class ID20Reader
{
public:	
    ID20Reader(uint8_t _rx, uint8_t _tx);	
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


#endif /* ID20READER_H */