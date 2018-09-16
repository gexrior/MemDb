#include"table.h"
#include"Buffer.h"
#include"schema.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<pthread.h>
class Manager
{
private:
    vector<WriteTable*>openTables_;
    vector<string>existTables_;
    int bufferSize_;
    string path_;
    string fileType_;
    pthread_rwlock_t openLock_;
    pthread_rwlock_t existLock_;
protected:
    //load the table from disk to memory
    WriteTable* loadTable(string tableName); //ok

    Schema* loadSchema(string tableName); //ok

    //return the ptr if table is in the memory(openTables)
    //or return 0
    WriteTable* isOpen(string tableName); // ok

    //return true if table is exited(in the existTables)
    //or false
    bool isExist(string tableName);  //ok
public:

    Manager():bufferSize_(0),path_(""),fileType_(".txt") 
    {
        pthread_rwlock_init(&openLock_, NULL);
        pthread_rwlock_init(&existLock_,NULL);
    }  //ok
    ~Manager() {}

    //init the existTables
    bool init(int bufferSize,string path=""); //ok

    //if table is existed, return the ptr to the table
    WriteTable* getTable(string tableName); //ok

    bool preserve(WriteTable* ptr);

    int auto_preserve();

    bool saveSchema(string schema);

    bool updateExistTable();

    Schema* creatSchema(string input);

    WriteTable* creatTable(Schema* s);

    //-------------------operator for table ------------
    bool create(string input);

    bool loadTuple(string tableName,string fileName,string sep=" ");

    bool insertTuple(string tableName,vector<CVpair>& data);

    bool updateTuple(string tableName,vector<CVpair>& clause,vector<CVpair>& data);

    bool deleteTuple(string tableName,vector<CVpair>& clause);

    bool deleteTable(string tableName);

    bool rangeQuery(string tableName,double x,double y,double r);

    bool close(string tableName);

    bool recovery(string line);
};
