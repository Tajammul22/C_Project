#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define maxUser 20
#define maxPass 15
#define FSIZE 100
#define carbrand 20
#define carmodel 25
#define cprice 20

struct customer{
	char name[maxUser];
	char password[maxPass];
};

//addon option function and structures
struct node {
    char key[100];
    float data;
    struct node* next;
};

// Function to display the commands
void DisplayCommand() {
    printf("\t\t\t\t\tEnter 1: Add\n");
    printf("\t\t\t\t\tEnter 2: Remove from UserAddons\n");
    printf("\t\t\t\t\tEnter 3: Confirm UserAddons\n");
}

// Function to display the linked list
void Display(struct node* temp) {
    int i = 0;
    while (temp != NULL) {
        i++;
        printf("\t\t\t\t\t%d. %s : %.2f\n", i, temp->key, temp->data);
        temp = temp->next;
    }
}

// Function to insert a node into the linked list
struct node* Insert(struct node* head, char* key, float data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed Error 4040");
        return head;
    }
    strcpy(newNode->key, key);
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

// Function to transfer an addon from Addons to UserAddons
void TransferAddon(struct node** fromList, struct node** toList, int index) {
    if (*fromList == NULL) {
        printf("No addons available to transfer.\n");
        return;
    }

    struct node* current = *fromList;
    struct node* prev = NULL;
    int i = 1; // Start index at 1

    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *fromList = current->next;
        }
        current->next = *toList;
        *toList = current;
    } else {
        printf("Invalid choice\n");
    }
}


void RemoveFromUserAddons(struct node** userList, struct node** addList, int index) {
    struct node* current = *userList;
    struct node* prev = NULL;
    int i = 1; // Start index at 1

    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *userList = current->next;
        }

        // Add the removed addon back to Addons list
        current->next = *addList;
        *addList = current;
    } else {
        printf("Invalid choice\n");
    }
}

float calculate_price(struct node*temp,float price){
	float total = 0;
	while(temp != NULL){
		total += ((temp->data) * price)/100;
		temp = temp->next;
	}
	return total;
}
//end struct function...


//admin portal {

void instruction(){
	printf("\t\t\t\t\t=============================================\n");
	printf(" \t\t\t\t\t      CAR INFORMATION ADMIN MANAGEMENT      \n");
	printf("\t\t\t\t\t=============================================\n");
	printf("\t\t\t\t\t\t  1. Add Car Info\n");
	printf("\t\t\t\t\t\t  2. View Car Info\n");
	printf("\t\t\t\t\t\t  3. Remove Car Info\n");
	printf("\t\t\t\t\t\t  4. See List Of User\n");
	printf("\t\t\t\t\t\t  5. Logout()\n\n");
}

void printPaddedName(const char *name, int paddingSize) {
    int nameLen = strlen(name);
    int totalLength = paddingSize + 4; // 2 "|" characters and 2 spaces
    printf("%-*s", totalLength, name); // Left-aligned padding
    printf("|\n");
}

void insert(){
	char brand[carbrand];
	char model[carmodel];
	char price[cprice];
	FILE * file;
	file = fopen("storage\\CarList.txt","a");
	printf("\t\t\t\t\t\tBrand : ");
	scanf("%s",&brand);
	printf("\t\t\t\t\t\tModel : ");
	scanf("%s",&model);
	printf("\t\t\t\t\t\tPrice : ");
	scanf("%s",&price);
	fprintf(file,"%s %s %s\n",&brand,&model,&price);
	printf("\t\t\t\t\t\tInsert Successful\n");
	printf("\t\t\t\t\t\tPress any key to continue...\n");
     getch();
	fclose(file);
}
void view(){
	char fbrand[carbrand];
	char fmodel[carmodel];
	char fprice[cprice];
	int padsize = 8;
	FILE * file;
	file = fopen("storage\\Carlist.txt","r");
	if(file == NULL){
		printf("file is empty\n");
	}
	while(fscanf(file,"%s %s %s",fbrand,fmodel,fprice) != EOF){
		printf("\n");
		printf("\t\t\t\t\t\t|\tBrand : ");
		 printPaddedName(fbrand,padsize);
		printf("\t\t\t\t\t\t|\tModel : ");
		 printPaddedName(fmodel,padsize);
		printf("\t\t\t\t\t\t|\tPrice : ");
		 printPaddedName(fprice,padsize);
		printf("\t\t\t\t\t\t+___________________________+");
		printf("\n");
	}
	fclose(file);
}

void removeinfo(){
	char brand[carbrand];
	char model[carmodel];
	char fbrand[carbrand];
	char fmodel[carmodel];
	char fprice[cprice];
	int delete = 0;
	printf("\t\t\t\t\t\tEnter Car brand : ");
	scanf("%s",&brand);
	printf("\t\t\t\t\t\tEnter Car model : ");
	scanf("%s",&model);
	FILE *file,*tempfile;
	file = fopen("storage\\Carlist.txt","r");
	tempfile = fopen("storage\\temp.txt","w");
	while(fscanf(file,"%s %s %s",fbrand,fmodel,fprice) != EOF){
		if(strcmp(fbrand,brand) == 0 && strcmp(fmodel,model) == 0){
			delete = 1;
		}
		else{
			fprintf(tempfile,"%s %s %s\n",fbrand,fmodel,fprice);
		}
	}
	fclose(file);
	fclose(tempfile);
	if(delete == 1){
		remove("storage\\Carlist.txt");
		rename("storage\\temp.txt","storage\\Carlist.txt");
		printf("\t\t\t\t\t\tCar Detail Deleted\n");
	} else {
		remove("storage\\temp.txt");
		printf("\t\t\t\t\t\tCar Info Not Found In File !\n");
	}
}

void view_customers(){
	char fbrand[carbrand];
	char fmodel[carmodel];
	float fprice;
	char user[50];
	int day,mon,year,primium,type;
	int i = 0;
	FILE * file;
	file = fopen("storage\\Customers.txt","r");
	if(file == NULL){
		printf("file is empty\n");
	}
	while(fscanf(file,"%s %s %s %d/%d/%d %d %f %d",user,fbrand,fmodel,&day,&mon,&year,&primium,&fprice,&type) != EOF){
		printf("\n");
		printf("\t\t\t\t\t\t|\tUser  : %s \n",user);
		printf("\t\t\t\t\t\t|\tBrand : %s \n",fbrand);
		printf("\t\t\t\t\t\t|\tModel : %s \n",fmodel);
		printf("\t\t\t\t\t\t|\tCurrent Car Price : %.2f \n",fprice);
		printf("\t\t\t\t\t\t|\tPrimium : %d \n",primium);
		if(type == 1){
			printf("\t\t\t\t\t\t|\tType : Comprehensive Insurence\n");
		} else if (type == 2){
			printf("\t\t\t\t\t\t|\tType : Third Party Insurence\n");
		}
		printf("\t\t\t\t\t\t+_________________________________________+");
		printf("\n");
	}
	fclose(file);
}

//} admin portal ends

void showcommands(){
	printf("\n\n");
    printf("\t\t\t\t\t+------------  Main Menu  ----------+\n");
    printf("\t\t\t\t\t¦   		1 : Login	    ¦\n");
    printf("\t\t\t\t\t¦  		2 : Register        ¦\n");
    printf("\t\t\t\t\t¦   		3 : Exit      	    ¦\n");
    printf("\t\t\t\t\t+-----------------------------------+\n\n");
};

int validUser(char *user){
	char fileUser[maxUser];
	char filePass[maxPass];
	FILE * file;
	file = fopen("storage\\User.txt", "r");
	if(file == NULL){
		return 0;
	}
	while(fscanf(file,"%s %s",fileUser,filePass) != EOF){
		if(strcmp(fileUser,user) == 0){
			fclose(file);
			return 1;
			break;
		}
	}
	fclose(file);
	return 0;
}

void registerUser(char *user,char *password){
	FILE * file;
	file = fopen("storage\\User.txt", "a");
	fprintf(file, "%s %s\n", user, password);
    	fclose(file);
    	printf("\t\t\t\t\t\tSuccessfull Registration\n");
}

int login(char *user,char *password){
	char fileUser[maxUser];
	char filePass[maxPass];
	
	FILE * file;
	file = fopen("storage\\User.txt", "r");
	if(file == NULL){
		printf("\t\t\t\t\t\tUser dose not exist\n");
		return 1;
	}
	int loggedin = 0;
	while(fscanf(file,"%s %s",fileUser,filePass) != EOF){
		if(strcmp(user,fileUser) == 0 && strcmp(password,filePass) == 0){
			loggedin = 1;
			break;
		}
	}
	fclose(file);
	return loggedin;
}

int	checkavailable(char *brand,char *model){
		int available = 0;
		char fbrand[carbrand];
	     char fmodel[carmodel];
	    	char fprice[cprice];
	    	int price = 0; // Initialize to 0
	    	FILE *file;
	    	file = fopen("storage\\Carlist.txt", "r");
	    	if (file == NULL) {
	     	printf("\t\t\t\t\t\tfile is empty\n");
	    	}
	    	while (fscanf(file, "%s %s %s", fbrand, fmodel, fprice) != EOF) {
	        	if (strcmp(fbrand, brand) == 0 && strcmp(fmodel, model) == 0) {
	        		available = 1;
				return available;
	          break;
	        	}
	    	}
	    	fclose(file);
		return 0;
	}
	
	
	
	//pull the price from file
int pullprice(char *brand, char *model) {
	    char fbrand[carbrand];
	    char fmodel[carmodel];
	    char fprice[cprice];
	    int price = 0; // Initialize to 0
	    FILE *file;
	    file = fopen("storage\\Carlist.txt", "r");
	    if (file == NULL) {
	        printf("\t\t\t\t\t\tfile is empty\n");
	    }
	    while (fscanf(file, "%s %s %s", fbrand, fmodel, fprice) != EOF) {
	        if (strcmp(fbrand, brand) == 0 && strcmp(fmodel, model) == 0) {
	            price = atoi(fprice);
	            break;
	        }
	    }
	    fclose(file);
	    return price;
	}
	
//calculate date and give days
int daycal(int day,int mon,int year)
{
	time_t t=time(NULL);
    struct tm tm1 = *localtime(&t);
    struct tm tm2 = { 0 };

    /* date 1: 2022-09-25 */
    tm1.tm_year+1900;
    tm1.tm_mon+1;
    tm1.tm_mday;
    /* date 2: 1990-10-02 */
    tm2.tm_year = year - 1900;
    tm2.tm_mon = mon - 1;
    tm2.tm_mday = day;
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    double dt = difftime(t1, t2);
    int days = round(dt / 86400);
//    printf("difference: %d days\n", days);
	return days;
}
	
	//check the final current price of that car 
int finalprice(int days,int p){
		int totalprice;
		if(days <= 186){
			totalprice = p - (p*5)/100;
		}
		else if(days > 186 && days <= 365){
			totalprice = p - (p*15)/100;
		}
		else if(days > 365 && days <= 731){
			totalprice = p - (p*20)/100;
		}
		else if(days > 731 && days <= 1095){
			totalprice = p - (p*30)/100;
		}
		else if(days > 1095 && days <= 1461){
			totalprice = p - (p*40)/100;
		}
		else if(days > 1461 && days <= 1825){
			totalprice = p - (p*55)/100;
		}
		else if(days >= 3000){
			totalprice = p - (p*90)/100;
		}
		else{
			totalprice = p - (p*70)/100;
		}
		return totalprice;
	}
	
	//print the bill to see what primium included


//try

void printtpbill(char *brand,char *model,int price){
	int i = 0;
    	int tp = (price * 1) / 100;
    	int discount = (price * 0.5) / 100;
    	int gst = (( tp - discount) * 18) / 100;
    	int total = tp + gst - discount;			
	
    	printf("\t\t\t\t\t  ====================================\n");
    	printf("\t\t\t\t\t              Invoice                 \n");
    	printf("\t\t\t\t\t  ====================================\n");
    	printf("\t\t\t\t\t  Brand: %s\n", brand);
    	printf("\t\t\t\t\t  Model: %s\n", model);
    	printf("\t\t\t\t\t  ------------------------------------\n");
    	printf("\t\t\t\t\t  Car Current Price: %d\n", price);
    	printf("\t\t\t\t\t  ------------------------------------\n");
    	printf("\t\t\t\t\t  < Premium Breakup >\n");
    	printf("\t\t\t\t\t  Basic Third-party Premium: %d\n", tp);
    	printf("\t\t\t\t\t  +-+ Discounts +-+\n");
    	printf("\t\t\t\t\t  OD discount: -%d\n", discount);
    	printf("\t\t\t\t\t  +18%% GST: %d\n", gst);
    	printf("\t\t\t\t\t  ------------------------------------\n");
    	printf("\t\t\t\t\t  Total Premium: %d (Annually)\n", total);
    	printf("\t\t\t\t\t  ====================================\n");
}

void printfinalbill(char *brand, char *model, int price, struct node *UserAddons, float totaladdonprice) {
    // Define the variables needed
    int i = 0;
    int od = (price * 1.5) / 100;
    int tp = (price * 0.7) / 100;
    int discount = (price * 1) / 100;
    float totaladdon = totaladdonprice;
    int gst = ((od + tp + totaladdon - discount) * 18) / 100;
    int total = od + tp + (int)totaladdon + gst - discount;

    printf("\t\t\t\t\t  ====================================\n");
    printf("\t\t\t\t\t              Invoice                 \n");
    printf("\t\t\t\t\t  ====================================\n");
    printf("\t\t\t\t\t  Brand: %s\n", brand);
    printf("\t\t\t\t\t  Model: %s\n", model);
    printf("\t\t\t\t\t  ------------------------------------\n");
    printf("\t\t\t\t\t  Car Current Price: %d\n", price);
    printf("\t\t\t\t\t  ------------------------------------\n");
    printf("\t\t\t\t\t  < Premium Breakup >\n");
    printf("\t\t\t\t\t  +-+ Basic Covers +-+\n");
    printf("\t\t\t\t\t  Basic Own Damage: %d\n", od);
    printf("\t\t\t\t\t  Basic Third-party Premium: %d\n", tp);
    printf("\t\t\t\t\t  +-+ Add-ons Covers +-+\n");

    while (UserAddons != NULL) {
        i++;
        printf("\t\t\t\t\t  %d.%s: %.2f\n", i, UserAddons->key, ((UserAddons->data * price)/100));
        UserAddons = UserAddons->next; // Move to the next addon
    }

    printf("\t\t\t\t\t  +-+ Discounts +-+\n");
    printf("\t\t\t\t\t  OD discount: -%d\n", discount);
    printf("\t\t\t\t\t  +18%% GST: %d\n", gst);
    printf("\t\t\t\t\t  ------------------------------------\n");
    printf("\t\t\t\t\t  Total Premium: %d (Annually)\n", total);
    printf("\t\t\t\t\t  ====================================\n");
}

//end try
	
void getPassword(char *pass)
{
    int c=0;
    char buff[30]={0},ch;
    int len=0;
    while((ch=getch())!='\n'){
        if(ch==0x7f)    // use 0x08 in turboc (WINDOWS)
        {
            if(len==0)  continue;
            printf("\b \b"); len--; continue;
        }
        printf("%c",'*');
        pass[len]=ch;
        len++;
    }
    pass[len]='\0';
 
}

int StoreBill(char*name,int days,int price,float c_price,char*brand,char*model,struct node*UserAddons,float totaladdon){
	int i = 0;
	int curentprice = (int)(c_price);
	int od = (curentprice * 1.5) / 100;
    	int tp = (curentprice * 0.7) / 100;
    	int discount = (curentprice * 1) / 100;
    	int gst = ((od + tp + totaladdon - discount) * 18) / 100;
    	int total = od + tp + (int)totaladdon + gst - discount;
	FILE *file;
	file = fopen("storage\\Cust_C_Bill.txt", "w");												
	fprintf(file,"****************************************\n");
	fprintf(file,"**         Car Insurance Plan         **\n");
	fprintf(file," -------------------------------------- \n");
	fprintf(file,"     Your insurance geek for life       \n");
//	fprintf(file,"Drive with Confidence, Insured with Care\n");
	fprintf(file,"****************************************\n");
	fprintf(file,"    Car Owner : %s\n",name);
	fprintf(file,"    Age of the Car : %d days\n",days);
	fprintf(file,"    Car Purchase Price : %d\n",price);
	fprintf(file,"    Car Current Price : %d\n",curentprice);
    	fprintf(file," ------------------------------------\n");
	fprintf(file,"  Brand: %s \t\t Model: %s\n", brand,model);
    	fprintf(file," ------------------------------------\n");
    	fprintf(file,"    < Premium Breakup >\n");
    	fprintf(file,"    **Basic Covers\n");
    	fprintf(file,"    Basic Own Damage: %d\n", od);
    	fprintf(file,"    Basic Third-party Premium: %d\n", tp);
    	fprintf(file,"    **Add-ons Covers\n");
     while (UserAddons != NULL) {
        i++;
        fprintf(file,"    %d.%s: %.2f\n", i, UserAddons->key, ((UserAddons->data * price)/100));
        UserAddons = UserAddons->next;
    	}
     fprintf(file,"    **Discounts\n");
    	fprintf(file,"    OD discount: -%d\n", discount);
    	fprintf(file,"    +18%% GST: %d\n", gst);
    	fprintf(file," ------------------------------------\n");
    	fprintf(file,"   Total Premium: %d (Annually)\n", total);
    	fprintf(file," ------------------------------------\n");
	fclose(file);
	return total;
}

int StoretpBill(char*name,int days,int price,float c_price,char*brand,char*model){
	int curentprice = (int)(c_price);
    	int tp = (curentprice * 1) / 100;
    	int discount = (curentprice * 1) / 100;
    	int gst = (( tp - discount) * 18) / 100;
    	int total = tp + gst - discount;
	FILE *file;
	file = fopen("storage\\Cust_TP_Bill.txt", "w");												
	fprintf(file,"****************************************\n");
	fprintf(file,"**         Car Insurance Plan         **\n");
	fprintf(file," -------------------------------------- \n");
	fprintf(file,"     Your insurance geek for life       \n");
//	fprintf(file,"Drive with Confidence, Insured with Care\n");
	fprintf(file,"****************************************\n");
	fprintf(file,"    Car Owner : %s\n",name);
	fprintf(file,"    Age of the Car : %d days\n",days);
	fprintf(file,"    Car Purchase Price : %d\n",price);
	fprintf(file,"    Car Current Price : %d\n",curentprice);
    	fprintf(file," ------------------------------------\n");
	fprintf(file,"  Brand: %s \t\t Model: %s\n", brand,model);
    	fprintf(file," ------------------------------------\n");
    	fprintf(file,"    **Basic Covers\n");
    	fprintf(file,"    Basic Third-party Premium: %d\n", tp);
     fprintf(file,"    **Discounts\n");
    	fprintf(file,"    OD discount: -%d\n", discount);
    	fprintf(file,"    +18%% GST: %d\n", gst);
    	fprintf(file," ------------------------------------\n");
    	fprintf(file,"   Total Premium: %d (Annually)\n", total);
    	fprintf(file," ------------------------------------\n");
	fclose(file);
	return total;
}

void store_users(char*user,char*brand,char*model,int day,int mon,int year,int primium,float price,int type){
	FILE *file;
	file = fopen("storage\\Customers.txt", "a");
	fprintf(file,"%s %s %s %d/%d/%d %d %.2f %d\n",user,brand,model,day,mon,year,primium,price,type);
	fclose(file);
}


void Greeting(char*user){
	printf("\n\t\t\t\t\tThank you Mr.%s,\n",user);
	printf("\t\t\t\t\t\tYour Insurence is successfully registered.\n");
	printf("\t\t\t\t\t\tThank you for Choosing our Insurance Service\n\n\n");
}


int main(){
	char user[maxUser];
	char password[maxPass];
	char ch,confirm;
	float total;
	int n,days;
	showcommands();
	do{
		fflush(stdin);
		printf("\t\t\t\t\t\tEnter the command : ");
		scanf("%d",&n);
		fflush(stdin);
		if(n == 2){
			fflush(stdin);
			printf("\t\t\t\t\t\tEnter User name : ");
			scanf("%s",user);
//			check user is available or not  
			if(validUser(user)){
				printf("\t\t\t\t\t\t*username already taken*\n");
			}
			else{
				printf("\t\t\t\t\t\tEnter Password : ");
				scanf("%s",password);
				registerUser(user,password);
			}
		}
		else if(n == 1){
			fflush(stdin);
			printf("\n");
			printf("\t\t\t\t\t\tUser : ");
			scanf("%s",&user);
			printf("\t\t\t\t\t\tPassword : ");
//			scanf("%s",&password);
			getPassword(password);
			if(validUser(user)){
				if(login(user,password)){
						system("cls");
						if(strcmp(user,"admin") == 0){
							instruction();
							int n;
							do{
								printf("\t\t\t\t\t\tEnter the command : ");
								scanf("%d",&n);
								switch(n){
									case 1:
										insert();
										break;
									case 2:
										view();
										break;
									case 3:
										removeinfo();
										break;
									case 4:
										printf("Registered User List : \n");
										view_customers();
										break;
									case 5:
										return 0;
										break;
									default:
										printf("\t\t\t\t\t\tInvalid Command\n");
								}
							}while(1);
							
						}
						else{
							int day,mon,year;
							fflush(stdin);
							char brand[carbrand];
							char model[carmodel];
						again:
							printf("\n\n");
							printf("\t\t\t\t\t\tEnter Your Car Brand : ");
							scanf("%s",&brand);
							printf("\t\t\t\t\t\tEnter Your Car Model : ");
							scanf("%s",&model);
							printf("\t\t\t\t\t\tEnter Your Car purchase Date (dd/mm/yyyy) :  ");
							scanf("%d/%d/%d",&day,&mon,&year);
							
							days = daycal(day,mon,year);
							fflush(stdin);
							struct node* UserAddons = NULL;
							struct node* Addons = NULL;
							// Sample addons for demonstration
						    	Addons = Insert(Addons, "Zero Depreciation Cover", 1.5);
							Addons = Insert(Addons, "No Claim Bonus Protection Cover", 0.7);
						    	Addons = Insert(Addons, "Road Side Assistance Cover", 0.5);
						    	Addons = Insert(Addons, "Return to Invoice Cover", 0.75);
							Addons = Insert(Addons, "Daily Allowance Cover", 1.0);
						    	Addons = Insert(Addons, "Passenger Cover", 0.5);
							Addons = Insert(Addons, "Consumables Cover", 0.3);
						    	Addons = Insert(Addons, "Key Protection or Replacement Cover", 0.07);
							Addons = Insert(Addons, "Paid Driver Cover", 0.1);
	//						date of purchase is gonna add here  
//							int days = 120;
							
							int check = checkavailable(brand,model);
							if(check == 1){
								int carprice = pullprice(brand,model);
								float price = finalprice(days,carprice);
								//get the type of insurence that user wants
								int type;
								int typeconfirm = 0;
								do{
									printf("\n\n");
									printf("\t\t\t\t\t\t   Car is Available\n");
									printf("\n\t\t\t\t\t****************************************\n");
	    								printf("\t\t\t\t\t**        Choose Insurance Type       **\n");
	    								printf("\t\t\t\t\t****************************************\n\n");
	    								printf("\t\t\t\t\t\t1. Comprehensive Insurance\n");
	    								printf("\t\t\t\t\t\t2. Third-Party Insurance\n");
	    								printf("\n\t\t\t\t\t\tEnter your choice: ");
									scanf("%d",&type);
								
									if(type == 1){
										//comprehensive
										int userinput;
										do{
					//						define the arrays and variables
											char addon[][25] = {};
											double addonprice[] = {};
											int  finalizebill;
											char confirmation;
					//						printbill
											int addonCount = sizeof(addon) / sizeof(addon[0]);
											printfinalbill(brand,model,price,UserAddons,total);
					//						askfor addons
											printf("\n\n");
											fflush(stdin);
											printf("\t\t\t\t\t  |----- Enter 1 : Add-on Option -----|\n");
											printf("\t\t\t\t\t  |----- Enter 0 : Exit --------------|\n\n");
											printf("\t\t\t\t\t\t  Enter (1/0): ");
											scanf("%d",&finalizebill);
											if(finalizebill == 1){
												//addon code gose from here// if any thing go wrong just use goto
												int choice, index;
												char confirm;
											
											    	while (1) {
											        	DisplayCommand();
											        	printf("\t\t\t\t\tEnter Command : ");
											        	scanf("%d", &choice);
											
											        	switch (choice) {
											            	case 1:
											            		if(Addons == NULL){
											            			printf("\t\t\t\t\tAll the addons are Selected\n");
														  	}
															else{
												                	printf("\t\t\t\t\tAvailable Addons:\n");
												                	Display(Addons);
												                	printf("\t\t\t\t\tEnter index : ");
												                	scanf("%d", &index);
												                	system("cls");
												                	TransferAddon(&Addons, &UserAddons, index);
												                	printf("\t\t\t\t\tYour Addons are -->>\n");
												                	Display(UserAddons);
											           		}
											                	break;
											            	case 2:
															printf("\t\t\t\t\tYour Addons:\n");
															Display(UserAddons);
														    	printf("\t\t\t\t\tEnter index of Addon: ");
														    	scanf("%d", &index);
														    	RemoveFromUserAddons(&UserAddons, &Addons, index);
														    	system("cls");
														    	printf("Your Addons:\n");
															Display(UserAddons);
															break;
											            	case 3:
											                	printf("\t\t\t\t\tConfirmed UserAddons:\n");
											                	Display(UserAddons);
											                	printf("\t\t\t\t\tConfirmation(Y/N) : ");
											                	fflush(stdin);
											                	scanf("%c",&confirmation);
											                	if(confirmation == 'Y' || confirmation == 'y'){											                		
											               	 	total = calculate_price(UserAddons,price);
//											                		printf("\n\t\t\t\t\tYour total Addon Charge : %.2f",total);
											                		goto exit;
											                		return 0;
											                	}
											                	else{
											                		printf("\t\t\tYour Operation has been Terminated\n\n\n");
											                		goto again;
															 }
											            	default:
											                	printf("\nInvalid Command\n");
											        	};
											    	}
												//addon code end here
												printf("here is the add on option\n\n");
											}
											//if not then just exit
											else if(finalizebill == 0){
												userinput = 0;
											}
										}while(userinput != 0);
										exit:
											printfinalbill(brand,model,price,UserAddons,total);
											fflush(stdin);
											printf("\t\t\t\t\tThis is the last confirmation(Y/N) : ");
											scanf("%c",&confirm);
											if(confirm == 'y' || confirm == 'Y'){
												int primium = StoreBill(user,days,carprice,price,brand,model,UserAddons,total);
												store_users(user,brand,model,day,mon,year,primium,price,1);
												Greeting(user);
												goto fullexit;
											}
											else{
												printf("\t\t\t\t\tYour Operation has been Terminated\n\n\n");
												goto again;
											}
										//print bill with loop gose from here... 
										
										typeconfirm = 1;//for the type loop to compelete
									}
									else if(type == 2){
										//thirdparty
										printtpbill(brand,model,price);
										printf("\t\t\t\t\tThis is the last confirmation(Y/N) : ");
										fflush(stdin);
										scanf("%c",&confirm);
										if(confirm == 'y' || confirm == 'Y'){
											int primium = StoretpBill(user,days,carprice,price,brand,model);
											store_users(user,brand,model,day,mon,year,primium,price,2);
											Greeting(user);
											goto fullexit;
										}
										else{
											printf("\t\t\t\t\tYour Operation has been Terminated\n\n\n");
											goto again;
										}
										typeconfirm = 1;//for the type loop to compelete
									}
									else{	
										printf("\t\t\t\t\t\tEnter valid Number\n\n");
									}		
								}while(typeconfirm != 1);
							}
							else{
								printf("\t\t\t\t\t\tSorry we dont have any insurence for this car brand model.\n\n");
							}
						}
				}
				else{
					printf("\t\t\t\t\t\tInvalid Password\n\n");
				}
			} else {
				printf("\t\t\t\t\t\tinvalid User credential\n\n");
			}
		}
		
		else{
			if(n == 3){
				fullexit:
					return 0;
			} else {
				printf("\t\t\t\t\t\tinvalid command\n\n");
			}
		}
	}while(1);
}
