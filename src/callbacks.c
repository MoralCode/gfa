#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>

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
		g_strlcat(combotext,argv[i],1024);
		//strcat(combotext, argv[i]);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo), combotext);
	  }
  }
  return 0;
}


static int callback_group(void *groupcombo, int argc, char **argv, char **azColName)
{
 
  GtkWidget* combo = (GtkWidget*) groupcombo;
  GtkWidget* combogroup = lookup_widget(combo, "comboboxgroup");

  int i;
  char combotext[1024];
  for(i=0; i<argc; i++){
	   if(strcmp(azColName[i],"group_name") == 0)
	  {
		//g_strlcat(combotext,argv[i],1024);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo), argv[i]);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combogroup), argv[i]);
	  }
  }
  return 0;
}

static int callback_change(void *addresscombo, int argc, char **argv, char **azColName)
{
  GtkWidget* combo = (GtkWidget*) addresscombo;

  int i;
  char combotext[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Last_Name") == 0)
	  {
		sprintf(combotext, "%s, ", argv[i]);
	  }
	  if(strcmp(azColName[i],"First_Name") == 0)
	  {
		g_strlcat(combotext,argv[i],1024);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo), combotext);
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
	  gtk_combo_box_remove_text (GTK_COMBO_BOX(combo), i);
  }
  return 0;
}

static 
int callback_id(void *id, int argc, char **argv, char **azColName)
{
	strcpy(id,argv[0]);
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
  if (!g_strrstr(del, "person.png")){
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
 
  GtkWidget* btn = GTK_WIDGET(combobox);
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
  GtkWidget* groupcombo = lookup_widget(btn, "comboboxgroup");
  GtkWidget* groupselect = lookup_widget(btn, "groupcombobox");

  const char* active_group = gtk_combo_box_get_active_text(GTK_COMBO_BOX(groupselect));
  int active_group_id = gtk_combo_box_get_active(GTK_COMBO_BOX(groupselect));


    
  int i;
  char entrytext[1024];
  for(i=0; i<argc; i++){
	  if(strcmp(azColName[i],"Last_Name") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(lastname),argv[i]);
	  }
	  if(strcmp(azColName[i],"First_Name") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(firstname),argv[i]);
	  }
	  if(strcmp(azColName[i],"Street") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(street),argv[i]);
	  }
	  if(strcmp(azColName[i],"No") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(no),argv[i]);
	  }
	  if(strcmp(azColName[i],"Zip") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(zip),argv[i]);
	  }
	  if(strcmp(azColName[i],"City") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(city),argv[i]);
	  }
	  if(strcmp(azColName[i],"Phone") == 0)
	  {
	       gtk_entry_set_text(GTK_ENTRY(phone),argv[i]);
	  }
	  if(strcmp(azColName[i],"Mobile") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(mobile),argv[i]);
	  }
	  if(strcmp(azColName[i],"Email") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(email),argv[i]);
	  }
	  if(strcmp(azColName[i],"Image")==0)
	  {
		if(argv[i] != NULL)
		{
			gtk_image_set_from_file(GTK_IMAGE(image),argv[i]);
			gtk_label_set_text(GTK_LABEL(label),argv[i]);
		}else{
			gtk_image_set_from_file(GTK_IMAGE(image),"/usr/share/gfa/pixmaps/person.png");
			gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");
		}
	  }
	  if(strcmp(azColName[i],"Birth") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(birth),argv[i]);
	  }
	  if(strcmp(azColName[i],"Web") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(web),argv[i]);
	  }
	  if(strcmp(azColName[i],"Icq") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(icq),argv[i]);
	  }
	  if(strcmp(azColName[i],"Yahoo") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(yahoo),argv[i]);
	  }
	  if(strcmp(azColName[i],"Msn") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(msn),argv[i]);
	  }
	  if(strcmp(azColName[i],"Workphone") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(workphone),argv[i]);
	  }
	  if(strcmp(azColName[i],"Workmobile") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(workmobile),argv[i]);
	  }
	  if(strcmp(azColName[i],"Workemail") == 0)
	  {
		gtk_entry_set_text(GTK_ENTRY(workemail),argv[i]);
	  }
	   if(strcmp(azColName[i],"Groups") == 0)
	  {
		  if ( !(strcmp(active_group,"All") == 0) )
		  {
			  gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),active_group_id-1);
		  } 
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

	GtkWidget* lastname = lookup_widget(GTK_WIDGET(button), "lastnameentry");
	GtkWidget* firstname = lookup_widget(GTK_WIDGET(button), "firstnameentry");
	GtkWidget* street = lookup_widget(GTK_WIDGET(button), "streetentry");
	GtkWidget* no = lookup_widget(GTK_WIDGET(button), "noentry");
	GtkWidget* zip = lookup_widget(GTK_WIDGET(button), "zipentry");
	GtkWidget* city = lookup_widget(GTK_WIDGET(button), "cityentry");
	GtkWidget* phone = lookup_widget(GTK_WIDGET(button), "phoneentry");
	GtkWidget* mobile = lookup_widget(GTK_WIDGET(button), "mobileentry");
	GtkWidget* email = lookup_widget(GTK_WIDGET(button), "emailentry");
	GtkWidget* label = lookup_widget(GTK_WIDGET(button), "url");
	GtkWidget* birth = lookup_widget(GTK_WIDGET(button), "birthdateentry");
	GtkWidget* web = lookup_widget(GTK_WIDGET(button), "webentry");
	GtkWidget* icq = lookup_widget(GTK_WIDGET(button), "icqentry");
	GtkWidget* yahoo = lookup_widget(GTK_WIDGET(button), "yahooentry");
	GtkWidget* msn = lookup_widget(GTK_WIDGET(button), "msnentry");
	GtkWidget* workphone = lookup_widget(GTK_WIDGET(button), "workphoneentry");
	GtkWidget* workmobile = lookup_widget(GTK_WIDGET(button), "workmobileentry");
	GtkWidget* workemail = lookup_widget(GTK_WIDGET(button), "workemailentry");
	GtkWidget* group = lookup_widget(GTK_WIDGET(button), "comboboxgroup");
	GtkWidget* addresscombobox = lookup_widget(GTK_WIDGET(button), "addresscombobox");
	GtkWidget* image = lookup_widget(GTK_WIDGET(button), "buddy");

	int comboid = gtk_combo_box_get_active(GTK_COMBO_BOX(addresscombobox));

	const char* groupname = gtk_combo_box_get_active_text(GTK_COMBO_BOX(group));
	char id[1024];		
	char id_request[1024];
	sprintf(id_request, "select group_id from gfa_groups where group_name = '%s';", groupname);
	rc = sqlite3_exec(db, id_request, callback_id, &id, &zErrMsg);


	GtkWidget* active_group = lookup_widget(GTK_WIDGET(button), "groupcombobox");

	const char* activegroupname = gtk_combo_box_get_active_text(GTK_COMBO_BOX(active_group));
	char id_active[1024];		
	char id_request_active[1024];
	sprintf(id_request_active, "select group_id from gfa_groups where group_name = '%s';", activegroupname);
	rc = sqlite3_exec(db, id_request_active, callback_id, &id_active, &zErrMsg);



	const char* lname = gtk_entry_get_text(GTK_ENTRY(lastname));
	const char* fname = gtk_entry_get_text(GTK_ENTRY(firstname));
	const char* str = gtk_entry_get_text(GTK_ENTRY(street));
	const char* n = gtk_entry_get_text(GTK_ENTRY(no));
	const char* z = gtk_entry_get_text(GTK_ENTRY(zip));
	const char* c = gtk_entry_get_text(GTK_ENTRY(city));
	const char* p = gtk_entry_get_text(GTK_ENTRY(phone));
	const char* m = gtk_entry_get_text(GTK_ENTRY(mobile));
	const char* e = gtk_entry_get_text(GTK_ENTRY(email));
	const char* u = gtk_label_get_text(GTK_LABEL(label));
	const char* b = gtk_entry_get_text(GTK_ENTRY(birth));
	const char* w = gtk_entry_get_text(GTK_ENTRY(web));
	const char* i = gtk_entry_get_text(GTK_ENTRY(icq));
	const char* y = gtk_entry_get_text(GTK_ENTRY(yahoo));
	const char* ms = gtk_entry_get_text(GTK_ENTRY(msn));
	const char* wp = gtk_entry_get_text(GTK_ENTRY(workphone));
	const char* wm = gtk_entry_get_text(GTK_ENTRY(workmobile));
	const char* we = gtk_entry_get_text(GTK_ENTRY(workemail));

	if (strlen(lname) == 0 || strlen(fname) == 0)
	{
		GtkWidget* dialog = create_dialog2();
		int result = gtk_dialog_run (GTK_DIALOG (dialog));
  	
  		gtk_widget_destroy (dialog);
	}else{

		char copy[1024];
		sprintf(copy,"cp -f '%s' '%s'",u, path);
		system(copy);

		char* imagefile = (char*)(strtok((char*)(u),"/"));
		char* temp;
		while(imagefile != NULL)
		{
			strcpy(temp,imagefile);
			imagefile = (char*)(strtok(NULL,"/"));
		}
		char img[1024];
		g_sprintf(img, "%s/%s",path,temp);

		char check[1024];
		sprintf(check, "SELECT * FROM gfa WHERE Last_Name = '%s' AND First_Name = '%s';", lname, fname);

		rc = sqlite3_exec(db, check, check_insert, 0, &zErrMsg);
		char query[1024];

		if (rc == 0)
		{
			if(strcmp(activegroupname,"All")==0)
			{
				rc = sqlite3_exec(db, "select * from gfa;", callback_insert, button, &zErrMsg);
				sprintf(query, "insert into gfa values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we,id); 
				rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
				char execute[1024];
				sprintf(execute, "select Last_Name,First_Name from gfa ORDER BY Last_Name,First_Name ASC", id_active);
				rc = sqlite3_exec(db, execute, callback, button, &zErrMsg);
			}else{
				rc = sqlite3_exec(db, "select * from gfa;", callback_insert, button, &zErrMsg);
				sprintf(query, "insert into gfa values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we,id); 
				rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
				char execute[1024];
				sprintf(execute, "select Last_Name,First_Name from gfa where Groups = '%s' ORDER BY Last_Name,First_Name ASC", id_active);
				rc = sqlite3_exec(db, execute, callback, button, &zErrMsg);	
			}
		}else{
			if(strcmp(activegroupname,"All")==0)
			{
				rc = sqlite3_exec(db, "select * from gfa;", callback_insert, button, &zErrMsg);
				sprintf(query, "UPDATE gfa SET Last_Name = '%s',First_Name = '%s',Street = '%s',No = '%s',Zip = '%s',City = '%s',Phone = '%s',Mobile = '%s', Email = '%s', Image = '%s', Birth = '%s', Web ='%s', Icq = '%s', Yahoo = '%s', Msn = '%s', Workphone = '%s', Workmobile = '%s', Workemail = '%s', Groups = '%s' WHERE Last_Name = '%s' AND First_Name = '%s';", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we,id,lname,fname);
				rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
			
				rc = sqlite3_exec(db, "select Last_Name,First_Name from gfa ORDER BY Last_Name,First_Name ASC;", callback, button, &zErrMsg);
			}else{
				rc = sqlite3_exec(db, "select * from gfa;", callback_insert, button, &zErrMsg);
				sprintf(query, "UPDATE gfa SET Last_Name = '%s',First_Name = '%s',Street = '%s',No = '%s',Zip = '%s',City = '%s',Phone = '%s',Mobile = '%s', Email = '%s', Image = '%s', Birth = '%s', Web ='%s', Icq = '%s', Yahoo = '%s', Msn = '%s', Workphone = '%s', Workmobile = '%s', Workemail = '%s', Groups = '%s' WHERE Last_Name = '%s' AND First_Name = '%s';", lname,fname,str,n,z,c,p,m,e,img,b,w,i,y,ms,wp,wm,we,id,lname,fname);
				rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
			
				char execute[1024];
				sprintf(execute, "select Last_Name,First_Name from gfa where Groups = '%s' ORDER BY Last_Name,First_Name ASC;", id_active);
				rc = sqlite3_exec(db, execute, callback, button, &zErrMsg);
			}
		}	
		sqlite3_close(db);
		gtk_combo_box_set_active(GTK_COMBO_BOX(addresscombobox),comboid);		
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

	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS gfa_groups(group_id INTEGER PRIMARY KEY AUTOINCREMENT, group_name char(100));", NULL, 0, &zErrMsg);

	rc = sqlite3_exec(db,"insert into gfa_groups (group_id,group_name) values('1','General');",NULL,0,&zErrMsg);
	rc = sqlite3_exec(db, "SELECT * FROM gfa;",oldcheck,db,&zErrMsg);
	rc = sqlite3_exec(db,"alter table gfa add column Groups INTEGER DEFAULT '1';", NULL, 0, &zErrMsg);

	rc = sqlite3_exec(db, "select Last_Name,First_Name from gfa ORDER BY Last_Name,First_Name ASC;", callback, widget, &zErrMsg);
	
	GtkWidget* combo = lookup_widget(widget, "groupcombobox");
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo),"All");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo),0);
	rc = sqlite3_exec(db, "select group_name from gfa_groups;", callback_group, combo, &zErrMsg);

	GtkWidget* combogroup = lookup_widget(combo, "comboboxgroup");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combogroup),0);

	
	sqlite3_close(db);
	
	GtkWidget* label = lookup_widget(widget, "url");
	gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");

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

	GtkWidget* lastname = lookup_widget(GTK_WIDGET(button), "lastnameentry");
	GtkWidget* firstname = lookup_widget(GTK_WIDGET(button), "firstnameentry");

	const char* lname = gtk_entry_get_text(GTK_ENTRY(lastname));
	const char* fname = gtk_entry_get_text(GTK_ENTRY(firstname));


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
		GtkWidget* combo = lookup_widget(GTK_WIDGET(button), "addresscombobox");
		int position = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));

		gtk_combo_box_remove_text(GTK_COMBO_BOX(combo), position);

		GtkWidget* lastname = lookup_widget(GTK_WIDGET(button), "lastnameentry");
		GtkWidget* firstname = lookup_widget(GTK_WIDGET(button), "firstnameentry");
		GtkWidget* street = lookup_widget(GTK_WIDGET(button), "streetentry");
		GtkWidget* no = lookup_widget(GTK_WIDGET(button), "noentry");
		GtkWidget* zip = lookup_widget(GTK_WIDGET(button), "zipentry");
		GtkWidget* city = lookup_widget(GTK_WIDGET(button), "cityentry");
		GtkWidget* phone = lookup_widget(GTK_WIDGET(button), "phoneentry");
		GtkWidget* mobile = lookup_widget(GTK_WIDGET(button), "mobileentry");
		GtkWidget* email = lookup_widget(GTK_WIDGET(button), "emailentry");
		GtkWidget* label = lookup_widget(GTK_WIDGET(button), "url");
		GtkWidget* birth = lookup_widget(GTK_WIDGET(button), "birthdateentry");
		GtkWidget* web = lookup_widget(GTK_WIDGET(button), "webentry");
		GtkWidget* icq = lookup_widget(GTK_WIDGET(button), "icqentry");
		GtkWidget* yahoo = lookup_widget(GTK_WIDGET(button), "yahooentry");
		GtkWidget* msn = lookup_widget(GTK_WIDGET(button), "msnentry");
		GtkWidget* workphone = lookup_widget(GTK_WIDGET(button), "workphoneentry");
		GtkWidget* workmobile = lookup_widget(GTK_WIDGET(button), "workmobileentry");
		GtkWidget* workemail = lookup_widget(GTK_WIDGET(button), "workemailentry");
		GtkWidget* image = lookup_widget(GTK_WIDGET(button), "buddy");
		GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(button), "comboboxgroup");

	
		gtk_entry_set_text(GTK_ENTRY(lastname),"");
		gtk_entry_set_text(GTK_ENTRY(firstname),"");
		gtk_entry_set_text(GTK_ENTRY(street),"");
		gtk_entry_set_text(GTK_ENTRY(no),"");
		gtk_entry_set_text(GTK_ENTRY(zip),"");
		gtk_entry_set_text(GTK_ENTRY(city),"");
		gtk_entry_set_text(GTK_ENTRY(phone),"");
		gtk_entry_set_text(GTK_ENTRY(mobile),"");
		gtk_entry_set_text(GTK_ENTRY(email),"");
		gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");
		gtk_image_set_from_file(GTK_IMAGE(image),"/usr/share/gfa/pixmaps/person.png");
		gtk_entry_set_text(GTK_ENTRY(birth),"");
		gtk_entry_set_text(GTK_ENTRY(web),"");
		gtk_entry_set_text(GTK_ENTRY(icq),"");
		gtk_entry_set_text(GTK_ENTRY(yahoo),"");
		gtk_entry_set_text(GTK_ENTRY(msn),"");
		gtk_entry_set_text(GTK_ENTRY(workphone),"");
		gtk_entry_set_text(GTK_ENTRY(workmobile),"");
		gtk_entry_set_text(GTK_ENTRY(workemail),"");
		gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),0);

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
	GtkWidget* combo = lookup_widget(GTK_WIDGET(button), "addresscombobox");
	GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(button), "comboboxgroup");
	GtkWidget* lastname = lookup_widget(GTK_WIDGET(button), "lastnameentry");
	GtkWidget* firstname = lookup_widget(GTK_WIDGET(button), "firstnameentry");
	GtkWidget* street = lookup_widget(GTK_WIDGET(button), "streetentry");
	GtkWidget* no = lookup_widget(GTK_WIDGET(button), "noentry");
	GtkWidget* zip = lookup_widget(GTK_WIDGET(button), "zipentry");
	GtkWidget* city = lookup_widget(GTK_WIDGET(button), "cityentry");
	GtkWidget* phone = lookup_widget(GTK_WIDGET(button), "phoneentry");
	GtkWidget* mobile = lookup_widget(GTK_WIDGET(button), "mobileentry");
	GtkWidget* email = lookup_widget(GTK_WIDGET(button), "emailentry");
	GtkWidget* label = lookup_widget(GTK_WIDGET(button), "url");
	GtkWidget* birth = lookup_widget(GTK_WIDGET(button), "birthdateentry");
	GtkWidget* web = lookup_widget(GTK_WIDGET(button), "webentry");
	GtkWidget* icq = lookup_widget(GTK_WIDGET(button), "icqentry");
	GtkWidget* yahoo = lookup_widget(GTK_WIDGET(button), "yahooentry");
	GtkWidget* msn = lookup_widget(GTK_WIDGET(button), "msnentry");
	GtkWidget* workphone = lookup_widget(GTK_WIDGET(button), "workphoneentry");
	GtkWidget* workmobile = lookup_widget(GTK_WIDGET(button), "workmobileentry");
	GtkWidget* workemail = lookup_widget(GTK_WIDGET(button), "workemailentry");
	GtkWidget* image = lookup_widget(GTK_WIDGET(button), "buddy");
	
	gtk_entry_set_text(GTK_ENTRY(lastname),"");
	gtk_entry_set_text(GTK_ENTRY(firstname),"");
	gtk_entry_set_text(GTK_ENTRY(street),"");
	gtk_entry_set_text(GTK_ENTRY(no),"");
	gtk_entry_set_text(GTK_ENTRY(zip),"");
	gtk_entry_set_text(GTK_ENTRY(city),"");
	gtk_entry_set_text(GTK_ENTRY(phone),"");
	gtk_entry_set_text(GTK_ENTRY(mobile),"");
	gtk_entry_set_text(GTK_ENTRY(email),"");
	gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");
	gtk_image_set_from_file(GTK_IMAGE(image),"/usr/share/gfa/pixmaps/person.png");
	gtk_entry_set_text(GTK_ENTRY(birth),"");
	gtk_entry_set_text(GTK_ENTRY(web),"");
	gtk_entry_set_text(GTK_ENTRY(icq),"");
	gtk_entry_set_text(GTK_ENTRY(yahoo),"");
	gtk_entry_set_text(GTK_ENTRY(msn),"");
	gtk_entry_set_text(GTK_ENTRY(workphone),"");
	gtk_entry_set_text(GTK_ENTRY(workmobile),"");
	gtk_entry_set_text(GTK_ENTRY(workemail),"");

	gtk_combo_box_set_active(GTK_COMBO_BOX(combo),-1);
	gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),0);

}


void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget(GTK_WIDGET(menuitem), "newbutton");
	on_newbutton_clicked(GTK_BUTTON(button), NULL);
}


void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget(GTK_WIDGET(menuitem), "savebutton");
	on_savebutton_clicked(GTK_BUTTON(button),NULL);
}


void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* button = lookup_widget(GTK_WIDGET(menuitem), "deletebutton");
	on_deletebutton_clicked(GTK_BUTTON(button),NULL);
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
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser),filter);
	int result = gtk_dialog_run(GTK_DIALOG(chooser));
	char *filename;
	GtkWidget* image = lookup_widget(GTK_WIDGET(button), "buddy");
	GtkWidget* label = lookup_widget(GTK_WIDGET(button), "url");

	switch (result)
  	{
      	case GTK_RESPONSE_OK:
    		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
		gtk_image_set_from_file(GTK_IMAGE(image),filename);
		gtk_label_set_text(GTK_LABEL(label),filename);
		break;
	
	case 123:
		gtk_image_set_from_file(GTK_IMAGE(image),"/usr/share/gfa/pixmaps/person.png");
		gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");
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
  GtkWidget* label = lookup_widget(GTK_WIDGET(expander), "label25");

  if (gtk_expander_get_expanded (expander))
    {
	    gtk_label_set_text(GTK_LABEL(label),"less fields");
    }
  else
    {
	    gtk_label_set_text(GTK_LABEL(label),"more fields");
    }
}

void
on_calendar_day_selected_double_click  (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	GtkWidget* button = GTK_WIDGET(user_data);
	GtkWidget* birth = lookup_widget(button, "birthdateentry");
	int year;
	int month;
	int day;
	gtk_calendar_get_date(calendar,&year,&month,&day);
	char date[1024];
	sprintf(date,"%i/%i/%i",month+1,day,year);
	gtk_entry_set_text(GTK_ENTRY(birth), date);

	GtkWidget* dlg = lookup_widget(GTK_WIDGET(calendar), "caldialog");
	gtk_widget_destroy(dlg);
}
 
void
on_datebutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* date = create_caldialog();
	GtkWidget* cal = lookup_widget(GTK_WIDGET(date), "calendar");
 
	g_signal_connect ((gpointer)cal, "day_selected_double_click",
                    G_CALLBACK (on_calendar_day_selected_double_click),
                    button);

	gtk_dialog_run (GTK_DIALOG(date));
}


void
on_group1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


static int callback_insert_group(void *groupcombo, int argc, char **argv, char **azColName)
{
  GtkWidget* combo = (GtkWidget*) groupcombo;
  GtkWidget* combogroup = lookup_widget(combo, "comboboxgroup");

  int i;
  for(i=0;i<argc;i++)
  {
	  gtk_combo_box_remove_text (GTK_COMBO_BOX(combo), i);
	  gtk_combo_box_remove_text (GTK_COMBO_BOX(combogroup), i);
  }

  return 0;
}

static int callback_change_group(void *addresscombo, int argc, char **argv, char **azColName)
{
  GtkWidget* combo = (GtkWidget*) addresscombo;
  
  int i;
  for(i=0;i<argc;i++)
  {
	  gtk_combo_box_remove_text (GTK_COMBO_BOX(combo), i);
  }
  return 0;
}


void
on_new_group_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* group = create_dialog4();
	int result = gtk_dialog_run (GTK_DIALOG(group));

	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;

	if(result == GTK_RESPONSE_OK)
	{
	
		char* home = getenv("HOME");
			
		char path[1024];
		sprintf(path,"%s/.gfa", home);
		
		char filename[1024];
		sprintf(filename, "%s/gfa.db",path);
	
		rc = sqlite3_open(filename, &db);
	
		GtkWidget* groupname = lookup_widget(GTK_WIDGET(group), "groupentry");
		const char* gname = gtk_entry_get_text(GTK_ENTRY(groupname));
		
		GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(menuitem), "groupcombobox");
		GtkWidget* combogroup = lookup_widget(GTK_WIDGET(menuitem), "comboboxgroup");
		int id = gtk_combo_box_get_active(GTK_COMBO_BOX(groupcombo));
		int group_id =  gtk_combo_box_get_active(GTK_COMBO_BOX(combogroup));
		gtk_combo_box_remove_text (GTK_COMBO_BOX(groupcombo), 0);
		rc = sqlite3_exec(db, "select * from gfa_groups;", callback_insert_group, groupcombo, &zErrMsg);

		char groupbuffer[1024];
		sprintf(groupbuffer, "insert into gfa_groups (group_name) values('%s');", gname);	
		rc = sqlite3_exec(db, groupbuffer, NULL, 0, &zErrMsg);
		gtk_combo_box_append_text(GTK_COMBO_BOX(groupcombo),"All");
		rc = sqlite3_exec(db, "select group_name from gfa_groups;", callback_group, groupcombo, &zErrMsg);

		gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),id);
		gtk_combo_box_set_active(GTK_COMBO_BOX(combogroup),group_id);
	}
	gtk_widget_destroy (group);

	sqlite3_close(db);


}


void
on_rename_group_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(menuitem), "groupcombobox");
	GtkWidget* combogroup = lookup_widget(GTK_WIDGET(menuitem), "comboboxgroup");
	int id = gtk_combo_box_get_active(GTK_COMBO_BOX(groupcombo));
	int group_id =  gtk_combo_box_get_active(GTK_COMBO_BOX(combogroup));
	const char* groupname = gtk_combo_box_get_active_text(GTK_COMBO_BOX(groupcombo));

	if(strcmp(groupname,"All") == 0 || strcmp(groupname,"General") == 0  ){
		GtkWidget* info = create_dialog6();
		gtk_dialog_run (GTK_DIALOG(info));
		gtk_widget_destroy (info);
	}else{
		GtkWidget* group = create_dialog5();		
		GtkWidget* entry = lookup_widget(GTK_WIDGET(group), "entry1");
		gtk_entry_set_text(GTK_ENTRY(entry), groupname);
		gtk_editable_select_region(GTK_EDITABLE(entry),0,-1);

		int result = gtk_dialog_run (GTK_DIALOG(group));

		sqlite3 *db;
		int rc;
		char *zErrMsg = 0;
	
		if(result == GTK_RESPONSE_OK)
		{
			char* home = getenv("HOME");
					
			char path[1024];
			sprintf(path,"%s/.gfa", home);
		
			char filename[1024];
			sprintf(filename, "%s/gfa.db",path);
			
			rc = sqlite3_open(filename, &db);


			const char* newname = gtk_entry_get_text(GTK_ENTRY(entry));
			rc = sqlite3_exec(db, "select * from gfa_groups;", callback_insert_group, groupcombo, &zErrMsg);

			char group[1024];
			sprintf(group, "UPDATE gfa_groups SET group_name = '%s' WHERE group_name = '%s';", newname, groupname);
			rc = sqlite3_exec(db, group, NULL, 0, &zErrMsg);
			gtk_combo_box_append_text(GTK_COMBO_BOX(groupcombo),"All");
			rc = sqlite3_exec(db, "select group_name from gfa_groups;", callback_group, groupcombo, &zErrMsg);
			sqlite3_close(db);
			gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),id);
			gtk_combo_box_set_active(GTK_COMBO_BOX(combogroup),group_id);


		}
		gtk_widget_destroy (group);
	}
}

void
on_delete_group_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(menuitem), "groupcombobox");
	GtkWidget* combogroup = lookup_widget(GTK_WIDGET(menuitem), "comboboxgroup");
	GtkWidget* addresscombo = lookup_widget(GTK_WIDGET(menuitem), "addresscombobox");
	const char* groupname = gtk_combo_box_get_active_text(GTK_COMBO_BOX(groupcombo));

	if(strcmp(groupname,"All") == 0 || strcmp(groupname,"General") == 0  ){
		GtkWidget* info = create_dialog7();
		gtk_dialog_run (GTK_DIALOG(info));
		gtk_widget_destroy (info);
	}else{
		sqlite3 *db;
		int rc;
		char *zErrMsg = 0;

		char* home = getenv("HOME");
					
		char path[1024];
		sprintf(path,"%s/.gfa", home);
		
		char filename[1024];
		sprintf(filename, "%s/gfa.db",path);
		
		rc = sqlite3_open(filename, &db);
	 	char id[1024];
		
		char id_request[1024];
		sprintf(id_request, "select group_id from gfa_groups where group_name = '%s';", groupname);
		rc = sqlite3_exec(db, id_request, callback_id, &id, &zErrMsg);

		GtkWidget* dialog = create_dialog8();
		int result = gtk_dialog_run (GTK_DIALOG(dialog));
		if (result == 1) //delete all contacts
		{
			char delete_contacts[1024];
			sprintf(delete_contacts, "DELETE FROM gfa WHERE Groups = '%s';", id);
			sqlite3_exec(db,delete_contacts,NULL,0,&zErrMsg);

			rc = sqlite3_exec(db, "select * from gfa_groups;", callback_insert_group, groupcombo, &zErrMsg);
			gtk_combo_box_append_text(GTK_COMBO_BOX(groupcombo),"All");

			char delete_group[1024];
			sprintf(delete_group, "DELETE FROM gfa_groups WHERE group_id = '%s';", id);
			sqlite3_exec(db,delete_group,NULL,0,&zErrMsg);

			rc = sqlite3_exec(db, "select group_name from gfa_groups;", callback_group, groupcombo, &zErrMsg);
			sqlite3_close(db);
			gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),0);
			gtk_combo_box_set_active(GTK_COMBO_BOX(combogroup),0);
			gtk_combo_box_set_active(GTK_COMBO_BOX(addresscombo),-1);
		}

		if ( result == 0 ) //move all contacts to general
		{
			char group[1024];
			sprintf(group, "UPDATE gfa SET Groups = '1' WHERE Groups = '%s';", id);
			rc = sqlite3_exec(db, group, NULL, 0, &zErrMsg);

			rc = sqlite3_exec(db, "select * from gfa_groups;", callback_insert_group, groupcombo, &zErrMsg);
			gtk_combo_box_append_text(GTK_COMBO_BOX(groupcombo),"All");

			char delete_group[1024];
			sprintf(delete_group, "DELETE FROM gfa_groups WHERE group_id = '%s';", id);
			sqlite3_exec(db,delete_group,NULL,0,&zErrMsg);

			rc = sqlite3_exec(db, "select group_name from gfa_groups;", callback_group, groupcombo, &zErrMsg);
			sqlite3_close(db);
			gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),0);
			gtk_combo_box_set_active(GTK_COMBO_BOX(combogroup),0);
			gtk_combo_box_set_active(GTK_COMBO_BOX(addresscombo),-1);
		}
		gtk_widget_destroy(dialog);
	}
}


void
on_groupcombobox_changed               (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GtkWidget* addresscombo = lookup_widget(GTK_WIDGET(combobox), "addresscombobox");
	const char* groupname = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox));

	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;
	
	char* home = getenv("HOME");
						
	char path[1024];
	sprintf(path,"%s/.gfa", home);
			
	char filename[1024];
	sprintf(filename, "%s/gfa.db",path);
			
	rc = sqlite3_open(filename, &db);

	if(strcmp(groupname,"All") == 0 )
	{
		char contacts[1024];
		rc = sqlite3_exec(db, "select * from gfa;", callback_change_group, addresscombo, &zErrMsg);
		rc = sqlite3_exec(db, "select * from gfa ORDER BY Last_Name,First_Name ASC;", callback_change, addresscombo, &zErrMsg);
	}else{
		char id[1024];
		
		char id_request[1024];
		sprintf(id_request, "select group_id from gfa_groups where group_name = '%s';", groupname);
		rc = sqlite3_exec(db, id_request, callback_id, &id, &zErrMsg);
	
		char contacts[1024];
		rc = sqlite3_exec(db, "select * from gfa;", callback_change_group, addresscombo, &zErrMsg);
	
		sprintf(contacts, "select * from gfa where Groups = '%s' ORDER BY Last_Name,First_Name ASC;",id);
		rc = sqlite3_exec(db, contacts, callback_change, addresscombo, &zErrMsg);
	}

	sqlite3_close(db);

	GtkWidget* lastname = lookup_widget(GTK_WIDGET(combobox), "lastnameentry");
	GtkWidget* firstname = lookup_widget(GTK_WIDGET(combobox), "firstnameentry");
	GtkWidget* street = lookup_widget(GTK_WIDGET(combobox), "streetentry");
	GtkWidget* no = lookup_widget(GTK_WIDGET(combobox), "noentry");
	GtkWidget* zip = lookup_widget(GTK_WIDGET(combobox), "zipentry");
	GtkWidget* city = lookup_widget(GTK_WIDGET(combobox), "cityentry");
	GtkWidget* phone = lookup_widget(GTK_WIDGET(combobox), "phoneentry");
	GtkWidget* mobile = lookup_widget(GTK_WIDGET(combobox), "mobileentry");
	GtkWidget* email = lookup_widget(GTK_WIDGET(combobox), "emailentry");
	GtkWidget* label = lookup_widget(GTK_WIDGET(combobox), "url");
	GtkWidget* birth = lookup_widget(GTK_WIDGET(combobox), "birthdateentry");
	GtkWidget* web = lookup_widget(GTK_WIDGET(combobox), "webentry");
	GtkWidget* icq = lookup_widget(GTK_WIDGET(combobox), "icqentry");
	GtkWidget* yahoo = lookup_widget(GTK_WIDGET(combobox), "yahooentry");
	GtkWidget* msn = lookup_widget(GTK_WIDGET(combobox), "msnentry");
	GtkWidget* workphone = lookup_widget(GTK_WIDGET(combobox), "workphoneentry");
	GtkWidget* workmobile = lookup_widget(GTK_WIDGET(combobox), "workmobileentry");
	GtkWidget* workemail = lookup_widget(GTK_WIDGET(combobox), "workemailentry");
	GtkWidget* image = lookup_widget(GTK_WIDGET(combobox), "buddy");
	GtkWidget* groupcombo = lookup_widget(GTK_WIDGET(combobox), "comboboxgroup");
	
	gtk_entry_set_text(GTK_ENTRY(lastname),"");
	gtk_entry_set_text(GTK_ENTRY(firstname),"");
	gtk_entry_set_text(GTK_ENTRY(street),"");
	gtk_entry_set_text(GTK_ENTRY(no),"");
	gtk_entry_set_text(GTK_ENTRY(zip),"");
	gtk_entry_set_text(GTK_ENTRY(city),"");
	gtk_entry_set_text(GTK_ENTRY(phone),"");
	gtk_entry_set_text(GTK_ENTRY(mobile),"");
	gtk_entry_set_text(GTK_ENTRY(email),"");
	gtk_label_set_text(GTK_LABEL(label),"/usr/share/gfa/pixmaps/person.png");
	gtk_image_set_from_file(GTK_IMAGE(image),"/usr/share/gfa/pixmaps/person.png");
	gtk_entry_set_text(GTK_ENTRY(birth),"");
	gtk_entry_set_text(GTK_ENTRY(web),"");
	gtk_entry_set_text(GTK_ENTRY(icq),"");
	gtk_entry_set_text(GTK_ENTRY(yahoo),"");
	gtk_entry_set_text(GTK_ENTRY(msn),"");
	gtk_entry_set_text(GTK_ENTRY(workphone),"");
	gtk_entry_set_text(GTK_ENTRY(workmobile),"");
	gtk_entry_set_text(GTK_ENTRY(workemail),"");
	gtk_combo_box_set_active(GTK_COMBO_BOX(groupcombo),0);

	gtk_combo_box_set_active(GTK_COMBO_BOX(addresscombo),-1);
}

