Pertanyaan praktikum percobaan 1:

1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
2. Mengapa diperlukan fungsi map() dalam program tersebut?
3. Program modifikasi berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap 
   memiliki rentang ADC 0–1023. menjelaskan program pada file README.md

Jawab:
1. Untuk membaca nilai tegangan analog dari potensiometer
2. Nilai ADC (0-1023), sedangkan servo (0-180). map() digunakan untuk mengubah jarak nilai tersebut agar sesuai dengan kebutuhan servo.
3. 
```
   #include <Servo.h> // library untuk servo motor

Servo myservo; // membuat objek servo

// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan servo
const int potensioPin = A0;   // isi pin analog input (contoh A0)
const int servoPin = 9;      // isi pin digital untuk servo (PWM)

// ===================== VARIABEL =====================
// Variabel untuk menyimpan data ADC dan sudut servo
int pos = 0; // isi dengan tipe data dan inisialisasi awal
int val = 0; // isi dengan tipe data dan inisialisasi awal

void setup() {

  // Hubungkan servo ke pin yang sudah ditentukan
  myservo.attach(servoPin); // isi dengan servoPin

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600); // isi baud rate (contoh 9600)

}

void loop() {

  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer (rentang 0–1023)
  val = analogRead(potensioPin); // isi dengan potensioPin

  // ===================== KONVERSI DATA =====================
  // Ubah nilai ADC menjadi sudut servo (0–180 derajat)
  pos = map(val,
             0,   // isi nilai minimum ADC
             1023,   // isi nilai maksimum ADC
             30,   // isi sudut minimum servo jadi 30
             150);  // isi sudut maksimum servo jadi 150

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); // isi dengan variabel sudut

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan sudut servo ke Serial Monitor
  Serial.print("ADC Potensio: ");
  Serial.print(val); // isi variabel ADC

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); // isi variabel sudut

  // ===================== STABILISASI =====================
  // Delay untuk memberi waktu servo bergerak stabil
  delay(1000); // isi dalam milidetik
}
```
Pada awal program, nilai ADC sudutnya 0–180°. Pada modifikasi ini, fungsi map() diubah agar output hanya berada pada rentang 30° (sudut min servo) \
hingga 150° (sudut maks servo). Artinya, meskipun potensiometer menghasilkan nilai ADC penuh (0–1023), servo tidak akan bergerak ke posisi 
ekstrem (0° atau 180°), melainkan hanya dalam batas yang lebih aman. Hal ini berguna untuk membatasi gerakan servo agar tidak mengalami beban 
berlebih atau kerusakan mekanis.

Pertanyaan praktikum percobaan 2:
1. Menjelaskan mengapa LED dapat mengatur kecerahannya menggunakan fungsi analogWrite()!
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada
   pada rentang 50 sampai 200. menjelaskan program pada file README.md.

Jawab:
1. Karena fungsi ini menghasilkan sinyal PWM (Pulse Wide Modulation). PWM bekerja dengan mengatur durasi sinyal HIGH dan LOW dalam
   satu periode (duty cycle). Semakin lama sinyal HIGH, semakin besar daya yang diterima LED sehingga terlihat lebih terang. Sebaliknya, jika
   durasi HIGH lebih kecil, LED akan terlihat redup.
2. Hubungannya bersifat linier, di mana nilai ADC yang besar akan menghasilkan nilai PWM yang besar pula, sehingga
   output (kecerahan LED) meningkat secara proporsional.
3.
```
  #include <Arduino.h> // library dasar Arduino (tidak wajib diubah)

// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan LED PWM
const int potPin = A0;   // isi dengan pin analog (contoh A0)
const int ledPin = 9;   // isi dengan pin digital PWM (contoh 9)

// ===================== VARIABEL =====================
// Variabel untuk menyimpan hasil pembacaan dan konversi PWM
int nilaiADC = 0;  // isi dengan nilai awal (default 0)
int pwm = 0;       // isi dengan nilai awal (default 0)

void setup() {

  // ===================== OUTPUT SETUP =====================
  // Atur pin LED sebagai output
  pinMode(ledPin, 9);

  // ===================== SERIAL MONITOR =====================
  // Aktifkan komunikasi serial untuk melihat data pembacaan
  Serial.begin(9600); // isi baud rate (contoh 9600)
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  // Baca nilai analog dari potensiometer (rentang 0–1023)
  nilaiADC = analogRead(potPin); // isi dengan potPin

  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (0–255)
  pwm = map(nilaiADC,
            0,   // isi nilai minimum ADC
            1023,   // isi nilai maksimum ADC
            50,   // isi PWM minimum
            200);  // isi PWM maksimum

  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED (mengatur kecerahan)
  analogWrite(ledPin, pwm); // isi dengan variabel PWM

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan PWM ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC); // isi variabel ADC

  Serial.print(" | PWM: ");
  Serial.println(pwm); // isi variabel PWM

  // ===================== STABILISASI SISTEM =====================
  // Delay untuk menstabilkan pembacaan dan tampilan data
  delay(100); // isi dalam milidetik (contoh 50)
}
```
Pada program awal, nilai ADC dipetakan ke rentang PWM 0–255 sehingga LED dapat mati (0) atau sangat terang (255). Pada modifikasi ini, 
fungsi map() diubah menjadi rentang 50 (pwm min) – 200 (pwm maks). Dengan demikian, LED hanya akan menyala pada tingkat kecerahan 
sedang dan tidak pernah benar-benar mati maupun terlalu terang. Pembatasan ini bertujuan untuk menghasilkan output yang lebih stabil dan 
nyaman dilihat serta menghindari perubahan intensitas yang terlalu ekstrem.
