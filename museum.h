#ifndef MUSEUM_H
#define MUSEUM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char description[200];
    char category[50];
    int year;
    double value;
} Item;
typedef struct {
    Item* items;
    int count;
    int capacity;
} ItemList;
void initList(ItemList* list);
void freeList(ItemList* list);
int loadFromFile(ItemList* list, const char* filename);
int saveToFile(const ItemList* list, const char* filename);
void printItems(const ItemList* list);
void addItem(ItemList* list);
void deleteItem(ItemList* list);
void editItem(ItemList* list);
void searchItems(const ItemList* list);
void resizeList(ItemList* list);

#endif