/*
 * protibadi_database.c
 *
 *  Created on: Nov 18, 2016
 *      Author: mansib
 */
#include "protibadi_service.h"

static int CreateTable(appdata_s *ad) {
	char *errorMsg;
	char *sql = "CREATE TABLE IF NOT EXISTS TestTable(KEY INTEGER PRIMARY KEY, NAME TEXT NOT NULL, PHONE TEXT NOT NULL, EMAIL TEXT NOT NULL);";

	int ret = sqlite3_exec(ad->db,sql,NULL,0,&errorMsg);

	dlog_print(DLOG_ERROR,LOG_TAG,errorMsg);

	return ret;
}

int n_count = 0, e_count = 0; //For passing to data processor
char num[10][30], mail[10][60];

static int db_read_cb(void *counter, int argc, char **argv, char **azColName)
{
	char buf[255];
	recdata_s* rd = malloc(sizeof(recdata_s));

	strcpy(rd->key, argv[0]);
	strcpy(rd->name, argv[1]);
	strcpy(rd->phone, argv[2]);
	strcpy(rd->email, argv[3]);
	/*sprintf(buf, "%s | %s | %s | %s", argv[0], argv[1], argv[2], argv[3]);
	dlog_print(DLOG_INFO,LOG_TAG,"Entry %s \n",buf);*/

	strcpy(num[n_count], argv[2]);
	strcpy(mail[e_count], argv[3]);
	n_count++; e_count++;

	/*elm_list_item_append(m_ad->list, buf, NULL, NULL, NULL, (void*)rd);
	elm_list_go(m_ad->list);*/

	return 0;
}

static int read_db(appdata_s *ad)
{
	char *sql = "select * from TestTable";
	int counter=0;
	char *ErrMsg;
	/*elm_list_clear(ad->list);*/
	//CLEANUP the table
	/*sqlite3_exec(ad->db, "delete from TestTable", NULL, NULL, &ErrMsg);
	sqlite3_exec(ad->db, "vacuum", NULL, NULL, &ErrMsg);*/

	int ret = sqlite3_exec(ad->db, sql, db_read_cb, &counter, &ErrMsg);
	dlog_print(DLOG_ERROR,LOG_TAG,ErrMsg);

	dlog_print(DLOG_DEBUG,LOG_TAG,"%d entries found", counter);

	return ret;
}

void init_db(appdata_s *ad) {
	sqlite3_shutdown();
	sqlite3_config(SQLITE_CONFIG_URI, 1);
	sqlite3_initialize();

	char * resource = app_get_data_path();

	int siz = strlen(resource) + 10;
	char * path = malloc(sizeof(char)*siz);
	memset(path,0,sizeof(path));
	strncat(path, resource, siz);
	strncat(path, "test.db", siz);
	/*char *path = "/opt/usr/apps/org.example.protibadi_service/data/test.db";*/
	sqlite3_open(path, &ad->db);
	free(path);

	CreateTable(ad);
}

static int InsertRecord(appdata_s *ad, unsigned char *name, unsigned char *number, char *email)
{
	char sql[256];
	char *errorMsg;

	snprintf(sql, 256, "INSERT INTO TestTable VALUES(NULL,\'%s\',\'%s\',\'%s\');", name, number, email);

	int ret = sqlite3_exec(ad->db, sql, NULL, 0, &errorMsg);

	dlog_print(DLOG_ERROR,LOG_TAG,errorMsg);

	return ret;
}

void add_contact(unsigned char *name, unsigned char *number, unsigned char *email) {
	InsertRecord(m_ad, name, number, email);
}

void list_contacts(int *num_count, int *mail_count, char *numbers[], char *emails[]) { //
	read_db(m_ad);
	*num_count = n_count;
	*mail_count = e_count;

	//Copying all number and emails to data processor
	int i;
	for (i = 0; i < n_count; ++i) {
		numbers[i] = num[i];
		emails[i] = mail[i];
	}
}
