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

#define map_int16(x, in_min, in_max, out_min, out_max) (((int)x - (int)in_min) * ((int)out_max - (int)out_min) / ((int)in_max - (int)in_min) + (int)out_min)

#include "SynthSoftEnvelope.h"

//@TODO document this class

void SynthSoftEnvelopeClass::begin()
{
    phaseLength = 255;
}

bool SynthSoftEnvelopeClass::update()
{
    //@TODO add slope curve option, add a release state
    uint8_t was = value;

    if(!shape) {
        value = max;
        return value != was;
    }

    if(value == -1) {
        // Initialize and send start value
        value = 0;
        if(shape & 0x80) {
            value = (uint8_t) map_int16(value, 255, 0, min, max);
        } else {
            value = (uint8_t) map_int16(value, 0, 255, min, max);
        }

        return true;
    }

    tick-=1;
    if(tick > 0) {
        return false;
    }

    tick = size;
    if(phase < 255) {
        phase+=increment;
    }

    if(phase >= 255) {
        if(shape & 0x80) {
            value = min;
            return value != was;
        } else {
            value = max;
            return value != was;
        }
    }

    if(lookupSize) {
        value = lookupTable[phase];
    } else {
        value = phase;
    }
    if(shape & 0x80) {
        value = (uint8_t) map_int16(value,255, 0, min, max);
    } else {
        value = (uint8_t) map_int16(value,0, 255, min, max);
    }

    return value != was;
}

uint16_t SynthSoftEnvelopeClass::read()
{
    return value;
}

void SynthSoftEnvelopeClass::setRange(uint8_t mn, uint8_t mx)
{
    min = mn;
    max = mx;
}

uint8_t SynthSoftEnvelopeClass::getShape()
{
    return shape;
}

void SynthSoftEnvelopeClass::setShape(uint8_t v)
{
    shape = v<<1;
    size = (((((unsigned long)(shape&0x7F))<<5))/255);
    increment = 1;
    if(size == 0) {
        increment = 255/((shape&0x7F)<<5);
    }
}

void SynthSoftEnvelopeClass::setLookupTable(const uint8_t t[], uint8_t size)
{
    lookupTable = t;
    lookupSize = size;
}

void SynthSoftEnvelopeClass::reset()
{
    tick = size;
    phase = 0;
    value = -1;
}
