#include <stdio.h>
#include <string.h>

#define MAXE 300

typedef struct {
    int id;
    char name[50];
    char dept[20];
    char desig[20];
    double salary;
    int experience;
    char phone[20];
    char email[50];
} Emp;

Emp emps[MAXE];
int ecount=0;

int add_emp(){
    if(ecount>=MAXE) return 0;
    Emp e;
    printf("id: "); scanf("%d",&e.id);
    for(int i=0;i<ecount;i++) if(emps[i].id==e.id) return 0;
    printf("name: "); scanf(" %49[^\n]",e.name);
    printf("dept (IT HR Finance Marketing Operations): "); scanf(" %19s",e.dept);
    printf("desig (Intern Junior Senior Manager Director): "); scanf(" %19s",e.desig);
    printf("salary: "); scanf("%lf",&e.salary);
    printf("experience (years): "); scanf("%d",&e.experience);
    printf("phone: "); scanf(" %19s",e.phone);
    printf("email: "); scanf(" %49s",e.email);
    emps[ecount++]=e;
    return 1;
}

void list_dept_stats(){
    char dept[20];
    printf("dept: "); scanf(" %19s",dept);
    double sum=0; int cnt=0;
    for(int i=0;i<ecount;i++) if(strcasecmp(emps[i].dept,dept)==0){ sum+=emps[i].salary; cnt++; }
    if(cnt==0) printf("none\n");
    else printf("count %d avg %.2f total %.2f\n",cnt,sum/cnt,sum);
}

void appraisal(){
    for(int i=0;i<ecount;i++){
        double p;
        printf("id %d performance 0-100: ",emps[i].id);
        if(scanf("%lf",&p)!=1) p=50;
        if(p>=85) p=15;
        else if(p>=70) p=10;
        else p=5;
        emps[i].salary += emps[i].salary * (p/100.0);
    }
    printf("done\n");
}

void search(){
    printf("1 dept 2 desig 3 experience\n");
    int c; scanf("%d",&c);
    if(c==1){
        char d[20]; printf("dept: "); scanf(" %19s",d);
        for(int i=0;i<ecount;i++) if(strcasecmp(emps[i].dept,d)==0) printf("%d %s %.2f\n",emps[i].id,emps[i].name,emps[i].salary);
    } else if(c==2){
        char s[20]; printf("desig: "); scanf(" %19s",s);
        for(int i=0;i<ecount;i++) if(strcasecmp(emps[i].desig,s)==0) printf("%d %s %.2f\n",emps[i].id,emps[i].name,emps[i].salary);
    } else if(c==3){
        int y; printf("min years: "); scanf("%d",&y);
        for(int i=0;i<ecount;i++) if(emps[i].experience>=y) printf("%d %s %d years\n",emps[i].id,emps[i].name,emps[i].experience);
    }
}

void eligible_promotion(){
    for(int i=0;i<ecount;i++){
        if(emps[i].experience>3) printf("%d %s %d years\n",emps[i].id,emps[i].name,emps[i].experience);
    }
}

int main(){
    while(1){
        printf("1 Add 2 DeptStats 3 Appraisal 4 Search 5 EligiblePromotion 6 List 0 Exit\n");
        int c; if(scanf("%d",&c)!=1) break;
        if(c==1){ if(add_emp()) printf("added\n"); }
        else if(c==2) list_dept_stats();
        else if(c==3) appraisal();
        else if(c==4) search();
        else if(c==5) eligible_promotion();
        else if(c==6){
            for(int i=0;i<ecount;i++)
                printf("%d %s %s %s %.2f %d yrs\n",
                    emps[i].id,emps[i].name,emps[i].dept,emps[i].desig,emps[i].salary,emps[i].experience);
        }
        else if(c==0) break;
    }
    return 0;
}

