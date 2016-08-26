/*
 * YmSynth
 * http://trash80.com
 * Copyright (c) 2016 Timothy Lamb
 *
 * This file is part of YmSynth.
 *
 * YmSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * YmSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "YMSynthController.h"

void YMSynthControllerClass::begin()
{
    Ym.begin();

    Ym.setPortIO(1,1);

    for(int i=0;i<3;i++) {
        Ym.setPin(8,1);
        digitalWrite(13,HIGH);
        delay(60);
        Ym.setPin(8,0);
        digitalWrite(13,LOW);
        delay(60);
    }

    Ym.setPin(8,1);
    Ym.mute();

    for(int x=0;x<3;x++) {
        Synth[x].begin(&Ym,x);
    }
}

void YMSynthControllerClass::update()
{

}

void YMSynthControllerClass::updateSoftSynths()
{
    Synth[0].updateSoftsynth();
    Synth[1].updateSoftsynth();
    Synth[2].updateSoftsynth();
}

void YMSynthControllerClass::updateEvents()
{
    Synth[0].updateEvents();
    Synth[1].updateEvents();
    Synth[2].updateEvents();
}

void YMSynthControllerClass::setChannels(uint8_t c1, int8_t c2, int8_t c3){
    channels[0] = c1;
    channels[1] = c2;
    channels[2] = c3;
}

void YMSynthControllerClass::onNoteOn()
{
    uint8_t * m = &channels[2];
    uint8_t synth = 3;

    while(synth--) {
        if(*m == midi->getChannel()) {
            Synth[synth].playNote(midi->getData1(),midi->getData2());
        }
        m--;
    }
}

void YMSynthControllerClass::onNoteOff()
{
    uint8_t * m = &channels[2];
    uint8_t synth = 3;
    while(synth--) {
        if(*m == midi->getChannel()) {
            Synth[synth].playNote(midi->getData1(),0);
        }
        m--;
    }
}

void YMSynthControllerClass::onControlChange()
{
    uint8_t * m = &channels[2];
    uint8_t synth = 3;
    while(synth--) {
        if(*m != midi->getChannel()) {
            m--;
            continue;
        }
        m--;
        switch(midi->getData1()) {
            case 1:
                Synth[synth].setPwmFreq(midi->getData2());
                break;
            case 2:
                Synth[synth].setSoftDetune(midi->getData2());
                break;
            case 3:
                Synth[synth].setSynthType(midi->getData2());
                break;
            case 4:
                Synth[synth].volumeEnvelope.setShape(midi->getData2());
                break;
            case 5:
                Synth[synth].setGlide(midi->getData2());
                break;
            case 6:
                Synth[synth].setVibratoAmount(midi->getData2());
                break;
            case 7:
                Synth[synth].setVibratoFreq(midi->getData2());
                break;
            case 8:
                Synth[synth].setNoiseDelay(midi->getData2());
                break;
            case 9:
                Synth[synth].setPitchEnvelopeAmount(midi->getData2());
                break;
            case 10:
                Synth[synth].pitchEnvelope.setShape(midi->getData2());
                break;
            case 11:
                Synth[synth].setTranspose(midi->getData2());
                break;
            case 120:
                //recallPreset(synth, midi->getData2());
                break;
            case 121:
                //if(midi->getData2()) savePreset(synth);
                break;
        }
    }
}

void YMSynthControllerClass::onProgramChange()
{

}

void YMSynthControllerClass::onAfterTouch()
{

}

void YMSynthControllerClass::onPitchBend()
{
    uint8_t * m = &channels[2];
    uint8_t synth = 3;
    unsigned short pb;
    int v;

    pb = (unsigned short)midi->getData2();
    pb<<=7;
    pb|= (unsigned short)midi->getData1();
    v = ((int)pb) - 0x2000;

    while(synth--) {
        if(*m == midi->getChannel()) {
            Synth[synth].setPitchbend(v);
        }
        m--;
    }
}
