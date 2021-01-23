#include <LiquidCrystal.h>
unsigned long TimeIn1;
unsigned long TimeIn2;
unsigned long TimeIn3;

unsigned long dureeParking1;
unsigned long dureeParking2;
unsigned long dureeParking3;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int trig_out = 24;
int ech_out= 25;
int  tr = 10;
int trig_in = 22;
int ech_in=23;

int place1= 6;
int place2= 7;
int place3= 8;

int total=3;

int bouton1= 9;
int bouton2= 10;
int bouton3= 13;

int s1=0, s2=0, s3=0;

void setup() {
   //définir les pins comme i/o 
   pinMode(trig_in, OUTPUT); 
   pinMode(ech_in, INPUT);
   pinMode(place1,INPUT);
   pinMode(place2,INPUT);
   pinMode(place3,INPUT);
   pinMode(bouton1,INPUT);
   pinMode(bouton2,INPUT);
   pinMode(bouton3,INPUT);


Serial.begin(9600); 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("welcome parking!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // ultrasons entre
  digitalWrite(trig_in, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_in, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_in, LOW);

 double duration1 = pulseIn(ech_in, HIGH);

  double d_in= duration1*0.034/2;
  // ultrasons sortie
  digitalWrite(trig_out, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_out, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_out, LOW);

 double duration2 = pulseIn(ech_out, HIGH);

  double d_out= duration2*0.034/2;

  // test des sénarios possibles:
  if(d_in < tr) // une voiture détecté à l'entré
  { if (total>0) // parking libre
  {
    delay(5000); // 5 seconds
 
    if (digitalRead(bouton1)==LOW) // si le client choisi la place 1 par pousser le bouton 1
      { delay(10000); // attendre 10 seconds
        if(digitalRead(place1)==HIGH)//le capteur détecte un mouvement à la place1
          {
            total--;
            TimeIn1 = millis();
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          } 
        else if(digitalRead(place2)==HIGH)
         { //le capteur détecte un mouvement à la place2
           lcd.print("la place est fausse !!!");
         } 
        else if(digitalRead(place3)==HIGH)
         { //le capteur détecte un mouvement 
           lcd.print("la place est fausse !!!");
         } 
        else
         {//sinon le capteur ne détecte aucun mouvement
           lcd.print("place 1 est réservée ");
         }
     }
     else if (digitalRead(bouton2)==LOW) // si le client choisi la place 2 par pousser le bouton 2
      { delay(10000); // attendre 10 seconds
        if(digitalRead(place2)==HIGH)//le capteur détecte un mouvement à la place2
          {
            total--;
            TimeIn2 = millis();
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          } 
        else if(digitalRead(place1)==HIGH)
         { //le capteur détecte un mouvement à la place1
           lcd.print("la place est fausse !!!");
         } 
        else if(digitalRead(place3)==HIGH)
         { //le capteur détecte un mouvement 
           lcd.print("la place est fausse !!!");
         } 
        else
         {//sinon le capteur ne détecte aucun mouvement
           lcd.print("place 2 est réservée ");
         }
     }
    else if (digitalRead(bouton3)==LOW) // si le client choisi la place 1 par pousser le bouton 3
      { delay(10000); // attendre 10 seconds
        if(digitalRead(place3)==HIGH)//le capteur détecte un mouvement à la place3
          {
            total--;
            TimeIn3 = millis();
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          } 
        else if(digitalRead(place2)==HIGH)
         { //le capteur détecte un mouvement à la place2
           lcd.print("la place est fausse !!!");
         } 
        else if(digitalRead(place1)==HIGH)
         { //le capteur détecte un mouvement 
           lcd.print("la place est fausse !!!");
         } 
        else
         {//sinon le capteur ne détecte aucun mouvement
           lcd.print("place 3 est réservée ");
         }
     }
     else
     {
      lcd.print("reservez la place : ");
      lcd.print(total);
     }
  }
  else {
    lcd.print("sorry parking is full !");
    }
  }
  if(d_out < tr)// voiture détecté à la sortie
  {
    delay(5000); // 5 seconds
    if(digitalRead(place1)==LOW)// place1 est libre
          {
            total++;
            dureeParking1+=millis()-TimeIn1;
            s1+=dureeParking1*100;
            lcd.print("votre somme est: ");
            lcd.print("/");
            lcd.print(s1);
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          } 
        else if(digitalRead(place2)==LOW)
                   {
            total++;
            dureeParking2+=millis()-TimeIn2;
            s2+=dureeParking2*100;
            lcd.print("votre somme est: ");
            lcd.print("/");
            lcd.print(s2);
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          }
        else if(digitalRead(place3)==LOW)
         {
            total++;
            dureeParking3+=millis()-TimeIn3;
            s3+=dureeParking3*100;
            lcd.print("votre somme est: ");
            lcd.print("/");
            lcd.print(s3);
            lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
          }
        else
         {  lcd.print("vacant:");
            lcd.print("/");
            lcd.print(total);
            delay(2000);
         }
    }
}
