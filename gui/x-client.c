#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

void main(int argc, char *argv[])
{
    Display *disp;
    Window win;
    GC gc;
    XEvent event;
    int running = 1;
    void *empty_void_pointer = NULL;
    int *empty_int_pointer = NULL;
    disp = XOpenDisplay("my-display");
    win = XCreateSimpleWindow(
        disp /* display */,
        0 /* parent */,
        3 /* x */,
        3 /* y */,
        10 /* width */,
        10 /* height */,
        1 /* border_width */,
        1 /* border */,
        1 /* background */);
    XSetStandardProperties(disp /* display */,
                           win /* w */,
                           empty_void_pointer /* window_name */,
                           empty_void_pointer /* icon_name */,
                           0 /* icon_pixmap */,
                           argv /* argv */,
                           argc /* argc */,
                           empty_void_pointer /* hints */);
    gc = XCreateGC(
        disp /* display */,
        win /* d */,
        0 /* valuemask */,
        0 /* values */);
    XSelectInput(
        disp /* display */,
        win /* w */,
        ButtonPressMask | KeyPressMask | ExposureMask /* event_mask */);
    XMapRaised(disp, win); /*mostra a janela; envia evento de exposicao de janela */
    while (running)
    {
        XNextEvent(disp, &event); /*obtem proximo evento */
        switch (event.type)
        {
        case Expose: /* repinta janela */
            printf("Expose\n");
            break;
        case ButtonPress: /* processa clique do mouse */
            printf("ButtonPress\n");
            break;
        case KeyPress: /* processa entrada do teclado */
            printf("KeyPress\n");
            break;
        }
    }
    XFreeGC(disp, gc);         /* libera contexto grafico */
    XDestroyWindow(disp, win); /* desaloca espaco de memoria da janela */
    XCloseDisplay(disp);       /* termina a conexao de rede */
}