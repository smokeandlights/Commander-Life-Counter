#include <BigNumbers.h> //https://github.com/seanauff/BigNumbers

//#define DEBUG
//#define AUTOSCROLL
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
BigNumbers bigNum(&lcd);

int LifeTtl = 40;

String Cmdr0LabelLine1 = "Plyr 1";
String Cmdr0LabelLine2 = "CMDR DMG";
int Cmdr0 = 0;

String Cmdr1LabelLine1 = "Plyr 2";
String Cmdr1LabelLine2 = "CMDR DMG";
int Cmdr1 = 0;

String Cmdr2LabelLine1 = "Plyr 3";
String Cmdr2LabelLine2 = "CMDR DMG";
int Cmdr2 = 0;

String Cmdr3LabelLine1 = "Plyr 4";
String Cmdr3LabelLine2 = "CMDR DMG";
int Cmdr3 = 0;

String Ctr1LabelLine1 = "Missed";
String Ctr1LabelLine2 = "Land Drops";
int Ctr1 = 0;

String Ctr2LabelLine1 = "Counter";
String Ctr2LabelLine2 = "   1";
int Ctr2 = 0;

String Ctr3LabelLine1 = "Treasure";
String Ctr3LabelLine2 = " Tokens";
int Ctr3 = 0;

String Ctr4LabelLine1 = " Poison";
String Ctr4LabelLine2 = "Counters";
int Ctr4 = 0;

String Ctr5LabelLine1 = "FUCKS";
String Ctr5LabelLine2 = "GIVEN";
int Ctr5 = 0;

int modeVar[10] {LifeTtl, Cmdr0, Cmdr1, Cmdr2, Cmdr3, Ctr1, Ctr2, Ctr3, Ctr4, Ctr5};
int modeBigNumPos[10] {6, 8, 8, 8, 8, 9, 8, 8, 8, 10}; //adjusts the placement of the big numbers on the display
int modeBigNumPlaces[10] {3, 2, 2, 2, 2, 2, 2, 2, 2, 1}; //how many digits will be diplayed in the big numbers. Whole numbers only, no decimals, etc.
String modeLabelLine1[10] {"Life", Cmdr0LabelLine1, Cmdr1LabelLine1, Cmdr2LabelLine1, Cmdr3LabelLine1, Ctr1LabelLine1, Ctr2LabelLine1, Ctr3LabelLine1, Ctr4LabelLine1, Ctr5LabelLine1};
String modeLabelLine2[10] {"Total", Cmdr0LabelLine2, Cmdr1LabelLine2, Cmdr2LabelLine2, Cmdr3LabelLine2, Ctr1LabelLine2, Ctr2LabelLine2, Ctr3LabelLine2, Ctr4LabelLine2, Ctr5LabelLine2};

int mode = 0;
int increment = 1;
String buttonPressed = "none";

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  bigNum.begin();

}

void loop() {
#ifdef DEBUG

  for (int m = 0; m <= 8; m++) {
    Serial.print(modeLabelLine1[m]);
    Serial.print(" ");
    Serial.print(modeLabelLine2[m]);
    Serial.print(": ");
    Serial.print(modeVar[m]);
    Serial.print("   ");
  }
  Serial.println();
#endif


  lcd.setCursor(0, 0);
  lcd.print(modeLabelLine1[mode]);
  lcd.setCursor(0, 1);
  lcd.print(modeLabelLine2[mode]);
  if (increment == 10) {
    lcd.setCursor(15, 0);
    lcd.print("*");
  }
  if (increment == 1) {
    lcd.setCursor(15, 0);
    lcd.print(" ");
  }
  readButton();
  bigNum.displayLargeInt(modeVar[mode], modeBigNumPos[mode], modeBigNumPlaces[mode], false);


#ifdef AUTOSCROLL   //Auto mode switching until I figure out how to use buttons
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (mode < 9) {
      mode++;
      lcd.clear(); //blank the screen so there's no leftovers from the previous mode being displayed. Do this only when changing modes, or there's visible "scanning"
    }
    else {
      mode = 0;
      lcd.clear();//blank the screen so there's no leftovers from the previous mode being displayed. Do this only when changing modes, or there's visible "scanning"
    }
  }
#endif

}

void readButton() { //hopefully, this will read the button pin, debounce, and change the buttonPressed variable for a brief time to change modes or change the variable value.

  int b = analogRead(A0);
  int i = 50;

  Serial.print("Button Pressed: ");
  Serial.print(buttonPressed);
  Serial.print("   Analog reading: ");
  Serial.print(analogRead(A0));
  Serial.print("   Increment value: ");
  Serial.println(increment);


  if (b >= 1020) {
    buttonPressed = "none";
  }

  if (b < 740 && b > 700) { //select should alternate the increment value between one and 10.
    buttonPressed = "select";
    if (increment == 1) {
      increment = 10;
      delay(i);
    }
    //    if (increment == 10) {
    else {
      increment = 1;
      delay(i);
    }
  }

  if (b < 325 && b > 285) {
    buttonPressed = "down";
    if (modeVar[mode] > 0) {
      modeVar[mode] = modeVar[mode] - increment;
      delay(i);
    }
  }

  if (b < 150 && b > 110) {
    buttonPressed = "up";
    modeVar[mode] = modeVar[mode] + increment;
    delay(i);
  }

  if (b < 500 && b > 460) { // left should change to the previous mode
    buttonPressed = "left";
    if (mode > 0) {
      mode--;
      lcd.clear();
      delay(i);
    }
  }

  if (b <= 10) {
    buttonPressed = "right";
    if (mode < 9) {
      mode++;
      lcd.clear();
      delay(i);
    }
  }

  //  }
  delay(100);
}
