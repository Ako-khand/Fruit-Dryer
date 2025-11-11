#include "DHT.h"//DHT sensor Library
#include <LiquidCrystal.h>//LCD Library 
#define DHTPIN 13 //Define sensor pin(pin 12)
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define POTENTIOMETER_PIN A0
const byte ButtonPin = 7;// Arduino pin for up button
String MenuItems[] = {  // creating the string of the options in menu
  "temp:",
  "humid:"
};
float h=0,t=0;
long previousMillis = 0;
long interval = 2000; //Read sensor each 2 seconds
int reading = 0;
const int relay1pin = 9;
const int relay2pin= 8;
int setTemp = 0;
int setHumid = 0; //variable to read the value of potentiometer
// initialize the library with the numbers of the interface pins
DHT dht(DHTPIN, DHTTYPE);//Create sensor object
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void menuFunctions(int menu) /* creating the functions of the options provided in the menu */
{
  if(menu == 1) // for first  option
  {
      setTemp = analogRead(POTENTIOMETER_PIN); 
      lcd.setCursor(0, 1);// setting the place for the data on LCD
      lcd.print("temp: ");// printing the temp option
      lcd.setCursor(1, 1);// setting the place for the data on LCD
      lcd.print(setTemp);// move the cursor on the ON optio
    }
   
  if(menu == 2)// if the second option in the menu is selected
  {
    setHumid = analogRead(POTENTIOMETER_PIN);  
    lcd.setCursor(0, 1);// setting the place for the data on LCD
    lcd.print("humid:     ");// displaying the data
    lcd.setCursor(1, 1);// setting the place for the data on LCD
    lcd.print(setHumid);// displaying the value of temperature
    }
}
template(/* variable for name of option and for size of the menu*/
size_t MenuItemsSize(T (&) [NumberOfSize]){ return NumberOfSize; } /* menu option name and the number of option*/
int numberOfMenuItems = MenuItemsSize(MenuItems) - 1;
int currentMenuItem = 0;// variable for storing current option
int previousMenuItem = 1;// variable for storing the previous option
byte button_flag = 0;
unsigned long previousMillis = millis();
// setup function
)
void setup() {
lcd.begin(16, 2);
// Print a message to the LCD.
pinMode(relay1pin, OUTPUT);
pinMode(relay2pin, OUTPUT);
pinMode(ButtonPin, INPUT_PULLUP);//assigning the up button INPUT_PULLUP mode
dht.begin();//Start DHT22 sensor
lcd.print("Tempera:");// print in lcd this word 
lcd.setCursor(0,1);//Change cursor position
lcd.print("Humedad:");// print in lcd this word 
}

void loop() {
 unsigned long currentMillis = millis();//time elapsed
  if(currentMillis - previousMillis > interval) //Comparison between the elapsed time and the time in which the action is to be executed
  {
    previousMillis = currentMillis; //"Last time is now"

     h = dht.readHumidity();//humidity value
     t = dht.readTemperature();//temperature value centigrades if you want farenheit change to
     //t = dht.readTemperature(true);
     //Below is for print data sensors in lcd 
     lcd.setCursor(10,0);
     lcd.print(t);
     lcd.setCursor(10,1);
     lcd.print(h);
    
    if(t<setTemp )//if temperature is under set temp degrees
    {
      digitalWrite(relay1pin,HIGH);//Active elements
     
    }
    else if(t>setTemp )//if temperature is above set temp
    {
      digitalWrite(relay2pin,LOW); //turn off elements
    }
    else if(h>setHumid )
    {
      digitalWrite(relay2pin,HIGH);
      }
      else if(h<setHumid )
      {
        digitalWrite(relay2pin,LOW);
        }
  }

   if(digitalRead(ButtonPin) == LOW && button_flag == 0) /*if button is pressed*/
  {
    ++currentMenuItem;
    if(currentMenuItem > numberOfMenuItems )
    {
      currentMenuItem = numberOfMenuItems ;
    }
    button_flag = 1;
    previousMillis = millis();
  }
    
  }
