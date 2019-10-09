#ifndef STRUCTDATA_H
#define STRUCTDATA_H
typedef struct package
{
    char header;
    char address;
    char command;
    char state;
    char id_arg1;
    char arg1[2];
    char id_arg2;
    char arg2[2];
    char checknum;
    char exitcode;
}Package;


#endif // STRUCTDATA_H
