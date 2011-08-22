/*
  nanomidi 0.1 - minimal MIDI parser for C

  December 2006
  Ole Martin Bjorndalen
  http://nerdly.info/ole/
*/

#ifndef NANOMIDI_H
#define NANOMIDI_H

struct midi_msg {
  unsigned char type;
  unsigned char channel;
  unsigned char data[2];
};

typedef void (*midi_callback)(struct midi_msg *msg);

struct midi_buffer {
  // MIDI message
  unsigned char opcode;
  unsigned char channel;
  unsigned char data[2];

  unsigned char type;


  // Parameters for the parser
  unsigned int channel_mask;  // One bit for each channel you want to listen to
                              // For example 0x02 to listen to channel 1 or 0x03
                              // to listen to channels 0 and 1.
                              // Defaults to 0xffff (all channels.)

  midi_callback callback;     // Function to be called when there is a message
  void *userdata;

  // Internal stuff for the parser
  unsigned char pos;
  unsigned char readlen;
};

void midi_buffer_init(struct midi_buffer *buf);
int midi_parse(struct midi_buffer *buf, unsigned char *bytes, int numbytes);
int midi_read(struct midi_buffer *buf, int fd);

// Values for msg.type (just the opcode with channel masked away)
#define MIDI_NOTE_OFF           0x80
#define MIDI_NOTE_ON            0x90
#define MIDI_POLY_PRESSURE      0xa0
#define MIDI_CONTROL_CHANGE     0xb0
#define MIDI_PROGRAM_CHANGE     0xc0
#define MIDI_CHANNEL_PRESSURE   0xd0
#define MIDI_PITCH_WHEEL        0xe0

#endif
