#include <unistd.h>
#include <getopt.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>

/* Report amount of X server idle time. */
/* Build with- */
/* cc xidle.c -o xidle -lX11 -lXext -lXss */

const struct option progoptions[] = { { "help", 0, NULL, '?' }, { NULL, 0, NULL, 0 } };

void print_usage() {
  printf("Usage: xidle [-hmsl] [--help]\n\n");
  printf("  Options:\n");
  printf("  -h  : print hours of idle time\n");
  printf("  -m  : print minutes of idle time\n");
  printf("  -s  : print seconds of idle time\n");
  printf("  -l  : print milliseconds of idle time\n\n");  
  printf("By default, all denominations are shown. Options specify which denominations are printed.\n");
  printf("  All numbers output will fully account for the total idle time insofar as their precision allows.\n");
  printf("  For example, if only minutes are *omitted* as options, their value below that of a full hour\n");
  printf("  will be multiplied into the seconds.\n\n");
}

int main(int argc, char *argv[]) {
  Display *display;
  int event_base, error_base;
  XScreenSaverInfo info;
  
  const int show_hours = (0x1 << 3);
  const int show_mins  = (0x1 << 2);
  const int show_secs  = (0x1 << 1);
  const int show_ms    = (0x1 << 0);
  int showflags = 0;

  int longindex=0;
  int r = getopt_long(argc, argv, "hmsl", progoptions, &longindex);
  while (r != -1) {
    switch(r) {
      case 'h': showflags |= show_hours; break;
      case 'm': showflags |= show_mins;  break;
      case 's': showflags |= show_secs;  break;
      case 'l': showflags |= show_ms;    break;
      case '?': print_usage(); return 0;
    }
    r = getopt_long(argc, argv, "hmsl", progoptions, &longindex);
  }

  if (showflags==0) {
    showflags |= show_hours | show_mins | show_secs | show_ms;
  }

  display = XOpenDisplay("");

  if (XScreenSaverQueryExtension(display, &event_base, &error_base)) {
    XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);

    unsigned long ms=info.idle, secs=0, mins=0, hours=0;
    long d;
    if (showflags & show_hours) {
      d = 60 * 60 * 1000;
      hours = ms / d;
      ms = ms % d;
      printf("%lu ", hours);
    }
    if (showflags & show_mins) {
      d = 60 * 1000;
      mins = ms / d;
      ms = ms % d;
      printf("%lu ", mins);
    }
    if (showflags & show_secs) {
      d = 1000;
      secs = ms / d;
      ms = ms % d;
      printf("%lu ", secs);
    }
    if (showflags & show_ms) {
      printf("%lu ", ms);
    }
    printf("\n");
    
    return (0);
  } else {
    fprintf(stderr, "Error: XScreenSaver Extension not present\n");
    return (1);
  }
}