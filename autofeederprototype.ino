#include <LiquidCrystal.h>// include the library code
#include <IRremote.h> 
#include <Servo.h> 
/**********************************************************/
/***Declare Global variables***/
char array1[] = " Good Morning               "; //the string to print on the LCD
char array2[] = "Yumi the Havanese             "; //the string to print on the LCD
String input = "";     // Temp string array 
int tim = 500;  //the value of delay time
int servoPin = 3;

bool set_breakfast = false;
bool set_lunch = false;
bool set_dinner = false; 

String breakfast_time = ""; 
String lunch_time = ""; 
String dinner_time = ""; 

String breakfast_final = "";  
String lunch_final = "";
String dinner_final = ""; 

// initial Time Display 
int h = 12;
int m = 59;
int s = 45;
int flag = 1; //PM 

// Time Set Buttons:
int button1;
int button2;

// Pin definitions for Time Set Buttons:
int hs=0; //pin 0 for Hour Setting
int ms=1; //pin 1 for Minute Setting

static uint32_t last_time, now = 0; // RTC

String result; 

Servo servo; 

int servoAngle = 0; 
int receiver_pin = 8; 


/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
/*********************************************************/
void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  IrReceiver.begin(receiver_pin);
  pinMode(hs, INPUT_PULLUP); // avoid external Pullup resistors for Button 1; 
  pinMode(ms, INPUT_PULLUP); // and Button 2; 

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}
/*********************************************************/
void loop()
{ 
  if (set_breakfast == false || set_lunch == false || set_dinner == false) {
    if (set_breakfast == false) {
      lcd.setCursor(0,0);
      lcd.print("Breakfast Time:");
      delay(1000);
      set_breakfast = true;
      lcd.clear();
      uint32_t val;
      while (val != 4061003520) {
         if (IrReceiver.decode()) {
          val = IrReceiver.decodedIRData.decodedRawData; 
          if (val == 3141861120) {
            lcd.clear();
            set_breakfast = false;   
            val = 0;
            break;
          }
          else {
            delay(1000);
            breakfast_time = decodeSignal(val);
            lcd.print(breakfast_time);
            breakfast_final.concat(breakfast_time);
            Serial.print(breakfast_final);   
          }
         
         }
      }
    }
    else if (set_lunch == false) {
      lcd.setCursor(0,0);
      lcd.print("Lunch Time:");
      delay(1000);
      set_lunch = true;
      lcd.clear();
       uint32_t val;
      while (val != 4061003520) {
         if (IrReceiver.decode()) {
          val = IrReceiver.decodedIRData.decodedRawData; 
          if (val == 3141861120) {
            lcd.clear();
            set_lunch = false;   
            val = 0;
            break;
          }
          else {
            delay(1000);
            lunch_time = decodeSignal(val);
            lcd.print(lunch_time);
            lunch_final.concat(lunch_time);
            Serial.print(lunch_time);   
          }
         
         }
      }
    }
    
    else {
      lcd.setCursor(0,0);
      lcd.print("Dinner Time:");
      delay(1000);
      set_dinner = true;
      lcd.clear(); 
      uint32_t val;
      while (val != 4061003520) {
         if (IrReceiver.decode()) {
          val = IrReceiver.decodedIRData.decodedRawData; 
          if (val == 3141861120) {
            lcd.clear();
            set_dinner = false;   
            val = 0;
            break;
         
          }
          else {
            delay(1000);
            dinner_time = decodeSignal(val);
            lcd.print(dinner_time);
            dinner_final.concat(dinner_time);
            Serial.print(dinner_time);   
          }
         
         }
      }
    }
  }
  else  {
    lcd.setCursor(0,0);
    lcd.print("Starting now!");
  }
}

/***Decoding IRremote helper function***/
String decodeSignal(uint32_t ir_data) {
  switch(ir_data)
  {
    case 3910598400:
      result = "0";
      break;
    case 4077715200:
      result = "1";
      break; 
    case 3877175040:
      result = "2";
      break;
    case 2707357440:
      result = "3";
      break;
    case 4144561920:
      result = "4";
      break;
    case 3810328320:
      result = "5";
      break;
    case 2774204160:
      result = "6";
      break;
    case 3175284480:
      result = "7";
      break;
    case 2907897600:
      result = "8";
      break;
    case 3041591040:
      result = "9";
      break;
    case 4061003520:
      result = "STOP";
      break;
    case 3860463360:
      result = ":";
      break;
    case 4161273600:
      result = "am";
      break;
    case 4127850240:
      result = "pm";
      break;
  }

  IrReceiver.resume();
 
  
  return result;
 
}



// Code for LC1602 Display that will display from left to right
//  lcd.setCursor(15, 0); // set the cursor to column 15, line 0
//  for ( int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
//  {
//    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
//    lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
//    delay(tim);  //wait for 250 ms
//  }
//  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
//  lcd.setCursor(15, 1); // set the cursor to column 15, line 1
//  for (int positionCounter2 = 0; positionCounter2 < 26; positionCounter2++)
//  {
//    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
//    lcd.print(array2[positionCounter2]);  // Print a message to the LCD.
//    delay(tim);  //wait for 250 ms
//  }
//  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
/************************************************************/
