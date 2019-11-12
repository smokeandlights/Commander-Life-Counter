#include <BigNumbers.h> //https://github.com/seanauff/BigNumbers
#include <DFRkeypad.h>  //https://github.com/DFRobot/LCD-KeyPad-Shield

#define DEBUG

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
BigNumbers bigNum(&lcd);

int LifeTtl = 40;
int CmdrScott = 0;
int CmdrHarber = 1;
int CmdrBarnett = 2;
int CmdrDoc = 3;
int Ctr1 = 4;
int Ctr2 = 5;
int Treasure = 6;
int Poison = 7;

int modeVar[9] {LifeTtl, CmdrScott, CmdrHarber, CmdrBarnett, CmdrDoc, Ctr1, Ctr2, Treasure, Poison};
int modeBigNumPos[9] {9, 10, 10, 10, 10, 9, 9, 9, 11};
int modeBigNumPlaces[9] {3, 2, 2, 2, 2, 2, 2, 3, 2};
String modeLabelLine1[9] {"Life", "Scott", "Harber", "Barnett", "Doc", "Counter", "Counter", "Treasure", "Poison"};
String modeLabelLine2[9] {"Total", "CMDR DMG", "CMDR DMG", "CMDR DMG", "CMDR DMG", "1", "2", "Tokens", "Counters"};


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
