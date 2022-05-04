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

unsigned char text1[] = {"Newhaven Display"};
unsigned char text2[] = {"  NHD-C0216CiZ  "};
unsigned char text3[] = {" I2C Interface  "};
unsigned char text4[] = {"Please enjoy! :)"};

const char slave2w = 0x3E;
const char comsend = 0x00;
const char datasend = 0x40;
const char line2 = 0xC0;

void show(unsigned char *text)
{
  Wire.beginTransmission(slave2w);
  Wire.write(datasend);
  for (int n = 0; n < 16; n++)
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

void CiZ_init()
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x38); // Function set: 8-bit data
  delay(10);
  Wire.write(0x39); // Function set: 8-bit data + instruction table 1
  delay(10);
  Wire.write(0x14); // Set OSC frequency
  Wire.write(0x78); // Set contrast
  Wire.write(0x5D); // Set ICON display ON | Booster ON | contrast
  Wire.write(0x6D); // Set follower circuit ON | Set follower ratio
  Wire.write(0x0C); // Set display ON
  Wire.write(0x01); // Clear display
  Wire.write(0x06); // Entry mode | Increment
  Wire.endTransmission();

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

  Wire.begin();
}

void loop()
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
