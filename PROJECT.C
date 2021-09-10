#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char Contact[12];
    char date[20];
    char time[20];
    int numofItems;
    struct items itm[50];
};

// function of generate biils
void generateBillHeader(char name[100], char date[20], char time[20], char Contact[12])
{
    printf("\n\n");
    printf("\t  XYZ. Restaurant\n");
    printf("\t -----------------\n\n");
    printf("Customer Details\n");
    printf("\nBill Date: %s",date);
    printf("\nBill Time: %s",time);
    printf("\nName: %s", name);
    printf("\nContact No: %s",Contact);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[50], int qty, float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty * price);
    printf("\n");
}


void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal +2*cgst;
    printf("----------------------------------------\n");
    printf("sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f\n", grandTotal);
    printf("----------------------------------------\n");
}
int main()
{
    float total;
    int opt,n;
    char NO[10];
    struct orders ord;
    struct orders order;
    char saveBill = 'Y', contFlag = 'Y';
    char name[50]; 
    FILE *fp;

    while(contFlag == 'Y'){
    float total = 0;
    int invoiceFound = 0;
    printf("\n\n\t==========XYZ.RESTAURANT==========\n\n");
    printf("Please select your prefered operation\n");
    printf("1.Generate Invoice\n");
    printf("2.Show all Invoice\n");
    printf("3.Search Invoice\n");
    printf("4.Exit");
    printf("\n\nYour choice: ");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt)
    {
        case 1:
        printf("\nPlease enter the name of the customer: ");
        fgets(ord.customer,80,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date, __DATE__);
        strcpy(ord.time,__TIME__);
        printf("Please enter the contact no: ");
        fgets(ord.Contact,80,stdin);
        printf("\nPlease entet the number of items: ");
        scanf("%d", &n);
        ord.numofItems = n;

        for(int i=0; i<n; i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d: ",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity: ");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter thr unit price: ");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer, ord.date, ord.time, ord.Contact);
        for(int i=0; i<ord.numofItems; i++)
        {
            generateBillBody(ord.itm[i].item, ord.itm[i].qty,ord.itm[i].price);
        } 
        generateBillFooter(total);

        printf("\nDo you want to save the invoice;[Y/N]: ");
        scanf("%s", &saveBill);

        if(saveBill == 'Y')
        {
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
                printf("\nSuccessfully saved");
            else
                printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float total = 0;  
            generateBillHeader(order.customer,order.date,order.time, order.Contact);
            for(int i=0; i<order.numofItems; i++)
            {
                generateBillBody(order.itm[i].item, order.itm[i].qty,order.itm[i].price);
                total+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(total);
        }
        fclose(fp);
        break; 

        case 3:
         printf("\nEnter the name of the customer: ");
        //  fgetc(stdin);
         fgets(name,50,stdin); 
         name[strlen(name-1)]=0;
         system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****", name);
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float total = 0; 
            if(strcmp(order.customer,name))
            {
                generateBillHeader(order.customer,order.date,order.time, order.Contact);
                for(int i=0; i<order.numofItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty,order.itm[i].price);
                    total+=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(total);
                invoiceFound = 1;
            }
        }
        if(!invoiceFound)
        {
            printf("Sorry the invoice for %s doesnot exists", name);
        }
        fclose(fp);
        break;  

        case 4:
        printf("\n\t\t Bye Bye :)"); 
        exit(0);
        break;  

        default:
        printf("Sorry invalid option");  
        break;  
    }
    printf("\nDo you want to perform another operation?[Y/N]: ");
    scanf("%s", &contFlag);
    }
    printf("\n\n");
    return 0;
}