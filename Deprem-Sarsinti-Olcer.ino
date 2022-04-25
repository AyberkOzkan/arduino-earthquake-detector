//---------------------------------------------------------------------------------------------------------
//Başlangıç Tarihi : 10.11.2020 
//Bitirme Projesi: Deprem Sensörü Yapımı 
//adxl335 seçtim. MPU6050 gyro sensörü gereksiz gibi duruyor ve kütüphanesi sorunlu.
//Gas sensörü, 1 Led, 1 Buzzer ekleyeceksin. Ek olarak sismograf(Grafik) oluştur. Altta veri tanımlama yaptın. 
//
//Arduino uno yerine pro micro kullanmaya çalış.
//*********************************************************************************************************
#include<LiquidCrystal.h>       // LCD kütüphanesi
LiquidCrystal lcd(7,6,5,4,3,2); // LCD bağlantı pinleri
 
#define buzzer 12               // Buzzer pin'i seçildi.
#define led 13                  // Led pin'i seçildi.
#define led2 8                  // 2.Led Pini seçildi.(Durum Ledi)
 
#define x A0                    // Accelerometer'ın X çıkışı Analog olarak tanımlandı.
#define y A1                    // Accelerometer'ın Y çıkışı Analog olarak tanımlandı.
#define z A2                    // Accelerometer'ın Z çıkışı Analog olarak tanımlandı.
 
           /*Değişkenler*/
int xdegeri=0;
int ydegeri=0;
int zdegeri=0;
long Baslat;
int buz=0;
 
      /*Değişmeyen Girdiler*/
#define ornekler 50
#define maxDeg 5                // max değişmesini istediğin değer limiti 
#define minDeg -500              // min değişmesini istediğin değer limiti
#define buzTime 5000            // buzzer ötme süresi
 
void setup()
{
lcd.begin(16,2);                //  LCD Başlatılıyor.
analogReference(EXTERNAL);      //  Daha iyi sonuçlar alabilmek için AREF girişini 3.3V'a çevirdim. Arduino Uno'da bağlantı yapmayı unutma. **Bu kodu yazmazsan ve bağlantı yaparsan Arduino'yu yakabilirsin !!!
Serial.begin(9600);             //  Serial bağlantı başlatılıyor.
delay(1000);                    //  Gecikme
lcd.print("Deprem ");
lcd.setCursor(0,1);             //  LCD Karakter ayarlaması için.
lcd.print("Sensoru ");
delay(2000);
lcd.clear();                    //  LCD ekranı sil.
lcd.print("Kalibre Ediliyor.....");
lcd.setCursor(0,1);
lcd.print("Bekleyin...");
         
delay(100);                       
pinMode(buzzer, OUTPUT);         //  Takılı kalmasın diye kapalı olduklarından emin oluyorum.
pinMode(led, OUTPUT);
//pinMode(led2, OUTPUT);
buz=0;                           // Buzzer'ın pasif konumda olduğundan emin oluyorum
digitalWrite(buzzer, buz);
digitalWrite(led, buz);
for(int i=0;i<ornekler;i++)      // Kalibrasyon için örnek alıyor.
{
xdegeri+=analogRead(x);
ydegeri+=analogRead(y);
zdegeri+=analogRead(z);
}
 
xdegeri/=ornekler;                // X için ortalama değer alınıyor.
ydegeri/=ornekler;                // Y için ortalama değer alınıyor.
zdegeri/=ornekler;                // Z için ortalama değer alınıyor.
 
delay(5000);
lcd.clear();
lcd.print("Kalibrasyon ");
lcd.setCursor(0,1);
lcd.print("Basarili");
digitalWrite(led2, HIGH);
delay(1000);
lcd.clear();
lcd.print("Cihaz Hazir");
delay(1000);
lcd.clear();
lcd.print(" X Y Z ");
}
 
void loop()
{
int deger1=analogRead(x);       //  X Çıkışı okunuyor.
int deger2=analogRead(y);      //  Y Çıkışı okunuyor.
int deger3=analogRead(z);     //  Z Çıkışı okunuyor.
 
int xDeger=xdegeri-deger1;        // X'teki değişim bulunuyor.
int yDeger=ydegeri-deger2;       // Y'teki değişim bulunuyor.
int zDeger=zdegeri-deger3;      // Z'teki değişim bulunuyor.
 
              /*LCD'de değerlerin gözükmesi için.*/
lcd.setCursor(0,1);
lcd.print(xDeger);
lcd.setCursor(6,1);
lcd.print(yDeger);
lcd.setCursor(12,1);
lcd.print(zDeger);
delay(100);
 
              /* Aralıkların belirlenmesi*/
if(xDeger < minDeg || xDeger > maxDeg || yDeger < minDeg || yDeger > maxDeg || zDeger < minDeg || zDeger > maxDeg)  //x,y ve z değerlerinin aralıklarındaki değişim şartları.
{
if(buz == 0)
Baslat=millis();                 // Zamanlayıcı
digitalWrite(led2, LOW);         // Durum Ledinin sönmesi
buz=1;                           // buzzer ve Led'in aktif olması
}
 
else if(buz == 1)                // Deprem alarmı verildiğinde buzzer'ın aktif olması 1 aktif 0 pasif
{
lcd.setCursor(0,0);
lcd.print("Deprem Alarmi ");
if(millis()>= Baslat+buzTime)
buz=0;
}
 
else
{
lcd.clear();
lcd.print("X      Y     Z ");
digitalWrite(led2, HIGH);        // Durum Ledi: stabil ve her şey çalışıyorsa aktif.
}
 
digitalWrite(buzzer, buz);       // buzzer aktif-pasif komutu
digitalWrite(led, buz);          // led aktif-pasif komutu



 
            /*Değerleri serial port'una gönderiyor.*/
Serial.print("x=");
Serial.println(xDeger);
Serial.print("y=");
Serial.println(yDeger);
Serial.print("z=");
Serial.println(zDeger);
Serial.println("_");
}
