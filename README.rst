Nanomidi 0.1
=============

Nanomidi is a very minimal MIDI parser for C. It supports all 7 MIDI
channel messages and ignores everything else. (I may support the rest
in the future, but that's all I need for now.)

The intended use is to read real-time MIDI data from a stream (for
example stdin).

It does not read MIDI files.

License: MIT


Example
--------

::

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


Sending MIDI
-------------

Nanomidi has no support for sending MIDI, but it's easy to do. For
example, to send a note on you could:

::

    fputc(MIDI_NOTE_ON | 2, file);  // channel = 2
    fputc(69, file);                // note
    fputc(30, file);                // velocity
    fflush(file);                   // remember to flush!


More about MIDI
----------------

http://www.midi.org/


Known bugs
-----------

  - midi_read() doesn't detect EOF
  - doesn't handle input from a pipe sometimes (accordion)


Todo
-----

  - implement sysex (but how should the API be?)
  - implement system messages

Ole Martin Bjørndalen - ombdalen@gmail.com - http://nerdly.info/ole/
