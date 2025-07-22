#include <stdlib.h>
#include <stdio.h>

typedef enum s_type
{
	ALO,
	CHALO = 3,
	BLO = 2,
	WOW
}t_type;

int main()
{
	t_type obj = ALO;
	int a = ALO;
	printf("nayi=>%d\n",obj);
	printf("nayiiii=>%d\n",a);

}