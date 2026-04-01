// C++ code

// Deklarasi pin
int merah[] = {13, 10, 7, 4};
int kuning[] = {12, 9, 6, 3};
int hijau[] = {11, 8, 5, 2};

void setup() {
  // Inisialisasi semua pin sebagai output
  for(int i = 0; i < 4; i++){
    pinMode(merah[i], OUTPUT);
    pinMode(kuning[i], OUTPUT);
    pinMode(hijau[i], OUTPUT);
  }
}

void loop() {
  // Perulangan untuk 4 arah (Utara, Timur, Selatan, Barat)
  for(int i = 0; i < 4; i++){
    semuaMerah();        // kondisi awal semua merah
    aktifkanSimpang(i);  // aktifkan satu jalur
  }
}

// Fungsi untuk set semua lampu menjadi merah
void semuaMerah(){
  for(int i = 0; i < 4; i++){
    digitalWrite(merah[i], HIGH);
    digitalWrite(kuning[i], LOW);
    digitalWrite(hijau[i], LOW);
  }
}

// Fungsi utama satu siklus lampu (hijau → kuning → merah)
void aktifkanSimpang(int i){
  // HIJAU nyala 5 detik
  digitalWrite(merah[i], LOW);
  digitalWrite(hijau[i], HIGH);
  delay(5000);

  // Matikan hijau sebelum kuning
  digitalWrite(hijau[i], LOW);

  // KUNING kedip 3x dalam total ±2 detik
  for(int j = 0; j < 3; j++){
    digitalWrite(kuning[i], HIGH);
    delay(300);
    digitalWrite(kuning[i], LOW);
    delay(300);
  }

  // Sisa waktu agar total kuning = 2 detik
  digitalWrite(kuning[i], HIGH);
  delay(200); 
  digitalWrite(kuning[i], LOW);

  // Kembali ke MERAH
  digitalWrite(merah[i], HIGH);
}
