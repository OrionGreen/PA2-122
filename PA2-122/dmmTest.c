#include"dmmTest.h"

//function to test the insert this will not insert because of invalid values and thus success is a 0 from the insert 
int testInsert(void) {
	Data d1 = { "Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, -1, 6 };
	List musicCollection = { NULL };
	int success = -1;

	success = insert(&musicCollection, &d1);
	if (success == 0) {
		return 1;
	}
	else
	return 0;
}

//tests the delete, it deletes the only thing in the list which will make the pointer NULL;
int testDelete(void) {
	List musicCollection = { NULL };
	Data d1 = { "Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, 3, 5 };
	insertFront(&musicCollection, &d1);
	int successdelete = 0;
	int success = 0;

	successdelete = delete(&musicCollection, &d1);

	if (musicCollection.pHead ==  NULL) {
		success = 1;
	}
	return success;
}

//Tests the shuffle with a hard coded array that will play in this specific order.
int testShuffle(void) {
	List musicCollection = { NULL };
	Data d1 = { "Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, 3, 5};
	Data d2 = { "Perri, Christina", "HEAD OF HEART", "Trust", "Pop", {2, 35}, 3, 5 };
	Data d3 = { "Eminem", "SHADYXV", "Vegas", "Rap", {3, 37}, 8, 3 };
	
	insertFront(&musicCollection, &d1);
	insertFront(&musicCollection, &d2);
	insertFront(&musicCollection, &d3);

	int shuffarr[3] = {3,1,2};
	int success = 0;

	success = shuffle(&musicCollection, shuffarr);
}

/*char artist[20]; // 20 bytes
char album[20];//20
char song[20];//20
char genre[20];//20
Duration length;//8
int playCount;//4 bytes
int rating;//4 bytes*/