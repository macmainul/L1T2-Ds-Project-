
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#include<string.h>

typedef struct Medicine
{
    int medicine_id;
    char medicine_name[50];
    char medicine_category[30];
    float price;
    int quantity;
    struct Medicine *next;

}medicine;

void addMedicine(medicine *list)
{
    system("cls");
    medicine *temp = (medicine*) malloc(sizeof(medicine));
    int medicineid;
    char medicinename[50];
    char medicinecategory[30];
    float price;
    int quantity;

    printf("Enter Medicine ID: ");
    scanf("%d",&medicineid);
    fflush(stdin);
    printf("Enter Medicine Name: ");
    gets(medicinename);
    fflush(stdin);
    printf("Enter Medicine Category: ");
    gets(medicinecategory);
    fflush(stdin);
    printf("Enter Medicine Price: ");
    scanf("%f",&price);
    fflush(stdin);
    printf("Enter Medicine Quantity: ");
    scanf("%d",&quantity);

    temp->medicine_id = medicineid;
    strcpy(temp->medicine_name,medicinename);
    strcpy(temp->medicine_category,medicinecategory);
    temp->price = price;
    temp->quantity = quantity;
    temp->next = NULL;


    while(list->next != NULL)
    {
        list = list->next;
    }
    list->next = temp;

    printf("%d ID is added in Medicine List!\n",medicineid);
    printf("\n\n\nPress any key to continue....");
    fflush(stdin);
    getch();
}

void delMedicine(medicine *list)
{
    medicine *temp = (medicine*)malloc(sizeof(medicine));

    int medicineid;
    printf("Enter medicine ID: ");
    scanf("%d",&medicineid);

    int cq = 0;

    if(list->next == NULL)
    {
        printf("List Is NULL\n");
        getch();
        return;
    }

    while(list->next->medicine_id != medicineid)
    {
        list = list->next;
        if(list->next==NULL && list->medicine_id != medicineid)
        {
            printf("The Medicine ID is invalid\n");
            getch();
            return;
        }
    }

    temp = list->next;
    list->next=temp->next;
    free(temp);
    printf("%d ID is deleted from Medicine List\n",medicineid);
    getch();
}

void searchMedicine(medicine *list)
{
    int flag=0;
    int medicineid;
    printf("Enter Medicine ID:");
    scanf("%d",&medicineid);

    while (list!=NULL){
        if(list->medicine_id==medicineid){
            flag=1;
            break;
        }
        list=list->next;
    }

    if(flag==1)
    {
        printf("\t%d Medidcine ID is found!",medicineid);
        printf("\n\nID\tMedicine_Name\t\tCetagory\t\tPrice\t\tquantity\n");
        printf("\n%d\t%s\t\t\t%s\t\t\t%f\t\t%d\n",list->medicine_id,list->medicine_name,list->medicine_category,list->price,list->quantity);
    }
    else
        printf("Not Found!!");
    getch();
}

void displayMedicine(medicine *list)
{
    printf("\t\t\t\t\tMedicine List\n");
    printf("----------------------------------------------------\n");
    printf("ID\tMedicine_Name\t\tCetagory\t\tPrice\t\tquantity\n");
    while(list!=NULL)
    {
        printf("%d\t%s\t\t\t%s\t\t%0.3f\t\t%d\n",list->medicine_id,list->medicine_name,list->medicine_category,list->price,list->quantity);
        list = list->next;
    }
    getch();
}

void saveData2File(medicine *list)
{
    FILE *fp;
    fp=fopen("medicine2.dat","wb");
    medicine b;

    if(fp==NULL){
        printf("Failed to open file!!");
        return;
    }

    while(list!=NULL){
        b.medicine_id=list->medicine_id;
        strcpy(b.medicine_name,list->medicine_name);
        strcpy(b.medicine_category,list->medicine_category);

        b.price=list->price;
        b.quantity = list->quantity;

        fwrite(&b,sizeof(b),1,fp);
        list=list->next;
    }
        printf("Data saved to file medicine.dat!");
    fclose(fp);
    getch();
}

void readDataFromFile(medicine *list)
{
    FILE *fp;
    fp=fopen("medicine2.dat","rb");

    medicine b;
    medicine *temp;

    if(fp==NULL){
        printf("Failed to open file!!");
        return;
    }

    while(list->next!= NULL)
    {
        list = list->next;
    }

    while(fread(&b,sizeof(b),1,fp))
    {
        temp=(medicine*)malloc(sizeof(medicine));
        temp->next=NULL;

        temp->medicine_id=b.medicine_id;
        strcpy(temp->medicine_name,b.medicine_name);
        strcpy(temp->medicine_category,b.medicine_category);
        temp->price=b.price;
        temp->quantity = b.quantity;

        list->next=temp;
        list=list->next;

    }
    fclose(fp);
    printf("Read from file success!!");
    getch();
}

int showmenu()
{
    int ch;
    system("cls");
    printf("\t\t\t\tMenu\n");
    printf("1. Add Medicine\n");
    printf("2. Delete a Medicine\n");
    printf("3. Search a Medicine\n");
    printf("4. Display Medicine\n");
    printf("5. Save data to File\n");
    printf("6. Read Data from file\n");
    printf("7. EXIT\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&ch);
    return ch;
}
int main()
{
    int ch;
    medicine *list;
    list = (medicine*)malloc(sizeof(medicine));
    list->next=NULL;
    list->medicine_id = 0;

    while(1)
    {
        ch = showmenu();
        switch(ch)
        {
            case 1:
                addMedicine(list);
                break;
            case 2:
                delMedicine(list);
                break;
            case 3:
                searchMedicine(list->next);
                break;
            case 4:
                displayMedicine(list->next);
                break;
            case 5:
                saveData2File(list->next);
                break;
            case 6:
                readDataFromFile(list);
                break;
            case 7:
                printf("\n\t\t\t Thank You !!!\n");
                exit(0);

            default:
                printf("Invalid Choise\n");
                getch();
                break;
        }
    }

    return 0;
}
