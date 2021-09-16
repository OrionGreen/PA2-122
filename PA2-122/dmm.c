#include "dmm.h"

void menuOptions(List* pList, Data* data, FILE* infile) {
	int go = 1;
	char proceed = NULL;
	while (go != 0) {
		printf("What would you like to do today\n1. Load\n2. Store\n3. Display\n4. Insert\n5. Delete\n6. Edit\n7. Sort\n8. Rate\n9. Play\n10. Shuffle\n11. Exit\n");
		int choice = 0;

		do {
			scanf("%d", &choice);
		} while (choice == 0 || choice > 11);

		system("cls");

		if (choice == 1) {
			int check = 0;
			do {
				check = load(pList, data, infile);
			} while (check == 0);
		}

		if (choice == 2) {
			int check = 0;
			do {
				check = store(pList, infile);
			} while (check == 0);
		}

		if (choice == 3) {
			display(pList);
			
			
		}

		if (choice == 4) {

		}

		if (choice == 5) {

		}
		if (choice == 6) {

		}
		if (choice == 7) {

		}
		if (choice == 8) {

		}
		if (choice == 9) {

		}
		if (choice == 10) {

		}
		if (choice == 11) {
			
		}
		
	}
}

int store(List* pList, FILE* infile) {
	int success = 0;
	Node* pMem = pList->pHead;
	while (pMem != NULL) {
		
		fprintf("%s,%s,%s,%s,%d:%d,%d,%d", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
			pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

		pMem = pMem->pNext;
		success = 1;
	}
	return success;
}

int load(List* pList, Data* pNewData, FILE* infile) {
	char line[300] = { '\0' };
	initList(pList);
	int success = 0;

	while (fgets(line, 300, infile) != NULL) {
		

		if (line[0] == '"') {
			strcpy(pNewData->artist, strtok(line, ","));
			strcat(pNewData->artist, ",");
			strcat(pNewData->artist, strtok(NULL, ","));
			strcpy(pNewData->album, strtok(NULL, ","));
			strcpy(pNewData->song, strtok(NULL, ","));
			strcpy(pNewData->genre, strtok(NULL, ","));
			pNewData->length.minutes = atoi(strtok(NULL, ":"));
			pNewData->length.seconds = atoi(strtok(NULL, ","));
			pNewData->playCount = atoi(strtok(NULL, ","));
			pNewData->rating = atoi(strtok(NULL, "\0"));
		}
		else
		{
			strcpy(pNewData->artist, strtok(line, ","));
			strcpy(pNewData->album, strtok(NULL, ","));
			strcpy(pNewData->song, strtok(NULL, ","));
			strcpy(pNewData->genre, strtok(NULL, ","));
			pNewData->length.minutes = atoi(strtok(NULL, ":"));
			pNewData->length.seconds = atoi(strtok(NULL, ","));
			pNewData->playCount = atoi(strtok(NULL, ","));
			pNewData->rating = atoi(strtok(NULL, "\0"));
		}
		
		success = insertFront(pList, pNewData);

	}
	return success;
}

void display(List* pList){
	int success = 0;
	int choice = 0;
	char search[40] = {'\0'};
	Node* pMem = pList->pHead;
		do {
			printf("Would you like to display all or just by artist\n1.Display all\n2. Display Artist\n");
			scanf("%d", &choice);
		} while (choice != 1 && choice != 2);


	if (choice == 1) {
		while (pMem != NULL) {
			printf("\n%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
				pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

			pMem = pMem->pNext;
			success = 1;
		}
		
	}

	if (choice == 2) {
		printf("Please type in an artist to search for:\n");
		
		scanf("%s", &search);

		while (pMem != NULL) {

			if (strcmp(pMem->songInfo.artist, search) == 0) {
				printf("\n%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
					pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);
				success = 1;
			}
			pMem = pMem->pNext;
			
		}
	}
	if (success = 0) {
		printf("No artist of that name was found.");
		}
		return success;
}

int edit() {

}

int rate(List* pList) {
	char search[40] = { '\0' };
	Node* pMem = pList->pHead;
	int success = 0;
	int rating = 0;

	printf("Please type in a song to search for:\n");
	do {
		scanf("%s", &search);
	} while (search != NULL);

	while (pMem != NULL) {
		if (strcmp(pMem->songInfo.song, search) == 0) {
			printf("What would you like to rate this song? 1 - 5 Rating scale.\n");
			do {
				scanf("&d", &rating);
			}while(success < 1 && success > 5);

			success = 1;
		}

		pMem = pMem->pNext;
	}
	return success;
}

int play(List*pList) {

}

int exitDmm(List* pList, FILE* infile) {
	int success = 1;
	Node* pMem = pList->pHead;
	while (pMem != NULL) {

		fprintf("%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
			pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

		pMem = pMem->pNext;
		success = 0;
	}
	return success;
}

void initList(List* pList)
{
	//empty list
	pList->pHead = NULL; // (*pList).phead = NULL;
}

Node* makeNode(const Data* pNewData) {

	Node* pMem = (Node*)malloc(sizeof(Node)); // we tried to allocate space

	if (pMem != NULL)
	{
		//malloc succeeded in allocating a Node
		strcpy(pMem->songInfo.song, pNewData->song);
		strcpy(pMem->songInfo.album, pNewData->album);
		strcpy(pMem->songInfo.artist, pNewData->artist);
		strcpy(pMem->songInfo.genre, pNewData->genre);
		pMem->songInfo.length.minutes = pNewData->length.minutes;
		pMem->songInfo.length.seconds = pNewData->length.seconds;
		pMem->songInfo.rating = pNewData->rating;
		pMem->songInfo.playCount = pNewData->playCount;
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}

int insertFront(List* pList, const Data* pNewData)
{
	Node* pMem = makeNode(pNewData);
	int success = 0;

	if (pMem != NULL)
	{
		if (pList->pHead != NULL) {
			pMem->pNext = pList->pHead;
			pList->pHead->pPrev = pMem;
		}
		pList->pHead = pMem;
		success = 1;
	}
	
	return success;
}