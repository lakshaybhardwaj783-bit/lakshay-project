#include<stdio.h>
#include<string.h>
void createaccount();
void depositemoney();
void withdrawmoney();
void checkbalance();
void forquery();

const char* ACCOUNT_NAME= "account.dat";

typedef struct {
char name[100];
int acc_no;
float balance;
char query[100];
int pass;
    
}acc;
 
int main(){

    while(1){
        int choice;
        printf(">>> bank management system >>>\n\n");
        printf("1. create account \n");
        printf("2. depostite money\n");
        printf("3. withdraw money \n");
        printf("4. check balance \n ");
        printf("5. for any query \n");
        printf("6. Exit \n");
        printf("enter your choice sir/mam : ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch(choice){

            case 1:
            createaccount();
             break;

             case 2:
             depositemoney();
             break;
              
              case 3:
              withdrawmoney();
             break;

              case 4:
              checkbalance();
             break;

              case 5:
            forquery();
             break;

              case 6:
                printf("closing your bank thank you for visit\n ");
                return 0;
             break;

             default:
             printf("invalid choice\n");
             break;
        }

    }
}

void createaccount(){
    acc account;
    FILE *file= fopen(ACCOUNT_NAME, "ab");
    if(file==NULL){
        printf("unable to open file \n");
        return;
    }

    printf("enter your name :");
    fgets(account.name,100,stdin);
    int ind = strcspn(account.name, "\n");
    account.name[ind]='\0';
    
    printf("Enter your account number :");
    scanf("%d", &account.acc_no);
    account.balance=0;
    printf("enter the password");
    scanf("%d", &account.pass);
fwrite(&account,sizeof(acc),1,file);
fclose(file);

printf("account created successfully!\n");

}

void depositemoney(){
     FILE *file=fopen(ACCOUNT_NAME, "rb+");
    if(file==NULL){
        printf("unable to open file \n");
        return;
    }
    acc account_depo;
    int acc_no;
    float money;
    printf("enter your account number :");
    scanf("%d", &acc_no);
    printf("enter your deposite ammount :");
     scanf("%f", &money);
    
    while(fread(&account_depo, sizeof(account_depo),1,file)){
    if(account_depo.acc_no==acc_no){
        account_depo.balance+=money;
        fseek(file,-sizeof(account_depo), SEEK_CUR);
        fwrite(&account_depo, sizeof(account_depo), 1, file);
        fclose(file);
        printf("syccessfully deposited Rs. %.2f New balance is Rs. %.2f ", money, account_depo.balance);
        return;
    }
    }
fclose(file);
printf("account mo %d not found in records. ", acc_no);
printf("your money could'nt able to deposite..");
}
void withdrawmoney(){
   FILE*file=fopen(ACCOUNT_NAME, "rb+");
    if(file==NULL){
        printf("unable to open file \n");
        return;
    }
int acc_no;
int password;
float money;
acc acc_w;
printf("enter your account number :");
scanf("%d", &acc_no);
printf("enter the withdramoney");
scanf("%f",&money);
printf("enter the password :");
scanf("%d", &acc_w.pass);

 while(fread(&acc_w, sizeof(acc_w),1,file)){
if(acc_w.acc_no==acc_no){
    if(acc_w.pass==password){
    if(acc_w.balance>=money){
        acc_w.balance-=money;
        fseek(file,-sizeof(acc_w), SEEK_CUR);
        fwrite(&acc_w, sizeof(acc_w), 1, file);
        fclose(file);
        return;
        printf("succesfully withdrwan Rs. %.2f reamining balance is Rs. %.2f",money, acc_w.balance );
    }else{
        printf("insuficient balance!");
    }

    
}else{
    printf("invalid password..");

}
}
 }
fclose(file);
return;
printf("account number was not found %d", acc_no);
}
void checkbalance(){
    FILE *file=fopen(ACCOUNT_NAME, "rb");
    if(file==NULL){
        printf("unable to open file \n");
        return;
    }

   int acc_no;
   acc account_read;
   printf("enter your account number :");
   scanf("%d", &acc_no);
   while(fread(&account_read, sizeof(account_read),1,file)){
    if(account_read.acc_no==acc_no){
        printf("your account balance is Rs\n %.2f",account_read.balance );
           fclose(file);
           return;
    }
   }
      fclose(file);
   printf("account number was not found %d\n", acc_no);

}
void forquery(){
    acc sher;
   printf("what is your query sir/mam :\n");
   fgets(sher.query,100,stdin);
   printf("thank you...\n");
   printf("your request has been succesfully submitted\n");
   
}
