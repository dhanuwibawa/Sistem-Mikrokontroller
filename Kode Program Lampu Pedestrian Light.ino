// C++ code
//
const int pinMerahKendaraan = 13;
const int pinKuningKendaraan = 12;
const int pinHijauKendaraan = 11;
const int pinMerahPedKiri = 10;
const int pinHijauPedKiri = 9;
const int pinMerahPedKanan = 8;
const int pinHijauPedKanan = 7;
const int pinButton = 2;

volatile bool tombolAktif = false;

void setup() {
  for (int i = 7; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(pinButton, INPUT_PULLUP);
  kondisiNormal();

  attachInterrupt(digitalPinToInterrupt(pinButton), tekanTombol, FALLING);
}

void loop() {
  if (tombolAktif) {
    jalankanPenyeberangan();
    tombolAktif = false;
  }
}

// fungsi interrupt
void tekanTombol() {
  tombolAktif = true;
}

void kondisiNormal() {
  digitalWrite(pinHijauKendaraan, HIGH);
  digitalWrite(pinMerahKendaraan, LOW);
  digitalWrite(pinKuningKendaraan, LOW);

  setLampuPedestrian(HIGH, LOW);
}

void setLampuPedestrian(int merah, int hijau) {
  digitalWrite(pinMerahPedKiri, merah);
  digitalWrite(pinMerahPedKanan, merah);
  digitalWrite(pinHijauPedKiri, hijau);
  digitalWrite(pinHijauPedKanan, hijau);
}

void jalankanPenyeberangan() {
  digitalWrite(pinHijauKendaraan, LOW);

  for (int i = 0; i < 3; i++) {
    digitalWrite(pinKuningKendaraan, HIGH);
    delay(450);
    digitalWrite(pinKuningKendaraan, LOW);
    delay(450);
  }

  digitalWrite(pinMerahKendaraan, HIGH);
  setLampuPedestrian(LOW, HIGH);
  delay(9000);

  setLampuPedestrian(HIGH, LOW);
  delay(1000);

  digitalWrite(pinMerahKendaraan, LOW);

  for (int i = 0; i < 3; i++) {
    digitalWrite(pinKuningKendaraan, HIGH);
    delay(400);
    digitalWrite(pinKuningKendaraan, LOW);
    delay(400);
  }

  kondisiNormal();
}
