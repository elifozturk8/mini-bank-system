#include<stdio.h>
#include<stdlib.h>
struct Account{
    int id;
    char name[20];
    float balance;
};

void createAccount();
void depositMoney();
void withdrawMoney();
void showAccounts();


int main(){
    int choice;
    do{
    printf("==== MINI BANK SYSTEM ====\n"); 
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Show Account Info\n");
    printf("5. Exit\n");
    printf("Choose an option:\n");
    scanf("%d",&choice);

        switch (choice)
        {
        case 1:  createAccount(); break;
        case 2:  depositMoney(); break;
        case 3:  withdrawMoney(); break;
        case 4:  showAccounts();  break;
        case 5:  printf("Exiting program...\n"); break;
        default: printf("Invalid choice!\n");
    }
}while(choice!=5);

return 0;


}

void createAccount(){
    struct Account acc;
    FILE *fp;
    fp=fopen("accounts.txt","a");

    if(fp==NULL)
    {
        printf("File error!\n");
        return 1;
    }

    printf("Enter account ID: ");
    scanf("%d",&acc.id);

    printf("Enter name: ");
    scanf("%s",&acc.name);

    printf("Enter initial balance:");
    scanf("%f",&acc.balance);

    fprintf(fp,"%d %19s %.2f\n",acc.id,acc.name,acc.balance);

    fclose(fp);
    printf("Account created successfully!\n");
}

void depositMoney(){
    struct Account acc;
    FILE *fp;
    FILE *temp=fopen("temp.txt","w");
    int searchID;
    float amount;
    int found=0;
    fp=fopen("accounts.txt","r+");

    if(fp==NULL || temp==NULL)
    {
        printf("File error!\n");
        return 1;

    }
    printf("Enter account ID:");
    scanf("%d",&searchID);
    printf("Enter amount to deposit:");
    scanf("%f",&amount);

    while(fscanf(fp,"%d %s %f",&acc.id,acc.name,&acc.balance) !=EOF)
    {
        if(acc.id==searchID)
        {
        acc.balance+=amount;
        fprintf(fp,"%d %19s %.2f\n",acc.id,acc.name,acc.balance);
        found=1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.id, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt","accounts.txt");
    if(found)
    printf("Money deposited successfully!\n");
    else
    printf("Account not found!\n");
}
void withdrawMoney() {
    struct Account acc;
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    int searchId, found = 0;
    float amount;

    if (fp == NULL || temp == NULL) 
    {
        printf("File error!\n");
        return;
    }

    printf("Enter account ID: ");
    scanf("%d", &searchId);

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %f", &acc.id, acc.name, &acc.balance) != EOF) 
    {
        if (acc.id == searchId) 
        {
            if (acc.balance >= amount) 
            {
                acc.balance -= amount;
                printf("Withdrawal successful!\n");
            } 
            else 
            {
                printf("Insufficient balance!\n");
            }
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.id, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
    printf("Account not found!\n");
}

void showAccounts() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.txt", "r");

    if (fp == NULL) 
    {
        printf("No accounts found!\n");
        return;
    }

    printf("\nID\tName\tBalance\n");

    while (fscanf(fp, "%d %s %f", &acc.id, acc.name, &acc.balance) != EOF) 
    {
        printf("%d\t%s\t%.2f\n", acc.id, acc.name, acc.balance);
    }

    fclose(fp);
}
