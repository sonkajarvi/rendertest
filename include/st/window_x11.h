#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include <st/window.h>

void impl_x11_window_create(StWindow *, const char *, int, int);
void impl_x11_window_destroy(StWindow *);
void impl_x11_window_show(StWindow *);

void impl_x11_window_get_size(StWindow *, int *, int *);
void impl_x11_window_get_pos(StWindow *, int *, int *);

double impl_x11_window_time(StWindow *);

void impl_x11_poll_events(StWindow *);
void impl_glx_swap_buffers(StWindow *);
void impl_glx_window_vsync(StWindow *, bool);

void impl_glx_context_create(StWindow *);
void impl_glx_context_destroy(StWindow *);

#endif // WINDOW_X11_H
