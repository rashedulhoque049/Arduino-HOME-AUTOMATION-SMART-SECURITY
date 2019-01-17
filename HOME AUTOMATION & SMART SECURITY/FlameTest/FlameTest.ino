int sensorPin = A0; // select the input pin for the LDR

int sensorValue = 0; // variable to store the value coming from the sensor



int buzzer = 8; // Output pin for Buzzer

void setup() {


pinMode(buzzer,OUTPUT);

Serial.begin(9600);

}

void loop()

{



sensorValue = analogRead(sensorPin);



if (sensorValue < 100)

{

Serial.println("Fire Detected");

tone(buzzer, 1000);

delay(500);

}else



noTone(buzzer);


}
