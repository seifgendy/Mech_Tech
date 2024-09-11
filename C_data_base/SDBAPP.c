 #include <stdio.h>
#include <stdlib.h>
#include "SDB.h"
#include "SDB.c"

int studentCount ;
int exit_checker = 0;
int add_checker = 0;
int delete_checker = 0;
int ReadEntry_checker = 0;
int id_checker = 0;
int full_checker = 0;
int number_checker = 0;
int getlist_checker = 0;
uint8 choice =10 ;
int info = 0;
int stu_id = 0;
int stu_id2 = 0;

//STARTUP FUNCTION
 void SDB_APP (){
while(1){
    printf("\n If you want to add a student, enter 1:\n If you want to know number  of a students, enter 2:\nIf you want to print data of a student, enter 3:\nIf you want to get list of the ids of students, enter 4:\nIf you want to check for an id of a student, enter 5:\nIf you want to delete a student, enter 6:\nif you want to check if the database is full or not. , enter 7:\nIf you want To exit enter , enter 0:\n");
    scanf("%d", &choice);
     SDB_action ( choice);
 if (choice == 0){
    break;

}
 }
 }

// TAKE ACTION ACCORDING TO USER CHOICE
  void SDB_action (uint8 choice){

  if (choice == 1){
        while(1){
       send_studentcount(studentCount);  // CALL THE FUNCTION THAT SEND NO. OF STUDENTS ACCROSS MODULES
       printf("Entering data for student #%d:\n", studentCount + 1);
        if (SDB_AddEntry()) {
                studentCount++;
            } else   {
                printf("Failed to add entry.\n");
            }


        printf("If you want to exit, enter 9 if u want to continue enter any number\n ");
        scanf("%d", &exit_checker);
        if (exit_checker == 9) {
            break;
        }
        }

  }


 if (choice == 6){

  printf("Enter his or her id: \n");
        scanf("%d", &info);
        SDB_DeletEntry(info);



  }


   if (choice == 5){
  printf("Enter his or her id: \n");
        scanf("%d", &stu_id2);
        bool1 result = SDB_IsIdExist(stu_id2);
        if (result) {
            printf("Student ID %d exists.\n", stu_id2);
        } else {
            printf("Student ID %d does not exist.\n", stu_id2);
        }

   }

 if (choice  == 3){

printf("Enter his or her id: \n");
        scanf("%d", &stu_id);
         bool1 result = SDB_ReadEntry(stu_id);
        if (result) {
            printf("Student ID %d data exists.\n", stu_id);
        } else {
            printf("Student ID %d data does not exist.\n", stu_id);
        }

 }

 if (choice  == 7){
 if( SDB_IsFull ()){
            printf("not full\n");
        }
        else {
        printf("full\n");
    }


 }


 if (choice  == 2 ){
  SDB_GetUsedSize();

  }


   if (choice == 4){


  uint32 idList[4]; // Assuming you have a maximum of 10 students
uint8 count = SDB_GetList(idList);

// Now, the idList array contains the Student_IDs, and count holds the number of IDs.
for (uint8 i = 0; i < count; i++) {
    printf("Student ID: %d\n", idList[i]);
}

  }
  }
