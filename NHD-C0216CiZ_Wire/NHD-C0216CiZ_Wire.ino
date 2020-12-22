/*****************************************************************************
 * 
/ Program for writing to NHD-C0216CiZ display series with the ST7032i Controller.
/ This code is written for the Arduino Uno R3 using I2C Interface
/
/ Newhaven Display invests time and resources providing this open source code,
/ Please support Newhaven Display by purchasing products from Newhaven Display!

* Copyright (c) 2019, Newhaven Display International
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample code is responsible for ensuring its safe and correct operation
* and for any consequences resulting from its use.
* See the GNU General Public License for more details. 
* 
*****************************************************************************/

#include <Wire.h>

int RES = 22;

/********Arduino Mega********/
int ASDA = A4;
int ASCL = A5;
/********Arduino Mega********/

int test = 55;

unsigned char text1[]={"Newhaven Display"};
unsigned char text2[]={"  NHD-C0216CiZ  "};
unsigned char text3[]={" I2C Interface  "};
unsigned char text4[]={"Please enjoy! :)"};

const char slave2w = 0x3E; 
const char comsend = 0x00;
const char datasend = 0x40;
const char line2 = 0xC0;

void show(unsigned char *text)
{
  int n, d;
  d=0x00;
  Wire.beginTransmission(slave2w);
  Wire.write(datasend);
  for(n=0;n<16;n++)
  {
    Wire.write(*text);
    ++text;
  }
  Wire.endTransmission();
}

void nextline(void)
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(line2);
  Wire.endTransmission();
}

void CGRAM(void)
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x38);
  Wire.write(0x40);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(slave2w);
  Wire.write(datasend);
  Wire.write(0x00);
  Wire.write(0x1E);
  Wire.write(0x18);
  Wire.write(0x14);
  Wire.write(0x12);
  Wire.write(0x01);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
}

void CiZ_init()
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x38);
  delay(10);
  Wire.write(0x39);
  delay(10);
  Wire.write(0x14);
  Wire.write(0x70); //was 70
  Wire.write(0x5E);
  Wire.write(0x6D);
  Wire.write(0x0C);
  Wire.write(0x01);
  Wire.write(0x06);
  Wire.endTransmission();
  
  CGRAM();
  
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x39);
  Wire.write(0x01);
  test = Wire.endTransmission();
  Wire.endTransmission();
  if(test!=0)
  {
    while(1)
    {
      delay(100);
    }
  }
  delay(10);
}

void setup() 
{
  pinMode(RES, OUTPUT);
  pinMode(ASCL, OUTPUT);
  pinMode(ASDA, OUTPUT);
  digitalWrite(RES, HIGH);
  delay(10);
  digitalWrite(ASCL, LOW);
  digitalWrite(ASDA, LOW);
  delay(10);
  
  delay(10);
  //CiZ_init();
  //delay(5);
}

void loop() 
{
  
  Wire.begin();
  while(1)
  {
  CiZ_init();
  show(text1);
  nextline();
  show(text2);
  delay(1000);
  
  CiZ_init();
  show(text3);
  nextline();
  show(text4);
  delay(1000); 
  }
}
