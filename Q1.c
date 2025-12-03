#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200

typedef struct {
    char name[50];
    char roll[20];
    float marks[3];
    float percentage;
    char grade[3];
    int rank;
} Student;

Student students[MAX];
int count=0;

int valid_mark(float m){ return m>=0 && m<=100; }

void calc(Student *s){
    s->percentage=(s->marks[0]+s->marks[1]+s->marks[2])/3.0f;
    float p=s->percentage;
    if(p>=90) strcpy(s->grade,"A+");
    else if(p>=80) strcpy(s->grade,"A");
    else if(p>=70) strcpy(s->grade,"B+");
    else if(p>=60) strcpy(s->grade,"B");
    else if(p>=50) strcpy(s->grade,"C");
    else strcpy(s->grade,"F");
}

int add_student(){
    if(count>=MAX) return 0;
    Student s;
    printf("name: ");
    scanf(" %49[^\n]",s.name);
    printf("roll: ");
    scanf(" %19s",s.roll);
    float m1,m2,m3;
    printf("mark1: "); if(scanf("%f",&m1)!=1) return 0;
    printf("mark2: "); if(scanf("%f",&m2)!=1) return 0;
    printf("mark3: "); if(scanf("%f",&m3)!=1) return 0;
    if(!valid_mark(m1)||!valid_mark(m2)||!valid_mark(m3)){ printf("invalid marks\n"); return 0; }
    for(int i=0;i<count;i++) if(strcmp(students[i].roll,s.roll)==0){ printf("roll exists\n"); return 0; }
    s.marks[0]=m1; s.marks[1]=m2; s.marks[2]=m3;
    calc(&s);
    students[count++]=s;
    return 1;
}

void list_students(){
    for(int i=0;i<count;i++){
        printf("%s %s %.2f %s\n",students[i].roll,students[i].name,students[i].percentage,students[i].grade);
    }
}

void sort_ranks(){
    for(int i=0;i<count;i++) students[i].rank=0;
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(students[j].percentage>students[i].percentage){
                Student t=students[i]; students[i]=students[j]; students[j]=t;
            }
        }
    }
    for(int i=0;i<count;i++) students[i].rank=i+1;
}

void show_ranks(){
    sort_ranks();
    for(int i=0;i<count;i++){
        printf("rank %d %s %s %.2f\n",students[i].rank,students[i].roll,students[i].name,students[i].percentage);
    }
}

void find_by_grade(){
    char g[3];
    printf("grade: ");
    scanf(" %2s",g);
    for(int i=0;i<count;i++) if(strcmp(students[i].grade,g)==0) printf("%s %s %.2f\n",students[i].roll,students[i].name,students[i].percentage);
}

void search_student(){
    char t[50];
    printf("roll or name: ");
    scanf(" %49[^\n]",t);
    for(int i=0;i<count;i++){
        if(strcmp(students[i].roll,t)==0 || strcasecmp(students[i].name,t)==0){
            printf("%s %s %.2f %s\n",students[i].roll,students[i].name,students[i].percentage,students[i].grade);
        }
    }
}

void avg_above_below(){
    if(count==0){ printf("no students\n"); return;}
    float sum=0;
    for(int i=0;i<count;i++) sum+=students[i].percentage;
    float avg=sum/count;
    printf("class average %.2f\n",avg);
    printf("above:\n");
    for(int i=0;i<count;i++) if(students[i].percentage>avg) printf("%s %s %.2f\n",students[i].roll,students[i].name,students[i].percentage);
    printf("below:\n");
    for(int i=0;i<count;i++) if(students[i].percentage<avg) printf("%s %s %.2f\n",students[i].roll,students[i].name,students[i].percentage);
}

int main(){
    while(1){
        printf("1 Add 2 List 3 Search 4 FindGrade 5 AvgAboveBelow 6 Ranks 0 Exit\n");
        int c; if(scanf("%d",&c)!=1) break;
        if(c==1){ if(add_student()) printf("added\n"); }
        else if(c==2) list_students();
        else if(c==3) search_student();
        else if(c==4) find_by_grade();
        else if(c==5) avg_above_below();
        else if(c==6) show_ranks();
        else if(c==0) break;
    }
    return 0;
}

