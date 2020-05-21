#include "targ3_header.h"

void OrderItem(Tmanage table_manage, Pmanage kitchen, int table_number, char* name, int quantity)
{
	product* tempP, * new_product;//tempP will point the kitchen list
	table* tempT = table_manage->head;//tempT will point to table list
	tempP = kitchen->head;
	if (check_name(kitchen, name))
	{
		if (check_quantity(quantity))
		{
			while (!strcmp(tempP->name, name))//loop till you reach the name we want to update its quantity
				tempP = tempP->next;
			if (tempP->quantity >= quantity)//check if we have enough of the item in our inventory
			{
				while (tempT->num != table_number)//run on all the tabels till we find the table with same serial number
					tempT = tempT->next;//go to next table
				new_product = Addtotable(tempT, tempP->name, tempP->quantity, tempP->price);//recieve junction of what we put on the table 
				//add products to the table(link list) in the style of head of list
				new_product->next = tempT->order;
				tempT->order = new_product;
				printf("%d %s were added to table number %d", quantity, name, table_number);
			}
			printf("sorry there isnt enough %s in the kitchen", name);
		}
	}
}

void CreateTables(Tmanage table_manage,int num)
{
	int i;
	Ptable temp;
	//set by defualt to be null
	table_manage->head = NULL;
	table_manage->tail = NULL;
	for (i = 0; i < num; i++)
	{
		if (!(temp = (table*)malloc(sizeof(table))))//create a table(link list node)
			Error_Msg("Could not allocate memory");
		temp->num = i + 1;//number of table
		temp->order = NULL;//initialize order to null(no orders on table)
		temp->next = NULL;//our tail next is always null
		if (table_manage->head == NULL)//if its the first item in link list
		{
			table_manage->head = temp;//make it first item
			temp->before = NULL;
		}
		else//if its not the first item in the list
		{
			table_manage->tail->next = temp;//attach to previous tail
			temp->before = table_manage->tail;//attach the list to go backward
		}
		table_manage->tail = temp;//update the tail
	}
}
//this func copys an item and we call the function to add that item to the table
product* Addtotable(Ptable t, char* name, int quantity,int price)
{
	product* temp;//make a product
	if(!(temp=(product*)malloc(sizeof(product))))
		Error_Msg("couldnt add product to table");
	temp->quantity=quantity;//updates it quantity 
	temp->price=price;//update its price
	if(!(temp->name=(char*)malloc(sizeof(char)*strlen(name+1))))
		Error_Msg("couldnt add new product name to table");
	strcpy(temp->name,name);
	return temp;
}

void AddItems(Pmanage kitchen, char* name, int quantity)
{
	product* temp;
	temp = kitchen->head;//pointer to move in the list
	if (check_name(kitchen, name))//check if our name is ok(in the list)
	{
		if (check_quantity(quantity))//check if our quantity is ok(not negative)
		{
			while (!strcmp(temp->name, name))//loop till you reach the name we want to update its quantity
				temp = temp->next;
			temp->quantity = quantity;//update quantity
			printf("%d %s were added to the kitchen", quantity, name);
		}
	}	
}
void CreateProducts(FILE* in, Pmanage kitchen)
{
	product* temp;
	char temp_name[50];
	kitchen->head = NULL;
	kitchen->tail = NULL;
	kitchen->size = 0;
	//allocate memory and check if it's valid
	if(!(temp=(product*)malloc(sizeof(product))))
		Error_Msg("Could not allocate memory");
	while (fscanf(in, "%s %d %d", &temp_name, &temp->price, &temp->quantity)!=EOF)//enter info from text file into temp
	{
		//check if our name and price and quantity are ok (not equal,not neg) if its ok we add to our link list
		if (check_name(kitchen, temp_name) && check_price(temp->price) && check_quantity(temp->quantity))
		{

			if (!(temp->name = (char*)malloc(strlen(temp_name) + 1 * sizeof(char))))
			{
				Error_Msg("Could not allocate memory");
				if (kitchen->size > 0)//only free memory if we have allocated memory
					DeleteProducts(kitchen);
			}
			strcpy(temp->name, temp_name);//move our temp_name into a product
			temp->next = NULL;//the item we add is always last
			if (kitchen->head == NULL)//if its the first item
				kitchen->head = temp;
			else
				kitchen->tail->next = temp;
			kitchen->tail = temp;
			kitchen->size++;//new item has been added
		}
		//create new temp for next item
		if (!(temp = (product*)malloc(sizeof(product))))
		{
			Error_Msg("Could not allocate memory");
			DeleteProducts(kitchen);
		}
	}
	free(temp);//free the one extra temp we have allocated
	//printf("All products have been registered");//CHECK IF WE NEED TO THROW THE PROGRAM IF PRODUCT IS NOT OK?
	printf("The kitchen has been created");
}
int check_price(int price)
{
	if (price <= 0)
	{
		Error_Msg("Price cannot be negative");
		return 0;//return 0 if price is negative
	}
	return 1;//return 1 if price is positive
}

int check_quantity(int q)
{
	if (q>0) return 1;//return 1 if quantity is valid
	Error_Msg("quantity isnt valid");
	return 0;
}
int check_name(Pmanage kitchen,char* name)
{
	product* temp;
	temp = kitchen->head;
	while (temp)
	{
		if (strcmp(temp->name, name) == 0)
		{
			return 0;//return 0 if strings are identical
			Error_Msg("We dont have %s ,sorry :(",name);
		}
	temp = temp->next;
	}
	 return 1;//return 1- if the name doesnt exist
}
void Error_Msg(char* s)
{
	printf("%s",s);
	exit(1);
}
void DeleteProducts(Pmanage kitchen)
{
	product* temp;
	while (kitchen->head != NULL)
	{
		temp = kitchen->head;
		kitchen->head = kitchen->head->next;
		free(temp);
	}
}
