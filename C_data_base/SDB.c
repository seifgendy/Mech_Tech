
#ifndef SDB_C
#define SDB_C



#include "SDB.h"   // Includes structure definitions from SDB.h

student* head = NULL;
static int scc;
int studentCount ;

// A FUNCTION TO SEND & RECIEVE THE NUMBER OF STUDENTS IN DB
void send_studentcount(int studentCount){

    scc=studentCount;
    }


bool1 SDB_AddEntry()
{

    int ID,year,Course1ID,Course1grade,Course2ID,Course2grade,Course3ID,Course3grade;
   student* newnode = (student*)malloc(sizeof(student));
   if (scc > 3  ) {
        printf("Memory allocation failed.\n");
        return false;}

printf("pls enter Student_ID\n  ") ;
scanf("%d",&ID);
  newnode -> Student_ID = ID ;

  printf("pls enter Student_year\n  ") ;
scanf("%d",&year);
  newnode -> Student_year = year ;

  printf("pls enter Course1_ID\n  ") ;
scanf("%d",&Course1ID);
  newnode -> Course1_ID = Course1ID ;

    printf("pls enter Course1grade\n  ") ;
scanf("%d",&Course1grade);
  newnode -> Course1_grade = Course1grade ;

    printf("pls enter Course2_ID\n  ") ;
scanf("%d",&Course2ID);
  newnode -> Course2_ID = Course2ID ;

      printf("pls enter Course2grade\n  ") ;
scanf("%d",&Course2grade);
  newnode -> Course2_grade = Course2grade ;

     printf("pls enter Course3_ID\n  ") ;
scanf("%d",&Course3ID);
  newnode -> Course3_ID = Course3ID ;

        printf("pls enter Course3grade\n  ") ;
scanf("%d",&Course3grade);
  newnode -> Course3_grade = Course3grade;


newnode->link = head;         // Link the new node to the list
    head = newnode;

  return true ;

}



void SDB_DeletEntry(uint32 id) {
    student* current = head;
    student* previous = NULL;

    // Traverse the linked list to find the student with the given ID
    while (current != NULL) {
        if (current->Student_ID == id) {
            // If the student is found, remove the node from the linked list
            if (previous == NULL) {
                head = current->link;  // If it's the first node
            } else {
                previous->link = current->link;  // If it's not the first node
            }

            free(current);  // Free memory occupied by the node
            printf("Student with ID %d deleted.\n", id);
            return;
        }

        // Move to the next node
        previous = current;
        current = current->link;
    }

    // If student with the given ID is not found
    printf("Student with ID %d not found.\n", id);
}




bool1 SDB_ReadEntry(uint32 id) {
    student* current = head;

    // Traverse the linked list to find the student with the given ID
    while (current != NULL) {
        if (current->Student_ID == id) {
            // Print the information of the found student
            printf("Student with ID %d found.\n", id);
            printf("Student_ID\tStudent_year\tCourse1_ID\tCourse1_grade\tCourse2_ID\tCourse2_grade\tCourse3_ID\tCourse3_grade\n");
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                   current->Student_ID, current->Student_year,
                   current->Course1_ID, current->Course1_grade,
                   current->Course2_ID, current->Course2_grade,
                   current->Course3_ID, current->Course3_grade);
            return true;
        }

        // Move to the next node
        current = current->link;
    }

    // If student with the given ID is not found
    printf("Student with ID %d not found.\n", id);
    return false;
}


bool1 SDB_IsIdExist(uint32 id) {
    student* current = head;

    // Traverse the linked list to find the student with the given ID
    while (current != NULL) {
        if (current->Student_ID == id) {
            // If the student is found, print a message and return true
            printf("Student with ID %d found.\n", id);
            return true;
        }

        // Move to the next node
        current = current->link;
    }

    // If student with the given ID is not found, print a message and return false
    printf("Student with ID %d not found.\n", id);
    return false;
}




bool1 SDB_IsFull (){


uint32 idList123[4];
    uint8 count123 = SDB_GetList(idList123);
    scc =  count123;






if (scc > 3  ) //CHECK IF NO. OF NODES MORE THAN THE LIMIT
    {

        return false;

        }
else {
    return true ;

}
}


uint8 SDB_GetUsedSize(){

    uint32 idList12[4];
    uint8 count12 = SDB_GetList(idList12);
    scc =  count12 ;




printf("number of students = %d\n",scc );





}






uint8 SDB_GetList(uint32 *idList) {
    uint8 count = 0;
    student* current = head;

    // Traverse the linked list and populate the idList array
    while (current != NULL) {
        idList[count] = current->Student_ID;
        count++;

        // Move to the next node
        current = current->link;
    }

    return count;
}















#endif

