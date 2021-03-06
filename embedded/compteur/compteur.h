#pragma once

#include "common/tickscounter.h"
#include "histogram.h"

class TicksReader {
    histogram::Histogram H;
    bool m_last_value = 0;
    u16 m_last_adc_value[64] = {0};
    u8 m_adc_index = 0;

  public:
    TicksReader();
    // returns 1 if the adc just got high.
    bool take();
    const u8 *histogram_data(usize *L) const;
    const u8 *adc_data(usize *L = 0) const;
#ifdef PC
    static int test();
#endif
};

class compteur {
    tickscounter::counter counter;
    TicksReader reader;

  public:
    compteur();
    bool update();
    void print();
    tickscounter::bin::count total();
    TicksReader *ticksReader();
    const u8 *data(size_t *L) const;
    static int test();
};
