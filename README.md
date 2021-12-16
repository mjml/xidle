xidle
=====

Reads X11 idle time from libXss and prints it to stdout.

```
Usage: xidle [-hmsl] [--help]

  Options:
  -h  : print hours of idle time
  -m  : print minutes of idle time
  -s  : print seconds of idle time
  -l  : print milliseconds of idle time

By default, all denominations are shown. Options specify which denominations are printed.
  All numbers output will fully account for the total idle time insofar as their precision allows.
  For example, if only minutes are *omitted* as options, their value below that of a full hour
  will be multiplied into the seconds.
```

Credit to stroyan from ubuntuforums for posting this code in 2009.
It still works in 2021! I have augmented it to print integers for use with shell automation.
