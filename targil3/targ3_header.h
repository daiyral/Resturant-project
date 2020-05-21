#ifndef _targ3_header
#define _targ3_header
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct product
{
	char* name;
	int price;
	int quantity;
	struct product* next;
}product;

typedef struct product_manage
{
	product* head;
	product* tail;
	int size;
}product_manage,*Pmanage;

typedef struct table
{
	product* order;
	int num;
	int price;
	struct table* next,*before;
	
}table, *Ptable;

typedef struct table_manage
{
	Ptable head;
	Ptable tail;
	int size;
}table_manage,*Tmanage;

void AddItems(Pmanage kitchen, char* name, int quantity);//add quantity to an item
int check_name(Pmanage kitchen, char* name);//this functions checks that we don't have the same products names
int check_quantity(int q);//this functions checks that the quantity is not negative
int check_price(int price);//this function checks that price is not negative
void CreateProducts(FILE*,Pmanage kitchen);//this functions creates a link list of products from a txt file
void DeleteProducts(Pmanage kitchen);//this functions deletes our link list
void Error_Msg(char* s);//this functions prints out an error msg and exits the program
void OrderItem(Tmanage table_manage, Pmanage kitchen, int table_number, char* name, int quantity);//add an item to our table
void CreateTables(Tmanage table_manage, int num);//create table link list
product* Addtotable(Ptable t, char* name, int quantity,int price);//creates a product that we add to our table
void RemoveItem(Tmanage table_manage, int table_number, char* name, int quantity);//remove an item from the table
#endif