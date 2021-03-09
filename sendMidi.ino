#include <usbmidi.h>

#define MIDI_NOTE_OFF   0b10000000
#define MIDI_NOTE_ON    0b10010000
#define MIDI_CONTROL    0b10110000
#define MIDI_PITCH_BEND 0b11100000

double base_a4=440; //set A4=440Hz

double note_to_freq(double n) {
  if( n>=0 && n<=119 ) {
    return base_a4*pow(2,(n-57)/12);
  } else {
    return -1;
  }
}


void sendCC(uint8_t channel, uint8_t control, uint8_t value) {
	USBMIDI.write(0xB0 | (channel & 0xf));
	USBMIDI.write(control & 0x7f);
	USBMIDI.write(value & 0x7f);
}

void sendNote(uint8_t channel, uint8_t note, uint8_t velocity) {
	USBMIDI.write((velocity != 0 ? 0x90 : 0x80) | (channel & 0xf));
	USBMIDI.write(note & 0x7f);
	USBMIDI.write(velocity &0x7f);
}


void setup() {
	Serial.begin(9600);
  USBMIDI.flush();
}

void loop() {
	//Handle USB communication
	USBMIDI.poll();

	// While there's MIDI USB input available...

  u8 b = USBMIDI.read();

  int note = 10;
  int velocity = 10;

  while(true){
    note = int(random(20, 127));
    velocity = int(random(20, 127));
    sendNote(1, note, velocity);
    delay(100);

  // Output the byte to the Serial interface.
  // Serial.print(b >> 4, HEX);
  // Serial.print(b & 0xf, HEX);
  // Serial.print('\n');

  // Echo the byte back to the MIDI USB output.
  // USBMIDI.write(b);
  USBMIDI.flush();
  }
}
