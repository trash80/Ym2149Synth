# Ym2149Synth
YM2149F Teensy Synthesizer

@TODO - Documentation.

## MIDI Implementation:
3 voices, 1 MIDI channel per voice.

### CC Map:
* CC1 - Softwave-voice / Env-voice finetune (Software PWM)
* CC2 - Softwave-voice note detune in synth type:5, otherwise square-voice detune
* CC3 - Synth Type:
  * 0 - Square-voice
  * 1 - Square-voice + Env-voice Saw (Square pitch modulations are soloed for "acid" effects.)
  * 2 - Square-voiec + Env-voice Triangle (Square pitch modulations are soloed for "acid" effects.)
  * 3 - Env-voice Triangle
  * 4 - Env-voice Saw
  * 5 - Square-voice + Softwave-voice (PWM)
  * 6 - Square-voice + Softwave-voice (Square pitch modulations are soloed for "acid" effects.)
  * 7 - Noise
* CC4 - Volume Env Shape: 0=OFF, 1-63=Ramp up time, 64-127 Ramp down time
* CC5 - Note Glide Amount
* CC6 - Vibrato Rate
* CC7 - Vibrato Depth
* CC8 - Trigger noise delay (useful for snare tail or Env synth type effect)
* CC9 - Pitch Envelope amount
* CC10- Pitch Env Shape: 0=OFF, 1-63=Ramp up time, 64-127 Ramp down time
* CC11- Transpose: 64 center.
* CC120 - Load Preset (0-15)
* CC121 - Save Preset (0-15)
* CC122 - Dump Patches
