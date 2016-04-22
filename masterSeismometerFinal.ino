#include "pitches.h"
#include <VirtualWire.h>

int speakerPin = 8;
int lightPin = 12;
int dataPin = 7;
int motionPin = A0;
int threshold = 150;

const int melody[][2] = 
{
    {NOTE_G5, 8},
    {NOTE_D5, 8},    
    {NOTE_C5, 8},
    {NOTE_B5, 8},    
    {NOTE_B5, 8},
    {NOTE_E5, 8},
    {NOTE_E5, 8},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_E5, 8},
    {NOTE_G5, 8},
    {NOTE_G5, 8},
};

const int warning[][2] = 
{
    {NOTE_C5, 32},
    {NOTE_D5, 32},    
    {NOTE_E5, 32},
    {NOTE_F5, 32},    
    {NOTE_G5, 32},
    {NOTE_C5, 32},
    {NOTE_D5, 32},
};
void setup() {
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(7);
}

void loop() {
  int interferenceValue;
  int earthquake;
  int numberOfNotes;

  if(Serial.read() == '2')
  {
    numberOfNotes = sizeof(warning) / sizeof(warning[0]);
    for (int thisNote = 0; thisNote < numberOfNotes; thisNote++)
    {
      digitalWrite(lightPin, HIGH);
      
      // grab our note and note duration from our array
      int thisNoteTone = warning[thisNote][0];
      int thisNoteDuration = warning[thisNote][1];
    
      // to calculate the note duration in ms
      int noteDurationMS = 1000 / thisNoteDuration;
    
      // play the note
      tone(speakerPin, thisNoteTone, noteDurationMS);
    
      delay(noteDurationMS * 1.10);
      digitalWrite(lightPin, LOW);
    }
  }
    if(Serial.read() == '1')
    {
         numberOfNotes = sizeof(melody) / sizeof(melody[0]);
         vw_send((uint8_t *)'1', 1);
                     digitalWrite(lightPin, HIGH);

         for (int thisNote = 0; thisNote < numberOfNotes; thisNote++)
         {
  
            // grab our note and note duration from our array
            int thisNoteTone = melody[thisNote][0];
            int thisNoteDuration = melody[thisNote][1];
    
            // to calculate the note duration in ms
            int noteDurationMS = 1000 / thisNoteDuration;
    
            // play the note
            tone(speakerPin, thisNoteTone, noteDurationMS);
    
            delay(noteDurationMS * 1.10);
         }
                     digitalWrite(lightPin, LOW);

      }
 }

