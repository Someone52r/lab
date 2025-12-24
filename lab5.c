#include "museum.h"

#define DATABASE "museum.dat"

int inputInt(int* out) {
    char buffer[64];
    char* endptr;

    if (!fgets(buffer, sizeof(buffer), stdin))
        return 0;

    *out = (int)strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\n')
        return 0;

    return 1;
}

int main() {
    ItemList list;
    initList(&list);
    if (loadFromFile(&list, DATABASE) != 0) {
        fprintf(stderr, "data error\n");
        freeList(&list);
        return 1;
    }

    int choice;
    do {
        printf("\n=== Museum inventory ===\n");
        printf("1. Show full list\n");
        printf("2. Add\n");
        printf("3. Delete\n");
        printf("4. Edit\n");
        printf("5. Search\n");
        printf("6. Save & exit\n");
        printf("Choose 1-6: ");
        
        if (!inputInt(&choice)) {
    printf("Incorrect input. Enter number 1-6.\n");
    continue;
        }

        switch (choice) {
            case 1:
                printItems(&list);
                break;
            case 2:
                addItem(&list);
                break;
            case 3:
                deleteItem(&list);
                break;
            case 4:
                editItem(&list);
                break;
            case 5:
                searchItems(&list);
                break;
            case 6:
                if (saveToFile(&list, DATABASE) == 0) {
                    printf("Saved\n");
                } else {
                    fprintf(stderr, "Saving error\n");
                }
                break;
            default:
                printf("Incorrect input.\n");
        }
    } while (choice != 6);
    freeList(&list);
    return 0;
}
