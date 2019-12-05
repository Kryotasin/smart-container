/* FSR testing sketch.
Connect one end of FSR to power, the other end to Analog 0. Then connect one end of a 10K resistor from Analog 0 to ground
For more information see www.ladyada.net/learn/sensors/fsr.html */
int fsrPin = A0;
int fsrReading;
int fsrVoltage;
unsigned long fsrResistance; 
// The voltage converted to resistance, can be very big so make "long" 
unsigned long fsrConductance;
// the FSR and 10K pulldown are connected to A0
// the analog reading from the FSR resistor divider 
// the analog reading converted to voltage

long fsrForce; 
// Finally, the resistance converted to force

void setup(void) {
//Serial.begin(9600); // We'll send debugging information via the Serial monitor
Particle.variable("weight", fsrForce);
}


void loop(void) {
fsrReading = analogRead(fsrPin); 
Serial.print("Analog reading = "); 
Serial.println(fsrReading);


// analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV) 
fsrVoltage = map(fsrReading, 0, 4095, 0, 3300);
Serial.print("Voltage reading in mV = ");
Serial.println(fsrVoltage);


if (fsrVoltage == 0) { 
    Serial.println("No pressure");
} else {
// The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
// so FSR = ((Vcc - V) * R) / V 
fsrResistance = 3300 - fsrVoltage; 
fsrResistance *= 10000;


fsrResistance /= fsrVoltage; 
Serial.print("FSR resistance in ohms = ");
Serial.println(fsrResistance);

// fsrVoltage is in millivolts so 5V = 5000mV // 10K resistor

fsrConductance = 1000000; // we measure in micromhos so 
fsrConductance /= fsrResistance;

Serial.print("Conductance in microMhos: "); 
Serial.println(fsrConductance);


// Use the two FSR guide graphs to approximate the force 
if (fsrConductance <= 1000) {
    fsrForce = fsrConductance / 80; 
    Serial.print("Force in Newtons: "); 
    Serial.println(fsrForce);
} else {
    fsrForce = fsrConductance - 1000; 
    fsrForce /= 30;
    Serial.print("Force in Newtons: "); 
    Serial.println(fsrForce);
} }

Serial.println("--------------------");
  delay(1000);
}