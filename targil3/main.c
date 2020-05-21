#include "targ3_header.h"

void main()
{
	int func,tables,new_quantity,table_num;
	char* name;
	
	product_manage kitchen;
	table_manage table_manage;
	FILE* manot,*instructions;
	if (!(manot = fopen("manot.txt", "r")))//open file for read and check if succeed
		Error_Msg("Could not open file");
	if (!(instructions = fopen("instructions.txt", "r")))//open file for read and check if succeed
		Error_Msg("Could not open file");
	fscanf(instructions, "%d", &tables);//get amount of tables
	CreateTables(&table_manage, tables);//create link list of tables
	while (fscanf(instructions, "%d", &func!=EOF))//get what function to start
	{
		switch (func)
		{
		case 1://create products link list
			CreateProducts(manot, &table_manage);
			break;

		case 2:
			fscanf(instructions, "%s %d", name, &new_quantity);
			AddItems(&kitchen, name, new_quantity);
			break;

		case 3:
			fscanf(instructions, "%d %s %d", &table_num, name, &new_quantity);
			OrderItem(&table_manage, &kitchen,table_num, name, new_quantity);
			break;

		case 4:
			break;

		case 5:
			break;
		}
	}
}

