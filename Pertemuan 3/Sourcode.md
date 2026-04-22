Percobaan 3A
```
#include <Arduino.h>

const int PIN_LED = 12;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {   // Cek apakah ada data dari komputer
    char data = Serial.read();    // Baca 1 karakter
    if (data == '1') {
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED ON");
    }
    else if (data == '0') {
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED OFF");
    }
    else if (data != '\n' && data != '\r') {
      // Hanya muncul jika bukan 1, 0, atau ENTER
      Serial.println("Perintah tidak dikenal");
    }
  }
}
```

Percobaan 3B
```
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Ganti alamat jika perlu (0x27 / 0x20)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  // Mapping ke bar (0–16)
  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // Tampilkan ke Serial
  Serial.print("Nilai ADC : ");
  Serial.println(nilai);

  // Baris 1: nilai ADC
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print("   "); // clear sisa

  // Baris 2: bar
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```
