#include <BigNumbers.h> //https://github.com/seanauff/BigNumbers
#include <DFRkeypad.h>  //https://github.com/DFRobot/LCD-KeyPad-Shield

#define DEBUG

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
BigNumbers bigNum(&lcd);

int LifeTtl = 40;

String Cmdr0LabelLine1 = "Scott";
String Cmdr0LabelLine2 = "CMDR DMG";
int Cmdr0 = 0;

String Cmdr1LabelLine1 = "Harber";
String Cmdr1LabelLine2 = "CMDR DMG";
int Cmdr1 = 1;

String Cmdr2LabelLine1 = "Barnett";
String Cmdr2LabelLine2 = "CMDR DMG";
int Cmdr2 = 2;

String Cmdr3LabelLine1 = "Doc";
String Cmdr3LabelLine2 = "CMDR DMG";
int Cmdr3 = 3;

String Ctr1LabelLine1 = "Counter";
String Ctr1LabelLine2 = "   1";
int Ctr1 = 4;

String Ctr2LabelLine1 = "Counter";
String Ctr2LabelLine2 = "   2";
int Ctr2 = 5;

String Ctr3LabelLine1 = "Treasure";
String Ctr3LabelLine2 = " Tokens";
int Ctr3 = 6;

String Ctr4LabelLine1 = " Poison";
String Ctr4LabelLine2 = "Counters";
int Ctr4 = 7;

int modeVar[9] {LifeTtl, Cmdr0, Cmdr1, Cmdr2, Cmdr3, Ctr1, Ctr2, Ctr3, Ctr4};
int modeBigNumPos[9] {9, 10, 10, 10, 10, 9, 9, 9, 11};
int modeBigNumPlaces[9] {3, 2, 2, 2, 2, 3, 3, 3, 2};
String modeLabelLine1[9] {"Life", Cmdr0LabelLine1, Cmdr1LabelLine1, Cmdr2LabelLine1, Cmdr3LabelLine1, Ctr1LabelLine1, Ctr2LabelLine1, Ctr3LabelLine1, Ctr4LabelLine1};
String modeLabelLine2[9] {"Total", Cmdr0LabelLine2, Cmdr1LabelLine2, Cmdr2LabelLine2, Cmdr3LabelLine2, Ctr1LabelLine2, Ctr2LabelLine2, Ctr3LabelLine2, Ctr4LabelLine2};


byte scratch ;
int mode = 0;

bool buttonsWork = false; //change to true to disable auto page switching

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  bigNum.begin();

}

void loop() {
#ifdef DEBUG
  Serial.print(modeLabelLine1[mode]);
  Serial.print(" ");
  Serial.print(modeLabelLine2[mode]);
  Serial.print(": ");
  Serial.println(modeVar[mode]);
#endif


  scratch = modeVar[mode];
  lcd.setCursor(0, 0);
  lcd.print(modeLabelLine1[mode]);
  lcd.setCursor(0, 1);
  lcd.print(modeLabelLine2[mode]);
  bigNum.displayLargeInt(scratch, modeBigNumPos[mode], modeBigNumPlaces[mode], false);
  modeVar[mode] = scratch;


  //Auto mode switching until I figure out how to use buttons
  if (buttonsWork == false) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (mode < 8) {
        mode++;
      }
      else {
        mode = 0;
      }
    }
  }

}
