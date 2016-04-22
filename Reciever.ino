//Reciever Code (Leonardo)
#include <VirtualWire.h>
#include "pitches.h"


int speakerPin = 8;
int lightPin = 12;
int numberOfNotes;

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
void setup()
{
  digitalWrite(lightPin,LOW);

  vw_setup(2000);
  vw_set_rx_pin(7);
  vw_rx_start();
}

void loop()
{
  digitalWrite(12, HIGH);
  int numberOfNotes;
  
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
  if(vw_get_message(buf, &buflen))
  {
    for(int i = 0;i < buflen;i++)
    {
      if(buf[i] == '1')
      {
        digitalWrite(13, HIGH);
        digitalWrite(lightPin, HIGH);
        numberOfNotes = sizeof(melody) / sizeof(melody[0]);

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

      else if(buf[i] == '0')
      {
        digitalWrite(13,LOW);
      }
    }
  }
  digitalWrite(12, LOW);
}


