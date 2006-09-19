#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


gboolean
on_mainwindow_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_main_quit();
  return FALSE;
}


void
on_quitbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_main_quit();
}

static int callback(void *mainwindow, int argc, char **argv, char **azColName)
{
 
  GtkWidget* mwnd = (GtkWidget*) mainwindow;
  GtkComboBox* combo = lookup_widget(mwnd, "addresscombobox");

  int i;
  char combotext[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Last_Name") == 0)
	  {
		sprintf(combotext, "%s, ", argv[i]);
	  }
	  if(strcmp(azColName[i],"First_Name") == 0)
	  {
		strcat(combotext, argv[i]);
		gtk_combo_box_append_text(combo, combotext);
	  }
  }
  return 0;
}

static int del_file_callback(void *unused, int argc, char **argv, char **azColName)
{
 
  int i;
  char del[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Image") == 0)
	  {
		sprintf(del, "rm -f %s", argv[i]);
	  }
  }
  if (strstr(del, "person.png")==NULL){
	 system(del);
  }
  return 0;
}



static int check_insert(void *unused, int argc, char **argv, char **azColName)
{
  if (argc != 0) return 1;
  return 0;
}


static int combo_active(void *combobox, int argc, char **argv, char **azColName)
{
 
  GtkWidget* btn = (GtkWidget*) combobox;
  GtkEntry* lastname = lookup_widget(btn, "lastnameentry");
  GtkEntry* firstname = lookup_widget(btn, "firstnameentry");
  GtkEntry* street = lookup_widget(btn, "streetentry");
  GtkEntry* no = lookup_widget(btn, "noentry");
  GtkEntry* zip = lookup_widget(btn, "zipentry");
  GtkEntry* city = lookup_widget(btn, "cityentry");
  GtkEntry* phone = lookup_widget(btn, "phoneentry");
  GtkEntry* mobile = lookup_widget(btn, "mobileentry");
  GtkEntry* email = lookup_widget(btn, "emailentry");
  GtkLabel* label = lookup_widget(btn, "url");
  GtkImage* image = lookup_widget(btn, "buddy");

  int i;
  char entrytext[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Last_Name") == 0)
	  {
		gtk_entry_set_text(lastname,argv[i]);
	  }
	  if(strcmp(azColName[i],"First_Name") == 0)
	  {
		gtk_entry_set_text(firstname,argv[i]);
	  }
	  if(strcmp(azColName[i],"Street") == 0)
	  {
		gtk_entry_set_text(street,argv[i]);
	  }
	  if(strcmp(azColName[i],"No") == 0)
	  {
		gtk_entry_set_text(no,argv[i]);
	  }
	  if(strcmp(azColName[i],"Zip") == 0)
	  {
		gtk_entry_set_text(zip,argv[i]);
	  }
	  if(strcmp(azColName[i],"City") == 0)
	  {
		gtk_entry_set_text(city,argv[i]);
	  }
	  if(strcmp(azColName[i],"Phone") == 0)
	  {
		gtk_entry_set_text(phone,argv[i]);
	  }
	  if(strcmp(azColName[i],"Mobile") == 0)
	  {
		gtk_entry_set_text(mobile,argv[i]);
	  }
	  if(strcmp(azColName[i],"Email") == 0)
	  {
		gtk_entry_set_text(email,argv[i]);
	  }
	  if(strcmp(azColName[i],"Image")==0)
	  {
		if(argv[i] != NULL)
		{
			gtk_image_set_from_file(image,argv[i]);
			gtk_label_set_text(label,argv[i]);
		}else{
			gtk_image_set_from_file(image,"/usr/share/gfa/pixmaps/person.png");
			gtk_label_set_text(label,"/usr/share/gfa/pixmaps/person.png");
		}
	  }
  }
  return 0;
}

void
on_addresscombobox_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GtkEntry* lastname = lookup_widget(combobox, "lastnameentry");
	GtkEntry* firstname = lookup_widget(combobox, "firstnameentry");
	GtkEntry* street = lookup_widget(combobox, "streetentry");
	GtkEntry* no = lookup_widget(combobox, "noentry");
	GtkEntry* zip = lookup_widget(combobox, "zipentry");
	GtkEntry* city = lookup_widget(combobox, "cityentry");
	GtkEntry* phone = lookup_widget(combobox, "phoneentry");
	GtkEntry* mobile = lookup_widget(combobox, "mobileentry");
	GtkEntry* email = lookup_widget(combobox, "emailentry");

	char* text = gtk_combo_box_get_active_text(combobox);
	char div[] = ",";
	char* lname = strtok(text, div);
	char* fname = strtok(NULL,div);
	fname = g_strchug(fname);

	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;

	char* home = getenv("HOME");
		
	char* path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char* filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	char* query[1024];
	sprintf(query, "SELECT * FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);

	rc = sqlite3_exec(db, query, combo_active, combobox, &zErrMsg);
	sqlite3_close(db);
}


void
on_savebutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;

	char* home = getenv("HOME");
		
	char* path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char* filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	GtkEntry* lastname = lookup_widget(button, "lastnameentry");
	GtkEntry* firstname = lookup_widget(button, "firstnameentry");
	GtkEntry* street = lookup_widget(button, "streetentry");
	GtkEntry* no = lookup_widget(button, "noentry");
	GtkEntry* zip = lookup_widget(button, "zipentry");
	GtkEntry* city = lookup_widget(button, "cityentry");
	GtkEntry* phone = lookup_widget(button, "phoneentry");
	GtkEntry* mobile = lookup_widget(button, "mobileentry");
	GtkEntry* email = lookup_widget(button, "emailentry");
	GtkLabel* label = lookup_widget(button, "url");

	const char* lname = gtk_entry_get_text(lastname);
	const char* fname = gtk_entry_get_text(firstname);
	const char* str = gtk_entry_get_text(street);
	const char* n = gtk_entry_get_text(no);
	const char* z = gtk_entry_get_text(zip);
	const char* c = gtk_entry_get_text(city);
	const char* p = gtk_entry_get_text(phone);
	const char* m = gtk_entry_get_text(mobile);
	const char* e = gtk_entry_get_text(email);
	const char* u = gtk_label_get_text(label);

	if (strlen(lname) == 0 || strlen(fname) == 0)
	{
		GtkWidget* dialog = create_dialog2();
		int result = gtk_dialog_run (GTK_DIALOG (dialog));
  	
  		gtk_widget_destroy (dialog);
	}else{

		char* copy[1024];
		sprintf(copy,"cp -f '%s' '%s'",u, path);
		system(copy);

		char* imagefile = strtok(u,"/");
		char* temp;
		while(imagefile != NULL)
		{
			strcpy(temp,imagefile);
			imagefile = strtok(NULL,"/");
		}
		char* img[1024];
		g_sprintf(img, "%s/%s",path,temp);

		char* check[1024];
		sprintf(check, "SELECT * FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);

		rc = sqlite3_exec(db, check, check_insert, 0, &zErrMsg);
		char* query[1024];

		if (rc == 0){
			sprintf(query, "insert into gfa values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');", lname,fname,str,n,z,c,p,m,e,img); 
		
			GtkComboBox* combo = lookup_widget(button, "addresscombobox");
			char* insert[1024];
			sprintf(insert, "%s, %s", lname,fname);
			gtk_combo_box_append_text(combo,insert);
		}else{
			sprintf(query, "UPDATE gfa SET Last_Name = '%s',First_Name = '%s',Street = '%s',No = '%s',Zip = '%s',City = '%s',Phone = '%s',Mobile = '%s', Email = '%s', Image = '%s' WHERE Last_Name = '%s' AND First_Name = '%s';", lname,fname,str,n,z,c,p,m,e,img,lname,fname);

		}	
		rc = sqlite3_exec(db, query, callback, button, &zErrMsg);
		sqlite3_close(db);
	}
}


void
on_mainwindow_realize                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;
	
	char* home = getenv("HOME");
	mode_t mode = (mode_t) 0755;

	char* path[1024];
	sprintf(path,"%s/.gfa", home);

	mkdir(path,mode);
	char* dbfile[1024];
	sprintf(dbfile,"%s/.gfa/gfa.db", home);


	rc = sqlite3_open(dbfile,&db);
	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS gfa(Last_Name char(50), First_Name char(50), Street char(100), No char(10), Zip char(10), City char(50), Phone char(30), Mobile char(30), Email char(200), Image char(1024)) ;", NULL, 0, &zErrMsg);


	rc = sqlite3_exec(db, "select Last_Name,First_Name from gfa ORDER BY Last_Name,First_Name ASC;", callback, widget, &zErrMsg);
	sqlite3_close(db);
	
	GtkLabel* label = lookup_widget(widget, "url");
	gtk_label_set_text(label,"/usr/share/gfa/pixmaps/person.png");

}


void
on_deletebutton_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;

	char* home = getenv("HOME");
		
	char* path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char* filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	GtkEntry* lastname = lookup_widget(button, "lastnameentry");
	GtkEntry* firstname = lookup_widget(button, "firstnameentry");

	const char* lname = gtk_entry_get_text(lastname);
	const char* fname = gtk_entry_get_text(firstname);


	char* del_file[1024];
	sprintf(del_file, "SELECT Image FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);
	


	char* del[1024];
	sprintf(del, "DELETE FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);

	GtkWidget* dialog = create_dialog1();
	int result = gtk_dialog_run (GTK_DIALOG (dialog));
  	switch (result)
  	{
      	case GTK_RESPONSE_YES:
		rc = sqlite3_exec(db, del_file, del_file_callback, 0, &zErrMsg);
		rc = sqlite3_exec(db, del, NULL, 0, &zErrMsg);

		if(rc==0)
		{
		GtkComboBox* combo = lookup_widget(button, "addresscombobox");
		int position = gtk_combo_box_get_active(combo);

		gtk_combo_box_remove_text(combo, position);

		GtkEntry* lastname = lookup_widget(button, "lastnameentry");
		GtkEntry* firstname = lookup_widget(button, "firstnameentry");
		GtkEntry* street = lookup_widget(button, "streetentry");
		GtkEntry* no = lookup_widget(button, "noentry");
		GtkEntry* zip = lookup_widget(button, "zipentry");
		GtkEntry* city = lookup_widget(button, "cityentry");
		GtkEntry* phone = lookup_widget(button, "phoneentry");
		GtkEntry* mobile = lookup_widget(button, "mobileentry");
		GtkEntry* email = lookup_widget(button, "emailentry");
		GtkLabel* label = lookup_widget(button, "url");
		GtkImage* image = lookup_widget(button, "buddy");



		gtk_entry_set_text(lastname,"");
		gtk_entry_set_text(firstname,"");
		gtk_entry_set_text(street,"");
		gtk_entry_set_text(no,"");
		gtk_entry_set_text(zip,"");
		gtk_entry_set_text(city,"");
		gtk_entry_set_text(phone,"");
		gtk_entry_set_text(mobile,"");
		gtk_entry_set_text(email,"");
		gtk_label_set_text(label,"/usr/share/gfa/pixmaps/person.png");
		gtk_image_set_from_file(image,"/usr/share/gfa/pixmaps/person.png");


		}	
		sqlite3_close(db);
		break;
      	default:
 		break;
    	}
  	gtk_widget_destroy (dialog);	
}


void
on_emailsend_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog = create_dialog3();
	int result = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);	
}


void
on_newbutton_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
		GtkComboBox* combo = lookup_widget(button, "addresscombobox");

		GtkEntry* lastname = lookup_widget(button, "lastnameentry");
		GtkEntry* firstname = lookup_widget(button, "firstnameentry");
		GtkEntry* street = lookup_widget(button, "streetentry");
		GtkEntry* no = lookup_widget(button, "noentry");
		GtkEntry* zip = lookup_widget(button, "zipentry");
		GtkEntry* city = lookup_widget(button, "cityentry");
		GtkEntry* phone = lookup_widget(button, "phoneentry");
		GtkEntry* mobile = lookup_widget(button, "mobileentry");
		GtkEntry* email = lookup_widget(button, "emailentry");
		GtkLabel* label = lookup_widget(button, "url");
		GtkImage* image = lookup_widget(button, "buddy");


		gtk_entry_set_text(lastname,"");
		gtk_entry_set_text(firstname,"");
		gtk_entry_set_text(street,"");
		gtk_entry_set_text(no,"");
		gtk_entry_set_text(zip,"");
		gtk_entry_set_text(city,"");
		gtk_entry_set_text(phone,"");
		gtk_entry_set_text(mobile,"");
		gtk_entry_set_text(email,"");
		gtk_label_set_text(label,"/usr/share/gfa/pixmaps/person.png");
		gtk_image_set_from_file(image,"/usr/share/gfa/pixmaps/person.png");

		gtk_combo_box_set_active(combo,-1);


}


void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkButton* button = lookup_widget(menuitem, "newbutton");
	on_newbutton_clicked(button, NULL);
}


void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkButton* button = lookup_widget(menuitem, "savebutton");
	on_savebutton_clicked(button,NULL);
}


void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkButton* button = lookup_widget(menuitem, "deletebutton");
	on_deletebutton_clicked(button,NULL);
}


void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* about = create_aboutdialog1();
	gtk_dialog_run(GTK_DIALOG (about));
  	gtk_widget_destroy (about);
}


void
on_buddy_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* chooser = create_filechooserdialog();
	GtkFileFilter *filter = gtk_file_filter_new ();
	gtk_file_filter_add_pixbuf_formats(filter);
	gtk_file_filter_set_name(filter,"Known image types");
	gtk_file_chooser_add_filter(chooser,filter);
	int result = gtk_dialog_run(GTK_DIALOG(chooser));
	char *filename;
	GtkImage* image = lookup_widget(button, "buddy");
	GtkLabel* label = lookup_widget(button, "url");
		


	switch (result)
  	{
      	case GTK_RESPONSE_OK:
    		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
		gtk_image_set_from_file(image,filename);
		gtk_label_set_text(label,filename);
		break;
	
	case GTK_RESPONSE_CANCEL:

		break;

	case 123:
		gtk_image_set_from_file(image,"/usr/share/gfa/pixmaps/person.png");
		gtk_label_set_text(label,"/usr/share/gfa/pixmaps/person.png");
		break;
	
	default:
		break;
	}

	gtk_widget_destroy(chooser);
}

