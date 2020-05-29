#pragma once

#include "common/debug.h"

namespace histogram {
  struct Bin {
    uint16_t value=0;
    uint32_t count=0;
  } __attribute__((packed));
  
  constexpr size_t NBINS=10; 

  struct packed {
    Bin bins[NBINS];
  };
  
  class Histogram {
    packed m_packed;
  public:
    void print() {
      for(size_t k=0;k<NBINS;++k) {
	DBG("k=%d count=%d value=%d\n",k,m_packed.bins[k].count,m_packed.bins[k].value);
      }
    }
    void update(uint16_t value);
    //! number of non-zero bins
    uint16_t size() const;
    //! number of update() calls.
    uint16_t count() const;
    uint16_t minimum() const;
    uint16_t maximum() const;
    uint16_t threshold(int percent) const;
    uint16_t least();
    const packed *get_packed(size_t * L) const {
      *L=sizeof(m_packed);
      return &m_packed;
    }
    static int test();
  };
}
