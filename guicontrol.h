
#ifndef _GUICONTROL_H_
#define _GUICONTROL_H_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

#include "guicallback.h"

/* GETTERS AND SETTERS */

gchar*   gui_get_off_file();
void     gui_set_off_file(gchar* filename);
void     gui_set_move_mode(gint index);
gint     gui_get_move_mode();
void     gui_set_flip_normals(gboolean b);
gboolean gui_get_flip_normals(void);
void     gui_set_I_light(GdkColor color);
GdkColor gui_get_I_light();
void     gui_set_I_ambient(GdkColor color);
GdkColor gui_get_I_ambient();
void     gui_set_k_ambient(gdouble k[3]);
void     gui_get_k_ambient(gdouble k[3]);
void     gui_set_k_diffuse(gdouble k[3]);
void     gui_get_k_diffuse(gdouble k[3]);
void     gui_set_k_specular(gdouble k[3]);
void     gui_get_k_specular(gdouble k[3]);
void     gui_set_light_pos(gdouble p[3]);
void     gui_get_light_pos(gdouble p[3]);
void     gui_set_phong(guint16 phong);
gdouble  gui_get_phong();

/* HELP FUNCTIONS */

void gui_draw_color_shower(GtkWidget *widget, GdkColor *color);
void gui_set_color(GtkRange *range, guint16 *color);

/* INITIALIZERS */

/* Initializes the glade gui.
   input:
      argc: number of string items in argv.
      argv: command line arguments as a string array.
 */
extern void guiInitWindow(const char*);

/* Initialize GTK.
 */
extern void guiInit(int *, char**);

/* Calls a single GTK main loop iteration to process
 * events (non-blocking).
 */
extern void guiMainIteration();

/* GLOBAL VARIABLES */


extern GtkWidget *gui_light_shower;
extern GtkWidget *gui_ambient_shower;

#endif
