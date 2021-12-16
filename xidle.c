#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>

/* Report amount of X server idle time. */
/* Build with- */
/* cc xidle.c -o xidle -lX11 -lXext -lXss */

int main(int argc, char *argv[]) {
  Display *display;
  int event_base, error_base;
  XScreenSaverInfo info;
  float seconds;

  display = XOpenDisplay("");

  if (XScreenSaverQueryExtension(display, &event_base, &error_base)) {
    XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);

    //seconds = (float)info.idle / 1000.0f;
    int ms = info.idle;
    int secs = ms / 1000;
    ms = ms % 1000;
    int mins = secs / 60;
    secs = secs % 60;
    int hours = mins / 60;
    mins = mins % 60;
    printf("%i %i %i %i\n", hours, mins, secs, ms);
    return (0);
  } else {
    fprintf(stderr, "Error: XScreenSaver Extension not present\n");
    return (1);
  }
}