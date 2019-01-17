/*
 * Arduino Air Quality Monitor
 * 

 */









int buzzer = 10;
int smoke = A5;
int airQuality = A0;
int sensorThres = 400;

                      
String quality ="";

void setup() {
                     
  pinMode(airQuality,INPUT);                  //set sensor for Air quality input
  pinMode(smoke, INPUT);                    //set sensor for Gas Detect input
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);


}

void loop() {
  int analogSensor = analogRead(airQuality);
  int analogSensor2 = analogRead(smoke);
  
Serial.print("Air Quality: ");
  if(analogSensor<175){
    quality = "GOOD! ";
    Serial.print(quality);
  }
  else if (analogSensor >175 && analogSensor<225){
    quality = "Medium ";
    Serial.print(quality);
  }
  else if (analogSensor >225 && analogSensor<300){
    quality = "Bad ";
    Serial.print(quality);
  }
  else if (analogSensor >300){
    quality = "Very Bad ";
    Serial.print(quality);
  }

  
  Serial.print(analogSensor);


  delay(1000);
  Serial.println("");
  Serial.print("Gas Detect: ");
  
  
  Serial.print(analogSensor2);
  // Checks if it has reached the threshold value
  if (analogSensor2 > sensorThres)
  {
    
    tone(buzzer, 1000, 200);
  }
  else
  {
   
    noTone(buzzer);
  }
  Serial.println("");
  delay(100);

}



