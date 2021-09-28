#include "dmm.h"

void menuOptions(List* pList, Data* data, FILE* infile) {
	int go = 1;
	
	while (go != 0) {
		printf("\nWhat would you like to do today\n1. Load\n2. Store\n3. Display\n4. Insert\n5. Delete\n6. Edit\n7. Sort\n8. Rate\n9. Play\n10. Shuffle\n11. Exit\n");
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
			int check = 0;
			do {
				Data newData;
				gatherData(&newData);
				check = insert(pList, &newData);
			} while (check == 0);
			check = 0;
		}

		if (choice == 5) {
			int check = 0;
			do {
				Data newData;
				gatherSongToDelete(&newData);
				check = delete(pList, &newData);
			} while (check == 0);
			check = 0;
		}
		if (choice == 6) {
			int check = 0;
			do {
				check = edit(pList);
			} while (check == 0);
		}
		if (choice == 7) {
			int check = 0;
			do {
				check = sortChoice(pList);
			} while (check == 0);
			check = 0;
		}
		if (choice == 8) {
			int check = 0;
			do {
				check = rate(pList);
			} while (check == 0);
			check = 0;
		}
		if (choice == 9) {
			int check = 0;
			do {
				check = play(pList);
			} while (check == 0);
			check = 0;
		}
		if (choice == 10) {
			int check = 0;
			int areturn[100] = { 0 };
			do {
				randOrder(pList, areturn);
				check = 0;
				check = shuffle(pList, areturn);
			} while (check == 0);
			check = 0;
		}
		if (choice == 11) {
			go = exitDmm(pList, infile);
		}
		
	}
}

int store(List* pList, FILE* infile) {
	int success = 0;
	Node* pMem = pList->pHead;

	while (pMem != NULL) {
		
		fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
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
		printList(pList->pHead);
		success = 1;
	}

	if (choice == 2) {
		
		//Finally found this fix online #gogoogleit
		do {
			printf("Please type in an artist to search for:\n");
			getchar();
			fgets(search, 40, stdin);
			search[strlen(search) - 1] = '\0';
			printf("\nYou searched for: %s\n", search);
		} while (search == NULL);

		while (pMem != NULL) {

			if (strcmp(pMem->songInfo.artist, search) == 0) {
				printList(pMem);
			}
			pMem = pMem->pNext;
			success = 1;
		}
		if (success == 0) {
			printf("\nNo Artist of that name was found.\n");
		}
	}

		return success;
}

int edit(List* pList) {
	int success = 0;
	int choice = 0;
	char search[40] = { '\0' };
	Node* pMem = pList->pHead;

	//Finally found this fix online #gogoogleit
	do {
		printf("Please type in an artist to search for:\n");
		getchar();
		fgets(search, 40, stdin);
		search[strlen(search) - 1] = '\0';
		printf("\nYou searched for: %s\n", search);
	} while (search == NULL);

	while (pMem != NULL) {

		if (strcmp(pMem->songInfo.artist, search) == 0) {
			printf("Would you like to change the information for this song?\n");
			printf("%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
				pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);
			printf("1.Yes\n2. No\nEnter 1 or 2.");

			do {
				scanf("%d", &choice);
			} while (choice == 0 || choice > 2);
			system("cls");

			if (choice == 1) {

				int success = 0;
				char input[40] = { '\0' };
				int userInt = 0;

				printf("Please type in the edited song name:\n");
				do {
					getchar();
					fgets(input, 40, stdin);
					input[strlen(input) - 1] = '\0';
				} while (input == NULL);
				strcpy(pMem->songInfo.song, input);
				strcpy(input, "\0");

				printf("Please type in the edited artist's name:\n");
				do {

					fgets(input, 40, stdin);
					input[strlen(input) - 1] = '\0';
				} while (input == NULL);
				strcpy(pMem->songInfo.artist, input);
				strcpy(input, "\0");

				printf("Please type in an edited album name:\n");
				do {

					fgets(input, 40, stdin);
					input[strlen(input) - 1] = '\0';
				} while (input == NULL);
				strcpy(pMem->songInfo.album, input);
				strcpy(input, "\0");

				printf("Please type in an edited genre:\n");
				do {

					fgets(input, 40, stdin);
					input[strlen(input) - 1] = '\0';
				} while (input == NULL);
				strcpy(pMem->songInfo.genre, input);
				strcpy(input, "\0");

				printf("Please type in an edited song length in minutes:seconds format\n");
				do {

					fgets(input, 40, stdin);
					input[strlen(input) - 1] = '\0';
				} while (input == NULL);
				pMem->songInfo.length.minutes = atoi(strtok(input, ":"));
				pMem->songInfo.length.seconds = atoi(strtok(NULL, "\0"));

				printf("\nPlease type in an edited rating:\n");
				do {
					scanf("%d", &userInt);

				} while (userInt == 0 || userInt > 5);
				pMem->songInfo.rating = userInt;
				userInt = -1;

				printf("\nPlease type in an edited play count amount:\n");
				do {
					scanf("%d", &userInt);

				} while (userInt < 0);
				pMem->songInfo.playCount = userInt;
				success = 1;
			}
			if (choice == 2) {
				success = 1;
			}

		}
		pMem = pMem->pNext;
		success = 1;
	}

	return success;
}

int rate(List* pList) {
	char search[40] = { '\0' };
	Node* pMem = pList->pHead;
	int success = 0;
	int rating = 0;

	//Finally found this fix online #gogoogleit
	do {
		printf("Please type in a song to search for:\n");
		getchar();
		fgets(search, 40, stdin);
		search[strlen(search) - 1] = '\0';
		printf("\nYou searched for: %s\n", search);
	} while (search == NULL);

	while (pMem != NULL) {
		if (strcmp(pMem->songInfo.song, search) == 0) {
			printf("What would you like to rate this song? 1 - 5 Rating scale.\n");
			do {
				scanf("%d", &rating);
			}while(rating < 1 || rating > 5);

			pMem->songInfo.rating = rating;
		}
		success = 1;
		pMem = pMem->pNext;
	}
	return success;
}

int play(List* pList) {
	Node* pMem = pList->pHead;
	int success = 0;
	int choice = 0;
	char search[40] = { '\0' };

	do {
		printf("Would you like to play all or from a specific song?\n1.Play all\n2. Play from Song\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2);

	if (choice == 1) {
		while (pMem != NULL) {

			printf("\n%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
				pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

			pMem->songInfo.playCount++;

			Sleep(4000);
			system("cls");

			pMem = pMem->pNext;
			success = 1;
		}
	}

	if (choice == 2) {

		do {
			printf("Please type in a song to search for\n");
			getchar();
			fgets(search, 40, stdin);
			search[strlen(search) - 1] = '\0';
			printf("\nYou searched for: %s\n", search);
		} while (search == NULL);

		while (pMem != NULL) {

			if (strcmp(pMem->songInfo.song, search) == 0) {
				while (pMem != NULL) {
					printf("\n%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
						pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

					pMem->songInfo.playCount++;

					Sleep(4000);
					system("cls");

					pMem = pMem->pNext;
				}
				continue;
			}
			pMem = pMem->pNext;
		}

		success = 1;
	}


	return success;
}

void printList(Node* pHead) {
	Node* pMem = pHead;

	printf("\n");
	while (pMem != NULL) {
		printf("%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
			pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

		pMem = pMem->pNext;
	}
}

int exitDmm(List* pList, FILE* infile) {
	int success = 1;
	Node* pMem = pList->pHead;

	while (pMem != NULL) {

		fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
			pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);

		pMem = pMem->pNext;
		success = 0;
	}
	return success;
}

int insert(List* pList, Data* data) {
	

	int success = 0;
	char input[40] = { '\0' };
	int userInt = 0;

	if (data->album != NULL && data->artist != NULL && data->genre != NULL && data->song != NULL && 
		data->playCount > 0 && data->rating <= 5 && data->rating > 0 && data->length.seconds >= 0) {
		insertFront(pList, data);
		success = 1;
	}
	else {
		printf("Your inserted data is invalid please try again!\n");
	}

	return success;
}

int delete(List* pList, Data* data) {
	int success = 0;
	int choice = 0;
	char search[40] = { '\0' };
	Node* pMem = pList->pHead;

	Node* pPrev = NULL;

	while (pMem != NULL) {
		if (strcmp(pMem->songInfo.song, data->song) == 0 && pMem->pPrev == NULL) {
			pList->pHead = pMem->pNext;
			free(pMem);
			success = 1;
			break;
		}

		else if (strcmp(pMem->songInfo.song, data->song) == 0 && pMem->pNext == NULL) {
			pMem->pPrev->pNext = NULL;
			free(pMem);
			success = 1;
			break;
		}

		else if (strcmp(pMem->songInfo.song, data->song) == 0) {
			pPrev->pNext = pMem->pNext;
			pMem->pPrev = pPrev;
			free(pMem);
			success = 1;
			break;
		}
		pPrev = pMem;
		pMem = pMem->pNext;
	}

	return success;
}

void randOrder(List* pList, int areturn[]) {
	Node* pMem = pList->pHead;
	int counter = 0;
	while (pMem != NULL) {
		counter++;
		pMem = pMem->pNext;
	}
	pMem = pList->pHead;

	const int maxSize = counter;


	for (int i = 0; i < maxSize; i++) {
		areturn[i] = i + 1;
	}
	srand(time(NULL));

	for (int i = maxSize - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(&areturn[i], &areturn[j]);
	}

}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int shuffle(List* pList, int shufarr[]) {
	Node* pMem = pList->pHead;
	int nodeSpot = 0;
	int i = 0;
	int found = 0;
	int success = 0;
	while (pMem != NULL) {
		nodeSpot = 0;
		if (shufarr[i] == 0) {
			break;
		}
		while (found != 1) {
			if (nodeSpot == shufarr[i]) {
				printf("Now Playing:");
				printf("\n%s,%s,%s,%s,%d:%d,%d,%d\n", pMem->songInfo.artist, pMem->songInfo.album, pMem->songInfo.song,
					pMem->songInfo.genre, pMem->songInfo.length.minutes, pMem->songInfo.length.seconds, pMem->songInfo.playCount, pMem->songInfo.rating);
				pMem->songInfo.playCount++;
				Sleep(4000);
				system("cls");

				while (pMem->pPrev != NULL) {
					pMem = pList->pHead;
				}
				found = 1;
			}
			if (pMem->pNext != NULL) {
				pMem = pMem->pNext;
			}
			nodeSpot++;
		}
		i++;
		success = 1;
		found = 0;
	}
	return success;
}

int sortChoice(List* pList) {
	
	Node* pTemp = NULL;
	printf("\nHow would you like to sort today:\n1.Sort based on artist (A-Z)\n2.Sort based on album title(A - Z)\n3.Sort based on rating(1 - 5)\n4.Sort based on times played(largest - smallest)\n");
	int choice = 0;
	int success = 0;

	do {
		scanf("%d", &choice);
	} while (choice == 0 || choice > 4);

	if (choice == 1) {
		bubbleSortArtist(pList);
		success = 1;
	}

	if (choice == 2) {
		bubbleSortAlbum(pList);
		success = 1;
	}

	if (choice == 3) {
		bubbleSortRating(pList);
		success = 1;
	}

	if (choice == 4) {
		bubbleSortTimesPlayed(pList);
		success = 1;
	}

	return success;
}

void bubbleSortArtist(List* pList) {
	Node* pMem;
	Node* pPrev = NULL;
	int swap;
	if (pList->pHead == NULL) {
		return;
	}

	do {
		swap = 0;
		pMem = pList->pHead;
		while (pMem->pNext != pPrev) {
			if (strcmp(pMem->songInfo.artist, pMem->pNext->songInfo.artist) > 0) {
				swapData(pMem, pMem->pNext);
				swap = 1;
			}
			pMem = pMem->pNext;
		}
		pPrev = pMem;
	} while (swap);
}

void bubbleSortAlbum(List* pList) {
	Node* pMem;
	Node* pPrev = NULL;
	int swap;
	if (pList->pHead == NULL) {
		return;
	}

	do {
		swap = 0;
		pMem = pList->pHead;
		while (pMem->pNext != pPrev) {
			if (strcmp(pMem->songInfo.album, pMem->pNext->songInfo.album) > 0) {
				swapData(pMem, pMem->pNext);
				swap = 1;
			}
			pMem = pMem->pNext;
		}
		pPrev = pMem;
	} while (swap);
}

void bubbleSortRating(List* pList) {
	Node* pMem;
	Node* pPrev = NULL;
	int swap;
	if (pList->pHead == NULL) {
		return;
	}

	do {
		swap = 0;
		pMem = pList->pHead;
		while (pMem->pNext != pPrev) {
			if (pMem->songInfo.rating > pMem->pNext->songInfo.rating) {
				swapData(pMem, pMem->pNext);
				swap = 1;
			}
			pMem = pMem->pNext;
		}
		pPrev = pMem;
	} while (swap);
}

void bubbleSortTimesPlayed(List* pList) {
	Node* pMem;
	Node* pPrev = NULL;
	int swap;
	if (pList->pHead == NULL) {
		return;
	}

	do {
		swap = 0;
		pMem = pList->pHead;
		while (pMem->pNext != pPrev) {
			if (pMem->songInfo.playCount < pMem->pNext->songInfo.playCount) {
				swapData(pMem, pMem->pNext);
				swap = 1;
			}
			pMem = pMem->pNext;
		}
		pPrev = pMem;
	} while (swap);
}

void swapData(Node* swap, Node* set) {
	Node temp = {NULL};

	strcpy(temp.songInfo.artist, swap->songInfo.artist);
	strcpy(temp.songInfo.album, swap->songInfo.album);
	strcpy(temp.songInfo.genre, swap->songInfo.genre);
	strcpy(temp.songInfo.song, swap->songInfo.song);
	temp.songInfo.length.minutes = swap->songInfo.length.minutes;
	temp.songInfo.length.seconds = swap->songInfo.length.seconds;
	temp.songInfo.playCount = swap->songInfo.playCount;
	temp.songInfo.rating = swap->songInfo.rating;

	strcpy(swap->songInfo.artist, set->songInfo.artist);
	strcpy(swap->songInfo.album, set->songInfo.album);
	strcpy(swap->songInfo.genre, set->songInfo.genre);
	strcpy(swap->songInfo.song, set->songInfo.song);
	swap->songInfo.length.minutes = set->songInfo.length.minutes;
	swap->songInfo.length.seconds = set->songInfo.length.seconds;
	swap->songInfo.playCount = set->songInfo.playCount;
	swap->songInfo.rating = set->songInfo.rating;

	strcpy(set->songInfo.artist, temp.songInfo.artist);
	strcpy(set->songInfo.album, temp.songInfo.album);
	strcpy(set->songInfo.genre, temp.songInfo.genre);
	strcpy(set->songInfo.song, temp.songInfo.song);
	set->songInfo.length.minutes = temp.songInfo.length.minutes;
	set->songInfo.length.seconds = temp.songInfo.length.seconds;
	set->songInfo.playCount = temp.songInfo.playCount;
	set->songInfo.rating = temp.songInfo.rating;

	
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

void gatherSongToDelete(Data* newData) {
	int success = 0;
	char input[40] = { '\0' };
	int userInt = 0;

	printf("Please type in a song name:\n");
	do {
		getchar();
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	strcpy(newData->song, input);
	strcpy(input, "\0");
}

void gatherData(Data* newData) {
	
	//Data data;// = NULL;
	//Data* newData = &data;

	int success = 0;
	char input[40] = { '\0' };
	int userInt = 0;

	printf("Please type in a song name:\n");
	do {
		getchar();
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	strcpy(newData->song, input);
	strcpy(input, "\0");

	printf("Please type in an artist's name:\n");
	do {
		
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	strcpy(newData->artist, input);
	strcpy(input, "\0");

	printf("Please type in an album name:\n");
	do {
		
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	strcpy(newData->album, input);
	strcpy(input, "\0");

	printf("Please type in a genre:\n");
	do {
		
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	strcpy(newData->genre, input);
	strcpy(input, "\0");

	printf("Please type in song length in minutes:seconds format\n");
	do {
		
		fgets(input, 40, stdin);
		input[strlen(input) - 1] = '\0';
	} while (input == NULL);
	newData->length.minutes = atoi(strtok(input, ":"));
	newData->length.seconds = atoi(strtok(NULL, "\0"));

	printf("\nPlease type in a rating:\n");
	do {
		scanf("%d", &userInt);

	} while (userInt == 0 || userInt > 5);
	newData->rating = userInt;
	userInt = -1;

	printf("\nPlease type in a play count amount:\n");
	do {
		scanf("%d", &userInt);

	} while (userInt < 0);
	newData->playCount = userInt;

}