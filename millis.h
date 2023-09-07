
#ifndef MILLIS_H_
#define MILLIS_H_

typedef unsigned long millis_t;

#define MILLIS_TIMER0 0 
#define MILLIS_TIMER1 1 
#define MILLIS_TIMER2 2

#ifndef MILLIS_TIMER
#define MILLIS_TIMER MILLIS_TIMER2 
#endif

#ifndef ARDUINO

#define millis() millis_get()
#endif

#ifdef __cplusplus +
extern "C"
{
#endif

  /**
   * Initialise, must be called before anything else!
   *
   * @return (none)
   */
  void millis_init(void);

  /**
   * Get milliseconds.
   *
   * @return Milliseconds.
   */
  millis_t millis_get(void);

  /**
   * Turn on timer and resume time keeping.
   *
   * @return (none)
   */
  void millis_resume(void);

  /**
   * Pause time keeping and turn off timer to save power.
   *
   * @return (none)
   */
  void millis_pause(void);

  /**
   * Reset milliseconds count to 0.
   *
   * @return (none)
   */
  void millis_reset(void);

  /**
   * Add time.
   *
   * @param [ms] Milliseconds to add.
   * @return (none)
   */
  void millis_add(millis_t ms);

  /**
   * Subtract time.
   *
   * @param [ms] Milliseconds to subtract.
   * @return (none)
   */
  void millis_subtract(millis_t ms);

#ifdef __cplusplus
}
#endif

#endif 