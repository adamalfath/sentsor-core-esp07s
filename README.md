# SENTSOR Core Board ESP-07S
## Introduction
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img0.jpg" width="600">  

IoT menjadi teknologi primadona untuk sistem interkoneksi baik dari sensor, otomasi, sistem analitik, dan masih banyak lagi yang wajib kita manfaatkan keberadaannya. Dengan adanya IoT, data menjadi komoditas yang sangat penting yang integritasnya perlu diperhatikan sebagai asupan sistem untuk melakukan rantai kalkulasi guna kebutuhan kontrol seketika ataupun analitik, misalnya data iklim (temperatur, kelembaban, PM) untuk keperluan meteorologi dan smart farming, data konsumsi elektrik (tegangan, arus, daya, PF) untuk analisa predictive maintenance, object counter untuk manajemen traffic, global positioning untuk asset tracker, atau hal simple seperti penempatan sensor di tempat yang sulit dijangkau, dan tentunya repot jika untuk mengambil datanya harus bolak-balik on site. Oleh karena itu pemilihan end-node device atau "things" yang ideal sangatlah penting untuk mendukung pemanfaatan teknologi IoT ini secara optimal.  

SENTSOR Core Board ESP-07S merupakan development board yang dioptimasi untuk melakukan remote sensing dan datalogging. Dipersenjatai oleh ESP8266 SOC dalam modul ESP-07S yang menghadirkan 32-bit MCU dengan konektivitas WiFi untuk komunikasi wireless, RTC presisi DS3231 ±3.5ppm dengan kapabilitas sinkronisasi terhadap NTP untuk timestamp akurat, dan adapter memory card ukuran MicroSD untuk keperluan penyimpanan data lokal. Untuk memaksimalkan fungsi remote sensing, board ini mampu dihidupkan dengan power via baterai Li-ion 1S dengan kemampuan low power hingga 182uA yang juga dilengkapi BMS (charger + proteksi). Selain itu, board ini dapat dihubungkan dengan solar cell kompatibel untuk proses recharge baterai sehingga memungkinkan penerapan skema install-and-forget untuk mengeliminasi kebutuhan maintenance rutin terhadap node. Dengan mempertahankan form factor board SENTSOR Core sebelumnya, semua fitur dari SENTSOR Core Board ESP-07S ini dikemas dalam ukuran mini (~6x4cm) dengan koneksi IO berupa header 2.45mm (male/female) ataupun castellated holes.

## Features
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-pinoutposter.jpg" width="600">  
  
- **Compact & powerful**, 58.42x40.64mm (2300x1600mil) dengan MCU+RTC+uSD+BMS onboard.  
- **2x18P pinout layout**, pitch 2.54mm (100mil), dengan susunan 1 sisi untuk peripheral (power, programming, communication) dan 1 sisi untuk GPIO, mempermudah manajemen jalur/kabel yang akan digunakan.  
- **Castellated holes & pin header**, pilihan koneksi untuk mempermudah pengaplikasian board SENTSOR Core pada setiap kebutuhan.  
- **ESP8266 SOC**, 32-bit MCU dan 4MB flash dengan clock up to 160MHz.  
- **802.11b/g/n WiFi connectivity**, support mode STA/AP/STA+AP dengan antena external via konektor U.FL/IPEX memungkinkan board SENTSOR Core ESP07-S ditanam didalam enclosure metal tanpa menggangu kualitas sinyal transceiver.  
- **Low Power**, down to 182uA saat deep sleep dan 16.2mA saat modem sleep (konsumsi gabungan ESP8266+DS3231 @ VCC=3.3V).  
- **DS3231 Extremely Accurate RTC**, terhubung via I2C pada alamat 0x68.  
- **MicroSD socket**, terhubung via SPI dengan slave select (SS) pada pin IO15.  
- **Built-in LED**, terhubung pada pin IO2, konfigurasi active-low.  
- **Auto-reset trigger**, memudahkan penggantian boot mode saat proses upload firmware dengan pin kontrol DTR dan RTS.  
- **Battery Powered**, jalankan board SENTSOR Core ESP-07S dimana saja tanpa masalah power dengan Li-ion 1S via konektor JST-PH.  
- **TP4054 Battery Charger**, charge baterai dengan arus up to 500mA.  
- **DW01A Battery Protection**, pengamanan saat penggunaan baterai terhadap overcharge, overdischarge, overcurrent, dan short circuit.  
- **ME6211 LDO**, dengan VIN max. 6V dan IOUT max. 500mA. Kompatibel untuk dihubungkan dengan solar cell sebagai power input charger.  
- **11 pin GPIO** @3V3 level, 1xUART, 1xSPI, 1xI2C, 1xI2S, plus 1x10bit ADC. Silahkan lihat gambar diatas untuk lebih lanjut.  
- **Built-in Voltage Divider**, 0.1% precision resistor divider rasio 1/5 pada pin ADC1 yang terhubung ke internal ADC0 memungkinkan untuk melakukan sensing tegangan up to 5V. Kompatibel untuk monitoring tegangan VBAT sebagai metode estimasi kapasitas baterai.  

## How to Use
### Programming & Uploading Firmware
SENTSOR Core Board ESP-07S memerlukan programmer external (USB to UART) untuk mengupload firmwarenya seperti FT232, CH340, CP2102, PL2303, dll. Untuk melakukan proses upload firmware, hubungkan chip programmer dengan board SENTSOR seperti berikut:
|Programmer|SENTSOR board|
|-|-|
|+3V3 (atau +5V)|+3V3 (atau VIN)|
|GND|GND|
|TX|RX|
|RX|TX|
|DTR|DTR|
|RTS|RTS|

Selanjutnya pilih board _Generic ESP8266 Module_. Beberapa hal yang perlu diperhatikan yaitu ESP-07S memiliki ukuran flash sebesar 4MB (silahkan pilih kombinasi alokasi FS dan OTA sesuai keperluan), dan metode auto-reset dengan menggunakan pin DTR. Setelah itu SENTSOR Core Board ESP-07S dapat digunakan sebagaimana development board pada umumnya. 

<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-arduinoideinfo.png" width="600">  

### Dependency
Arduino IDE memerlukan ESP8266 Core untuk bisa melakukan pemrograman terhadap chip ESP8266. Silahkan ikuti instruksi [ini](https://github.com/esp8266/Arduino) untuk melakukan instalasi ESP8266 Core untuk Arduino IDE, untuk IDE lain menyesuaikan sesuai instruksi masing-masing.

File example yang disediakan memiliki library dependency terkait RTC, NTP dan akses memory card, yaitu:
- RTCLib https://github.com/adafruit/RTClib  
- NTPClient https://github.com/arduino-libraries/NTPClient  
- SdFat https://github.com/greiman/SdFat  

Silahkan install library tersebut jika dibutuhkan dalam program yang akan kalian buat.  

### Battery Powered
SENTSOR Core Board ESP-07S dapat dijalankan dengan menggunakan battery Li-ion 1S (3.7V-4.2V) via konektor JST-PH. Proses charging dapat dilakukan langsung on-board dengan cara mensupply daya via pin VIN (max. 6V).  

> **:warning: Perhatian!**  
> Harap perhatikan secara seksama polaritas dari konektor baterai agar sama dengan yang tertera pada board (terdapat tulisan +/- pada silkscreen). Dikarenakan konektor ini belum distandarisasi maka memungkinkan baterai yang akan digunakan memiliki susunan polaritas berbeda (positif di pin 1 & negatif di pin 2 atau sebaliknya).

### On-board Jumper Pad
SENTSOR Core Board ESP-07S memiliki 2 buah jumper pad:
- Jumper JP1 menghubungkan VBAT dengan ADC1 yang selanjutnya terhubung ke ADC0 via voltage divider.
- Jumper JP2 menghubungkan IO16 dengan RST yang digunakan sebagai pin wake-up saat mode deep sleep diaktifkan.  

Untuk informasi lebih lengkap silahkan lihat pada file skematik.  

## Bill of Materials
|Designator|Qty|Name/Value|Footprint|
|-|-|-|-|
|U1|1|ESP-07S|ESP-07S|
|U2|1|ME6211C33|SOT-23-5|
|U3|1|TP4054|SOT-23-5|
|U4|1|DW01A|SOT-23-6|
|U5|1|DS3231SN#|SOIC-16_300MIL|
|R1,R2|2|100k|R0603|
|R13,R11,R12|3|10k|R0603|
|R14,R15|2|4.7k|R0603|
|R9,R3,R6,R4|4|1k|R0603|
|R10|1|470|R0603|
|R5|1|100|R0603|
|R7|1|300k 0.1%|R0603|
|R8|1|75k 0.1%|R0603|
|C2,C10,C1|3|1u|C0603|
|C4,C6,C7|3|10u|C0603|
|C11,C8,C5,C9,C12|5|100n|C0603|
|C3|1|330u 4V|CASE-B_3528|
|Q1|1|CJ2301|SOT-23-3|
|Q2|1|SL8205S|SOT-23-6|
|Q3|1|UMH3N|SC-70-6|
|D1|1|B5819W|SOD-123|
|LED1|1|Blue|LED0603|
|LED2|1|White|LED0603|
|RST|1|Tact Switch|3x4x2_SMD|
|CN1|1|JST-PH, 2P|PH-2P_P2.00_SMD|
|CARD1|1|MicroSD|TF-115K|
|B1|1|CR1220|BAT_CR1220_SMD|  

## Design 
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-pcb-ss.png" width="600">  

SENTSOR Core Board ESP-07S merupakan open source hardware, silahkan dimanfaatkan secara bijaksana.  

Link: https://easyeda.com/sentsor-project/sentsor-core-esp-07s  

## Gallery
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img1.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img2.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img3.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img4.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img5.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img6.jpg" width="400">  
<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img7.jpg" width="400"> <img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/core07s-img8.jpg" width="400">

## Support Open-Source Hardware & SENTSOR!
Bila kalian tertarik dengan produk-produk SENTSOR, kalian bisa cek marketplace ataupun memberikan donasi pada link berikut:  

[![Store](https://img.shields.io/badge/marketplace-Tokopedia-brightgreen.svg)](https://www.tokopedia.com/gerai-sagalarupa/etalase/sentsor-product)  [![Donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://www.paypal.me/adamalfath)  

Support kalian akan sangat membantu untuk pengembangan open-source hardware dari SENTSOR selanjutnya.

## Information
SENTSOR  
Author: Adam Alfath  
Contact: adam.alfath23@gmail.com  
Web: [sentsor.net](http://www.sentsor.net)  
Repo: [SENTSOR Main Repo](http://github.com/adamalfath/sentsor)

<img src="https://github.com/adamalfath/sentsor-core-esp07s/blob/master/media/OSHW_ID000004.png" width="80"><br/><a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png"/></a><br/>
SENTSOR Core Board ESP-07S is a certified open source hardware project UID <a rel="certification" href="https://certification.oshwa.org/id000004.html">ID000004</a> and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
