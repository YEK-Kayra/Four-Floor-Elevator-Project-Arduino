#include<LiquidCrystal.h>    ///lcd ekranýmýzý kullanmak üzere ekran kütüphanesini caðýrýr.

LiquidCrystal lcd{8,7,6,5,4,3};   ///lcd ekranýmýzýn baðlý olduðu pinleri sýrasýyla tanýtýrýz.


const int but1=9;                                                                                   /////PROGRAM SAHÝBÝ =YUNUS EMRE KAYRA 
const int but2=10;                                                                                  /////PROGRAMI GELÝÞTÝREN=YUNUS EMRE KAYRA
const int but3=53;     
const int but4=12;

const int sen1=A0;                    
const int sen2=A1;
const int sen3=A2;
const int sen4=A3;

const int leda1=13;
const int ledb1=22;     /// bu bölümde bizim asansör projesinde kullandýðýmýz buton,sensör,segment,motor kontaklarý vardýr.Bu elemanlarýn gideceði pinleri belirtiriz. 
const int ledc1=23;
const int ledd1=24;

const int leda2=25;
const int ledb2=26;
const int ledc2=27;
const int ledd2=28;

const int leda3=29;
const int ledb3=30;
const int ledc3=31;
const int ledd3=32;

const int leda4=33;
const int ledb4=34;
const int ledc4=35;
const int ledd4=36;

const int aydina=37;
const int aydinb=38;                 ///Pano içerisindeki aydýnlatýcý rgblerin pinleri.
const int aydinc=39;

const int rgba=40;
const int rgbb=41;                   ///Pano içerisindeki aydýnlatýcý rgblerin pinleri.
const int rgbc=42;

const int motorup=44;              ///motorup pinimiz motoru saat yönünün tersinde haraket ettirir ve asansör kabini yukarýya doðru haraket eder.
const int motordown=45;            ///motordown pinimiz motoru saat yönünün tersinde haraket ettirir ve asansör kabini aþaðýya doðru haraket eder.

const int anahtar=46;             /// asansör kabinini haraket haliyken olurda sensörler gerektiði deðere ulaþamaz ve algýlamaz ise 
                                     ///motor fazla çalýþýp üst katý patlatmamasý  için güvenlik anahtarý.
int hafiza;    

const int icbut1=48;
const int icbut2=49;               /// Kabin içerisindeki butonlar
const int icbut3=50;
const int icbut4=51;

byte yardimci=HIGH;               ///byte olarak oluþturduðumuz "yardimci" deðiþkeni sensörün algýladýðý anda diyer yönlendirme caselerin içine gitmesini önler (yönlendiricicase=

byte arayardimci=HIGH;

int sayac=0;

int newsendurum1;                  ///sayac deðiþkeni ve newsendurum deðiþkenleri tanýmladýk.
int newsendurum2;                  ///sayac=bizim switchcase ifademizdeki deðiþkendir bu deðikene atýyacaðýmýz tam sayý (int) deðerlerine göre case komutlarýna ulaþýrýz.
int newsendurum3;                  ///newsendurum=analog sensör deðerlerimiz 0-255 arasýndaki deðere 'map' komutu sayesinde indirildikten sonra yeni bir deðiþken olarak  yani "newsendurum" deðikenine atadýk.
int newsendurum4;

void setup(){
  lcd.begin(20,2);            ///lcd ekranýmýzýn tanýmlamasýný yaptýk.
   Serial.begin(9600);             /// seri haberleþmeyi baþlattýk. 

 lcd.setCursor(3,0);
lcd.write("*WELCOME*");
delay(5000);
lcd.setCursor(0,1);                 ///Asansör sistemimiz baþaltýrken lcd ekrana gelecek kodlarýmýzý yazdýk.
lcd.write("system is ready");
delay(4000);
lcd.clear();
delay(500);

/////AYDINLATICI BÖLÜMÜ////

  digitalWrite(aydina,HIGH);
digitalWrite(aydinb,LOW);
digitalWrite(aydinc,HIGH);

                                         /// Pano içerisindeki aydýnlatýcý ledleri yeþil olarak ayarladýk(rgb).

digitalWrite(rgba,HIGH);
digitalWrite(rgbb,LOW);
digitalWrite(rgbc,LOW);
  
///////////////////////////////////////////////////

  pinMode(but1,INPUT);
  pinMode(but2,INPUT);
  pinMode(but3,INPUT);
  pinMode(but4,INPUT);

  pinMode(icbut1,INPUT);
  pinMode(icbut2,INPUT);
  pinMode(icbut3,INPUT);
  pinMode(icbut4,INPUT);
  
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(sen3,INPUT);
  pinMode(sen4,INPUT);

  pinMode(leda1,OUTPUT);
  pinMode(ledb1,OUTPUT);
  pinMode(ledc1,OUTPUT);
  pinMode(ledd1,OUTPUT);                ///butonlarýmýzý,switchimizi ,sensörlerimizi giriþ olarak arduino'ya tanýttýk. 
                                        ///motor kontaklarýný, segmentler için yazdýðýmýz led deðiþkenlerini,pano aydýnlatmalarýný çýkýs olarak arduino'ya bildirdik.
 pinMode(leda2,OUTPUT);
  pinMode(ledb2,OUTPUT);
  pinMode(ledc2,OUTPUT);
  pinMode(ledd2,OUTPUT);

   pinMode(leda3,OUTPUT);
  pinMode(ledb3,OUTPUT);
  pinMode(ledc3,OUTPUT);
  pinMode(ledd3,OUTPUT);

   pinMode(leda4,OUTPUT);
  pinMode(ledb4,OUTPUT);
  pinMode(ledc4,OUTPUT);
  pinMode(ledd4,OUTPUT);

   pinMode(motordown,OUTPUT);
  pinMode(motorup,OUTPUT);

  pinMode(aydina,OUTPUT);
  pinMode(aydinb,OUTPUT);
  pinMode(aydinc,OUTPUT);

  pinMode(rgba,OUTPUT);
   pinMode(rgbb,OUTPUT);
    pinMode(rgbc,OUTPUT);

    
 pinMode(anahtar,INPUT);
/////lcd ekran byte/////
   byte temizleyici[8]={B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000};
  

  
////////////////aradaki çizgilerin pixel kodlamasý/////////////////////
  byte uzuna[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};



byte uzunc[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};                                                  

byte uzund[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};

byte uzune[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};

byte uzung[8]={B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011};

byte okimleci[8]={B00000,
B00100,
B00100,
B01110,
B11111,                                ///Lcd ekrandaki rakamlarýn altýnda beliren ok imleci.
B00100,
B00100,
B00100};

////ara çizgilerin yazýlýmý////
///ara çizgilerin yazýlýmý///
  lcd.createChar(1,uzuna);     

lcd.createChar(3,uzunc);
                                    /// 2 sütunluk dikey çizgiler için karakterler oluþturuyoruz .
lcd.createChar(4,uzund);
                                       
lcd.createChar(5,uzune);

lcd.createChar(6,uzung);

lcd.createChar(7,okimleci);         ///analog sensör algýladýðý zaman "K1||K2||K3||K4" kelimelerinin altýnda beliren ok imleci.
lcd.createChar(8,temizleyici);      /// eðer analog sensör algýlamýyorsa ok imlecini temizlemeye yarayan süpürge.


//////lcd ekran//////
  lcd.setCursor(0,0);
  lcd.write(byte(1));       ///lcd ekrandaki en sol düz 2 sütunluk çizgi yazýlýmý ve "K1" yazýsý. 
  lcd.setCursor(0,1);
  lcd.write(byte(1));
lcd.setCursor(1,0);
 lcd.print("K1");

  lcd.setCursor(4,1);
  lcd.write(byte(3));
  lcd.setCursor(4,0);         /// lcd ekrandaki "K1" yazýsýnýn hemen saðýndaki 2 sutunluk dar çizgi ve "K2" yazýsý.
  lcd.write(byte(3));
  lcd.setCursor(5,0);
  lcd.print("K2");

  lcd.setCursor(8,1);
  lcd.write(byte(4));                                      
  lcd.setCursor(8,0);        /// lcd ekrandaki "K2" yazýsýnýn hemen  saðýndaki  2 sütunluk dar çizgi ve "K3" yazýsý.
  lcd.write(byte(4));
  lcd.setCursor(9,0);
  lcd.print("K3");

  lcd.setCursor(12,1);
  lcd.write(byte(5));            /// lcd ekrandaki "K3" yazýsýnýn hemen  saðýndaki 2 sütunluk dar çizgi ve "K4" yazýsý.
  lcd.setCursor(12,0);
  lcd.write(byte(5));
  lcd.setCursor(13,0);
  lcd.print("K4");
  
  lcd.setCursor(15,1);
  lcd.write(byte(6));              ///lcd ekranýn en sað bölümünde yer alan 2 sütunluk dar çizgi.
  lcd.setCursor(15,0);
  lcd.write(byte(6));


}

void loop(){
  int butdurum1=digitalRead(but1);
  int butdurum2=digitalRead(but2);     ///but1,but2,but3,but4  dijital olarak bu butonlarý sürekli oku ve okuduðun her deðeri butdurumlarýn içerisine tam sayý olarak ata(0V=0,+5V=1).
 int butdurum3=digitalRead(but3);
 int butdurum4=digitalRead(but4);
int anahtardurum=digitalRead(anahtar);   ///Tavanda bulunan switchden gelen deðerleri anahtardurum deðiþkeninin içine atýyoruz.

int icbutdurum1=digitalRead(icbut1);
int icbutdurum2=digitalRead(icbut2);
int icbutdurum3=digitalRead(icbut3);   /// Kabin içerisindeki butonlarýn gelen deðerlerini icbutdurum deðiþkeninin içine atýyoruz.
int icbutdurum4=digitalRead(icbut4);

int sendurum1=analogRead(sen1);
 int sendurum2=analogRead(sen2);
 int sendurum3=analogRead(sen3);      ///sen1,sen2,sen3,sen4  analog olarak bu sensörlerden gelen deðerleri sürekli olarak oku ve okuduðun her deðeri tam sayý olarak sendurumlarýn içerisine ata (0-255).
 int sendurum4=analogRead(sen4);



int newsendurum1=map(sendurum1,0,1023,0,255);


int newsendurum2=map(sendurum2,0,1023,0,255);
                       ///map komutu sayesinde okuduðumuz sendurum deðerlerini 0 ile 1023 arasýndaki sayýyý 0 ile 255 arasýna çevirip benim yeni deðiþkenim olan newsendurum'un içerisine atýyoruz.
                                                    
int newsendurum3=map(sendurum3,0,1023,0,255);


int newsendurum4=map(sendurum4,0,1023,0,255);


////BUTON DURUMLARI SERÝ HABERLEÞMESÝ////

if(icbutdurum1||butdurum1==HIGH){
  Serial.println("buton 1 aktif");        ///Eðer butdurum1 e basýlý ise seri olarak "buton 1 aktif " yazdýr.
}

if(icbutdurum2||butdurum2==HIGH){
  Serial.println("buton 2 aktif");        ///Eðer butdurum2 e basýlý ise seri olarak "buton 2 aktif " yazdýr.
}
                                         
if(icbutdurum3||butdurum3==HIGH){
  Serial.println("buton 3 aktif");        ///Eðer butdurum3 e basýlý ise seri olarak "buton 3 aktif " yazdýr.
}

if(icbutdurum4||butdurum4==HIGH){
  Serial.println("buton 4 aktif");        ///Eðer butdurum4 e basýlý ise seri olarak "buton 4 aktif " yazdýr.
}

if(anahtardurum==HIGH){
  digitalWrite(motorup,LOW);
  digitalWrite(motordown,LOW);

 lcd.clear();                            //// eðer en üstteki limit anahtarýna dokunursa çalýsýcak kod.   
 lcd.setCursor(1,0);
lcd.write("TAVANA CARPTI");
 lcd.setCursor(2,1);
 lcd.write("!! ALARM !!");
 delay(4000);
 lcd.clear();
 /////lcd ekran byte/////
   byte temizleyici[8]={B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000};
  

  
////////////////aradaki çizgilerin pixel kodlamasý/////////////////////
  byte uzuna[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};



byte uzunc[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};                                                  

byte uzund[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};

byte uzune[8]={B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000};

byte uzung[8]={B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011};

byte okimleci[8]={B00000,
B00100,
B00100,
B01110,
B11111,
B00100,
B00100,
B00100};

////ara çizgilerin yazýlýmý////
///ara çizgilerin yazýlýmý///
  lcd.createChar(1,uzuna);     

lcd.createChar(3,uzunc);
                                    /// 2 sütunluk dikey çizgiler için karakterler oluþturuyoruz 
lcd.createChar(4,uzund);
                                       
lcd.createChar(5,uzune);

lcd.createChar(6,uzung);

lcd.createChar(7,okimleci);         ///analog sensör algýladýðý zaman "K1||K2||K3||K4" kelimelerinin altýnda beliren ok imleci 
lcd.createChar(8,temizleyici);      /// eðer analog sensör algýlamýyorsa ok imlecini temizlemeye yarayan süpürge

delay(2000);
   sayac=18;

}



/////YÖNLENDÝRÝCÝ CASE BÖLÜMÜ////
if(yardimci&&newsendurum1>=30){
  sayac=1;                                        ///Eðer yardimci deðiþkeni ve sensör1  aktif ise case(1) e git.
               
}

if(yardimci&&newsendurum4>=30){                   
  sayac=5;                                       ///Eðer yardimci deðiþkeni ve sensör2  aktif ise case(5) e git.
}

if(yardimci&&newsendurum2>=30){
  sayac=9;                                       ///Eðer yardimci deðiþkeni ve sensör3  aktif ise case(9) e git.
}

if(yardimci&&newsendurum3>=30){
  sayac=13;                                     ///Eðer yardimci deðiþkeni ve sensör4  aktif ise case(13) e git.
}


                               ///buradaki yardimci deðiþken digital olduðu için ve biz baþta onu HIGH yani içine 5v verdiðimizden dolayý analog olarak 130 sayýsýný görse bile 250 içerisinde decimal
                               ///olarak var olduðu için onu dikkate almayacaktýr.
       


//////HARAKET ALGORÝTMASI /////////////////////////
switch(sayac){

  ///MOTOR DURDURMA BÖLÜMÜ////
case(0):
delay(50);
digitalWrite(motorup,LOW);
digitalWrite(motordown,LOW);
arayardimci=HIGH;
yardimci=HIGH;

  break;

/////////1.KAT///////  
  case(1):
  yardimci=LOW;
  if(icbutdurum2||butdurum2==HIGH){         ///Eðer buton2 ye basýldýysa case(2) ye atla.
  sayac=2;
}
else if(icbutdurum3||butdurum3==HIGH){       ///Eðer buton3 ye basýldýysa case(3) ye atla.
  sayac=3;  
}

else if(icbutdurum4||butdurum4==HIGH){       ///Eðer buton4 ye basýldýysa case(4) ye atla.
  sayac=4;
}
break;
  

case(2):
yardimci=LOW;
digitalWrite(motorup,HIGH);          ///yardimci deðiþkeninin içine 0 at  ayný zamanda motoru saat yönünde tersine çevir.
digitalWrite(motordown,LOW);         ///eðer sensör2 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum2>=30){
  sayac=0;
}

else if(hafiza==1&&newsendurum2>=30){
  digitalWrite(motorup,LOW);
  
  digitalWrite(leda1,LOW);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
    
      digitalWrite(ledb2,HIGH);
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);
     digitalWrite(leda2,LOW);         ///eðer ikinci kattaki sensör aktif ise bütün katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///eðer ikinci katýn sensörü algýlýyorsa ok imlecini 6. sütunun 1. satýrda yazdýr .
  lcd.write(byte(7));
  
  delay(4000);
  arayardimci=HIGH;
  sayac=3;
}
else if(hafiza==2&&newsendurum2>=30){
  digitalWrite(motorup,LOW);
  

 
  digitalWrite(leda1,LOW);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
    
      digitalWrite(ledb2,HIGH);
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);
     digitalWrite(leda2,LOW);         ///eðer ikinci kattaki sensör aktif ise bütün katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
       lcd.setCursor(6,1);            ///eðer ikinci katýn sensörü algýlýyorsa ok imlecini 6. sütunun 1. satýrda yazdýr .
  lcd.write(byte(7));
  
  delay(4000);
   arayardimci=HIGH;
  sayac=4;
}
break;                               //// break komutu bir case ifadesinin sonu olduðunu belirtmek için kullanýlýr.

case(3):
yardimci=LOW;
digitalWrite(motorup,HIGH);           ///yardimci deðiþkeninin içine 0 at  ayný zamanda motoru saat yönünde tersine çevir.
digitalWrite(motordown,LOW);          ///eðer sensör3 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum3>=30){
  sayac=0; 
}

else if(icbutdurum2||butdurum2==HIGH&&newsendurum3<=30){       ///asansör kabini basýlan kata doðru yol alýyor daha sensör3 e ulaþmamýs ve 2. kattan birisi çaðýrdýysa case(2) ye git.
  arayardimci=LOW;
  hafiza=1;
  sayac=2;
}
else if(hafiza==3&&newsendurum3>=30){
  digitalWrite(motorup,LOW);
  
   digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz. 
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr. 
  lcd.write(byte(7));
 
  delay(4000);
  arayardimci=HIGH;
  sayac=4;
}
break;

case(4):
yardimci=LOW;
digitalWrite(motorup,HIGH);               ///yardimci deðiþkeninin içine 0 at  ayný zamanda motoru saat yönünde tersine çevir.
digitalWrite(motordown,LOW);               ///eðer sensör4 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum4>=30){
  sayac=0;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum3&&newsendurum4<=30){    ///asansör kabini 4. kata doðru giderken daha sensör3 ve sensör4 aktif deðilse o anda kiþi 2. katýn butonuna basarsa case(2) ye git.
  arayardimci=LOW;
  hafiza=2;
  sayac=2;
  
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum4<=30){                    ////asansör kabini daha 4. kata ulaþmamýþ 3.kattan caðýrýlýrsa case(3) e git.
   arayardimci=LOW;
  hafiza=3;
  sayac=3;
}
break;


 //////4.KAT////////////////


case(5):
yardimci=LOW;
if(icbutdurum3||butdurum3==HIGH){         ///Eðer buton3 e basýldýysa case(6) ye atla.
  sayac=6;
}
else if(icbutdurum2||butdurum2==HIGH){    ///Eðer buton2 ye basýldýysa case(7) ye atla.
  sayac=7;
}
else if(icbutdurum1||butdurum1==HIGH){     ///Eðer buton1 e basýldýysa case(8) ye atla.
  sayac=8;
}
break;

case(6):
yardimci=LOW;
digitalWrite(motordown,HIGH);      ///yardimci deðiþkeninin içine 0 at ve ayný zamanda motoru saat yönünde çevir.
digitalWrite(motorup,LOW);            ///eðer sensör3 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum3>=30){
  sayac=0;
}

else if(hafiza==4&&newsendurum3>=30){
  digitalWrite(motordown,LOW);
  
     digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz. 
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr. 
  lcd.write(byte(7));
  
  delay(4000);
  arayardimci=HIGH;
  sayac=7;
  
}

else if(hafiza==5&&newsendurum3>=30){
  digitalWrite(motordown,LOW);
  
 
   digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz. 
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
 lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr. 
  lcd.write(byte(7));
  

  delay(4000);
  arayardimci=HIGH;
  sayac=8;
  
}
break;

case(7):
yardimci=LOW;
digitalWrite(motordown,HIGH);         ///yardimci deðiþkeninin içine 0 at ve ayný zamanda motoru saat yönünde çevir.
digitalWrite(motorup,LOW);              ///eðer sensör2 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum2>=30){
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum2<=30){     ////asansör kabini daha 2.kata varmadýysa ve 3.kattan çaðrýldýysa case(6) ya git.
  hafiza=4;
  arayardimci=LOW;
  sayac=6;
}
else if(hafiza==6&&newsendurum2>=30){
  digitalWrite(motordown,LOW);
  
    digitalWrite(leda1,LOW);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
    
      digitalWrite(ledb2,HIGH);
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);
     digitalWrite(leda2,LOW);         ///eðer ikinci kattaki sensör aktif ise bütün katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///eðer ikinci katýn sensörü algýlýyorsa ok imlecini 6. sütunun 1. satýrda yazdýr .
  lcd.write(byte(7));
  delay(4000);
  arayardimci=HIGH;
  sayac=8;
}
break;

case(8):
yardimci=LOW;
digitalWrite(motordown,HIGH);           ///yardimci deðiþkeninin içine 0 at ve ayný zamanda motoru saat yönünde çevir.
digitalWrite(motorup,LOW);               ///eðer sensör1 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
if(arayardimci&&newsendurum1>=30){
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum2<=30){         ////asansör kabini daha 2.kata varmadýysa ve 3.kattan çaðrýldýysa case(6) ya git.
  hafiza=5;
   arayardimci=LOW;
  sayac=6;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum1<=30){           ////asansör kabini daha 1.kata varmadýysa ve 2.kattan çaðrýldýysa case(7) ya git.
   hafiza=6;
   arayardimci=LOW;
  sayac=7;
}
break;

////////2.KAT////////////

case(9):
yardimci=LOW;           
if(icbutdurum1||butdurum1==HIGH){      /// buton1 e basýlýrsa case(8) e git .
  sayac=8;
}
else if(icbutdurum3||icbutdurum4||butdurum3||butdurum4==HIGH){    /// buton3 veya buton4 e basýlýrsa case(10) a git.
  sayac=10;
}
break;


case(10):
yardimci=LOW;              ///yardimci deðiþkeninin içine 0 at ve eðer buton3 e basýldýysa da case(11) e git .
if(icbutdurum3||butdurum3==HIGH){
  sayac=11;
}
else if(icbutdurum4||butdurum4==HIGH){     ///eðer buton 3 basýlý deðilse buton4 e basýldýysa case(11) e git.
  sayac=12;
}
break;


case(11):
yardimci=LOW;
digitalWrite(motorup,HIGH);     ///yardimci deðiþkeninin içine 0 at ve motoru saat yönünün tersine çevir .
digitalWrite(motordown,LOW);
if(arayardimci!=7&&newsendurum3>=30){         ///eðer sensör3 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
  sayac=0;
}
else if(hafiza==7&&newsendurum3>=30){
  digitalWrite(motordown,LOW);
 
                                   ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 10. sütunun 1. satýrýna yazdýr.
  digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz. 
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     
  lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr. 
  lcd.write(byte(7));
  delay(4000);
  arayardimci=HIGH;
  sayac=12;
}
case(12):
yardimci=LOW;
digitalWrite(motorup,HIGH);         ///yardimci deðiþkeninin içine 0 at ve motoru saat yönünün tersine çevir .
digitalWrite(motordown,LOW);
if(arayardimci&&newsendurum4>=30){                ///eðer sensör4 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum4<=30){    ////daha 4. kata ulaþmadýysa ve 3. kattan caðrýldýysa case(11) e git.
  arayardimci=LOW;
  hafiza=7;
  sayac=11;
}
break;

//////3.KAT///////////
case(13):
yardimci=LOW;
if(icbutdurum4||butdurum4==HIGH){      ////yardimci deðiþkeninin içene 0 at ve eðer buton4 e basýldýysa case(14) e git.
  sayac=14;
}
if(icbutdurum1||icbutdurum2||butdurum2||butdurum1==HIGH){    ////buton2 veya buton1 e basýldýysa case(15) e git. 
  sayac=15;
}
break;

case(14):
yardimci=LOW; 
digitalWrite(motorup,HIGH);     ////yardimci deðiþkenin içine 0 at ve motoru saat yönünün tersine çevir .
digitalWrite(motordown,LOW);
if(newsendurum4>=30){          ///eðer sensör4 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
  sayac=0;
}
break;

case(15):
yardimci=LOW;
if(icbutdurum2||butdurum2==HIGH){          ////yardimci deðiþkenin içine 0 at ve eðer buton2 ye basýldýysa case(16) ya git.
  sayac=16;
}
else if(icbutdurum1||butdurum1==HIGH){         /// yok eðer buton2 ye basýlmamýs ama buton1 e basýldýysa case(17) ye git. 
  sayac=17;
}
break;

case(16):
yardimci=LOW;
digitalWrite(motordown,HIGH);   ////yardimci deðiþkeninin içine 0 at ve motoru saat yönünde çevir .
digitalWrite(motorup,LOW);

if(arayardimci&&newsendurum2>=30){              ///eðer sensör2 istenilen ýþýk þiddetine ulaþtýysa case(0) a git.
  sayac=0;                    
}
if(hafiza==8&&newsendurum2>=30){
  digitalWrite(motordown,LOW);
   
  

   digitalWrite(leda1,LOW);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
    
      digitalWrite(ledb2,HIGH);
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);
     digitalWrite(leda2,LOW);         ///eðer ikinci kattaki sensör aktif ise bütün katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///eðer ikinci katýn sensörü algýlýyorsa ok imlecini 6. sütunun 1. satýrda yazdýr .
  lcd.write(byte(7));
  
  delay(4000);
  arayardimci=HIGH;            
  sayac=17;
}

break;

case(17):
yardimci=LOW;          
digitalWrite(motordown,HIGH);           ////yardimci deðiþkeninin içine 0 at ve motoru saat yönünde çevir. 
digitalWrite(motorup,LOW);
if(arayardimci&&newsendurum1>=30){                   ///eðer sensör1 istenilen ýþýk þiddetine ulaþtýysa ve arayardimci=1 ise case(0) a git.
  sayac=0;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum1<=30){    ////eðer asansör kabini sensör1 e ulaþmadýysa ve 2. kattan çaðrýldýysa case(16) ya git.
  arayardimci=LOW;
  hafiza=8;                                                    ///hafiza deðiþkeninin içine 8 at , arayardimci byte ný=0 yap 
  sayac=16;                                          
}
break;

case(18):                              ///Switch in kodu
yardimci=LOW;
digitalWrite(motorup,LOW);
digitalWrite(motordown,HIGH);
if(newsendurum3>=40){
  digitalWrite(motordown,LOW);
  digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz .
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);

   if(newsendurum3>=40){
  lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr .
  lcd.write(byte(7));
  }                                  ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 10. sütunun 1. satýrýna yazdýr.
  else{
    lcd.setCursor(10,1);
    lcd.write(byte(8));
  }

 
  sayac=0;
}
break;


default:                                  ///default ile switch ifademizin burada son bulduðunu söylüyoruz ve seri olarak eðer hiçbir switch çalýþmýyorsa bize "BEKLÝYOR" ifadesini yazdýrmasýný söylüyoruz.
      Serial.println(" BEKLIYOR ");         ///

}
//////////////////////////////////////////////////////////////////




//////////segment//////////
  if(newsendurum1>=30){
    digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,LOW);
     digitalWrite(ledc1,LOW);
      digitalWrite(ledd1,LOW);

       digitalWrite(leda2,HIGH);
       digitalWrite(ledb2,LOW);          ///eðer birinci kattaki sensör aktif ise bütün katlardaki segmentlere "1" yaz. 
     digitalWrite(ledc2,LOW);
      digitalWrite(ledd2,LOW);

      digitalWrite(leda3,HIGH);
       digitalWrite(ledb3,LOW);
     digitalWrite(ledc3,LOW);
      digitalWrite(ledd3,LOW);

       digitalWrite(leda4,HIGH);
       digitalWrite(ledb4,LOW);
     digitalWrite(ledc4,LOW);
      digitalWrite(ledd4,LOW);

      


      
  }

  if(newsendurum2>=50){
    digitalWrite(leda1,LOW);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
    
      digitalWrite(ledb2,HIGH);
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);
     digitalWrite(leda2,LOW);         ///eðer ikinci kattaki sensör aktif ise bütün katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
    
  }
  if(newsendurum3>=50){
    
    digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///eðer üçüncü  kattaki sensör aktif ise bütün katlardaki segmentlere "3" yaz. 
    digitalWrite(ledc2,LOW);
    digitalWrite(ledd2,LOW);

    
     digitalWrite(leda3,HIGH);
    digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);

   digitalWrite(leda4,HIGH);
    digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);

    
    
  }

  if(newsendurum4>=50){
    digitalWrite(leda1,LOW);
    digitalWrite(ledb1,LOW);
    digitalWrite(ledc1,HIGH);
    digitalWrite(ledd1,LOW);

    digitalWrite(leda2,LOW);
    digitalWrite(ledb2,LOW);
    digitalWrite(ledc2,HIGH);           ///eðer dördüncü kattaki sensör aktif ise bütün katlardaki segmentlere "4" yaz .
    digitalWrite(ledd2,LOW);

    digitalWrite(leda3,LOW);
    digitalWrite(ledb3,LOW);
    digitalWrite(ledc3,HIGH);
    digitalWrite(ledd3,LOW);

     digitalWrite(leda4,LOW);
    digitalWrite(ledb4,LOW);
    digitalWrite(ledc4,HIGH);
    digitalWrite(ledd4,LOW);
  }
  
  
  //////lcd ekran//////
  lcd.setCursor(0,0);
  lcd.write(byte(1));       ///lcd ekrandaki en sol düz 2 sütunluk çizgi yazýlýmý ve "K1" yazýsý. 
  lcd.setCursor(0,1);
  lcd.write(byte(1));
lcd.setCursor(1,0);
 lcd.print("K1");

  lcd.setCursor(4,1);
  lcd.write(byte(3));
  lcd.setCursor(4,0);         /// lcd ekrandaki "K1" yazýsýnýn hemen saðýndaki 2 sutunluk dar çizgi ve "K2" yazýsý.
  lcd.write(byte(3));
  lcd.setCursor(5,0);
  lcd.print("K2");

  lcd.setCursor(8,1);
  lcd.write(byte(4));                                      
  lcd.setCursor(8,0);        /// lcd ekrandaki "K2" yazýsýnýn hemen  saðýndaki  2 sütunluk dar çizgi ve "K3" yazýsý.
  lcd.write(byte(4));
  lcd.setCursor(9,0);
  lcd.print("K3");

  lcd.setCursor(12,1);
  lcd.write(byte(5));            /// lcd ekrandaki "K3" yazýsýnýn hemen  saðýndaki 2 sütunluk dar çizgi ve "K4" yazýsý.
  lcd.setCursor(12,0);
  lcd.write(byte(5));
  lcd.setCursor(13,0);
  lcd.print("K4");
  
  lcd.setCursor(15,1);
  lcd.write(byte(6));              ///lcd ekranýn en sað bölümünde yer alan 2 sütunluk dar çizgi.
  lcd.setCursor(15,0);
  lcd.write(byte(6));

  if(newsendurum1>=30){
  lcd.setCursor(2,1);          ///eðer birinci katýn sensörü algýlýyorsa ok imlecini 2 sütunun 1 satýrda yazdýr .
  lcd.write(byte(7));
  }                               ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 2 sütunun 1 satýrýna yazdýr.
  else{
    lcd.setCursor(2,1);
    lcd.write(byte(8));
  }


  if(newsendurum2>=50){
  lcd.setCursor(6,1);            ///eðer ikinci katýn sensörü algýlýyorsa ok imlecini 6. sütunun 1. satýrda yazdýr .
  lcd.write(byte(7));
  }
  else{                              ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 6. sütunun 1. satýrýna yazdýr.
    lcd.setCursor(6,1);
    lcd.write(byte(8));
  }

 
  if(newsendurum3>=50){
  lcd.setCursor(10,1);            ///eðer üçüncü katýn sensörü algýlýyorsa ok imlecini 10 sütunun 1 satýrda yazdýr. 
  lcd.write(byte(7));
  }                                  ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 10. sütunun 1. satýrýna yazdýr.
  else{
    lcd.setCursor(10,1);
    lcd.write(byte(8));
  }


  if(newsendurum4>=50){
  lcd.setCursor(14,1);
  lcd.write(byte(7));             ///eðer dördüncü  katýn sensörü algýlýyorsa ok imlecini 14. sütunun 1. satýrda yazdýr.
  }
  else{                              ///yok eðer algýlamýyorsa bizim süpürge dediðimiz byte 'tý ayný 14. sütunun 1. satýrýna yazdýr.
    lcd.setCursor(14,1);
    lcd.write(byte(8));
  }

}


