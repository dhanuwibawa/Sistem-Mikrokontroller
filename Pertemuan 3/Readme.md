iv.Pertanyaan Praktikum
1. Jelaskan proses dari input keyboard hingga LED menyala/mati!
2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya
   diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem

Jawab:
1. Proses dari Input Keyboard hingga LED Menyala/Mati
- Input Keyboard: Pengguna mengetik karakter ('1' atau '0') di keyboard dan menekan Enter melalui antarmuka Serial Monitor di komputer.
- Transmisi Data: Komputer mengirimkan karakter tersebut dalam bentuk data serial melalui kabel USB menuju IC antarmuka USB-to-Serial pada Arduino, yang kemudian
  diteruskan ke pin RX (Receive) mikrokontroler.
- Pembacaan oleh Arduino: Program mengeksekusi Serial.available() untuk memeriksa apakah ada data yang masuk ke buffer receiver. Jika ada, Serial.read()
  akan mengambil satu byte (karakter) dari buffer tersebut.
- Logika Percabangan: Karakter yang dibaca dievaluasi oleh statement if atau else if. Jika datanya adalah '1', mikrokontroler akan mengeksekusi
  digitalWrite(PIN_LED, HIGH).
- Eksekusi Fisik: Pin digital 12 akan mengeluarkan tegangan logika HIGH (5V), yang menyebabkan arus mengalir melalui rangkaian LED, sehingga LED menyala.
  (Proses sebaliknya berlaku untuk logika LOW jika input '0').

2. Serial.available() digunakan untuk memeriksa jumlah byte data yang telah tiba dan tersimpan di dalam buffer penerima serial mikrokontroler. Jika
   penghapusan: Perintah Serial.read() akan terus-menerus dieksekusi oleh fungsi loop() yang berjalan sangat cepat. Jika tidak ada data yang dikirim dari
   komputer, Serial.read() akan mengembalikan nilai -1. Arduino akan membuang siklus pemrosesan untuk terus menyalakan nilai -1 ini dengan kondisi if, yang
   sangat tidak efisien dan dapat menyebabkan error logika jika program tidak menangani nilai -1 dengan benar.

3. Program modifikasi
```
   // Mendeklarasikan konstanta pin untuk LED pada pin digital 12 [cite: 121]
const int PIN_LED = 12;
// Variabel 'mode' menyimpan status atau perintah aktif saat ini, default diset '0' (OFF)
char mode = '0';
// Variabel 'lastMode' menyimpan status mode sebelumnya. 
// Diinisialisasi dengan 'x' (nilai sembarang) agar saat program pertama kali jalan, 
// sistem langsung mendeteksi adanya perubahan status.
char lastMode = 'x';

void setup() {
  // Memulai komunikasi serial dengan baud rate 9600 bps agar Arduino bisa bertukar data dengan komputer [cite: 126]
  Serial.begin(9600);
  
  // Mengatur pin digital 12 (PIN_LED) sebagai OUTPUT agar bisa mengirim tegangan ke LED [cite: 128]
  pinMode(PIN_LED, OUTPUT);
  
  // Menampilkan pesan instruksi ke layar Serial Monitor saat program pertama kali dihidupkan [cite: 127]
  Serial.println("Ketik 1 = ON, 0 = OFF, 2 = BLINK");
}

void loop() {
  // Mengecek apakah ada data yang masuk dan tersedia di buffer penerima serial [cite: 132]
  if (Serial.available() > 0) {
    // Membaca 1 karakter (byte) pertama dari data yang dikirim oleh pengguna [cite: 133]
    char data = Serial.read();

    // Memfilter input: Hanya memproses jika karakter yang diketik adalah '1', '0', atau '2'
    if (data == '1' || data == '0' || data == '2') {
      // Menyimpan input valid tersebut sebagai mode operasi yang baru
      mode = data;
    }
  }
  
  // Mengecek apakah mode saat ini berbeda dengan mode sebelumnya
  // Logika ini mencegah Serial Monitor dipenuhi (spam) oleh teks yang sama berulang-ulang
  if (mode != lastMode) {
    
    // Mencetak status ke Serial Monitor sesuai mode yang sedang aktif
    if (mode == '1') Serial.println("LED ON");
    else if (mode == '0') Serial.println("LED OFF");
    else if (mode == '2') Serial.println("LED BLINK");

    // Memperbarui nilai lastMode dengan mode saat ini, 
    // sehingga pesan di atas tidak akan dicetak lagi sampai pengguna mengubah mode.
    lastMode = mode;
  }

  // Mengeksekusi instruksi ke perangkat keras sesuai 'mode' yang sedang disimpan
  if (mode == '1') {
    // Mode ON: Memberikan tegangan HIGH (5V) ke pin LED agar menyala terus [cite: 141]
    digitalWrite(PIN_LED, HIGH);
  }
  else if (mode == '0') {
    // Mode OFF: Memberikan tegangan LOW (0V) ke pin LED agar mati terus [cite: 149]
    digitalWrite(PIN_LED, LOW);
  }
  else if (mode == '2') {
    // Mode BLINK: Membuat LED berkedip secara berulang
    digitalWrite(PIN_LED, HIGH); // Nyalakan LED [cite: 141]
    delay(500);                  // Tahan posisi menyala selama 500 milidetik (0.5 detik)
    digitalWrite(PIN_LED, LOW);  // Matikan LED [cite: 149]
    delay(500);                  // Tahan posisi mati selama 500 milidetik sebelum mengulang loop
  }
}
```

4. Menggunakan millis(). Pengaruhnya terhadap sistem: Jika Anda menggunakan delay(500) untuk membuat kedipan, mikrokontroler akan "tertidur"
   selama 500ms. Selama masa tidur ini, Arduino tidak bisa membaca input baru dari Serial Monitor secara instan. Pengguna mungkin harus menekan
   tombol '0' berkali-kali sampai bertepatan dengan momen mikrokontroler "terbangun" agar program merespons. Dengan millis(), sistem berjalan
   secara asynchronous (non-blocking), sehingga Arduino dapat mengatur kedipan waktu sambil terus siaga menghubungkan input Serial di setiap persekian milidetik.

3.6.4 Pertanyaan Praktikum
1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
2. Apakah pin potensiometer harus seperti itu? menjelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!
3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
   - Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
   - Adapun data yang ditampilkan pada Serial Monitor sesuai dengan tabel berikut: ADC: 0 Volt: 0.00 V Persen: 0% Tampilan jika
   - potensiometer dalam kondisi diputar paling kiri
   - ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
   - Berikan penjelasan disetiap baris kodenya dalam bentuk README.md!
4. Tabel lengkap berikut berdasarkan pengamatan pada Serial Monitor

Jawab:
1. Protokol I2C menggunakan sistem Master-Slave. Pada rangkaian ini, Arduino bertindak sebagai Master (Sopir Bus) dan LCD bertindak sebagai
   Slave (Penumpang). Komunikasi hanya menggunakan dua jalur kabel, yaitu SDA (jalur data pada pin A4) dan SCL (jalur sinyal clock pada pin A5). Arduino
   memulai komunikasi dengan mengirimkan sinyal clock dan alamat unik I2C milik LCD (seperti 0x27 pada inisialisasi LiquidCrystal_I2C lcd(0x27, 16, 2);). Jika
   LCD merespons, Arduino kemudian mengirimkan instruksi (seperti inisialisasi, menghidupkan backlight, memindahkan kursor) atau
   data (karakter ASCII dari nilai sensor) untuk ditampilkan di layar.
2. Pin tengah potensiometer (wiper) wajib dihubungkan ke pin Analog Arduino (A0) karena pin inilah yang mengeluarkan variabel tegangan hasil putaran. Jika
   pin kiri dan kanan tertukar: Rangkaian tidak akan rusak. Namun, arah pembacaan akan terbalik. Jika sebelumnya memutar ke kanan (searah jarum jam)
   membuat nilai ADC naik mendekati 1023 (5V), jika pin VCC dan GND ditukar, memutar ke kanan justru akan membuat nilai ADC turun mendekati 0 (GND).
3. Program Modifikasi:
```
   #include <Wire.h>               // Library untuk komunikasi I2C [cite: 191]
#include <LiquidCrystal_I2C.h>  // Library untuk modul LCD I2C [cite: 192]
#include <Arduino.h>            // Library standar Arduino [cite: 193]

// Inisialisasi LCD pada alamat 0x27 (atau 0x20) dengan ukuran 16 kolom dan 2 baris [cite: 195, 196]
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0; // Pin analog untuk potensiometer [cite: 198]

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial UART pada baud rate 9600 [cite: 201]

  lcd.init();         // Inisialisasi modul LCD [cite: 205]
  lcd.backlight();    // Menyalakan lampu latar LCD [cite: 207]
}

void loop() {
  // 1. Membaca nilai analog dari potensiometer (0-1023) [cite: 212]
  int nilaiADC = analogRead(pinPot);

  // 2. Kalkulasi Data Tambahan
  // Menghitung tegangan (Volt) dengan rumus (ADC / 1023) * 5V
  float volt = (nilaiADC * 5.0) / 1023.0;
  
  // Mengonversi nilai ADC menjadi persentase (0-100%)
  int persen = map(nilaiADC, 0, 1023, 0, 100);
  
  // Menentukan panjang bar (level) untuk baris kedua LCD (0-16 karakter) [cite: 217]
  int panjangBar = map(nilaiADC, 0, 1023, 0, 16);

  // 3. Tampilan ke Serial Monitor (UART) [cite: 301]
  // Format: ADC: [nilai] | Persen: [persen]% | Volt: [volt] V
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | Persen: ");
  Serial.print(persen);
  Serial.print("% | Volt: ");
  Serial.print(volt);
  Serial.println(" V");

  // 4. Tampilan ke LCD (I2C) [cite: 227-253]
  // Baris 1: Menampilkan nilai ADC dan Persentase
  lcd.setCursor(0, 0); // [cite: 229, 305]
  lcd.print("ADC:");
  lcd.print(nilaiADC);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("%   "); // Spasi tambahan untuk membersihkan sisa karakter sebelumnya 

  // Baris 2: Menampilkan Bar Level [cite: 237, 305]
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255); // Karakter blok penuh untuk level bar [cite: 245]
    } else {
      lcd.print(" ");       // Karakter kosong jika level belum tercapai [cite: 249]
    }
  }

  delay(250); // Delay singkat untuk stabilitas pembacaan dan tampilan [cite: 256]
}
```
4. (tidak akurat, tapi mungkin mendekati nilai yang diminta)
   <img width="1510" height="682" alt="WhatsApp Image 2026-04-22 at 22 33 53" src="https://github.com/user-attachments/assets/0b32e29c-5bc5-4ede-838e-67379316ff13" />
