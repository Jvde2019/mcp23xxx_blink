// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

//#define LED_PIN 16     // MCP23XXX pin LED is attached to

// only used for SPI
#define CS_PIN 6

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");
  randomSeed(analogRead(0));

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure pins for output
  for (uint8_t LED_PIN=0; LED_PIN<16; LED_PIN++){
    mcp.pinMode(LED_PIN, OUTPUT);
  }
// all pins off 
   mcp.writeGPIOAB(65535); 

  Serial.println("Looping...");
}

void loop() {
  int gpio[16] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int p = 0;
  while (1) {
    p = random(0,16);
    gpio[p]++; 
    mcp.digitalWrite(p, LOW);  // turn LED on by sinking current to ground
    delay(5);
    mcp.digitalWrite(p, HIGH); // turn LED off by turning off sinking transistor
    delay(100);
    mcp.digitalWrite(p, LOW);  // turn LED on by sinking current to ground
    delay(5);
    mcp.digitalWrite(p, HIGH); // turn LED off by turning off sinking transistor
    for(int t=0;t<15;t++){
      Serial.print(gpio[t]);
      Serial.print(";");
    }  
    Serial.println();    
    delay(1000);
    }
}