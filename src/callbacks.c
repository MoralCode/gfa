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
  GtkWidget* combo = lookup_widget(mwnd, "addresscombobox");
 
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
		gtk_combo_box_append_text((GtkComboBox*)combo, combotext);
	  }
  }
  return 0;
}


static int callback_insert(void *button, int argc, char **argv, char **azColName)
{
  GtkWidget* btn = (GtkWidget*) button;
  GtkWidget* combo = lookup_widget(btn, "addresscombobox");

  int i;
  for(i=0;i<argc;i++)
  {
	  gtk_combo_box_remove_text ((GtkComboBox*)combo, i);
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

static int oldcheck(void *db, int argc, char **argv, char **azColName)
{
  if (argc < 17)
  {
	  sqlite3* database = (sqlite3*)db;
	  char *zErrMsg = 0;
	  sqlite3_exec(db,"alter table gfa add column Birth char(30) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Web char(200) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Icq char(20) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Yahoo char(20) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Msn char(50) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Workphone char(30) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Workmobile char(30) DEFAULT '';", NULL, 0, &zErrMsg);
	  sqlite3_exec(db,"alter table gfa add column Workemail char(200) DEFAULT '';", NULL, 0, &zErrMsg);
  }
  return 0;
}




static int combo_active(void *combobox, int argc, char **argv, char **azColName)
{
 
  GtkWidget* btn = (GtkWidget*) combobox;
  GtkWidget* lastname = lookup_widget(btn, "lastnameentry");
  GtkWidget* firstname = lookup_widget(btn, "firstnameentry");
  GtkWidget* street = lookup_widget(btn, "streetentry");
  GtkWidget* no = lookup_widget(btn, "noentry");
  GtkWidget* zip = lookup_widget(btn, "zipentry");
  GtkWidget* city = lookup_widget(btn, "cityentry");
  GtkWidget* phone = lookup_widget(btn, "phoneentry");
  GtkWidget* mobile = lookup_widget(btn, "mobileentry");
  GtkWidget* email = lookup_widget(btn, "emailentry");
  GtkWidget* label = lookup_widget(btn, "url");
  GtkWidget* image = lookup_widget(btn, "buddy");
  GtkWidget* birth = lookup_widget(btn, "birthdateentry");
  GtkWidget* web = lookup_widget(btn, "webentry");
  GtkWidget* icq = lookup_widget(btn, "icqentry");
  GtkWidget* yahoo = lookup_widget(btn, "yahooentry");
  GtkWidget* msn = lookup_widget(btn, "msnentry");
  GtkWidget* workphone = lookup_widget(btn, "workphoneentry");
  GtkWidget* workmobile = lookup_widget(btn, "workmobileentry");
  GtkWidget* workemail = lookup_widget(btn, "workemailentry");

  int i;
  char entrytext[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Last_Name") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)lastname,argv[i]);
	  }
	  if(strcmp(azColName[i],"First_Name") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)firstname,argv[i]);
	  }
	  if(strcmp(azColName[i],"Street") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)street,argv[i]);
	  }
	  if(strcmp(azColName[i],"No") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)no,argv[i]);
	  }
	  if(strcmp(azColName[i],"Zip") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)zip,argv[i]);
	  }
	  if(strcmp(azColName[i],"City") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)city,argv[i]);
	  }
	  if(strcmp(azColName[i],"Phone") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)phone,argv[i]);
	  }
	  if(strcmp(azColName[i],"Mobile") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)mobile,argv[i]);
	  }
	  if(strcmp(azColName[i],"Email") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)email,argv[i]);
	  }
	  if(strcmp(azColName[i],"Image")==0)
	  {
		if(argv[i] != NULL)
		{
			gtk_image_set_from_file((GtkImage*)image,argv[i]);
			gtk_label_set_text((GtkLabel*)label,argv[i]);
		}else{
			gtk_image_set_from_file((GtkImage*)image,"/usr/share/gfa/pixmaps/person.png");
			gtk_label_set_text((GtkLabel*)label,"/usr/share/gfa/pixmaps/person.png");
		}
	  }
	  if(strcmp(azColName[i],"Birth") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)birth,argv[i]);
	  }
	  if(strcmp(azColName[i],"Web") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)web,argv[i]);
	  }
	  if(strcmp(azColName[i],"Icq") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)icq,argv[i]);
	  }
	  if(strcmp(azColName[i],"Yahoo") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)yahoo,argv[i]);
	  }
	  if(strcmp(azColName[i],"Msn") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)msn,argv[i]);
	  }
	  if(strcmp(azColName[i],"Workphone") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)workphone,argv[i]);
	  }
	  if(strcmp(azColName[i],"Workmobile") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)workmobile,argv[i]);
	  }
	  if(strcmp(azColName[i],"Workemail") == 0)
	  {
		gtk_entry_set_text((GtkEntry*)workemail,argv[i]);
	  }
  }
  return 0;
}

void
on_addresscombobox_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	char* text = gtk_combo_box_get_active_text(combobox);
	const char* div = ",";
	char* lname = strtok(text, div);
	char* fname = strtok(NULL,div);
	fname = g_strchug(fname);

	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;

	char* home = getenv("HOME");
		
	char path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	char query[1024];
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
		
	char path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	GtkWidget* lastname = lookup_widget((GtkWidget*)button, "lastnameentry");
	GtkWidget* firstname = lookup_widget((GtkWidget*)button, "firstnameentry");
	GtkWidget* street = lookup_widget((GtkWidget*)button, "streetentry");
	GtkWidget* no = lookup_widget((GtkWidget*)button, "noentry");
	GtkWidget* zip = lookup_widget((GtkWidget*)button, "zipentry");
	GtkWidget* city = lookup_widget((GtkWidget*)button, "cityentry");
	GtkWidget* phone = lookup_widget((GtkWidget*)button, "phoneentry");
	GtkWidget* mobile = lookup_widget((GtkWidget*)button, "mobileentry");
	GtkWidget* email = lookup_widget((GtkWidget*)button, "emailentry");
	GtkWidget* label = lookup_widget((GtkWidget*)button, "url");
	GtkWidget* birth = lookup_widget((GtkWidget*)button, "birthdateentry");
	GtkWidget* web = lookup_widget((GtkWidget*)button, "webentry");
	GtkWidget* icq = lookup_widget((GtkWidget*)button, "icqentry");
	GtkWidget* yahoo = lookup_widget((GtkWidget*)button, "yahooentry");
	GtkWidget* msn = lookup_widget((GtkWidget*)button, "msnentry");
	GtkWidget* workphone = lookup_widget((GtkWidget*)button, "workphoneentry");
	GtkWidget* workmobile = lookup_widget((GtkWidget*)button, "workmobileentry");
	GtkWidget* workemail = lookup_widget((GtkWidget*)button, "workemailentry");

	const char* lname = gtk_entry_get_text((GtkEntry*)lastname);
	const char* fname = gtk_entry_get_text((GtkEntry*)firstname);
	const char* str = gtk_entry_get_text((GtkEntry*)street);
	const char* n = gtk_entry_get_text((GtkEntry*)no);
	const char* z = gtk_entry_get_text((GtkEntry*)zip);
	const char* c = gtk_entry_get_text((GtkEntry*)city);
	const char* p = gtk_entry_get_text((GtkEntry*)phone);
	const char* m = gtk_entry_get_text((GtkEntry*)mobile);
	const char* e = gtk_entry_get_text((GtkEntry*)email);
	const char* u = gtk_label_get_text((GtkLabel*)label);
	const char* b = gtk_entry_get_text((GtkEntry*)birth);
	const char* w = gtk_entry_get_text((GtkEntry*)web);
	const char* i = gtk_entry_get_text((GtkEntry*)icq);
	const char* y = gtk_entry_get_text((GtkEntry*)yahoo);
	const char* ms = gtk_entry_get_text((GtkEntry*)msn);
	const char* wp = gtk_entry_get_text((GtkEntry*)workphone);
	const char* wm = gtk_entry_get_text((GtkEntry*)workmobile);
	const char* we = gtk_entry_get_text((GtkEntry*)workemail);

	if (strlen(lname) == 0 || strlen(fname) == 0)
	{
		GtkWidget* dialog = create_dialog2();
		int result = gtk_dialog_run (GTK_DIALOG (dialog));
  	
  		gtk_widget_destroy (dialog);
	}else{

		char copy[1024];
		sprintf(copy,"cp -f '%s' '%s'",u, path);
		printf("%s\n",copy);//system(copy);

		char* imagefile = strtok(u,"/");
		char* temp;
		while(imagefile != NULL)
		{
			strcpy(temp,imagefile);
			imagefile = strtok(NULL,"/");
		}
		char img[1024];
		g_sprintf(img, "%s/%s",path,temp);

		char check[1024];
		sprintf(check, "SELECT * FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);

		rc = sqlite3_exec(db, check, check_insert, 0, &zErrMsg);
		char query[1024];

		if (rc == 0){
			rc = sqlite3_exec(db, "select * from gfa;", callback_insert, button, &zErrMsg);
			sprintf(query, "insert into gfa values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we); 
			rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
			rc = sqlite3_exec(db, "select Last_Name,First_Name from gfa ORDER BY Last_Name,First_Name ASC;", callback, button, &zErrMsg);

		}else{
			sprintf(query, "UPDATE gfa SET Last_Name = '%s',First_Name = '%s',Street = '%s',No = '%s',Zip = '%s',City = '%s',Phone = '%s',Mobile = '%s', Email = '%s', Image = '%s', Birth = '%s', Web ='%s', Icq = '%s', Yahoo = '%s', Msn = '%s', Workphone = '%s', Workmobile = '%s', Workemail = '%s' WHERE Last_Name = '%s' AND First_Name = '%s';", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we,lname,fname);
			rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
		}	
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

	char path[1024];
	sprintf(path,"%s/.gfa", home);

	mkdir(path,mode);
	char dbfile[1024];
	sprintf(dbfile,"%s/.gfa/gfa.db", home);


	rc = sqlite3_open(dbfile,&db);
	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS gfa(Last_Name char(50), First_Name char(50), Street char(100), No char(10), Zip char(10), City char(50), Phone char(30), Mobile char(30), Email char(200), Image char(1024), Birth char(30), Web char(200), Icq char(20), Yahoo char(20), Msn char(50), Workphone char(30), Workmobile char(30), Workemail char(200)) ;", NULL, 0, &zErrMsg);

	rc = sqlite3_exec(db, "SELECT * FROM gfa;",oldcheck,db,&zErrMsg);

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
		
	char path[1024];
	sprintf(path,"%s/.gfa", home);
	
	char filename[1024];
	sprintf(filename, "%s/gfa.db",path);

	rc = sqlite3_open(filename, &db);

	GtkWidget* lastname = lookup_widget((GtkWidget*)button, "lastnameentry");
	GtkWidget* firstname = lookup_widget((GtkWidget*)button, "firstnameentry");

	const char* lname = gtk_entry_get_text((GtkEntry*)lastname);
	const char* fname = gtk_entry_get_text((GtkEntry*)firstname);


	char del_file[1024];
	sprintf(del_file, "SELECT Image FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);
	


	char del[1024];
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
		GtkWidget* combo = lookup_widget((GtkWidget*)button, "addresscombobox");
		int position = gtk_combo_box_get_active((GtkComboBox*)combo);

		gtk_combo_box_remove_text((GtkComboBox*)combo, position);

		GtkWidget* lastname = lookup_widget((GtkWidget*)button, "lastnameentry");
		GtkWidget* firstname = lookup_widget((GtkWidget*)button, "firstnameentry");
		GtkWidget* street = lookup_widget((GtkWidget*)button, "streetentry");
		GtkWidget* no = lookup_widget((GtkWidget*)button, "noentry");
		GtkWidget* zip = lookup_widget((GtkWidget*)button, "zipentry");
		GtkWidget* city = lookup_widget((GtkWidget*)button, "cityentry");
		GtkWidget* phone = lookup_widget((GtkWidget*)button, "phoneentry");
		GtkWidget* mobile = lookup_widget((GtkWidget*)button, "mobileentry");
		GtkWidget* email = lookup_widget((GtkWidget*)button, "emailentry");
		GtkWidget* label = lookup_widget((GtkWidget*)button, "url");
		GtkWidget* image = lookup_widget((GtkWidget*)button, "buddy");
		GtkWidget* birth = lookup_widget((GtkWidget*)button, "birthdateentry");
		GtkWidget* web = lookup_widget((GtkWidget*)button, "webentry");
		GtkWidget* icq = lookup_widget((GtkWidget*)button, "icqentry");
		GtkWidget* yahoo = lookup_widget((GtkWidget*)button, "yahooentry");
		GtkWidget* msn = lookup_widget((GtkWidget*)button, "msnentry");
		GtkWidget* workphone = lookup_widget((GtkWidget*)button, "workphoneentry");
		GtkWidget* workmobile = lookup_widget((GtkWidget*)button, "workmobileentry");
		GtkWidget* workemail = lookup_widget((GtkWidget*)button, "workemailentry");
	
		gtk_entry_set_text((GtkEntry*)lastname,"");
		gtk_entry_set_text((GtkEntry*)firstname,"");
		gtk_entry_set_text((GtkEntry*)street,"");
		gtk_entry_set_text((GtkEntry*)no,"");
		gtk_entry_set_text((GtkEntry*)zip,"");
		gtk_entry_set_text((GtkEntry*)city,"");
		gtk_entry_set_text((GtkEntry*)phone,"");
		gtk_entry_set_text((GtkEntry*)mobile,"");
		gtk_entry_set_text((GtkEntry*)email,"");
		gtk_label_set_text((GtkLabel*)label,"/usr/share/gfa/pixmaps/person.png");
		gtk_image_set_from_file((GtkImage*)image,"/usr/share/gfa/pixmaps/person.png");
		gtk_entry_set_text((GtkEntry*)birth,"");
		gtk_entry_set_text((GtkEntry*)web,"");
		gtk_entry_set_text((GtkEntry*)icq,"");
		gtk_entry_set_text((GtkEntry*)yahoo,"");
		gtk_entry_set_text((GtkEntry*)msn,"");
		gtk_entry_set_text((GtkEntry*)workphone,"");
		gtk_entry_set_text((GtkEntry*)workmobile,"");
		gtk_entry_set_text((GtkEntry*)workemail,"");
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
		GtkWidget* combo = lookup_widget((GtkWidget*)button, "addresscombobox");

		GtkWidget* lastname = lookup_widget((GtkWidget*)button, "lastnameentry");
		GtkWidget* firstname = lookup_widget((GtkWidget*)button, "firstnameentry");
		GtkWidget* street = lookup_widget((GtkWidget*)button, "streetentry");
		GtkWidget* no = lookup_widget((GtkWidget*)button, "noentry");
		GtkWidget* zip = lookup_widget((GtkWidget*)button, "zipentry");
		GtkWidget* city = lookup_widget((GtkWidget*)button, "cityentry");
		GtkWidget* phone = lookup_widget((GtkWidget*)button, "phoneentry");
		GtkWidget* mobile = lookup_widget((GtkWidget*)button, "mobileentry");
		GtkWidget* email = lookup_widget((GtkWidget*)button, "emailentry");
		GtkWidget* label = lookup_widget((GtkWidget*)button, "url");
		GtkWidget* image = lookup_widget((GtkWidget*)button, "buddy");
		GtkWidget* birth = lookup_widget((GtkWidget*)button, "birthdateentry");
		GtkWidget* web = lookup_widget((GtkWidget*)button, "webentry");
		GtkWidget* icq = lookup_widget((GtkWidget*)button, "icqentry");
		GtkWidget* yahoo = lookup_widget((GtkWidget*)button, "yahooentry");
		GtkWidget* msn = lookup_widget((GtkWidget*)button, "msnentry");
		GtkWidget* workphone = lookup_widget((GtkWidget*)button, "workphoneentry");
		GtkWidget* workmobile = lookup_widget((GtkWidget*)button, "workmobileentry");
		GtkWidget* workemail = lookup_widget((GtkWidget*)button, "workemailentry");

		gtk_entry_set_text((GtkEntry*)lastname,"");
		gtk_entry_set_text((GtkEntry*)firstname,"");
		gtk_entry_set_text((GtkEntry*)street,"");
		gtk_entry_set_text((GtkEntry*)no,"");
		gtk_entry_set_text((GtkEntry*)zip,"");
		gtk_entry_set_text((GtkEntry*)city,"");
		gtk_entry_set_text((GtkEntry*)phone,"");
		gtk_entry_set_text((GtkEntry*)mobile,"");
		gtk_entry_set_text((GtkEntry*)email,"");
		gtk_label_set_text((GtkLabel*)label,"/usr/share/gfa/pixmaps/person.png");
		gtk_image_set_from_file((GtkImage*)image,"/usr/share/gfa/pixmaps/person.png");
		gtk_entry_set_text((GtkEntry*)birth,"");
		gtk_entry_set_text((GtkEntry*)web,"");
		gtk_entry_set_text((GtkEntry*)icq,"");
		gtk_entry_set_text((GtkEntry*)yahoo,"");
		gtk_entry_set_text((GtkEntry*)msn,"");
		gtk_entry_set_text((GtkEntry*)workphone,"");
		gtk_entry_set_text((GtkEntry*)workmobile,"");
		gtk_entry_set_text((GtkEntry*)workemail,"");
		
		gtk_combo_box_set_active((GtkComboBox*)combo,-1);
}


void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget((GtkWidget*)menuitem, "newbutton");
	on_newbutton_clicked((GtkButton*)button, NULL);
}


void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget((GtkWidget*)menuitem, "savebutton");
	on_savebutton_clicked((GtkButton*)button,NULL);
}


void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget((GtkWidget*)menuitem, "deletebutton");
	on_deletebutton_clicked((GtkButton*)button,NULL);
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
	gtk_file_chooser_add_filter((GtkFileChooser*)chooser,filter);
	int result = gtk_dialog_run(GTK_DIALOG(chooser));
	char *filename;
	GtkWidget* image = lookup_widget((GtkWidget*)button, "buddy");
	GtkWidget* label = lookup_widget((GtkWidget*)button, "url");

	switch (result)
  	{
      	case GTK_RESPONSE_OK:
    		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
		gtk_image_set_from_file((GtkImage*)image,filename);
		gtk_label_set_text((GtkLabel*)label,filename);
		break;
	
	case 123:
		gtk_image_set_from_file((GtkImage*)image,"/usr/share/gfa/pixmaps/person.png");
		gtk_label_set_text((GtkLabel*)label,"/usr/share/gfa/pixmaps/person.png");
		break;
	
	default:
		break;
	}

	gtk_widget_destroy(chooser);
}

void
expander_callback (GObject    *object,
                   GParamSpec *param_spec,
                   gpointer    user_data)
{
  GtkExpander *expander;

  expander = GTK_EXPANDER (object);
  GtkWidget* label = lookup_widget((GtkWidget*)expander, "label25");

  if (gtk_expander_get_expanded (expander))
    {
	    gtk_label_set_text((GtkLabel*)label,"less fields");
    }
  else
    {
	    gtk_label_set_text((GtkLabel*)label,"more fields");
    }
}

void
on_calendar_day_selected_double_click  (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	GtkWidget* button = (GtkWidget*) user_data;
	GtkWidget* birth = lookup_widget(button, "birthdateentry");
	int year;
	int month;
	int day;
	gtk_calendar_get_date(calendar,&year,&month,&day);
	char date[1024];
	sprintf(date,"%i/%i/%i",month+1,day,year);
	gtk_entry_set_text(GTK_ENTRY(birth), date);

	GtkWidget* dlg = lookup_widget((GtkWidget*)calendar, "caldialog");
	gtk_widget_destroy(dlg);
}

void
on_datebutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkDialog* date = create_caldialog();
	GtkWidget* cal = lookup_widget((GtkWidget*)date, "calendar");
 
	g_signal_connect ((gpointer)cal, "day_selected_double_click",
                    G_CALLBACK (on_calendar_day_selected_double_click),
                    button);

	gtk_dialog_run (GTK_DIALOG(date));
}

