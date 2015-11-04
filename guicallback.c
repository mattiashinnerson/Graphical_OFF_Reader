#include "guicallback.h"
#include "walking_in_air.h"
#include "illumination.h"
#include "variables.h"
#include "openNRead.h"

GdkColor gui_light_color;
GdkColor gui_ambient_color;

extern "C" void on_off_chooser_selection_changed(GtkFileChooser *filechooser, gpointer user_data)
{
    gchar* filename = gtk_file_chooser_get_filename(filechooser);
    char* name = (char*) filename;

    loadVertices(name);
    glutPostRedisplay();
}

extern "C" void on_flip_normals_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    flipNormals();
}

extern "C" void on_move_mode_changed(GtkComboBox *combobox, gpointer user_data)
{
    gint index = gtk_combo_box_get_active(combobox);
    printf("Move mode chosen: %d\n", index);

    if(index == 1){
    	enableSmoothBezierMove(true);
    }else{
    	enableSmoothBezierMove(false);
    }
}

/*Change in lightposition x*/
extern "C" void on_light_x_value_changed(GtkSpinButton*spinbutton,gpointer user_data)
{
    gdouble value = gtk_spin_button_get_value(spinbutton);
    setLightScourcePosX(value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in lightposition y*/
extern "C" void on_light_y_value_changed(GtkSpinButton *spinbutton,gpointer user_data)
{
    gdouble value = gtk_spin_button_get_value(spinbutton);
    setLightScourcePosY(value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in lightposition z*/
extern "C" void on_light_z_value_changed(GtkSpinButton*spinbutton, gpointer user_data)
{
    gdouble value = gtk_spin_button_get_value(spinbutton);
    setLightScourcePosZ(value);
    sendColorToGPU();
    glutPostRedisplay();
}

extern "C" gboolean on_I_light_r_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_light_color.red);
    gui_draw_color_shower(gui_light_shower, &gui_light_color);
    gtk_widget_queue_draw(gui_light_shower);

    return FALSE;
}

extern "C" gboolean on_I_light_g_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_light_color.green);
    gui_draw_color_shower(gui_light_shower, &gui_light_color);
    gtk_widget_queue_draw(gui_light_shower);

    return FALSE;
}

extern "C" gboolean on_I_light_b_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_light_color.blue);
    gui_draw_color_shower(gui_light_shower, &gui_light_color);
    gtk_widget_queue_draw(gui_light_shower);

    return FALSE;
}

/*Change in light scource color (r,g,b)*/
extern "C" void on_I_light_value_changed(GdkColor color) {

     setLightScourceIntens((float)color.red/65535,(float)color.green/65535,(float)color.blue/65535);
     sendColorToGPU();
     glutPostRedisplay();
}

extern "C" void on_I_light_r_value_changed (GtkRange *range, gpointer user_data)
{
    on_I_light_r_value_changing(range, user_data);
    on_I_light_value_changed(gui_light_color);
}

extern "C" void on_I_light_g_value_changed (GtkRange *range, gpointer user_data)
{
    on_I_light_g_value_changing(range, user_data);
    on_I_light_value_changed(gui_light_color);
}

extern "C" void on_I_light_b_value_changed (GtkRange *range, gpointer user_data)
{
    on_I_light_b_value_changing(range, user_data);
    on_I_light_value_changed(gui_light_color);
}

extern "C" gboolean on_I_ambient_r_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_ambient_color.red);
    gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
    gtk_widget_queue_draw(gui_ambient_shower);

    return FALSE;
}

extern "C" gboolean on_I_ambient_g_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_ambient_color.green);
    gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
    gtk_widget_queue_draw(gui_ambient_shower);

    return FALSE;
}

extern "C" gboolean on_I_ambient_b_value_changing(GtkRange *range, gpointer user_data)
{
    gui_set_color(range, &gui_ambient_color.blue);
    gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
    gtk_widget_queue_draw(gui_ambient_shower);

    return FALSE;
}

/*Change in ambient light scource color (r,g,b)*/
extern "C" void on_I_ambient_value_changed(GdkColor color) {
     setAmbientLightIntens((float)color.red/65535,(float)color.green/65535,
    		 	 	 	 	 	 (float)color.blue/65535);
     sendColorToGPU();
     glutPostRedisplay();
}

extern "C" void on_I_ambient_r_value_changed(GtkRange *range, gpointer user_data)
{
    on_I_ambient_r_value_changing(range, user_data);
    on_I_ambient_value_changed(gui_ambient_color);
}

extern "C" void on_I_ambient_g_value_changed(GtkRange *range, gpointer user_data)
{
    on_I_ambient_g_value_changing(range, user_data);
    on_I_ambient_value_changed(gui_ambient_color);
}

extern "C" void on_I_ambient_b_value_changed(GtkRange *range, gpointer user_data)
{
    on_I_ambient_b_value_changing(range, user_data);
    on_I_ambient_value_changed(gui_ambient_color);
}

/*unknown function*/
extern "C" void on_ambient_value_changed(GdkColor color) {
    printf("Ambient color set rgb=(%i,%i,%i)\n",color.red,color.green,color.blue);

}

/*Change in material ambient light R (float)*/
extern "C" void on_k_ambient_r_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialAmbientCoeffR((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material ambient light G (float)*/
extern "C" void on_k_ambient_g_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialAmbientCoeffG((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material ambient light B (float)*/
extern "C" void on_k_ambient_b_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialAmbientCoeffB((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material diffuse light R (float)*/
extern "C" void on_k_diffuse_r_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialDiffuseCoeffR((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material diffuse light G (float)*/
extern "C" void on_k_diffuse_g_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialDiffuseCoeffG((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material diffuse light B (float)*/
extern "C" void on_k_diffuse_b_value_changed (GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialDiffuseCoeffB((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material specular light R (float)*/
extern "C" void on_k_specular_r_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialSpecularCoeffR((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material specular light G (float)*/
extern "C" void on_k_specular_g_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialSpecularCoeffG((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/*Change in material specular light B (float)*/
extern "C" void on_k_specular_b_value_changed(GtkRange *range, gpointer user_data)
{
    gdouble value = gtk_range_get_value(range);
    setMaterialSpecularCoeffB((float)value);
    sendColorToGPU();
    glutPostRedisplay();
}

/* The phong lingning (how much the specular light will spread (focus).
 * higher value gives less spread.*/
extern "C" void on_phong_value_changed(GtkSpinButton *spinbutton, gpointer user_data)
{
    gint32 value = (gint32)round(gtk_spin_button_get_value(spinbutton));
    setPhongShininess((int)value);
    sendColorToGPU();
    glutPostRedisplay();
}

extern "C" void on_win_destroy_event()
{
    printf("Quit\n");
    exit(0);
}

extern "C" gboolean on_ambient_shower_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
    gui_draw_color_shower(widget, &gui_ambient_color);

    return TRUE;
}

extern "C" gboolean on_light_shower_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
    gui_draw_color_shower(widget, &gui_light_color);

    return TRUE;
}
