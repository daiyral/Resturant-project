#ifndef _targ3_header
#define _targ3_header
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



void CreateProducts(FILE*,Pmanage);
void DeleteProducts(Pmanage);
void Error_Msg(char* s);
#endif