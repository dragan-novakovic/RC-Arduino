// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

int speedPin = 5;
int directionPin1 = 4;
int directionPin2 = 3;

int stepSpeed= 180;

// Declare the Servo pin 
int servoPin = 6; 
int servoSpeed = 151;
int servoD1 = 7;
int servoD2 = 8;

 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);

    pinMode(speedPin, OUTPUT);
    pinMode(directionPin1, OUTPUT);
    pinMode(directionPin2, OUTPUT);

    //servo
    pinMode(servoPin, OUTPUT);
    pinMode(servoD1, OUTPUT);
    pinMode(servoD2, OUTPUT);
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[1];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      if ((char)buf[0] != '0') {
        Serial.print("Yes: ");
         Serial.println((char)buf[0]); 

         if ((char)buf[0] == '1') {
           Serial.println("Yes: 1 (Napred)");
          digitalWrite(directionPin1, HIGH);
          digitalWrite(directionPin2, LOW);
          analogWrite(speedPin, stepSpeed);
          }


            if ((char)buf[0] == '2') {
           Serial.println("Yes: 2 (Rikverc)");
           digitalWrite(directionPin1, LOW);
          digitalWrite(directionPin2, HIGH);
          analogWrite(speedPin, stepSpeed);
          }

               if ((char)buf[0] == '3') {
           Serial.println("Yes: 3 (Levo)");
           digitalWrite(servoD1, LOW);
          digitalWrite(servoD2, HIGH);
          analogWrite(servoPin, servoSpeed);
          }

                 if ((char)buf[0] == '4') {
           Serial.println("Yes: 3 (Desno)");
           digitalWrite(servoD1, HIGH);
          digitalWrite(servoD2, LOW);
          analogWrite(servoPin, servoSpeed);
          }

        
         
        } else {
           Serial.print("No: ");
         Serial.println((char)buf[0]); 
          digitalWrite(directionPin1, HIGH);
          digitalWrite(directionPin2, HIGH);
         analogWrite(speedPin, 0);

         //servo
         digitalWrite(servoD1, LOW);
          digitalWrite(servoD2, LOW);
         analogWrite(servoPin, 0);
        }
            
    }
}
