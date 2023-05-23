#include <Wire.h>

int led = A3;
int led2 = A1;
int photoresistor = A5;
// Create a variable to hold the light reading
int photoCellReading = 0;



void setup() {
    Wire.begin(0x8); // I2C slave mode
    Wire.onReceive(receiveEvent);
    
    // led 2
    pinMode(led2, OUTPUT);
    digitalWrite(led2, LOW);
    
    // led 1
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    
    // start serial monitor
    Serial.begin(9600);

}

void receiveEvent(int howMany){
    while(Wire.available() >= 1){
        
        // read brightness btw 0-255, data is transmitted through SDA 
        int brightness = Wire.read();
        
        // turn on leds
        analogWrite(led, brightness);
        analogWrite(led2, brightness);
    }
}

void loop() {
    
    // Use analogRead to read the photo cell reading
    photoCellReading = analogRead(photoresistor);

    // Turn on and print message to serial monitor based on brightness read
    if (photoCellReading > 2000)
    {
        Serial.println("bright");
        Serial.println(photoCellReading);
    }
    else if (photoCellReading < 2000 && photoCellReading > 1000)
    {
        Serial.println("medium");
        Serial.println(photoCellReading);
    }
    else if (photoCellReading < 1000 && photoCellReading > 0)
    {
        Serial.println("dark");
        Serial.println(photoCellReading);
    }
    
    delay(1000);
}

