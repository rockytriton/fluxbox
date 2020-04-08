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

    XSelectInput(d, win, ButtonPressMask | StructureNotifyMask);
    XMapWindow(d, win);

    GC pen;
    XGCValues values;

    values.foreground = WhitePixel(d, screenNum);
    values.line_width = 1;
    values.line_style = LineSolid;
    pen = XCreateGC(d, win, GCForeground | GCLineWidth | GCLineStyle, &values);

    printf("Events...\n");

    int done = 0;

    while(!done) {
        XEvent ev;
        XNextEvent(d, &ev);

        switch(ev.type) {
            case ButtonPress:
                done = 1;
                break;

            case Expose:
                XDrawLine(d, win, pen, 0, 0, w, h);
                XDrawLine(d, win, pen, w, 0, 0, h);
                break;

            case ConfigureNotify:
                if (w != ev.xconfigure.width || h != ev.xconfigure.height) {
                    w = ev.xconfigure.width;
                    h = ev.xconfigure.h;
                    XClearWindow(d, ev.xany.window);
                    printf("Resized\n");
                }
                break;

            default:
                printf("XEvent: %d\n", ev.type);
        }

        if (ev.type == ButtonPress) {
            printf("PRESS\n");
            break;
        } else if (ev.type != 0) {
            printf("XEvent: %d\n", ev.type);
        }
    }

    XCloseDisplay(d);


    return 0;

}

