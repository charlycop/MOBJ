#include  <ctime>
#include  <iostream>

#ifndef  TIMER_H
#define  TIMER_H

class Timer {
  public:
    inline               Timer      ();
    inline Timer&        start      ();
    inline Timer&        stop       ();
    friend std::ostream& operator<< ( std::ostream&, const Timer& );
  private:
    clock_t  start_;
    clock_t  stop_;
};

inline        Timer::Timer () : start_(clock()), stop_(start_) { }
inline Timer& Timer::start () { start_ = clock(); return *this; }
inline Timer& Timer::stop  () { stop_  = clock(); return *this; }

inline std::ostream& operator<< ( std::ostream& o, const Timer& timer )
{
  clock_t delta = (timer.stop_ - timer.start_) / (CLOCKS_PER_SEC/1000);
  o << (delta/1000) << "." << (delta%1000) << " secondes ecoulees";
  return o;
}

#endif  // TIMER_H

