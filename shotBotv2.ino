#include "pitches.h"

//Pins
const int speaker = 6;
const int laser = 8;
const int omiron_switch = 10;
const int pump = 12;
int shotBotState;
int switchReadValue;

//   Music //////
const int tempoTheLick = 168;
int theLickMelody[] = {NOTE_D4,8, NOTE_E4,8, NOTE_F4,8, NOTE_G4,8, 
                      NOTE_E4,4, NOTE_C4,8, NOTE_D4,1,};


int takeOnMeMelody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
int takeOnMeLength = sizeof(takeOnMeMelody)/sizeof(takeOnMeMelody[0]);
int takeOnMeDurations[] = {
8, 8, 8, 4, 4, 4,
4, 8, 8, 8, 8, 8,
8, 8, 8, 4, 4, 4,
4, 8, 8, 8, 8, 8
};

/////////////////


void setup() {
  pinMode(speaker, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(omiron_switch, INPUT);
  Serial.begin(115200);
  digitalWrite(pump, HIGH);

}
 
void loop() {
  if(switchAndStateIsActive()){
    shotBotState = 1;
    Serial.println("Value: " + static_cast<String>(switchReadValue));
    event();
    //Cooldown
    delay(5000);
  }
 
 else {
    digitalWrite(laser, LOW);
    digitalWrite(pump, HIGH);
    shotBotState = 0;
    }
}


bool switchAndStateIsActive(){ 
    switchReadValue = digitalRead(omiron_switch);
    return switchReadValue == HIGH && shotBotState == 0;
  }


void event(){
    bool laserState = 0;
    digitalWrite(laser, HIGH);
    int num = random(0,10);
    delay(1000);
    Serial.print("Random Number: ");
    Serial.println(num);
    Serial.println("Rolling Dice");
    for (int i = 0; i<26; i++){
        delay(100);
        if(laserState) {
          digitalWrite(laser, HIGH);
          tone(speaker, 262); 
        }
        else {digitalWrite(laser, LOW); noTone(speaker);}
        laserState = !laserState;
      } 
      noTone(speaker);
    digitalWrite(laser, LOW);
    }

void drawEvent(int randomNumber){
      switch (randomNumber){ //Adjust probabilities here
      case 0:
        drink();
        break;
      case 1:
        drink();
        break;
      case 2:
        drink();
        break;
      case 3:
        drink();
        break;
      case 4:
        everyoneDrinks();
        break;
      case 5:
        everyoneDrinks();
        break;
      default:
        lose();
        break;
      }
  }
  
void drink(){
    Serial.println("Drink Triggered!");
    digitalWrite(laser, HIGH);
    playTakeOnMe();
    digitalWrite(pump, LOW);
    digitalWrite(pump, HIGH);
    delay(5000);
  }

void lose(){
  tone(speaker, 150);
  delay(100);
  tone(speaker, 100);
  noTone(speaker);
  }
void everyoneDrink(){
  playTheLick();
  }

  
void playTakeOnMe(){
  for (int thisNote = 0; thisNote < takeOnMeLength; thisNote++){
    int duration = 1000/ takeOnMeDurations[thisNote];
    tone(speaker, takeOnMeMelody[thisNote], duration);
    int pause = duration * 1.3;
    delay(pause);
    noTone(speaker);
      } 
  }

void playTheLick(){
      int notes_lick = sizeof(theLickMelody) / sizeof(theLickMelody[0]) / 2;
      int wholenote = (60000 * 4) / tempoTheLick;
      int divider = 0, noteDuration = 0;
      for (int thisNote = 0; thisNote < notes_lick * 2; thisNote = thisNote + 2) {
        divider = theLickMelody[thisNote + 1];
        
        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
        tone(speaker, theLickMelody[thisNote], noteDuration*0.9);    
        delay(noteDuration);
        noTone(speaker);
      }
  
  }
