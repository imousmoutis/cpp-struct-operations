#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define FILENAME "students.txt"
 
typedef struct Student{
    int id;         
    char name[20];  
    char surname[20]; 
} Student;
 
 
typedef struct Students{
    Student *arr;
    int size;
    int sorted;
} Students;
 
void swap(Student *d1, Student *d2);
int surNameCmp(Student st1, Student st2);
int idCmp(Student st1, Student st2);
void bubblesort(Student *A, int (*cmp)(Student, Student), int left, int right);
int partition (Student *A, int (*cmp)(Student, Student), int left, int right, int pivotIndex);
void quicksort(Student *A, int (*cmp)(Student, Student), int left, int right);
void insertSorted(Student *A, int (*cmp)(Student, Student));
void sortSurName(Students *st);
void sortID(Students *st);
void saveData(char fname[], Students *st);
void addStudent(Students *st);
void initStudents(Students *st);
void displayStudents(Students AL);
int displayMainMenu();
void deleteStudent(Students *st);
void loadData(char fname[], Students *st);
 
main(int argc, char *argv[]){
    int menuchoice;
    Students st;
    char filename[100];
 
    if (argc > 1)
    {
        printf("You have imported a file.\n");
        strcpy(filename, argv[1]);
    }
    else
    {
        printf("The program is going to use the default file.\n");
        strcpy(filename, FILENAME);
    }
    printf("Filename: %s\n", filename);
    initStudents (&st);
    do
    {
        menuchoice=displayMainMenu();
        switch (menuchoice)
        {
            case 0: exit(0);
            case 1: loadData(filename, &st); break;
            case 2: saveData(filename, &st); break;
            case 3: addStudent(&st); break;
            case 4: deleteStudent(&st); break;
            case 5: sortID(&st); break;
            case 6: sortSurName(&st); break;
            case 7: displayStudents(st);break;
        }
    } while(1);
}
 
void swap(Student *d1, Student *d2){
    Student temp;
 
    temp=*d1;
    *d1=*d2;
    *d2=temp;
}
 
int surNameCmp(Student st1, Student st2){ 
 
    if (strcmp(st1.surname, st2.surname)==0)
        return strcmp(st1.name, st2.name);
    else return strcmp(st1.surname, st2.surname);
}
 
int idCmp(Student st1, Student st2){ 
 
    if (st1.id==st2.id)
        return 0;
    else if (st1.id < st2.id) return -1;
    else return 1;
}
 
void bubblesort(Student *A, int (*cmp)(Student, Student), int left, int right){
    int i,j;
    Student a;
 
    for(i=left; i<right; i++)
    {
        for(j=left; j<(right-i); j++)
        {
            if (cmp(A[j], A[j+1])> 0)
            {
                a=A[j];
                A[j]=A[j+1];
                A[j+1]=a;
            }
        }
    }
}
 
int partition (Student *A, int (*cmp)(Student, Student), int left, int right, int pivotIndex){
    
    int i, j;
    i = left-1;
    j = right;
    
    Student v = A[pivotIndex];
    for (;;){
        while ((*cmp)(A[++i],v)==-1);
        while ((*cmp)(A[--j],v)==+1)
        if (j == left) break;
        if (i >= j) break;
     
    swap( A+i, A+j);
    }
 
    swap( A+i, A+right);
    return i;
}
 
void quicksort(Student *A, int (*cmp)(Student, Student), int left, int right){
 
    int i;
    
    if (right <= left)
       return;
       
    int pivot=rand()%right;
    i = partition ( A, idCmp ,left, right,pivot);
    quicksort (A,idCmp, left, i-1);
    quicksort (A,idCmp, i+1, right);
}
 
void insertSorted(Student *A, int (*cmp)(Student, Student), int left, int right){
    Student a;
 
    int i = right-1;
    while ((cmp(A[i],A[i+1]) > 0) && (i >=0)){
        a=A[i];
        A[i]=A[i+1];
        A[i+1]=a;
        i--;
    }
}
 
 
void sortSurName(Students *st){
 
    bubblesort(st->arr, surNameCmp, 0, st->size-1);
    st->sorted=1;
}
 
void sortID(Students *st){
 
    quicksort(st->arr, idCmp, 0, st->size-1);
    st->sorted=2;
}
 
 
void saveData(char fname[], Students *st)
{
    FILE *fp;
 
    fp=fopen(fname,"w");
    if (fp == NULL)
        printf("The file cannot be located.\n****");
    fprintf(fp, "%d\n", st->size); 
    for (int i=0; i<st->size; i++)
         fprintf(fp, "%d %s %s\n", st->arr[i].id, st->arr[i].name, st->arr[i].surname);
    fclose(fp);
}
 
void addStudent(Students *st){
    int i;
    FILE *fp;
 
    st->arr = (Student*)realloc(st->arr, ((st->size)+1)*sizeof(Student)); 
    if (st->sorted==0){
                       
        printf("Insert the student's id: ");
        scanf("%d", &st->arr[st->size].id);
        printf("\n");
        printf("Insert the student's first name: ");
        scanf("%s", &st->arr[st->size].name);
        printf("\n");
        printf("Insert the student's last name: ");
        scanf("%s", &st->arr[st->size].surname);
        printf("\n");
    }else if (st->sorted==1){
          
        printf("Insert the student's id: ");
        scanf("%d", &st->arr[st->size].id);
        printf("\n");
        printf("Insert the student's first name: ");
        scanf("%s", &st->arr[st->size].name);
        printf("\n");
        printf("Insert the student's last name: ");
        scanf("%s", &st->arr[st->size].surname);
        printf("\n");
        insertSorted(st->arr, surNameCmp, 0, st->size);
    }else if (st->sorted==2){
          
        printf("Insert the student's id: ");
        scanf("%d", &st->arr[st->size].id);
        printf("\n");
        printf("Insert the student's first name: ");
        scanf("%s", &st->arr[st->size].name);
        printf("\n");
        printf("Insert the student's last name: ");
        scanf("%s", &st->arr[st->size].surname);
        printf("\n");
        insertSorted(st->arr, idCmp, 0, st->size);
    }
    st->size=st->size+1;
}
 
void initStudents(Students *st){
 
    st->arr = (Student*) malloc (0);
    st->size=0;
    st->sorted=0;
}
 
 
void displayStudents(Students AL){ 
    int i;
 
    for (i=0; i< AL.size; i++)
    {
        printf("%d\t", AL.arr[i].id);
        printf("%s\t", AL.arr[i].name);
        printf("%s\n", AL.arr[i].surname);
    }
}
 
int displayMainMenu(){
    int choice;
 
    do
    {
        printf("\n\nMenu:\n");
        printf("1. Load students from file\n");
        printf("2. Save students to file\n");
        printf("3. Add a student\n");
        printf("4. Delete a student by id\n");
        printf("5. Sort by id\n");
        printf("6. Sort by surname, name\n");
        printf("7. Display students\n");
        printf("0. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");
    }while (choice<0 && choice>7);
    
    return choice;
}
 
void deleteStudent(Students *st){ 
     
    int student_id, F, i;
    F=0;
    i=0;
 
    printf("The id of the student you want to remove: ");
    scanf("%d",&student_id);
    while (i<st->size){
        if ((student_id==st->arr[i].id) && (F==0))
        {
          printf("The students was removed.\n");
          F=1;
          swap(&st->arr[i],&st->arr[st->size-1]);
          st->arr = (Student*) realloc (st->arr, ((st->size)-1) * sizeof(Student)); 
          st->size--;
        }
        i++;
    }
    if (F==0)
      printf("The student with id %d doesn't exist.\n",student_id);
}
 
void loadData(char fname[], Students *st){
     
    int i;
    FILE *fp;
 
    fp=fopen(fname,"r");
    if (fp == NULL)
        printf("The file can't be located.\n");
    fscanf(fp, "%d", &(st->size)); 
    free(st->arr); 
    st->arr=(Student*) malloc(st->size*(sizeof(Student))); 
    for (i=0; i<st->size; i++){
        fscanf(fp, "%d", &st->arr[i].id);
        fscanf(fp, "%s", &st->arr[i].name);
        fscanf(fp, "%s", &st->arr[i].surname);
    }
    fclose(fp);
}
