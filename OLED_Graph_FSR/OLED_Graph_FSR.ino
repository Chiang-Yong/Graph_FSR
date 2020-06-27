/* Created on 27th June 2020
 *  Name: Heng Chiang Yong
 *  Using the OLED libraries from Adafruit
 *  
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
//#include <gfxfont.h>
void writeText(char *text, int x, int y);
void textInverse(char *text, int x, int y);
//int readFSR();

//Used for software SPI
#define OLED_CLK 13
#define OLED_MOSI 11

#define OLED_CS 10
#define OLED_DC 8

#define OLED_RESET 9

Adafruit_SSD1305 display(138,64,&SPI,OLED_DC,OLED_RESET,OLED_CS);

#define xpos 0
#define ypos 1
#define deltay 2

#define FSR A1


void setup() 
{
  Serial.begin(9600);
  while(!Serial) delay(100);
  Serial.println("OLED Display");

  if(! display.begin(0x3C))
  { 
    Serial.println("unable to initialize OLED");
    while(1) yield();
  }
  display.clearDisplay();
  
}

void loop() 
{
int value;
//display.display();
//delay(1000);
//display.clearDisplay();
writeText("Live Graph",10,0);
for(int i = 15; i <64; i++)
  display.drawFastVLine(15,i,2,WHITE);
display.display();
for(int j = 5; j <127; j++)
 display.drawFastHLine(j,55,2,WHITE);
display.display();
display.setRotation(3);
writeText("ADC",25,0);
display.setRotation(0);
writeText("Time",50,56);
for(int h = 0; h < 115;h++)
  {
  value = readFSR();
  value = value/20;
  display.drawPixel(h+15,54-value, WHITE);
  delay(200);
  display.display();
  }
  display.clearDisplay();
}

void writeText(char *text, int x, int y)
{
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(x,y);
display.println(text);
display.display();
delay(1000);
}

void textInverse(char *text, int x, int y)
{
display.setTextSize(1);
display.setTextColor(BLACK,WHITE);
display.setCursor(x,y);
display.println(text);
display.display();
delay(1000);
}

int readFSR()
{
  int ADCvalue = analogRead(FSR);
  Serial.println(ADC);
  return ADCvalue;
}
