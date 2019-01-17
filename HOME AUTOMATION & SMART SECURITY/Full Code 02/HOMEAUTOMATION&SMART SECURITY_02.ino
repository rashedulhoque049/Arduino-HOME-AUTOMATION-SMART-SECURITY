#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h> 
SoftwareSerial mySerialblue(0, 1); // RX, TX

int led1 = 11;
int led2 = 12;
int set=LOW;

int getFingerprintIDez();
int ledg = 8;
int ledr =10;
int servoPin = 5;
Servo Servo2;

int servoPin2 = 6;
Servo Servo1;

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  Serial.begin(9600);
  Serial.println("Adafruit finger detect test");
  pinMode(ledg, OUTPUT);
  pinMode(ledr, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Servo1.attach(servoPin2);
  Servo2.attach(servoPin);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{

  if(Serial.available() > 0)  // Send data only when you receive data:
  {
    Serial.print("found"); 
    int data = Serial.read();      
    Serial.print(data);        
    Serial.println("");
    bluetooth(data);
    
  }     

   delay(100);

  
  int a= getFingerprintIDez();
  if (a == -1) {
    Serial.println("Not Found!");
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, LOW);
    //Servo2.write(0);
  } else{
    
    Serial.println("Found a match!");
    digitalWrite(ledg, HIGH);
    digitalWrite(ledr, LOW);
    if (set == LOW){
      Servo2.write(90);
      set = HIGH;
    }else {
       Servo2.write(0);
      set = LOW;
      }
    }
  
  delay(500);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  
  return finger.fingerID; 
  
}


// Bluetooth Work

  int bluetooth(int d){

  
    
    if(d == 255){             
     
      digitalWrite(led1, HIGH);
      
    }
    else if(d == 241) {      
      digitalWrite(led1, LOW); 
    }

    else if(d == 225) {      
      digitalWrite(led2, HIGH); 
    }

    else if(d == 33) {      
      digitalWrite(led2, LOW); 
    }

    else if(d == 97) {      
      digitalWrite(led2, LOW); 
    }

    else if(d == 141) {      
      Servo1.write(180);
    }

    else if(d == 13) {      
      Servo1.write(0);
    }

    
 
    
    
    }
