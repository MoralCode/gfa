#include <gtk/gtk.h>


gboolean
on_mainwindow_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_quitbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_aboutbutton_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_addresscombobox_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_savebutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_mainwindow_realize                  (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_deletebutton_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_emailsend_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_aboutbutton_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_quitbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_newbutton_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_new1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_delete1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quitbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_buddy_button_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
expander_callback (GObject    *object,
                   GParamSpec *param_spec,
                   gpointer    user_data);


void
on_datebutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_calendar_day_selected_double_click  (GtkCalendar     *calendar,
                                        gpointer         user_data);
