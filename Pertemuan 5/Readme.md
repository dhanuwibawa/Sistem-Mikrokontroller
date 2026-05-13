5.5.4 Pertanyaan Praktikum
1. Apakah tugas ketiga berjalan secara bersamaan atau bergantian? menjelaskan mekanismenya!
2. Bagaimana cara menambahkan tugas keempat? jelaskan langkahnya!
3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED!
   Bagaimana hasilnya? menjelaskan program pada file README.md.
Jawab:

1. Tugas ketiga berjalan secara bergantian dengan sangat cepat menggunakan penjadwal FreeRTOS. Penjadwal mengatur pembagian waktu eksekusi
   setiap tugas sehingga masing-masing tugas mendapatkan giliran untuk dijalankan. Ketika suatu tugas menjalankan vTaskDelay(),
   tugas tersebut masuk ke kondisi diblokir sehingga penjadwal akan menjalankan tugas lain yang siap dieksekusi. Karena tugas
   berjalan sangat cepat, seolah-olah tugas berjalan secara bersamaan.
2. Task keempat dapat ditambahkan dengan membuat fungsi task baru terlebih dahulu, misalnya TaskBlink3(). Setelah itu, tugas didaftarkan
   menggunakan fungsi xTaskCreate() di dalam setup(). Task baru dapat memiliki delay, prioritas, dan fungsi yang berbeda sesuai kebutuhan.
3. Modifikasi:
```
#include <Arduino_FreeRTOS.h>

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);

const int led1 = 8;
const int led2 = 7;
const int potPin = A0;

int nilaiPot = 0;
int delayLed = 200;

void setup() {

  Serial.begin(9600);

  xTaskCreate(
    TaskBlink1,
    "task1",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskBlink2,
    "task2",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    Taskprint,
    "task3",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler();
}

void loop() {

}

void TaskBlink1(void *pvParameters) {

  pinMode(led1, OUTPUT);

  while (1) {

    nilaiPot = analogRead(potPin);

    delayLed = map(nilaiPot, 0, 1023, 100, 1000);

    digitalWrite(led1, HIGH);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);

    digitalWrite(led1, LOW);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {

  pinMode(led2, OUTPUT);

  while (1) {

    digitalWrite(led2, HIGH);
    vTaskDelay((delayLed + 100) / portTICK_PERIOD_MS);

    digitalWrite(led2, LOW);
    vTaskDelay((delayLed + 100) / portTICK_PERIOD_MS);
  }
}

void Taskprint(void *pvParameters) {

  int counter = 0;

  while (1) {

    counter++;

    Serial.print("Counter: ");
    Serial.print(counter);

    Serial.print(" | Potensiometer: ");
    Serial.print(nilaiPot);

    Serial.print(" | Delay LED: ");
    Serial.println(delayLed);

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```
Penjelasan: Potensiometer digunakan sebagai input untuk mengatur kecepatan kedipan LED. Nilai analog dari potensiometer dibaca menggunakan 
fungsi analogRead() kemudian petakan menggunakan fungsi map() menjadi nilai delay antara 100 ms hingga 1000 ms. Semakin besar nilai potensiometer, 
semakin besar pula delay yang dihasilkan sehingga LED berkedip lebih lambat, sedangkan nilai potensiometer yang kecil membuat LED berkedip lebih cepat. 
Program tetap menggunakan FreeRTOS dengan tiga tugas yang berjalan secara bersamaan, yaitu LED tugas pertama, LED tugas kedua, dan tugas pencetakan data 
pada Serial Monitor. Scheduler FreeRTOS mengatur pergantian eksekusi setiap tugas menggunakan vTaskDelay() sehingga seluruh tugas dapat berjalan secara 
bersamaan tanpa hambatan. Hasil percobaan menunjukkan bahwa perubahan nilai potensiometer dapat mempengaruhi kecepatan kedipan LED secara real-time dan 
sistem tetap berjalan stabil meskipun menjalankan beberapa tugas secara bersamaan.

5.6.4 Pertanyaan Praktikum
1. Apakah kedua tugas tersebut berjalan secara bersamaan atau bergantian? menjelaskan mekanismenya!
2. Apakah program ini berpotensi mengalami kondisi balapan? jelaskan!
3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis.
   Bagaimana hasilnya? menjelaskan program pada file README.md.
Jawab:

1. Tugas kedua berjalan secara bersamaan menggunakan penjadwal FreeRTOS. Task read_data bertugas mengirim data ke antrian, sedangkan task
   display menerima dan menampilkan data tersebut ke Serial Monitor. Ketika salah satu tugas sedang tertunda atau menunggu antrian, penjadwal
   akan menjalankan tugas lainnya sehingga kedua tugas dapat bekerja secara bergantian dengan teratur.
2. Program ini memiliki risiko kondisi balapan yang sangat kecil karena komunikasi data dilakukan menggunakan antrian FreeRTOS. Antrian bekerja
   sebagai media pertukaran data yang aman sehingga akses data antar tugas diatur oleh sistem RTOS. Dengan demikian, data tidak diakses secara
   bersamaan oleh dua tugas pada waktu yang sama sehingga konflik akses data dapat dihindari.
3. Modifikasi:
```
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  int temp;
  int h;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {

  Serial.begin(9600);

  dht.begin();

  my_queue = xQueueCreate(1, sizeof(struct readings));

  xTaskCreate(
    read_data,
    "read sensors",
    128,
    NULL,
    0,
    NULL
  );

  xTaskCreate(
    display,
    "display",
    128,
    NULL,
    0,
    NULL
  );
}

void loop() {

}

void read_data(void *pvParameters) {

  struct readings x;

  for (;;) {

    x.temp = dht.readTemperature();
    x.h = dht.readHumidity();

    xQueueSend(my_queue, &x, portMAX_DELAY);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters) {

  struct readings x;

  for (;;) {

    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {

      Serial.print("Temperature = ");
      Serial.println(x.temp);

      Serial.print("Humidity = ");
      Serial.println(x.h);
    }
  }
}
```

Penjelasan: Pada modifikasi ini, sensor DHT11 digunakan untuk membaca suhu dan kelembapan secara langsung. Program terdiri dari dua tugas, 
yaitu read_data untuk membaca data sensor dan mengirimkannya ke antrian menggunakan xQueueSend(), serta display untuk menerima data dari 
antrian menggunakan xQueueReceive() dan menampilkannya pada Serial Monitor. Penggunaan antrian membuat komunikasi antar tugas menjadi 
lebih aman dan terstruktur. Hasil percobaan menunjukkan bahwa nilai dinamis suhu dan kelembapan berubah secara sesuai kondisi lingkungan, 
sementara kedua tugas tetap dapat berjalan secara bersamaan dengan pengaturan scheduler FreeRTOS.
