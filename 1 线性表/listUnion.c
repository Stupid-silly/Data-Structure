#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem;

typedef struct {
    Elem *elems;
    int length;
    int capacity;  
} List;

void listVisit(List *list)
{
    int i;

    printf("List elems:");
    for (i = 0; i < list->length; i++)
        printf("  %d", list->elems[i]);
    printf("\n");
}

#define INITIAL_CAPACITY 4

void listInit(List *list)
{
    list->elems = malloc(sizeof(Elem) * INITIAL_CAPACITY);
    list->length = 0;
    list->capacity = INITIAL_CAPACITY;
}

void listDestroy(List *list)
{
    free(list->elems);
}

int listLength(List *list)
{
    return list->length;
}

int listEmpty(List *list)
{
    return list->length == 0;
}

Elem listGetElem(List *list, int index)
{
    assert(index >= 0 && index < list->length);
    return list->elems[index];
}

void listPutElem(List *list, int index, Elem elem)
{
    assert(index >= 0 && index < list->length);
    list->elems[index] = elem;
}

int listLocateElem(List *list, Elem elem)
{
    int i;

    for (i = 0; i < list->length; i++) {
        if (list->elems[i] == elem)
            return i;
    }
    return -1;
}

void listInsertElem(List *list, int index, Elem elem)
{
    assert(index >= 0 && index <= list->length);

    if (list->length >= list->capacity) {
        int newCapacity = list->capacity * 2;
        list->elems = realloc(list->elems, sizeof(Elem) * newCapacity);
        list->capacity = newCapacity;
    }

    int i;
    for (i = list->length; i > index; i--)
        list->elems[i] = list->elems[i - 1];
    list->elems[index] = elem;
    list->length++;
}

void listAppendElem(List *list, Elem elem)
{
    listInsertElem(list, list->length, elem);
}

void listDeleteElem(List *list, int index)
{
    assert(index < list->length);

    int i;
    for (i = index; i < list->length - 1; i++) 
        list->elems[i] = list->elems[i + 1];
    list->length--;
}

void testListAppendElem()
{
    List list;
    listInit(&list);

    int i;
    for (i = 0; i < 8; i++)
        listAppendElem(&list, i);
    listVisit(&list);

    listDestroy(&list);
}

void listUnion(List *listA, List *listB, List *listC)
{
	//遍历A。
	int i;
    for (i = 0; i < listA->length; i++)
    {
		Elem e=listGetElem(listA,i);
		listAppendElem(listC,e);
    }
	
	//遍历B，在A中查找
    for (i = 0; i < listB->length; i++)
    {
		Elem e=listGetElem(listB,i);
		int i=listLocateElem(listA,e);
		
		if(i==-1)
		{
			listAppendElem(listC,e);
		}
    }
	
}

void testListUnion()
{
    List listA;
    listInit(&listA);
    listAppendElem(&listA, 1);
    listAppendElem(&listA, 2);
    listAppendElem(&listA, 3);

    List listB;
    listInit(&listB);
    listAppendElem(&listB, 2);
    listAppendElem(&listB, 3);
    listAppendElem(&listB, 4);
    listAppendElem(&listB, 5);

    List listC;
    listInit(&listC);

    listUnion(&listA, &listB, &listC);
    listVisit(&listC);
}

int main()
{
    testListUnion();
    return 0;
}