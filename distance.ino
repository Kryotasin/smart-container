#include <math.h>

// Assigning the pin to which the IR distance sensor is connected
int analogPin = A0; 

// Store raw analog value from IR distance sensor
int val = 0;

// Intermediate value holder
float inter = 0;

// Distance of reflective surface in cm
double dist = 0;

// Avg distance calculated over five dist readings
double avgDist = 0;

// Counter to keep track of number of readings for average
int count = 0;


void setup() { 
    //Set the variable for GET on web interface
    Particle.variable("dist", avgDist);
  
}

void loop() {
    val = analogRead(analogPin);  // Read the raw value
    
    inter = val * (3.3/4095); // Multiply by 3.3volts/4095, i.e. max 12-bit value
    
    dist = 27/inter - 1.5; // Use constant factor 27 from manual and -1.5 for error correction
    Serial.print(dist);
  
    if(count < 5){
        avgDist += dist;
        count++;
    }
    else{
        count = 1;
        avgDist /= 5;
        Particle.publish("dist", String(avgDist));
    }
   
  
  delay(1000);
}





