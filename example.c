#include <stdio.h>
#include "nanomidi.h"

void handle_msg(struct midi_msg *msg)
{
  switch(msg->type) {
  case MIDI_NOTE_ON:
    printf("Note on #%d note=%d velocity=%d\n", msg->channel, msg->data[0], msg->data[1]);
    break;
  case MIDI_NOTE_OFF:
    printf("Note off #%d note=%d velocity=%d\n", msg->channel, msg->data[0], msg->data[1]);
    break;
  case MIDI_PROGRAM_CHANGE:
    printf("Program change #%d program=%d\n", msg->channel, msg->data[0]);
    break;
  }
}

int main() 
{ 
  struct midi_buffer buf; 
  
  midi_buffer_init(&buf); 
  buf.callback = handle_msg;  // Set a callback
  buf.channel_mask = 0xff;    // Listen to channels 0 to 7
  
  // Read from stdin 
  while(midi_read(&buf, 0) == 0) { 
  } 
  
  return 0; 
} 
