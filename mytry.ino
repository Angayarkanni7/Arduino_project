#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


int count = 0 ;
int count1 = 0 ;
int ouuu =0;
int p1=0,p2=0,p3=0,p4=0; 
double total = 0;


void setup ()
{
//  Pin direction
   
  pinMode(3, INPUT_PULLUP);   //Push Switch
  pinMode(4, OUTPUT);         //BUZZER
  pinMode(5, OUTPUT);         //RED LED
  pinMode(6, OUTPUT);         //GREEN LED
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(13,LOW);
// Initialization
  Serial.begin(9600);

  
//  lcd.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" AUTOMATIC BILL");
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print("  SHOPPING CART       ");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART SHOPPING");
  delay (2000);
  lcd.setCursor(0, 1); 
  lcd.print("USING RFID TAG");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  TAP TO READ  ");
  lcd.setCursor(0, 1);
  lcd.print("   THE ITEMS   "); 

}
 void loop()
{

 char input[12] ="0";

if (Serial.available() > 0)
  {
    count =0;
    while ( count < 12)
    {
      input [count]= Serial.read();
      delay(5);
      count ++;
      ouuu =  strncmp(input, "0B0024297B7D", 12);
      
    }
    Serial.println(input);
    Serial.println(ouuu);    
  }

    
      int a = digitalRead(3);
      
     if ((strncmp(input, "0B0024297B7D", 12) == 0))
      {
       
        lcd.setCursor(0, 0);
        lcd.print("Butter Added       ");
        lcd.setCursor(0, 1);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(100);
        total = total + 40.00;
        lcd.print("Price(Rs):" + String(total));
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        p1=p1+1;
      }

if ((strncmp(input, "0B00284DF49A", 12) == 0))    // remove card swipe
   {  
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(100);
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        
     char input1[12] ="0";
     while(!Serial.available()){}
     if (Serial.available() > 0)
      {
       count1 =0;
       while ( count1 < 12 )
        {
        input1 [count1]= Serial.read();
        delay(5);
        count1 ++;
        }
      }
       if ((strncmp(input1, "0B0024297B7D", 12) == 0) && p1>0 )   // card identification
      {
        lcd.setCursor(0, 0);
        lcd.print("Butter Removed       ");
        lcd.setCursor(0, 1);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(100);
        total = total - 40.00;
        lcd.print("Price(Rs):" + String(total));
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        p1=p1-1;
      }
      else
      {
        lcd.setCursor(0, 0);
        lcd.print("No more Butter ");
        lcd.setCursor(0, 1);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(1000);
        lcd.print("Price(Rs):" + String(total));
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
      }
   }




///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
      

   if ((strncmp(input, "0B002416EBD2", 12) == 0) )    //MASTER CARD
      {

     lcd.clear();  
     lcd.setCursor(0, 0);
     lcd.print("Total Price paid");
     lcd.setCursor(0, 1);  
     digitalWrite(4,LOW);
     digitalWrite(5,LOW);
     digitalWrite(6,LOW);
     delay(100);
     digitalWrite(4,HIGH);
     digitalWrite(5,HIGH);
     digitalWrite(6,HIGH);
     lcd.print(total);
     delay(2000);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  THANKS FOR  ");
     lcd.setCursor(0, 1);
     lcd.print("   VISITING ");
     
      }    
}
