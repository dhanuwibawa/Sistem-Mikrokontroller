2.5.4 Pertanyaan Praktikum

1. Gambarkan skema rangkaian yang digunakan pada percobaan!
2. Apa yang terjadi jika nilai angka lebih dari 15?
3. Apakah program ini menggunakan common cathode atau common anode? jelaskan alasannya!
4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

Jawab :
1. <img width="443" height="646" alt="Screenshot 2026-04-15 232829" src="https://github.com/user-attachments/assets/b9527214-f189-4c48-8231-30d1283a8a01" />
2. Programnya akan kebingungan. Di dalam kode hanya menyiapkan daftar pola lampu untuk 16 karakter (angka 0 sampai huruf F). Kalau Arduino diminta membaca data ke-16 atau lebih, dia akan mengambil "sampah memori". Akibatnya, lampu di Seven Segment akan menyala berantakan, atau mikrokontrolernya bisa nge-crash.
3. Program ini menggunakan tipe Common Anode (Anoda Umum) karena pada tipe ini, lampu LED baru mau menyala kalau dikasih listrik 0 Volt (atau LOW). Di dalam kode, ada tanda seru (!) pada perintah !digitPattern[num][i]. Tanda seru ini mengemukakan perintah: yang tadinya 1 (menyala) diubah jadi 0 (LOW) supaya lampunya benar-benar menyala sesuai tipe Common Anode.
4. ```
   #include <Arduino.h>
```
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Daftar pola untuk angka 0 sampai F
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3 
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,0}, // A
  {0,0,1,1,1,1,1,0}, // b
  {1,0,0,1,1,1,0,0}, // C
  {0,1,1,1,1,0,1,0}, // d
  {1,0,0,1,1,1,1,0}, // E
  {1,0,0,0,1,1,1,0}  // F
};

void displayDigit(int num) {
  for(int i=0; i<8; i++) { 
    // Pakai tanda '!' supaya nyala untuk Common Anode
    digitalWrite(segmentPins[i], !digitPattern[num][i]); 
  }
}

void setup() {
  for(int i=0; i<8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // MODIFIKASI: Mulai dari angka 15, dan terus dikurangi (i--) sampai angka 0
  for(int i=15; i>=0; i--) { 
    displayDigit(i); 
    delay(1000); // Tunggu 1 detik biar angkanya kelihatan jelas
  }
}
```
