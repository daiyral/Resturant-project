#include "targ3_header.h"
#include <stdio.h>

void CreateProducts(FILE* in, Pmanage manager)
{
	product* temp;
	char temp_name[50];
	//allocate memory and check if it's valid
	if(!(temp=(product*)malloc(sizeof(product))))
	{
		Error_Msg("Could not allocate memory");
	}

	while (fscanf(in, "%s %d %d", temp_name, &temp->price, &temp->quantity))//enter info from text file into temp
	{
		if(!(temp->name=(char*)malloc(strlen(temp_name)*sizeof(char))))
		{
			Error_Msg("Could not allocate memory");
			if(manager->size>0)//only free memory if we have allocated memory
				DeleteProducts(manager);
		}
		strcpy(temp->name, temp_name);//move our temp_name into a product
		temp->next = NULL;//the item we add is always last
		if (manager->head == NULL)//if its the first item
			manager->head = temp;
		else
			manager->tail->next = temp;
		manager->tail = temp;
		manager->size++;//new item has been added
		if(!(temp=(product*)malloc(sizeof(product))))
		{
			Error_Msg("Could not allocate memory");
			if(manager->size>0)//only free memory if we have allocated memory
				DeleteProducts(manager);
		}
	}
}
void Error_Msg(char* s)
{
	printf("%s",s);
}
void DeleteProducts(Pmanage manager)
{
	product* temp;
	while (manager->head != NULL)
	{
		temp = manager->head;
		manager->head = manager->head->next;
		free(temp);
	}
}