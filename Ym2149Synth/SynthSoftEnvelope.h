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

#ifndef SYMTHSOFTENVELOPE_h
#define SYNTHSOFTENVELOPE_h

#include "Arduino.h"
#include "fixed.h"

class SynthSoftEnvelopeClass {
  public:

    void begin();
    bool update();
    uint16_t read();
    void setShape(uint8_t v);
    void setRange(uint8_t mn, uint8_t mx);
    void setLookupTable(const uint8_t t[], uint8_t size);
    uint8_t getShape();
    void reset();

  private:
    uint32_t t;
    const uint8_t * lookupTable;
    uint8_t lookupSize;
    uint16_t phase;
    uint16_t size;
    int16_t tick;
    uint8_t increment;
    uint8_t phaseLength;
    uint8_t shape;
    uint16_t min;
    uint16_t max;
    int value;
};

typedef SynthSoftEnvelopeClass SynthSoftEnvelope;

#endif
