#ifndef IntervalTimer_H
#define IntervalTimer_H

#include "Arduino.h"

class IntervalTimer {
   public:
      IntervalTimer(unsigned long interval, void (*callback) (void));
      bool update();
      void setInterval(unsigned long interval);
      void reset();
   private:
      unsigned long _interval;
      unsigned long _nextTrigger;
      void (*_callback) (void);
};

#endif
