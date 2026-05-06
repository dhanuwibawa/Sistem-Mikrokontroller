Percobaan 1 :
```
#include <Servo.h> 

Servo myservo; 

// ===================== PIN SETUP =====================
const int potensioPin = A0;   // pin analog
const int servoPin = 9;       // pin PWM

// ===================== VARIABEL =====================
int pos = 0; 
int val = 0; 

void setup() {
  myservo.attach(servoPin);  
  Serial.begin(9600);        
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  val = analogRead(potensioPin);  

  // ===================== KONVERSI DATA =====================
  pos = map(val, 0, 1023, 0, 180);  

  // ===================== OUTPUT SERVO =====================
  myservo.write(pos);  

  // ===================== MONITORING DATA =====================
  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  // ===================== STABILISASI =====================
  delay(15); 
}
```

Percobaan 2 :
```
#include <Arduino.h> // library dasar Arduino

// ===================== PIN SETUP =====================
const int potPin = A0;   // pin analog untuk potensiometer
const int ledPin = 9;    // pin PWM untuk LED

// ===================== VARIABEL =====================
int nilaiADC = 0;  // nilai awal
int pwm = 0;       // nilai awal

void setup() {

  // ===================== OUTPUT SETUP =====================
  pinMode(ledPin, OUTPUT);

  // ===================== SERIAL MONITOR =====================
  Serial.begin(9600);
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  nilaiADC = analogRead(potPin);

  // ===================== PEMROSESAN DATA (SCALING) =====================
  pwm = map(nilaiADC,
            0,     // minimum ADC
            1023,  // maksimum ADC
            0,     // PWM minimum
            255);  // PWM maksimum

  // ===================== OUTPUT PWM =====================
  analogWrite(ledPin, pwm);

  // ===================== MONITORING DATA =====================
  Serial.print("ADC: ");
  Serial.print(nilaiADC);

  Serial.print(" | PWM: ");
  Serial.println(pwm);

  // ===================== STABILISASI SISTEM =====================
  delay(50);
}
```
