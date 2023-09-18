/* 
Dino Game (lcd 20x4 & joystick)
Coded by: Ahmed Orabi 

#you must stop the arrow first ,then kill it.
#you have two seconds when you stop the arrow before arrow kill your Dinosaur D:
Enjoy !!
^ _ ^
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
//define joystick
#define vx A1
#define vy A0
//directions of Dinosaur
int vert = 1;
int horz = 0;

byte row;
byte i;
uint16_t score = 0;
unsigned long time;
unsigned long currentTime;
bool millisCounter = false;
//create character for killing arrow D: 
byte arrow[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00001
};
//create character for Dinosaur :D 
byte dino[8] = {
  B00110,
  B01101,
  B01111,
  B01110,
  B11110,
  B11110,
  B11100,
  B00100
};
void dinoMove() //method for moving the Dinosaur on lcd 20x4
{
  if(analogRead(vy) == 1023 && analogRead(vx) == 512)
  {
    lcd.setCursor(horz,vert);
    lcd.write(byte(0));
    if(vert <= 0)vert=4;
    vert = vert - 1;
    lcd.setCursor(horz,vert);
    lcd.write(byte(2));
    delay(150);
  } 
  if(analogRead(vy) == 0 && analogRead(vx) == 512)
  {
    lcd.setCursor(horz,vert);
    lcd.write(byte(0));
    vert++;
    if(vert >= 4)vert=0;
    lcd.setCursor(horz,vert);
    lcd.write(byte(2));
    delay(150);
  }
  if(analogRead(vx) == 1023 && analogRead(vy) == 512)
  {    
    lcd.setCursor(horz,vert);
    lcd.write(byte(0));
    if(horz <= 0)horz=20;
    horz = horz - 1;
    lcd.setCursor(horz,vert);
    lcd.write(byte(2));
    delay(150);
  }
  if(analogRead(vx) == 0 && analogRead(vy) == 512)
  {
    lcd.setCursor(horz,vert);
    lcd.write(byte(0));
    horz++;
    if(horz >= 20)horz=0;
    lcd.setCursor(horz,vert);
    lcd.write(byte(2));
    delay(150);
  } 
}
void setup() {
Serial.begin(9600);
lcd.init();
lcd.backlight();
//Create all new characters
lcd.createChar(1,arrow);
lcd.createChar(2,dino);
//pins of joystick 
pinMode(A0, INPUT);
pinMode(A1, INPUT);
//start the game
lcd.setCursor(horz, vert);
lcd.write(byte(2));
}
void loop() {
  row = random(4);//select a random value for row between{0,1,2,3}.
  for(i = 20;i>=0;i=i-1)
  {
   lcd.setCursor(i,row);
   lcd.write(1);
   dinoMove();
   if((horz == i) && (vert == row))
    {
     Serial.print("Score = ");
     score = score +1;
     Serial.println(score);
     lcd.setCursor(horz,vert);
     lcd.write(byte(2));
     i = 19;
     break;
    }
    if((horz == (i-1)) && (vert == row))
    {
    lcd.setCursor(i,row);
    lcd.write(byte(1));
    lcd.setCursor(horz,vert);
    lcd.write(byte(2));
     for(int t = 0;t<=10000;t++)
     {
      if(millisCounter == false)
     {
      time = millis();
      millisCounter = true;
     }
      dinoMove();
      currentTime = millis() - time;
      if(currentTime >= 2000)
      {
       Serial.println("Game Over");
       Serial.print("Your Score = ");
       Serial.println(score);
       Serial.println("===============");
       delay(500);
       lcd.clear();
       score = 0;
       vert = 1;
       horz = 0;
       i = 20;
       millisCounter = false;
       lcd.setCursor(horz,vert);
       lcd.write(byte(2));
       row = random(4);
       break;
      }
      if((i == horz) && (row == vert))
      {
       Serial.print("Score = ");
       score = score +1;
       Serial.println(score);
       lcd.setCursor(i,row);
       lcd.write(byte(2));
       i = 19;
       millisCounter = false;
       row = random(4);
       break;
      }
      delay(1);
     }
    }
    delay(90);
    lcd.setCursor(i,row);
    lcd.print(" ");
    dinoMove();
    if(i==0)break;
  }
 }