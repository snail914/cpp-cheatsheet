MarkDown cheatsheet: https://github.com/adam-p/markdown-here/wiki/Markdown-Here-Cheatsheet


# C++
### don't take shared pointers by value unless you want to share/take ownership!

### no need to call default constructor of a member on class construction, redendant 

### About StringRef:
  ```C++
  const StringRef& = "sss"; // wrong, dangling, "sss" is out of scope at end of this line
  
  void test(const StringRef& s)
  {
    "do with s"

  }

  test("sss"); // this is OK, because "sss" is only out of scope at next line, so everything happens inside `test` is OK
  ```
### chrono: system_clock vs steady_clock
  a. `high_resolution_clock` is an alias for system_clock
  b. `system_clock forwards` to the first of the following that is available:
      - clock_gettime(CLOCK_REALTIME, ...)
      - gettimeofday
      - time
  c. `steady_clock` forwards to the first of the following that is available:
      - clock_gettime(CLOCK_MONOTONIC, ...)
      - system_clock
  
  Then `CLOCK_REALTIME` vs `CLOCK_MONOTONIC` is explained at: https://stackoverflow.com/q/3523442:
      - CLOCK_REALTIME represents the machine's best-guess as to the current wall-clock, time-of-day time. As Ignacio and MarkR say, this means that CLOCK_REALTIME can jump forwards and backwards as the system time-of-day clock is changed, including by NTP.
      - CLOCK_MONOTONIC represents the absolute elapsed wall-clock time since some arbitrary, fixed point in the past. It isn't affected by changes in the system time-of-day clock.
