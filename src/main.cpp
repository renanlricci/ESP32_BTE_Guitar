#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad;

#define BUTTON_STATE        INPUT_PULLUP
#define TOTAL_BUTTONS       9

#define PIN_BUTTON_GREEN    32
#define PIN_BUTTON_RED      33
#define PIN_BUTTON_YELLOW   25
#define PIN_BUTTON_BLUE     26
#define PIN_BUTTON_ORANGE   27

#define PIN_START           23
#define PIN_SELECT          22

#define PIN_DPAD_UP         21
#define PIN_DPAD_DOWN       19


int pinToButton[TOTAL_BUTTONS]
{
  PIN_BUTTON_GREEN,
  PIN_BUTTON_RED,
  PIN_BUTTON_YELLOW,
  PIN_BUTTON_BLUE,
  PIN_BUTTON_ORANGE,
  PIN_START,
  PIN_SELECT,
  PIN_DPAD_UP,
  PIN_DPAD_DOWN,
};

uint16_t buttonToPin[TOTAL_BUTTONS]
{
  BUTTON_1,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_5,
  BUTTON_6,
  BUTTON_7,
  BUTTON_8,
  BUTTON_9,  
};

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  
  //LED TEST
  pinMode(LED_BUILTIN, OUTPUT);
  //
  for (int index = 0; index < TOTAL_BUTTONS; index++)
  {
    pinMode(pinToButton[index], BUTTON_STATE);  
  }
  
  bleGamepad.begin();
  // The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, and no simulation controls or special buttons
}

void loop()
{
  if (bleGamepad.isConnected())
  {
    for (int index = 0; index < TOTAL_BUTTONS; index++)
    {
      int pinStatus = !digitalRead(pinToButton[index]);
      if (pinStatus == HIGH)
      {
        bleGamepad.press(buttonToPin[index]);
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else
      {
        bleGamepad.release(buttonToPin[index]);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }

}