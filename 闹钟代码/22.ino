
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_3x7)
#define setFont_M u8g.setFont(u8g_font_3x7)
#define setFont_S u8g.setFont(u8g_font_3x7)
#define setFont_SS u8g.setFont(u8g_font_3x7)

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN  2
#define DHTTYPE DHT11

//iic驱动方式
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

int speakerPin = 8; 

int length = 15; // the number of notes 
char notes[] = "ccggaagffeeddc "; // a space represents a rest 
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }; 
int tempo = 300; 

void playTone(int tone, int duration) { 
  for (long i = 0; i < duration * 1000L; i += tone * 2) { 
    digitalWrite(speakerPin, HIGH); 
    delayMicroseconds(tone); 
    digitalWrite(speakerPin, LOW); 
    delayMicroseconds(tone); 
  } 
} 



const int buttonPin = 4;    // 连接矩阵按键的引脚
const int ledPin = 13;      // LED引脚

// 变量的声明与定义:
int ledState = HIGH;         // 记录LED的状态
int buttonState;             // 记录按键的状态
int lastButtonState = LOW;   // 上一次按键的状态

// 以下代码以long类型声明，因为时间值以毫秒为单位(用整型会很快溢出)
long lastDebounceTime = 0;  // 按键最后一次被触发
long debounceDelay = 50;   
void playNote(char note, int duration) { 
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; 
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; 

  // play the tone corresponding to the note name 
  for (int i = 0; i < 8; i++) { 
    if (names[i] == note) { 
      playTone(tones[i], duration); 
    } 
  } 
} 


  

void setup( ) {
Serial.begin(115200); //串口初始化
analogReference(INTERNAL); //调用板载1.1V基准源
pinMode(11, OUTPUT);
digitalWrite(11, HIGH);
pinMode(10, OUTPUT);
digitalWrite(10, HIGH);
pinMode(9, OUTPUT);
digitalWrite(9, HIGH);
pinMode(8, OUTPUT);
digitalWrite(8, HIGH);


pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // 设置LED初始状态
  digitalWrite(ledPin, ledState);
pinMode(speakerPin, OUTPUT); 
   u8g2.begin();
  dht.begin();
}
char h_str[3];
char t_str[3];
float h;
float t;
void loop( ) {
double analogVotage = 1.1*(double)analogRead(A3)/1023;
double temp = 100*analogVotage; //计算温度
unsigned int dutyCycle; //占空比
 h = dht.readHumidity();//读湿度
  t = dht.readTemperature();//读温度(摄氏度)
  strcpy(h_str, u8x8_u8toa(h, 2));    /* convert m to a string with two digits */
  strcpy(t_str, u8x8_u8toa(t, 2));    /* convert m to a string with two digits */

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_luBS10_tf);
    u8g2.drawStr(0, 23, "T");
    u8g2.drawStr(20, 23, ":");
    u8g2.drawStr(40, 23, t_str);
    u8g2.drawStr(90, 23, "C");

    u8g2.drawStr(0, 38, "H");
    u8g2.drawStr(20, 38, ":");
    u8g2.drawStr(40, 38, h_str);
    u8g2.drawStr(90, 38, "%");
    u8g2.drawStr(0,53,"Tuesday");
  } while ( u8g2.nextPage() );
  
  delay(1000);
for (int i = 0; i < length; i++) { 
    if (notes[i] == ' ') { 
      delay(beats[i] * tempo); // rest 
    } else { 
      playNote(notes[i], beats[i] * tempo); 
    } 

    // pause between notes 
    delay(tempo / 2);  
  } 
   int reading = digitalRead(buttonPin);

      buttonState = reading;

      
      if (buttonState == HIGH) {
        digitalWrite(9, LOW);digitalWrite(8, LOW);digitalWrite(11, LOW);digitalWrite(10, LOW);
       for(int i=1000;i<=1000000000;i++){
      delay(i*i);
    };
    };
  delay(10000);
  



Serial.print("Temp: "); Serial.print(temp);
Serial.print(" Degrees Duty cycle: ");
Serial.println(dutyCycle);



// 读取按键状态并存储到变量中:
 

      buttonState = reading;

      
      if (buttonState == HIGH) {
        digitalWrite(9, LOW);digitalWrite(8, LOW);digitalWrite(11, LOW);digitalWrite(10, LOW);
       for(int i=1000;i<=1000000000;i++){
      delay(i*i);
    }; 
   
    };
  }
