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

#include "ID20Reader.h"

ID20Reader::ID20Reader(uint8_t _rx, uint8_t _tx) 
    : RFIDSerial(_rx, _tx), is_available(false)
{
    RFIDSerial.begin(9600);
}

void ID20Reader::read() 
{
    byte val = 0;
    byte tempbyte = 0;
    byte bytesread = 0;
    byte ID[6];
    if(RFIDSerial.available() > 0) 
    {
        if((val = RFIDSerial.read()) == 0x02) 
        { //Receiving 0x02 indicates the beginning of data
            bytesread = 0;
            while(bytesread < 12) 
            {
                if(RFIDSerial.available() > 0)
                {
                    val = RFIDSerial.read();
                    if(val == 0x0D || val == 0x0A || val == 0x03 || val == 0x02) //stop reading, you're no longer in the data range.
                        break;
                    
                    //convert received ascii characters to hex (must be in hex to calculate checksum)
                    if(val >= '0' && val <= '9')
                        val = val - '0';
                    else if(val >= 'A' && val <= 'F')
                        val = val + 10 - 'A';
                    
                    //combine every two received hex characters (4 bits each) into one hex byte
                    if((bytesread & 1) == 1) 
                        ID[bytesread >> 1] = (val | (tempbyte << 4));
                    else
                        tempbyte = val;
                    ++bytesread;
                }
            }
        }
    }	
    if(bytesread == 12) 
    { //read a full code
        //calculate the checksum for the code
        byte checksum = 0;
        for(int i = 0; i < 5; ++i)
            checksum ^= ID[i];
                
        if(checksum == ID[5]) 
        { //if the checksums are equal, add the ID to the queue.
            String temp;
            for(byte i = 0; i < 5; ++i) 
            {	
                if(ID[i] < 16)
                    temp += "0" + String(ID[i], HEX);		
                else 
                    temp += String(ID[i], HEX);
            }			
            
            temp.toUpperCase();
            currentCode = temp;
        } else 
            currentCode = "ERROR_CHECKSUM";
        is_available = true;
    }
}

bool ID20Reader::available()
{
    return is_available;
}

String ID20Reader::get()
{
    if(available())
    {
        is_available = false;
        return currentCode;
    }    
}