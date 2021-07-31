
//#include <SPI.h>

//const unsigned int LDAC_PIN = 9;          //physical pin: 3
const unsigned int SDI_PIN  = 5; /*MISO *///physical pin: 8
const unsigned int SCK_PIN  = 4; /*SCK*/  //physical pin: 9
const unsigned int CS_PIN   = 10;         //physical pin: 2

unsigned int sample = 0;

int led = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

//  pinMode(LDAC_PIN, OUTPUT);
  pinMode(SDI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);

  digitalWrite(CS_PIN, HIGH);
//  digitalWrite(LDAC_PIN, HIGH);
}


void loop() {

//  writeToDAC(4095);
//
//  digitalWrite(led, HIGH); // sanity led on
//
//  delay(2000);
//
//  writeToDAC(0);
//  digitalWrite(led, LOW); // sanity led on
//
//  delay(3000);
  if(sample<4096){
    digitalWrite(led, HIGH);
    sample++;
  } else {
    digitalWrite(led, LOW);
    sample=0;  
  }
  writeToDAC(sample);
  delay(1);
  
  
}

inline void writeToDAC(const int& number){
  const int DAC_MODE_BIT = 7;
  const int GAIN_MODE_BIT = 5;
  const int SHUDONW_MODE_BIT = 4;
  const int DAC_ON = 0;
  const int GAIN2x = 0;
  const int NOSHUTDOWN = 1;
  const byte writeCMDHighByte = ((number>>8) & 0xff) | (DAC_ON << DAC_MODE_BIT) | (GAIN2x << GAIN_MODE_BIT) | (NOSHUTDOWN << SHUDONW_MODE_BIT);
  const byte writeCMDLowByte  = ((number   ) & 0xff);

  digitalWrite(CS_PIN, LOW);
  shiftOut(SDI_PIN, SCK_PIN, MSBFIRST, writeCMDHighByte); // DAC low
  shiftOut(SDI_PIN, SCK_PIN, MSBFIRST, writeCMDLowByte); // DAC low
  digitalWrite(CS_PIN, HIGH);
}

const inline int setBit(const int& number, const unsigned int& pos, const bool data){
  if(data==0){
    return number & ~(0<<pos);
  } else {
    return number | (1<<pos);
  }
}
