/*
#include <EEPROM.h>

const uint8_t numberPresets = 128;
const uint8_t presetSize = 10;
uint8_t preset[3][presetSize];
uint8_t currentPreset[3];

void recallPreset(uint8_t channel, uint8_t preset_number)
{
    if(preset_number >= numberPresets) return;
    currentPreset[channel] = preset_number;
    preset[channel][0] = 0;
    preset[channel][1] = 0;
    preset[channel][2] = 0;
    preset[channel][3] = 0;
    preset[channel][4] = 0;
    preset[channel][5] = 0;
    preset[channel][6] = 0;
    preset[channel][7] = 0;
    preset[channel][8] = 0;
    preset[channel][9] = 0;

    uint16_t offset = (currentPreset[channel]*presetSize);
    for(int x=0; x<presetSize;x++) {
        preset[channel][x] = EEPROM.read(offset+x);
    }

    bool is_playing = Synth[channel].playing;
    if(is_playing) {
        Synth[channel].playing = false;
    }

    Synth[channel].setPwmFreq(preset[channel][0]);
    Synth[channel].setSoftDetune(preset[channel][1]);
    Synth[channel].volumeEnvelope.setShape(preset[channel][3]);
    Synth[channel].setGlide(preset[channel][4]);
    Synth[channel].setVibratoAmount(preset[channel][5]);
    Synth[channel].setVibratoFreq(preset[channel][6]);
    Synth[channel].setNoiseDelay(preset[channel][7]);
    Synth[channel].setPitchEnvelopeAmount(preset[channel][8]);
    Synth[channel].pitchEnvelope.setShape(preset[channel][9]);

    if(is_playing) {
        Synth[channel].playing = true;
    }

    Synth[channel].setSynthType(preset[channel][2]);
}

void getPreset(uint8_t channel)
{
    uint8_t message[3] = {(uint8_t)(0xB0+channel), 0x00, 0x00};
    for(int x=0; x<presetSize;x++) {
        message[1] = x+1;
        message[2] = preset[channel][x];
        Serial1.write(message,3);
    }
}

void savePreset(uint8_t channel)
{
    uint16_t offset = (currentPreset[channel]*presetSize);
    for(int x=0; x<presetSize;x++) {
        EEPROM.write(offset+x,preset[channel][x]);
    }
}
*/
