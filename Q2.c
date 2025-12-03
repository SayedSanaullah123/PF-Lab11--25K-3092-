#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAXA 200
#define MAXT 100

typedef struct {
    time_t date;
    int type;
    double amount;
} Txn;

typedef struct {
    int acc_no;
    char name[50];
    int atype;
    double balance;
    time_t created_at;
    time_t last_txn;
    Txn txns[MAXT];
    int txn_count;
} Account;

Account accounts[MAXA];
int acount=0;

double min_balance(int t){ if(t==1) return 1000; if(t==2) return 5000; return 10000; }
double interest_rate(int t){ if(t==1) return 0.04; if(t==3) return 0.07; return 0.0; }

Account* find_account(int no){
    for(int i=0;i<acount;i++) if(accounts[i].acc_no==no) return &accounts[i];
    return NULL;
}

void add_txn(Account *a,int type,double amount){
    if(a->txn_count<MAXT){
        a->txns[a->txn_count].date=time(NULL);
        a->txns[a->txn_count].type=type;
        a->txns[a->txn_count].amount=amount;
        a->txn_count++;
    }
    a->last_txn=time(NULL);
}

int create_account(){
    if(acount>=MAXA) return 0;
    Account a;
    printf("acc no: "); scanf("%d",&a.acc_no);
    if(find_account(a.acc_no)){ printf("exists\n"); return 0; }
    printf("name: "); scanf(" %49[^\n]",a.name);
    printf("type 1 Savings 2 Current 3 Fixed: "); scanf("%d",&a.atype);
    double bal; printf("initial deposit: "); scanf("%lf",&bal);
    if(bal<min_balance(a.atype)){ printf("below min\n"); return 0; }
    a.balance=bal;
    a.created_at=time(NULL);
    a.last_txn=0;
    a.txn_count=0;
    add_txn(&a,1,bal);
    accounts[acount++]=a;
    return 1;
}

void deposit(){
    int no; double amt;
    printf("acc no: "); scanf("%d",&no);
    Account *a=find_account(no);
    if(!a){ printf("not found\n"); return; }
    printf("amount: "); scanf("%lf",&amt);
    if(amt<=0){ printf("invalid\n"); return; }
    a->balance+=amt;
    add_txn(a,1,amt);
    printf("new balance %.2f\n",a->balance);
}

void withdraw(){
    int no; double amt;
    printf("acc no: "); scanf("%d",&no);
    Account *a=find_account(no);
    if(!a){ printf("not found\n"); return; }
    printf("amount: "); scanf("%lf",&amt);
    if(amt<=0){ printf("invalid\n"); return; }
    if(a->balance-amt < min_balance(a->atype)){ printf("cannot withdraw, min balance required\n"); return; }
    a->balance-=amt;
    add_txn(a,2,amt);
    printf("new balance %.2f\n",a->balance);
}

void show_account(){
    int no; printf("acc no: "); scanf("%d",&no);
    Account *a=find_account(no);
    if(!a){ printf("not found\n"); return; }
    printf("acc %d %s type %d balance %.2f\n",a->acc_no,a->name,a->atype,a->balance);
    printf("created %ld lasttxn %ld\n",(long)a->created_at,(long)a->last_txn);
    for(int i=0;i<a->txn_count;i++){
        printf("%d %ld %.2f\n",a->txns[i].type,(long)a->txns[i].date,a->txns[i].amount);
    }
}

void apply_interest(){
    for(int i=0;i<acount;i++){
        double r=interest_rate(accounts[i].atype);
        if(r>0){
            double interest=accounts[i].balance*r/12.0;
            accounts[i].balance+=interest;
            add_txn(&accounts[i],1,interest);
        }
    }
    printf("interest applied\n");
}

int main(){
    while(1){
        printf("1 Create 2 Deposit 3 Withdraw 4 Show 5 ApplyInterest 0 Exit\n");
        int c; if(scanf("%d",&c)!=1) break;
        if(c==1){ if(create_account()) printf("created\n"); }
        else if(c==2) deposit();
        else if(c==3) withdraw();
        else if(c==4) show_account();
        else if(c==5) apply_interest();
        else if(c==0) break;
    }
    return 0;
}

