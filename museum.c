#include "museum.h"

void initList(ItemList* list) {
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}
void freeList(ItemList* list) {
    if (list->items) {
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}
void resizeList(ItemList* list) {
    if (list->count >= list->capacity) {
        int newCapacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        Item* newItems = (Item*)realloc(list->items, newCapacity * sizeof(Item));
        if (!newItems) {
            fprintf(stderr, "Mem creation error\n");
            exit(1);
        }
        list->items = newItems;
        list->capacity = newCapacity;
    }
}
int loadFromFile(ItemList* list, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        initList(list);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    int itemCount = fileSize / sizeof(Item);
    list->items = (Item*)malloc(itemCount * sizeof(Item));
    if (!list->items) {
        fclose(file);
        fprintf(stderr, "Mem creation error\n");
        return -1;
    }
    size_t readCount = fread(list->items, sizeof(Item), itemCount, file);
    fclose(file);
    list->count = readCount;
    list->capacity = itemCount;
    return 0;
}
int saveToFile(const ItemList* list, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Cannot open file\n");
        return -1;
    }
    size_t written = fwrite(list->items, sizeof(Item), list->count, file);
    fclose(file);
    if (written != (size_t)list->count) {
        fprintf(stderr, "Sving Error\n");
        return -1;
    }
    return 0;
}
void printItems(const ItemList* list) {
    if (list->count == 0) {
        printf("Empty\n");
        return;
    }
    printf("\n--- Museum inventory ---\n");
    for (int i = 0; i < list->count; i++) {
        printf("ID: %d\n", list->items[i].id);
        printf("Name: %s\n", list->items[i].name);
        printf("Description: %s\n", list->items[i].description);
        printf("Category: %s\n", list->items[i].category);
        printf("Year: %d\n", list->items[i].year);
        printf("Prise: %.2f\n", list->items[i].value);
        printf("- - - - - - - - - - -\n");
    }
}
void addItem(ItemList* list) {
    resizeList(list);
    Item* item = &list->items[list->count];
    item->id = list->count + 1;
    printf("Name: ");
    scanf(" %99[^\n]", item->name);
    printf("Description: ");
    scanf(" %199[^\n]", item->description);
    printf("Category: ");
    scanf(" %49[^\n]", item->category);
    printf("Year: ");
    scanf("%d", &item->year);
    printf("Prise: ");
    scanf("%lf", &item->value);
    list->count++;
    printf("Added\n");
}
void deleteItem(ItemList* list) {
    if (list->count == 0) {
        printf("Empty!\n");
        return;
    }
    int id;
    printf("Put id to delite item: ");
    scanf("%d", &id);
    for (int i = 0; i < list->count; i++) {
        if (list->items[i].id == id) {
            for (int j = i; j < list->count - 1; j++) {
                list->items[j] = list->items[j + 1];
            }
            list->count--;
            printf("Delited sucsessfully!\n");
            return;
        }
    }
    printf("item ID %d not found\n", id);
}
void editItem(ItemList* list) {
    if (list->count == 0) {
        printf("empty\n");
        return;
    }
    int id;
    printf("inter № of item: ");
    scanf("%d", &id);
    for (int i = 0; i < list->count; i++) {
        if (list->items[i].id == id) {
            char input[200];
            printf("current name: %s\n", list->items[i].name);
            printf("new name : ");
            scanf(" %99[^\n]", input);
            if (strlen(input) > 0) strcpy(list->items[i].name, input);
            printf("current desc: %s\n", list->items[i].description);
            printf("new desc : ");
            scanf(" %199[^\n]", input);
            if (strlen(input) > 0) strcpy(list->items[i].description, input);
            printf("current category: %s\n", list->items[i].category);
            printf("new category : ");
            scanf(" %49[^\n]", input);
            if (strlen(input) > 0) strcpy(list->items[i].category, input);
            printf("current year: %d\n", list->items[i].year);
            printf("new year: ");
            int year;
            scanf("%d", &year);
            if (year != 0) list->items[i].year = year;
            printf("current prise: %.2f\n", list->items[i].value);
            printf("new prise: ");
            double value;
            scanf("%lf", &value);
            if (value != 0.0) list->items[i].value = value;
            printf("shanged!\n");
            return;
        }
    }
    printf("item № %d not found\n", id);
}
void searchItems(const ItemList* list) {
    if (list->count == 0) {
        printf("Empty\n");
        return;
    }
    char searchTerm[100];
    int yearFilter = 0;
    double valueFilter = 0.0;
    printf("Search\n");
    printf("input 1 of the item spec words: ");
    scanf(" %99[^\n]", searchTerm);
    printf("year filter: ");
    scanf("%d", &yearFilter);
    printf("price filter: ");
    scanf("%lf", &valueFilter);
    printf("\nsearch result:\n");
    int found = 0;
    for (int i = 0; i < list->count; i++) {
        int textMatch = (strstr(list->items[i].name, searchTerm) != NULL ||
                         strstr(list->items[i].description, searchTerm) != NULL ||
                         strstr(list->items[i].category, searchTerm) != NULL);
        int yearMatch = (yearFilter == 0) || (list->items[i].year == yearFilter);
        int valueMatch = (valueFilter == 0.0) || (list->items[i].value >= valueFilter);
        if (textMatch && yearMatch && valueMatch) {
            printf("№: %d\n", list->items[i].id);
            printf("name: %s\n", list->items[i].name);
            printf("description: %s\n", list->items[i].description);
            printf("category: %s\n", list->items[i].category);
            printf("year: %d\n", list->items[i].year);
            printf("price: %.2f\n", list->items[i].value);
            printf("- - - - - - - - - - -\n");
            found++;
        }
    }

    if (found == 0) {
        printf("not found\n");
    } else {
        printf("search results: %d\n", found);
    }
}