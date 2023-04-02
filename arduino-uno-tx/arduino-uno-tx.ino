// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
const int UP = 2;
const int DOWN = 4;
const int LEFT = 7;
const int RIGHT = 8;

// ButtonState
int UPState = 0;
int DOWNState = 0;
int LEFTState = 0;
int RIGHTState = 0;
char msg = '0';
void setup()
{
    // Initialize ASK Object
    rf_driver.init();

    //Buttons
     pinMode(UP, INPUT);
     pinMode(DOWN, INPUT);
     pinMode(LEFT, INPUT);
     pinMode(RIGHT, INPUT);

     // Setup Serial Monitor
    Serial.begin(9600);
}
 
void loop()
{
    UPState = digitalRead(UP);
    DOWNState = digitalRead(DOWN);
    LEFTState = digitalRead(LEFT);
    RIGHTState = digitalRead(RIGHT);

     if (UPState == HIGH) {
     msg = '1';
     }

     if (DOWNState == HIGH) {
     msg = '2';
     }

     if (LEFTState == HIGH) {
     msg = '3';
     }

     if (RIGHTState == HIGH) {
     msg = '4';
     }
     Serial.print(msg);
    rf_driver.send((uint8_t *)&msg, 1);
    rf_driver.waitPacketSent();
    delay(1000);
    msg = '0';
}
