#include "dmm.h"
/*
* Programmer: Orion Green
* Date: 9/27/21
* Digital Music Manager Program
*/
int main(void) {

	int check = 0;
	List musicCollection = { NULL };
	Data dataInsert = {NULL};
	FILE* infile = fopen("musicPlayList.csv", "r");

	menuOptions(&musicCollection, &dataInsert, infile);
	fclose(infile);

	return 0;
}