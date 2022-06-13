#include <X113647Stepper.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>


int kahveadim; //64*32 tam tur 2048
int sekeradim; //64*32 tam tur 2048
int sutadim; //64*32 tam tur 2048


tardate::X113647Stepper kahve(kahveadim,22,23,24,25);
tardate::X113647Stepper sut(sutadim,26,27,28,29);
tardate::X113647Stepper seker(sekeradim,30,31,32,33);


#define kontrol A0
int irdeger = 0;

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float sicaklik = 0;

#define yukaributon 7
#define enterbuton 6
#define asagibuton 5
int secim = 0;

int kahveoran = 5;
int sutoran = 5;
int sekeroran = 5;

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int kirmiziPin = 48; //Kırmızı
int yesilPin = 47; //yeşil
int maviPin = 46; //mavi 

int suseviyePin = A1;
int suseviye;

int supompaPin = 4;
int rezistansPin = 3;


void setup() {
  
  renkAyarla(0, 0, 255); //mavi
  
  Serial.begin(9600);
  sensors.begin();
  
  pinMode(kirmiziPin, OUTPUT);
  pinMode(yesilPin, OUTPUT);
  pinMode(maviPin, OUTPUT);
  
  lcd.begin(20, 4);
  
  pinMode(yukaributon , INPUT);
  pinMode(enterbuton , INPUT);
  pinMode(asagibuton , INPUT);

  pinMode(suseviyePin, INPUT);

  pinMode(supompaPin, OUTPUT);
  pinMode(rezistansPin, OUTPUT);
  
  kahve.setSpeed(5);
  seker.setSpeed(5);
  sut.setSpeed(5);

  
  renkAyarla(0, 255, 0); // yeşil
}

void loop() {
  sensors.requestTemperatures();
  sicaklik = sensors.getTempCByIndex(0);
  irdeger = analogRead(kontrol);
  suseviye = analogRead(suseviyePin);
  digitalWrite(supompaPin,HIGH);
  digitalWrite(rezistansPin,HIGH);

  if (suseviye < 600){
    renkAyarla(255, 0, 0); //kırmızı
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ISITICIYA SU EKLEYIN");
    
  }
  else{
    renkAyarla(0, 255, 0); // yeşil
    lcd.clear();
    if (sicaklik < 92) {
    digitalWrite(rezistansPin , LOW);
  }
  if (sicaklik > 93){
    digitalWrite(rezistansPin , HIGH);
  }
  
  if(digitalRead(yukaributon) == 1){
    secim++;
    lcd.clear();
  }
  
  if(digitalRead(asagibuton) == 1){
    secim--;
    lcd.clear();
  }
  if(secim > 4){
    secim = 0;
  }
  if(secim < 0){
    secim = 4;
  }
  
  if(secim == 0){
    lcd.setCursor(0, 0);
    lcd.print(">KAHVE<");
    lcd.setCursor(0, 1);
    lcd.print("SUT");
    lcd.setCursor(0, 2);
    lcd.print("SEKER");
    lcd.setCursor(0, 3);
    lcd.print("TAMAM");
  }
  if(secim == 1){
    lcd.setCursor(0, 0);
    lcd.print("KAHVE");
    lcd.setCursor(0, 1);
    lcd.print(">SUT<");
    lcd.setCursor(0, 2);
    lcd.print("SEKER");
    lcd.setCursor(0, 3);
    lcd.print("TAMAM");
  }
  if(secim == 2){
    lcd.setCursor(0, 0);
    lcd.print("KAHVE");
    lcd.setCursor(0, 1);
    lcd.print("SUT");
    lcd.setCursor(0, 2);
    lcd.print(">SEKER<");
    lcd.setCursor(0, 3);
    lcd.print("TAMAM");
  }
  if(secim == 3){
    lcd.setCursor(0, 0);
    lcd.print("KAHVE");
    lcd.setCursor(0, 1);
    lcd.print("SUT");
    lcd.setCursor(0, 2);
    lcd.print("SEKER");
    lcd.setCursor(0, 3);
    lcd.print(">TAMAM<");
  }
  if(secim == 4){
    lcd.setCursor(0, 0);
    lcd.print(">DURUM BILGI<");
  }

  if(digitalRead(enterbuton) == 1 && secim == 0){ //KAHVE ORANI EKRANI
      lcd.clear();
      while (secim == 0){
        delay(500);
        if (digitalRead(yukaributon) == 1){
          kahveoran ++;
          lcd.clear();
          }
        if (digitalRead(asagibuton) == 1){
          kahveoran-- ;
          lcd.clear();
          }
        if (kahveoran > 20){
          kahveoran = 0;
          }
        if (kahveoran < 0){
          kahveoran = 20;
          }
        if (kahveoran == 0){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("                    ");
          }
        if (kahveoran == 1){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*                   ");
          }
        if (kahveoran == 2){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**                  ");
          }
        if (kahveoran == 3){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***                 ");
          }
        if (kahveoran == 4){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****                ");
          }
        if (kahveoran == 5){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****               ");
          }
        if (kahveoran == 6){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******              ");
          }
        if (kahveoran == 7){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*******             ");
          }
        if (kahveoran == 8){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********            ");
          }
        if (kahveoran == 9){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*********           ");
          }
        if (kahveoran == 10){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**********          ");
          }
        if (kahveoran == 11){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***********         ");
          }
        if (kahveoran == 12){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("************        ");
          }
        if (kahveoran == 13){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*************       ");
          }
        if (kahveoran == 14){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**************      ");
          }
        if (kahveoran == 15){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***************     ");
          }
        if (kahveoran == 16){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****************    ");
          }
        if (kahveoran == 17){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****************   ");
          }
        if (kahveoran == 18){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************  ");
          }
        if (kahveoran == 19){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************* ");
          }
        if (kahveoran == 20){
          lcd.setCursor(0, 0);
          lcd.print("KAHVE ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********************");
          }
        if(digitalRead(enterbuton)== 1 ){
          lcd.clear();
          break;
          }
        }
    }

  if(digitalRead(enterbuton) == 1 && secim == 1){ //SÜT ORANI EKRANI
    lcd.clear();
      while (secim == 1){
        delay(500);
        if (digitalRead(yukaributon) == 1){
          sutoran ++;
          lcd.clear();
          }
        if (digitalRead(asagibuton) == 1){
          sutoran-- ;
          lcd.clear();
          }
        if (sutoran > 20){
          sutoran = 0;
          }
        if (sutoran < 0){
          sutoran = 20;
          }
        if (sutoran == 0){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("                    ");
          }
        if (sutoran == 1){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*                   ");
          }
        if (sutoran == 2){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**                  ");
          }
        if (sutoran == 3){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***                 ");
          }
        if (sutoran == 4){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****                ");
          }
        if (sutoran == 5){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****               ");
          }
        if (sutoran == 6){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******              ");
          }
        if (sutoran == 7){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*******             ");
          }
        if (sutoran == 8){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********            ");
          }
        if (sutoran == 9){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*********           ");
          }
        if (sutoran == 10){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**********          ");
          }
        if (sutoran == 11){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***********         ");
          }
        if (sutoran == 12){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("************        ");
          }
        if (sutoran == 13){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*************       ");
          }
        if (sutoran == 14){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**************      ");
          }
        if (sutoran == 15){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***************     ");
          }
        if (sutoran == 16){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****************    ");
          }
        if (sutoran == 17){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****************   ");
          }
        if (sutoran == 18){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************  ");
          }
        if (sutoran == 19){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************* ");
          }
        if (sutoran == 20){
          lcd.setCursor(0, 0);
          lcd.print("SUT ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********************");
          }
        if(digitalRead(enterbuton)== 1 ){
          lcd.clear();
          break;
          }
        }

  }
  if(digitalRead(enterbuton) == 1 && secim == 2){ //ŞEKER ORANI EKRANI
    lcd.clear();
      while (secim == 2){
        delay(500);
        if (digitalRead(yukaributon) == 1){
          sekeroran ++;
          lcd.clear();
          }
        if (digitalRead(asagibuton) == 1){
          sekeroran-- ;
          lcd.clear();
          }
        if (sekeroran > 20){
          sekeroran = 0;
          }
        if (sekeroran < 0){
          sekeroran = 20;
          }
        if (sekeroran == 0){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("                    ");
          }
        if (sekeroran == 1){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*                   ");
          }
        if (sekeroran == 2){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**                  ");
          }
        if (sekeroran == 3){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***                 ");
          }
        if (sekeroran == 4){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****                ");
          }
        if (sekeroran == 5){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****               ");
          }
        if (sekeroran == 6){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******              ");
          }
        if (sekeroran == 7){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*******             ");
          }
        if (sekeroran == 8){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********            ");
          }
        if (sekeroran == 9){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*********           ");
          }
        if (sekeroran == 10){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**********          ");
          }
        if (sekeroran == 11){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***********         ");
          }
        if (sekeroran == 12){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("************        ");
          }
        if (sekeroran == 13){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*************       ");
          }
        if (sekeroran == 14){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("**************      ");
          }
        if (sekeroran == 15){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("***************     ");
          }
        if (sekeroran == 16){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("****************    ");
          }
        if (sekeroran == 17){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("*****************   ");
          }
        if (sekeroran == 18){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************  ");
          }
        if (sekeroran == 19){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("******************* ");
          }
        if (sekeroran == 20){
          lcd.setCursor(0, 0);
          lcd.print("SEKER ORANI");
          lcd.setCursor(0, 1);
          lcd.print("********************");
          }
        if(digitalRead(enterbuton)== 1 ){
          lcd.clear();
          break;
          }
        }
  }
  if(digitalRead(enterbuton) == 1 && secim == 3){ //TAMAM EKRANI
    oran();
    if(irdeger < 1015){
      renkAyarla(255, 0, 0); //kırmızı
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lutfen Bekleyin");
      lcd.setCursor(0, 1);
      lcd.print("Kahveniz");
      lcd.setCursor(0, 2);
      lcd.print("Hazirlanıyor !");
      delay(1000);
      digitalWrite(supompaPin,LOW);
      delay(10000);
      digitalWrite(supompaPin,HIGH);
      seker.step(sekeradim);
      sut.step(sutadim);
      kahve.step(kahveadim);
      renkAyarla(0, 255, 0);
      lcd.clear();
      }
    else{
    renkAyarla(255, 0, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lutfen Bardak Koyun");
    delay(3000);
    renkAyarla(0, 255, 0);
    lcd.clear();
    }
  }
  if(digitalRead(enterbuton) == 1 && secim == 4){ //DURUM BİLGİ EKRANI
    lcd.clear();
    while(secim == 4){
      sensors.requestTemperatures();
      sicaklik = sensors.getTempCByIndex(0);
      irdeger = analogRead(kontrol);
      suseviye = analogRead(suseviyePin);
      lcd.setCursor(0, 0);
      lcd.print("Su Sicakligi: ");
      lcd.print(sicaklik);
      lcd.setCursor(0, 1);
      lcd.print("Bardak Sensor:");
      lcd.print(irdeger);
      lcd.setCursor(0, 2);
      lcd.print("Su seviye: ");
      lcd.print(suseviye);
      if(digitalRead(enterbuton)==1){
        lcd.clear();
        break;
        
        }
      
      }
    
  }
  }
    }
  
  


void renkAyarla(int kirmizi, int yesil, int mavi){ 
  analogWrite(kirmiziPin, kirmizi); 
  analogWrite(yesilPin, yesil); 
  analogWrite(maviPin, mavi);
  }
void oran(){
  if(sekeroran==0){
    sekeradim = 0;
    }
  if(sekeroran==1){
    sekeradim = 64*32;
    }
  if(sekeroran==2){
    sekeradim = 64*64;
    }
  if(sekeroran==3){
    sekeradim = 128*32;
    }
  if(sekeroran==4){
    sekeradim = 128*64;
    }
  if(sekeroran==5){
    sekeradim = 128*80;
    }
  if(sekeroran==6){
    sekeradim = 128*96;
    }
  if(sekeroran==7){
    sekeradim = 128*112;
    }
  if(sekeroran==8){
    sekeradim = 128*128;
    }
  if(sekeroran==9){
    sekeradim = 144*128;
    }
  if(sekeroran==10){
    sekeradim = 160*128;
    }
    
  if(kahveoran==0){
    kahveadim = 0;
    }
  if(kahveoran==1){
    kahveadim = 64*32;
    }
  if(kahveoran==2){
    kahveadim = 64*64;
    }
  if(kahveoran==3){
    kahveadim = 128*32;
    }
  if(kahveoran==4){
    kahveadim = 128*64;
    }
  if(kahveoran==5){
    kahveadim = 128*80;
    }
  if(kahveoran==6){
    kahveadim = 128*96;
    }
  if(kahveoran==7){
    kahveadim = 128*112;
    }
  if(kahveoran==8){
    kahveadim = 128*128;
    }
  if(kahveoran==9){
    kahveadim = 144*128;
    }
  if(kahveoran==10){
    kahveadim = 160*128;
    }

   if(sutoran==0){
    sutadim = 0;
    }
  if(sutoran==1){
    sutadim = 64*32;
    }
  if(sutoran==2){
    sutadim = 64*64;
    }
  if(sutoran==3){
    sutadim = 128*32;
    }
  if(sutoran==4){
    sutadim = 128*64;
    }
  if(sutoran==5){
    sutadim = 128*80;
    }
  if(sutoran==6){
    sutadim = 128*96;
    }
  if(sutoran==7){
    sutadim = 128*112;
    }
  if(sutoran==8){
    sutadim = 128*128;
    }
  if(sutoran==9){
    sutadim = 144*128;
    }
  if(sutoran==10){
    sutadim = 160*128;
    }


  
  }
