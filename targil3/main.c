#include "targ3_header.h"

void main()
{
	product_manage test;
	FILE* in;
	if (!(in = fopen("manot.txt", "r")))
	{
		Error_Msg("Could not open file");
	}
	CreateProducts(in, &test);
	printf("sucsess");
}

