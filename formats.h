#ifndef FORMATS_H
#define FORMATS_H
 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
 
void SaveLong(FILE *file,long arg);
long LoadLong(FILE *file);
void SaveShort(FILE *file,short arg);
short LoadShort(FILE *file);
void SaveChar(FILE *file,char arg);
char LoadChar(FILE *file);
void SaveFloat(FILE *file,float arg);
float LoadFloat(FILE *file);
long GetReadPos(FILE *File,char *SearchString);
float ReadNumber(FILE *File);
 
#endif
