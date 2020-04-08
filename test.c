#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    Display *d = XOpenDisplay(argv[1]);

    if (!d) {
        printf("Failed to connect to display\n");
        return -1;
    }

    printf("DISP: %X\n", d);
    int screenNum = DefaultScreen(d);
    long bg = BlackPixel(d, screenNum);
    long border = WhitePixel(d, screenNum);

    int w = 200;
    int h = 200;

    Window win = XCreateSimpleWindow(d, DefaultRootWindow(d), 50, 50, w, h, 2, border, bg);

    printf("WIN: %X\n", win);

    XMapWindow(d, win);

    sleep(5);

    XCloseDisplay(d);

    return 0;

}

