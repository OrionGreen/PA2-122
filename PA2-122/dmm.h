#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> //sleep(2000) time to stay.

typedef struct duration
{
	int minutes;//4
	int seconds;//4
}Duration;//8

typedef struct data
{
	char artist[20]; // 20 bytes
	char album[20];//20
	char song[20];//20
	char genre[20];//20
	Duration length;//8
	int playCount;//4 bytes
	int rating;//4 bytes

}Data;//96 bytes


typedef struct node
{
	Data songInfo;//54 bytes
	struct node* pNext;//4 bytes
	struct node* pPrev; //4bytes
} Node;//62 bytes

typedef struct list
{
	Node* pHead;
}List;


void menuOptions(List* pList, Data* data, FILE* infile);
void initList(List* pList);
Node* makeNode(const Data* pNewData);
int insertFront(List* pList, const Data* pNewData);
int store(List* pList, FILE* infile);
int load(List* pList, Data* pNewData, FILE* infile);
void display(List* pList);
int exitDmm(List* pList, FILE* infile);