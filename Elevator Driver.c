#include<LiquidCrystal.h>    ///lcd ekran�m�z� kullanmak �zere ekran k�t�phanesini ca��r�r.

LiquidCrystal lcd{8,7,6,5,4,3};   ///lcd ekran�m�z�n ba�l� oldu�u pinleri s�ras�yla tan�t�r�z.


const int but1=9;                                                                                   /////PROGRAM SAH�B� =YUNUS EMRE KAYRA 
const int but2=10;                                                                                  /////PROGRAMI GEL��T�REN=YUNUS EMRE KAYRA
const int but3=53;     
const int but4=12;

const int sen1=A0;                    
const int sen2=A1;
const int sen3=A2;
const int sen4=A3;

const int leda1=13;
const int ledb1=22;     /// bu b�l�mde bizim asans�r projesinde kulland���m�z buton,sens�r,segment,motor kontaklar� vard�r.Bu elemanlar�n gidece�i pinleri belirtiriz. 
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
const int aydinb=38;                 ///Pano i�erisindeki ayd�nlat�c� rgblerin pinleri.
const int aydinc=39;

const int rgba=40;
const int rgbb=41;                   ///Pano i�erisindeki ayd�nlat�c� rgblerin pinleri.
const int rgbc=42;

const int motorup=44;              ///motorup pinimiz motoru saat y�n�n�n tersinde haraket ettirir ve asans�r kabini yukar�ya do�ru haraket eder.
const int motordown=45;            ///motordown pinimiz motoru saat y�n�n�n tersinde haraket ettirir ve asans�r kabini a�a��ya do�ru haraket eder.

const int anahtar=46;             /// asans�r kabinini haraket haliyken olurda sens�rler gerekti�i de�ere ula�amaz ve alg�lamaz ise 
                                     ///motor fazla �al���p �st kat� patlatmamas�  i�in g�venlik anahtar�.
int hafiza;    

const int icbut1=48;
const int icbut2=49;               /// Kabin i�erisindeki butonlar
const int icbut3=50;
const int icbut4=51;

byte yardimci=HIGH;               ///byte olarak olu�turdu�umuz "yardimci" de�i�keni sens�r�n alg�lad��� anda diyer y�nlendirme caselerin i�ine gitmesini �nler (y�nlendiricicase=

byte arayardimci=HIGH;

int sayac=0;

int newsendurum1;                  ///sayac de�i�keni ve newsendurum de�i�kenleri tan�mlad�k.
int newsendurum2;                  ///sayac=bizim switchcase ifademizdeki de�i�kendir bu de�ikene at�yaca��m�z tam say� (int) de�erlerine g�re case komutlar�na ula��r�z.
int newsendurum3;                  ///newsendurum=analog sens�r de�erlerimiz 0-255 aras�ndaki de�ere 'map' komutu sayesinde indirildikten sonra yeni bir de�i�ken olarak  yani "newsendurum" de�ikenine atad�k.
int newsendurum4;

void setup(){
  lcd.begin(20,2);            ///lcd ekran�m�z�n tan�mlamas�n� yapt�k.
   Serial.begin(9600);             /// seri haberle�meyi ba�latt�k. 

 lcd.setCursor(3,0);
lcd.write("*WELCOME*");
delay(5000);
lcd.setCursor(0,1);                 ///Asans�r sistemimiz ba�alt�rken lcd ekrana gelecek kodlar�m�z� yazd�k.
lcd.write("system is ready");
delay(4000);
lcd.clear();
delay(500);

/////AYDINLATICI B�L�M�////

  digitalWrite(aydina,HIGH);
digitalWrite(aydinb,LOW);
digitalWrite(aydinc,HIGH);

                                         /// Pano i�erisindeki ayd�nlat�c� ledleri ye�il olarak ayarlad�k(rgb).

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
  pinMode(ledd1,OUTPUT);                ///butonlar�m�z�,switchimizi ,sens�rlerimizi giri� olarak arduino'ya tan�tt�k. 
                                        ///motor kontaklar�n�, segmentler i�in yazd���m�z led de�i�kenlerini,pano ayd�nlatmalar�n� ��k�s olarak arduino'ya bildirdik.
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
  

  
////////////////aradaki �izgilerin pixel kodlamas�/////////////////////
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
B11111,                                ///Lcd ekrandaki rakamlar�n alt�nda beliren ok imleci.
B00100,
B00100,
B00100};

////ara �izgilerin yaz�l�m�////
///ara �izgilerin yaz�l�m�///
  lcd.createChar(1,uzuna);     

lcd.createChar(3,uzunc);
                                    /// 2 s�tunluk dikey �izgiler i�in karakterler olu�turuyoruz .
lcd.createChar(4,uzund);
                                       
lcd.createChar(5,uzune);

lcd.createChar(6,uzung);

lcd.createChar(7,okimleci);         ///analog sens�r alg�lad��� zaman "K1||K2||K3||K4" kelimelerinin alt�nda beliren ok imleci.
lcd.createChar(8,temizleyici);      /// e�er analog sens�r alg�lam�yorsa ok imlecini temizlemeye yarayan s�p�rge.


//////lcd ekran//////
  lcd.setCursor(0,0);
  lcd.write(byte(1));       ///lcd ekrandaki en sol d�z 2 s�tunluk �izgi yaz�l�m� ve "K1" yaz�s�. 
  lcd.setCursor(0,1);
  lcd.write(byte(1));
lcd.setCursor(1,0);
 lcd.print("K1");

  lcd.setCursor(4,1);
  lcd.write(byte(3));
  lcd.setCursor(4,0);         /// lcd ekrandaki "K1" yaz�s�n�n hemen sa��ndaki 2 sutunluk dar �izgi ve "K2" yaz�s�.
  lcd.write(byte(3));
  lcd.setCursor(5,0);
  lcd.print("K2");

  lcd.setCursor(8,1);
  lcd.write(byte(4));                                      
  lcd.setCursor(8,0);        /// lcd ekrandaki "K2" yaz�s�n�n hemen  sa��ndaki  2 s�tunluk dar �izgi ve "K3" yaz�s�.
  lcd.write(byte(4));
  lcd.setCursor(9,0);
  lcd.print("K3");

  lcd.setCursor(12,1);
  lcd.write(byte(5));            /// lcd ekrandaki "K3" yaz�s�n�n hemen  sa��ndaki 2 s�tunluk dar �izgi ve "K4" yaz�s�.
  lcd.setCursor(12,0);
  lcd.write(byte(5));
  lcd.setCursor(13,0);
  lcd.print("K4");
  
  lcd.setCursor(15,1);
  lcd.write(byte(6));              ///lcd ekran�n en sa� b�l�m�nde yer alan 2 s�tunluk dar �izgi.
  lcd.setCursor(15,0);
  lcd.write(byte(6));


}

void loop(){
  int butdurum1=digitalRead(but1);
  int butdurum2=digitalRead(but2);     ///but1,but2,but3,but4  dijital olarak bu butonlar� s�rekli oku ve okudu�un her de�eri butdurumlar�n i�erisine tam say� olarak ata(0V=0,+5V=1).
 int butdurum3=digitalRead(but3);
 int butdurum4=digitalRead(but4);
int anahtardurum=digitalRead(anahtar);   ///Tavanda bulunan switchden gelen de�erleri anahtardurum de�i�keninin i�ine at�yoruz.

int icbutdurum1=digitalRead(icbut1);
int icbutdurum2=digitalRead(icbut2);
int icbutdurum3=digitalRead(icbut3);   /// Kabin i�erisindeki butonlar�n gelen de�erlerini icbutdurum de�i�keninin i�ine at�yoruz.
int icbutdurum4=digitalRead(icbut4);

int sendurum1=analogRead(sen1);
 int sendurum2=analogRead(sen2);
 int sendurum3=analogRead(sen3);      ///sen1,sen2,sen3,sen4  analog olarak bu sens�rlerden gelen de�erleri s�rekli olarak oku ve okudu�un her de�eri tam say� olarak sendurumlar�n i�erisine ata (0-255).
 int sendurum4=analogRead(sen4);



int newsendurum1=map(sendurum1,0,1023,0,255);


int newsendurum2=map(sendurum2,0,1023,0,255);
                       ///map komutu sayesinde okudu�umuz sendurum de�erlerini 0 ile 1023 aras�ndaki say�y� 0 ile 255 aras�na �evirip benim yeni de�i�kenim olan newsendurum'un i�erisine at�yoruz.
                                                    
int newsendurum3=map(sendurum3,0,1023,0,255);


int newsendurum4=map(sendurum4,0,1023,0,255);


////BUTON DURUMLARI SER� HABERLE�MES�////

if(icbutdurum1||butdurum1==HIGH){
  Serial.println("buton 1 aktif");        ///E�er butdurum1 e bas�l� ise seri olarak "buton 1 aktif " yazd�r.
}

if(icbutdurum2||butdurum2==HIGH){
  Serial.println("buton 2 aktif");        ///E�er butdurum2 e bas�l� ise seri olarak "buton 2 aktif " yazd�r.
}
                                         
if(icbutdurum3||butdurum3==HIGH){
  Serial.println("buton 3 aktif");        ///E�er butdurum3 e bas�l� ise seri olarak "buton 3 aktif " yazd�r.
}

if(icbutdurum4||butdurum4==HIGH){
  Serial.println("buton 4 aktif");        ///E�er butdurum4 e bas�l� ise seri olarak "buton 4 aktif " yazd�r.
}

if(anahtardurum==HIGH){
  digitalWrite(motorup,LOW);
  digitalWrite(motordown,LOW);

 lcd.clear();                            //// e�er en �stteki limit anahtar�na dokunursa �al�s�cak kod.   
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
  

  
////////////////aradaki �izgilerin pixel kodlamas�/////////////////////
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

////ara �izgilerin yaz�l�m�////
///ara �izgilerin yaz�l�m�///
  lcd.createChar(1,uzuna);     

lcd.createChar(3,uzunc);
                                    /// 2 s�tunluk dikey �izgiler i�in karakterler olu�turuyoruz 
lcd.createChar(4,uzund);
                                       
lcd.createChar(5,uzune);

lcd.createChar(6,uzung);

lcd.createChar(7,okimleci);         ///analog sens�r alg�lad��� zaman "K1||K2||K3||K4" kelimelerinin alt�nda beliren ok imleci 
lcd.createChar(8,temizleyici);      /// e�er analog sens�r alg�lam�yorsa ok imlecini temizlemeye yarayan s�p�rge

delay(2000);
   sayac=18;

}



/////Y�NLEND�R�C� CASE B�L�M�////
if(yardimci&&newsendurum1>=30){
  sayac=1;                                        ///E�er yardimci de�i�keni ve sens�r1  aktif ise case(1) e git.
               
}

if(yardimci&&newsendurum4>=30){                   
  sayac=5;                                       ///E�er yardimci de�i�keni ve sens�r2  aktif ise case(5) e git.
}

if(yardimci&&newsendurum2>=30){
  sayac=9;                                       ///E�er yardimci de�i�keni ve sens�r3  aktif ise case(9) e git.
}

if(yardimci&&newsendurum3>=30){
  sayac=13;                                     ///E�er yardimci de�i�keni ve sens�r4  aktif ise case(13) e git.
}


                               ///buradaki yardimci de�i�ken digital oldu�u i�in ve biz ba�ta onu HIGH yani i�ine 5v verdi�imizden dolay� analog olarak 130 say�s�n� g�rse bile 250 i�erisinde decimal
                               ///olarak var oldu�u i�in onu dikkate almayacakt�r.
       


//////HARAKET ALGOR�TMASI /////////////////////////
switch(sayac){

  ///MOTOR DURDURMA B�L�M�////
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
  if(icbutdurum2||butdurum2==HIGH){         ///E�er buton2 ye bas�ld�ysa case(2) ye atla.
  sayac=2;
}
else if(icbutdurum3||butdurum3==HIGH){       ///E�er buton3 ye bas�ld�ysa case(3) ye atla.
  sayac=3;  
}

else if(icbutdurum4||butdurum4==HIGH){       ///E�er buton4 ye bas�ld�ysa case(4) ye atla.
  sayac=4;
}
break;
  

case(2):
yardimci=LOW;
digitalWrite(motorup,HIGH);          ///yardimci de�i�keninin i�ine 0 at  ayn� zamanda motoru saat y�n�nde tersine �evir.
digitalWrite(motordown,LOW);         ///e�er sens�r2 istenilen ���k �iddetine ula�t�ysa case(0) a git.
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
     digitalWrite(leda2,LOW);         ///e�er ikinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///e�er ikinci kat�n sens�r� alg�l�yorsa ok imlecini 6. s�tunun 1. sat�rda yazd�r .
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
     digitalWrite(leda2,LOW);         ///e�er ikinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
       lcd.setCursor(6,1);            ///e�er ikinci kat�n sens�r� alg�l�yorsa ok imlecini 6. s�tunun 1. sat�rda yazd�r .
  lcd.write(byte(7));
  
  delay(4000);
   arayardimci=HIGH;
  sayac=4;
}
break;                               //// break komutu bir case ifadesinin sonu oldu�unu belirtmek i�in kullan�l�r.

case(3):
yardimci=LOW;
digitalWrite(motorup,HIGH);           ///yardimci de�i�keninin i�ine 0 at  ayn� zamanda motoru saat y�n�nde tersine �evir.
digitalWrite(motordown,LOW);          ///e�er sens�r3 istenilen ���k �iddetine ula�t�ysa case(0) a git.
if(arayardimci&&newsendurum3>=30){
  sayac=0; 
}

else if(icbutdurum2||butdurum2==HIGH&&newsendurum3<=30){       ///asans�r kabini bas�lan kata do�ru yol al�yor daha sens�r3 e ula�mam�s ve 2. kattan birisi �a��rd�ysa case(2) ye git.
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
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz. 
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
lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r. 
  lcd.write(byte(7));
 
  delay(4000);
  arayardimci=HIGH;
  sayac=4;
}
break;

case(4):
yardimci=LOW;
digitalWrite(motorup,HIGH);               ///yardimci de�i�keninin i�ine 0 at  ayn� zamanda motoru saat y�n�nde tersine �evir.
digitalWrite(motordown,LOW);               ///e�er sens�r4 istenilen ���k �iddetine ula�t�ysa case(0) a git.
if(arayardimci&&newsendurum4>=30){
  sayac=0;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum3&&newsendurum4<=30){    ///asans�r kabini 4. kata do�ru giderken daha sens�r3 ve sens�r4 aktif de�ilse o anda ki�i 2. kat�n butonuna basarsa case(2) ye git.
  arayardimci=LOW;
  hafiza=2;
  sayac=2;
  
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum4<=30){                    ////asans�r kabini daha 4. kata ula�mam�� 3.kattan ca��r�l�rsa case(3) e git.
   arayardimci=LOW;
  hafiza=3;
  sayac=3;
}
break;


 //////4.KAT////////////////


case(5):
yardimci=LOW;
if(icbutdurum3||butdurum3==HIGH){         ///E�er buton3 e bas�ld�ysa case(6) ye atla.
  sayac=6;
}
else if(icbutdurum2||butdurum2==HIGH){    ///E�er buton2 ye bas�ld�ysa case(7) ye atla.
  sayac=7;
}
else if(icbutdurum1||butdurum1==HIGH){     ///E�er buton1 e bas�ld�ysa case(8) ye atla.
  sayac=8;
}
break;

case(6):
yardimci=LOW;
digitalWrite(motordown,HIGH);      ///yardimci de�i�keninin i�ine 0 at ve ayn� zamanda motoru saat y�n�nde �evir.
digitalWrite(motorup,LOW);            ///e�er sens�r3 istenilen ���k �iddetine ula�t�ysa case(0) a git.
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
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz. 
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
lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r. 
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
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz. 
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
 lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r. 
  lcd.write(byte(7));
  

  delay(4000);
  arayardimci=HIGH;
  sayac=8;
  
}
break;

case(7):
yardimci=LOW;
digitalWrite(motordown,HIGH);         ///yardimci de�i�keninin i�ine 0 at ve ayn� zamanda motoru saat y�n�nde �evir.
digitalWrite(motorup,LOW);              ///e�er sens�r2 istenilen ���k �iddetine ula�t�ysa case(0) a git.
if(arayardimci&&newsendurum2>=30){
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum2<=30){     ////asans�r kabini daha 2.kata varmad�ysa ve 3.kattan �a�r�ld�ysa case(6) ya git.
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
     digitalWrite(leda2,LOW);         ///e�er ikinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///e�er ikinci kat�n sens�r� alg�l�yorsa ok imlecini 6. s�tunun 1. sat�rda yazd�r .
  lcd.write(byte(7));
  delay(4000);
  arayardimci=HIGH;
  sayac=8;
}
break;

case(8):
yardimci=LOW;
digitalWrite(motordown,HIGH);           ///yardimci de�i�keninin i�ine 0 at ve ayn� zamanda motoru saat y�n�nde �evir.
digitalWrite(motorup,LOW);               ///e�er sens�r1 istenilen ���k �iddetine ula�t�ysa case(0) a git.
if(arayardimci&&newsendurum1>=30){
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum2<=30){         ////asans�r kabini daha 2.kata varmad�ysa ve 3.kattan �a�r�ld�ysa case(6) ya git.
  hafiza=5;
   arayardimci=LOW;
  sayac=6;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum1<=30){           ////asans�r kabini daha 1.kata varmad�ysa ve 2.kattan �a�r�ld�ysa case(7) ya git.
   hafiza=6;
   arayardimci=LOW;
  sayac=7;
}
break;

////////2.KAT////////////

case(9):
yardimci=LOW;           
if(icbutdurum1||butdurum1==HIGH){      /// buton1 e bas�l�rsa case(8) e git .
  sayac=8;
}
else if(icbutdurum3||icbutdurum4||butdurum3||butdurum4==HIGH){    /// buton3 veya buton4 e bas�l�rsa case(10) a git.
  sayac=10;
}
break;


case(10):
yardimci=LOW;              ///yardimci de�i�keninin i�ine 0 at ve e�er buton3 e bas�ld�ysa da case(11) e git .
if(icbutdurum3||butdurum3==HIGH){
  sayac=11;
}
else if(icbutdurum4||butdurum4==HIGH){     ///e�er buton 3 bas�l� de�ilse buton4 e bas�ld�ysa case(11) e git.
  sayac=12;
}
break;


case(11):
yardimci=LOW;
digitalWrite(motorup,HIGH);     ///yardimci de�i�keninin i�ine 0 at ve motoru saat y�n�n�n tersine �evir .
digitalWrite(motordown,LOW);
if(arayardimci!=7&&newsendurum3>=30){         ///e�er sens�r3 istenilen ���k �iddetine ula�t�ysa case(0) a git.
  sayac=0;
}
else if(hafiza==7&&newsendurum3>=30){
  digitalWrite(motordown,LOW);
 
                                   ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 10. s�tunun 1. sat�r�na yazd�r.
  digitalWrite(leda1,HIGH);
    digitalWrite(ledb1,HIGH);
    digitalWrite(ledc1,LOW);
    digitalWrite(ledd1,LOW);
 
     digitalWrite(leda2,HIGH);
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz. 
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
     
  lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r. 
  lcd.write(byte(7));
  delay(4000);
  arayardimci=HIGH;
  sayac=12;
}
case(12):
yardimci=LOW;
digitalWrite(motorup,HIGH);         ///yardimci de�i�keninin i�ine 0 at ve motoru saat y�n�n�n tersine �evir .
digitalWrite(motordown,LOW);
if(arayardimci&&newsendurum4>=30){                ///e�er sens�r4 istenilen ���k �iddetine ula�t�ysa case(0) a git.
  sayac=0;
}
else if(icbutdurum3||butdurum3==HIGH&&newsendurum4<=30){    ////daha 4. kata ula�mad�ysa ve 3. kattan ca�r�ld�ysa case(11) e git.
  arayardimci=LOW;
  hafiza=7;
  sayac=11;
}
break;

//////3.KAT///////////
case(13):
yardimci=LOW;
if(icbutdurum4||butdurum4==HIGH){      ////yardimci de�i�keninin i�ene 0 at ve e�er buton4 e bas�ld�ysa case(14) e git.
  sayac=14;
}
if(icbutdurum1||icbutdurum2||butdurum2||butdurum1==HIGH){    ////buton2 veya buton1 e bas�ld�ysa case(15) e git. 
  sayac=15;
}
break;

case(14):
yardimci=LOW; 
digitalWrite(motorup,HIGH);     ////yardimci de�i�kenin i�ine 0 at ve motoru saat y�n�n�n tersine �evir .
digitalWrite(motordown,LOW);
if(newsendurum4>=30){          ///e�er sens�r4 istenilen ���k �iddetine ula�t�ysa case(0) a git.
  sayac=0;
}
break;

case(15):
yardimci=LOW;
if(icbutdurum2||butdurum2==HIGH){          ////yardimci de�i�kenin i�ine 0 at ve e�er buton2 ye bas�ld�ysa case(16) ya git.
  sayac=16;
}
else if(icbutdurum1||butdurum1==HIGH){         /// yok e�er buton2 ye bas�lmam�s ama buton1 e bas�ld�ysa case(17) ye git. 
  sayac=17;
}
break;

case(16):
yardimci=LOW;
digitalWrite(motordown,HIGH);   ////yardimci de�i�keninin i�ine 0 at ve motoru saat y�n�nde �evir .
digitalWrite(motorup,LOW);

if(arayardimci&&newsendurum2>=30){              ///e�er sens�r2 istenilen ���k �iddetine ula�t�ysa case(0) a git.
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
     digitalWrite(leda2,LOW);         ///e�er ikinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "2" yaz .

      digitalWrite(ledb3,HIGH);
    digitalWrite(ledc3,LOW);
    digitalWrite(ledd3,LOW);
     digitalWrite(leda3,LOW);

       digitalWrite(ledb4,HIGH);
    digitalWrite(ledc4,LOW);
    digitalWrite(ledd4,LOW);
     digitalWrite(leda4,LOW);
     lcd.setCursor(6,1);            ///e�er ikinci kat�n sens�r� alg�l�yorsa ok imlecini 6. s�tunun 1. sat�rda yazd�r .
  lcd.write(byte(7));
  
  delay(4000);
  arayardimci=HIGH;            
  sayac=17;
}

break;

case(17):
yardimci=LOW;          
digitalWrite(motordown,HIGH);           ////yardimci de�i�keninin i�ine 0 at ve motoru saat y�n�nde �evir. 
digitalWrite(motorup,LOW);
if(arayardimci&&newsendurum1>=30){                   ///e�er sens�r1 istenilen ���k �iddetine ula�t�ysa ve arayardimci=1 ise case(0) a git.
  sayac=0;
}
else if(icbutdurum2||butdurum2==HIGH&&newsendurum1<=30){    ////e�er asans�r kabini sens�r1 e ula�mad�ysa ve 2. kattan �a�r�ld�ysa case(16) ya git.
  arayardimci=LOW;
  hafiza=8;                                                    ///hafiza de�i�keninin i�ine 8 at , arayardimci byte n�=0 yap 
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
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz .
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
  lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r .
  lcd.write(byte(7));
  }                                  ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 10. s�tunun 1. sat�r�na yazd�r.
  else{
    lcd.setCursor(10,1);
    lcd.write(byte(8));
  }

 
  sayac=0;
}
break;


default:                                  ///default ile switch ifademizin burada son buldu�unu s�yl�yoruz ve seri olarak e�er hi�bir switch �al��m�yorsa bize "BEKL�YOR" ifadesini yazd�rmas�n� s�yl�yoruz.
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
       digitalWrite(ledb2,LOW);          ///e�er birinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "1" yaz. 
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
     digitalWrite(leda2,LOW);         ///e�er ikinci kattaki sens�r aktif ise b�t�n katlardaki segmentlere "2" yaz .

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
    digitalWrite(ledb2,HIGH);         ///e�er ���nc�  kattaki sens�r aktif ise b�t�n katlardaki segmentlere "3" yaz. 
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
    digitalWrite(ledc2,HIGH);           ///e�er d�rd�nc� kattaki sens�r aktif ise b�t�n katlardaki segmentlere "4" yaz .
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
  lcd.write(byte(1));       ///lcd ekrandaki en sol d�z 2 s�tunluk �izgi yaz�l�m� ve "K1" yaz�s�. 
  lcd.setCursor(0,1);
  lcd.write(byte(1));
lcd.setCursor(1,0);
 lcd.print("K1");

  lcd.setCursor(4,1);
  lcd.write(byte(3));
  lcd.setCursor(4,0);         /// lcd ekrandaki "K1" yaz�s�n�n hemen sa��ndaki 2 sutunluk dar �izgi ve "K2" yaz�s�.
  lcd.write(byte(3));
  lcd.setCursor(5,0);
  lcd.print("K2");

  lcd.setCursor(8,1);
  lcd.write(byte(4));                                      
  lcd.setCursor(8,0);        /// lcd ekrandaki "K2" yaz�s�n�n hemen  sa��ndaki  2 s�tunluk dar �izgi ve "K3" yaz�s�.
  lcd.write(byte(4));
  lcd.setCursor(9,0);
  lcd.print("K3");

  lcd.setCursor(12,1);
  lcd.write(byte(5));            /// lcd ekrandaki "K3" yaz�s�n�n hemen  sa��ndaki 2 s�tunluk dar �izgi ve "K4" yaz�s�.
  lcd.setCursor(12,0);
  lcd.write(byte(5));
  lcd.setCursor(13,0);
  lcd.print("K4");
  
  lcd.setCursor(15,1);
  lcd.write(byte(6));              ///lcd ekran�n en sa� b�l�m�nde yer alan 2 s�tunluk dar �izgi.
  lcd.setCursor(15,0);
  lcd.write(byte(6));

  if(newsendurum1>=30){
  lcd.setCursor(2,1);          ///e�er birinci kat�n sens�r� alg�l�yorsa ok imlecini 2 s�tunun 1 sat�rda yazd�r .
  lcd.write(byte(7));
  }                               ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 2 s�tunun 1 sat�r�na yazd�r.
  else{
    lcd.setCursor(2,1);
    lcd.write(byte(8));
  }


  if(newsendurum2>=50){
  lcd.setCursor(6,1);            ///e�er ikinci kat�n sens�r� alg�l�yorsa ok imlecini 6. s�tunun 1. sat�rda yazd�r .
  lcd.write(byte(7));
  }
  else{                              ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 6. s�tunun 1. sat�r�na yazd�r.
    lcd.setCursor(6,1);
    lcd.write(byte(8));
  }

 
  if(newsendurum3>=50){
  lcd.setCursor(10,1);            ///e�er ���nc� kat�n sens�r� alg�l�yorsa ok imlecini 10 s�tunun 1 sat�rda yazd�r. 
  lcd.write(byte(7));
  }                                  ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 10. s�tunun 1. sat�r�na yazd�r.
  else{
    lcd.setCursor(10,1);
    lcd.write(byte(8));
  }


  if(newsendurum4>=50){
  lcd.setCursor(14,1);
  lcd.write(byte(7));             ///e�er d�rd�nc�  kat�n sens�r� alg�l�yorsa ok imlecini 14. s�tunun 1. sat�rda yazd�r.
  }
  else{                              ///yok e�er alg�lam�yorsa bizim s�p�rge dedi�imiz byte 't� ayn� 14. s�tunun 1. sat�r�na yazd�r.
    lcd.setCursor(14,1);
    lcd.write(byte(8));
  }

}


