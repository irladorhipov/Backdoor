#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Не удалось открыть дисплей\n");
        return 1;
    }

    Window root = DefaultRootWindow(display);
    Atom clipboard = XInternAtom(display, "CLIPBOARD", False);
    Atom type;
    int format;
    unsigned long nitems, bytes_after;
    unsigned char *data;
    XGetWindowProperty(display, root, clipboard, 0, 1024, False, AnyPropertyType, &type, &format, &nitems, &bytes_after, &data);

    if (type == XA_STRING && format == 8) {
        printf("Содержимое буфера обмена:\n%s\n", data);
    }

    XCloseDisplay(display);
    return 0;
}