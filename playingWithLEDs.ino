/* MAIN CONFIGS */
#define firstPort 2                             // defines the first port.
#define lastPort 7                              // defines the last port.
#define buttonLEDPort 9                         // defines the port used for the button LED.
#define buttonPort 10                           // defines the button port.

#define LED_delayTimeHIGH 200                   // delay time to turn ON each LED.                                      /*
#define LED_delayTimeLOW 50                     // delay time to turn OFF each LED.                                       ********************************
#define LED_delayTimeRestartLoop 500            // delay time to restart the loops.                                       ALL THE VALUES IN THIS SCOPE ARE
#define buttonLED_delayTimeHIGH 600             // delay time to turn ON the button LED.                                  REPRESENTED IN MILISECONDS (MS).
#define buttonLED_delayTimeLOW 300              // delay time to turn OFF the button LED.                                 ********************************
#define buttonLED_delayToResetCount 1500        // delay time to turn ON/OFF the button LED and reset the VAR count.    */

/* GLOBAL VARIABLES */
int count = 0;                                  // variable used to count how many times the button has been pressed.

/* FUNCTIONS  - All the functions are defined bellow the LOOP function, here its only their declaration */
void firstToLastLED();                          //  turn on the leds in a sequential order.
void lastToFirstLED();                          //  turn on the leds in a reverse order.
void everyOtherLED();                           //  turn on the leds in a "random" order.
void checkButton();                             //  fuction that verifys if the button was used and changes between the other three functions above.

/* MAIN */
void setup() {
  pinMode(buttonPort, INPUT_PULLUP);
  pinMode(buttonLEDPort, OUTPUT);
  for (int i = firstPort; i <= lastPort; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  checkButton();
  switch (count) {
    case 1:
      firstToLastLED();
      break;
    case 2:
      lastToFirstLED();
      break;
    case 3:
      everyOtherLED();
      break;
  }
}

void firstToLastLED() {
  for (int i = firstPort; i <= lastPort; i++) {
    digitalWrite(i, HIGH);
    delay(LED_delayTimeHIGH);
  }
  for (int j = firstPort; j <= lastPort; j++) {
    digitalWrite(j, LOW);
    delay(LED_delayTimeLOW);
  }
  delay(LED_delayTimeRestartLoop);
}

void lastToFirstLED() {
  for (int i = lastPort; i >= firstPort; i--) {
    digitalWrite(i, HIGH);
    delay(LED_delayTimeHIGH);
  }
    for (int j = lastPort; j >= firstPort; j--) {
    digitalWrite(j, LOW);
    delay(LED_delayTimeLOW);
  }
  delay(LED_delayTimeRestartLoop);
}

void everyOtherLED() {
  int startCount;
  for (startCount = 2; startCount < lastPort; startCount += 2) {
    digitalWrite(startCount, HIGH);
    delay(LED_delayTimeHIGH);
  }
  for (startCount = 3; startCount <= lastPort; startCount += 2) {
    digitalWrite(startCount, HIGH);
    delay(LED_delayTimeHIGH);
  }
  for (int i = 6; i >= firstPort; i -= 2) {
    digitalWrite(i, LOW);
    delay(LED_delayTimeLOW);
  }  
  for (int i = 7; i >= firstPort+1; i -= 2) {
    digitalWrite(i, LOW);
    delay(LED_delayTimeLOW);
  }
  delay(LED_delayTimeRestartLoop);
}

void checkButton() {
  if (!digitalRead(buttonPort)) {
    while (!digitalRead(buttonPort)) {
    if (count >= 3) {
      digitalWrite(buttonLEDPort, HIGH);
      delay(buttonLED_delayToResetCount);
      digitalWrite(buttonLEDPort, LOW);
      delay(buttonLED_delayToResetCount);
      count = 0;
    }
      digitalWrite(buttonLEDPort, HIGH);
      count++;
      delay(buttonLED_delayTimeHIGH);
      digitalWrite(buttonLEDPort, LOW);
      delay(buttonLED_delayTimeLOW);
    }
  }
}