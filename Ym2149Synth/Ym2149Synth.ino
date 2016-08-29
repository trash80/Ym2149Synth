/*
 * Ym2149Synth
 * http://trash80.com
 * Copyright (c) 2016 Timothy Lamb
 *
 * This file is part of Ym2149Synth.
 *
 * Ym2149Synth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ym2149Synth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MidiDeviceUsb.h"
#include "MidiDeviceSerial.h"
#include "SynthController.h"

SynthController synth;

MidiDeviceSerial midi(&Serial1);
MidiDeviceUsb usbMidi;

IntervalTimer samplerTimer;
IntervalTimer eventTimer;

const float sampleRate = 22050;
const float softSynthTimer = 1000000L/sampleRate;

void updateSoftSynth()
{
    synth.updateSoftSynths();
}

void updateEvents()
{
    synth.updateEvents();
}

void setup()
{
    pinMode(13,OUTPUT); // debug led on teensy

    synth.setChannels(1,2,3);
    synth.begin();

    usbMidi.setCallback(&synth);
    midi.setCallback(&synth);
    midi.begin();

    samplerTimer.begin(updateSoftSynth, softSynthTimer);
    samplerTimer.priority(0);
    eventTimer.begin(updateEvents, 1000);
    eventTimer.priority(1);

}

void loop()
{
    midi.update();
    usbMidi.update();
}
