

#ifndef SDB_H
#define SDB_H

#include "STD.h"


typedef struct SimpleDb
{
 uint32 Student_ID;
 uint32 Student_year;
 uint32 Course1_ID;
 uint32 Course1_grade;
 uint32 Course2_ID;
 uint32 Course2_grade;
 uint32 Course3_ID;
 uint32 Course3_grade;
 struct SimpleDb* link;

} student;
extern student* head;// Global pointer to the head of the linked list

bool1 SDB_IsFull ();
uint8 SDB_GetUsedSize();
bool1 SDB_AddEntry();
void SDB_DeletEntry (uint32 id);
bool1 SDB_ReadEntry (uint32 id);
uint8 SDB_GetList (uint32 *idList);
bool1 SDB_IsIdExist (uint32 id);
void SDB_APP ();
void SDB_action (uint8 choice);
void SDB_ReadAllEntries();
void send_studentcount(int studentCount);





#endif
