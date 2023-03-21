#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

//the base for SetAdptArrayAt function i borrowed from the exam of C last semester moed a
//and when i almost finished and got stuck with segmantation fault a freind of mine that did this course last year helped me find the mistake

struct AdptArray_
{
    int size;
    PElement* pelmt;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
};

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del,PRINT_FUNC print)
{
    PAdptArray adpt = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if (adpt == NULL) {
        printf("Memory not allocated.\n");
        return NULL;
    }
    adpt->size = 0;
    adpt->pelmt = NULL;
    adpt->copy = copy;
    adpt->del = del;
    adpt->print = print;
    return  adpt;
}

void DeleteAdptArray(PAdptArray padt)
{
    if(padt == NULL)
    {
        return;
    }
    if(padt->pelmt == NULL)
    {
        free(padt);
        return;
    }
    if (padt->pelmt != NULL)
    {
        for(int i = 0; i < padt->size; i++)
        {
            if (padt->pelmt[i] != NULL)
            {
                padt->del(padt->pelmt[i]);
            }
        }
        free(padt->pelmt);
        free(padt);
    }
}


Result SetAdptArrayAt(PAdptArray padt, int index, PElement element)
{
    PElement * temp = (PElement *) malloc((index + 1) * sizeof(PElement));
    if (padt == NULL)
        return FAIL;
    if (index >= padt->size)
    {
    // Extend Array
        if (temp == NULL)
            return FAIL;
    // Init new array and copy old array to new array
        for(int i = 0; i < padt->size; i++)
        {
            if(padt->pelmt[i] != NULL)
                temp[i] = padt->copy(padt->pelmt[i]);
            else
                temp[i] = NULL;
        }
        for(int i = padt->size; i < index + 1; i++)
        {
            temp[i] = NULL;
        }
    // Free old array and save new array
        for(int i = 0; i < padt->size; i++)
        {
            if(padt->pelmt[i] != NULL)
            {
                padt->del(padt->pelmt[i]);
            }
        }
        free(padt->pelmt);
        padt->pelmt = temp;
    }
    // Delete Previous Elem and Set New Elem
    if(padt->pelmt[index] != NULL)
    {
        padt->del(padt->pelmt[index]);
    }
    padt->pelmt[index] = padt->copy(element);
    // Update Array Size
    padt->size = (index >= padt->size) ? (index + 1) : padt->size;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray padt, int index)
{
    if(padt == NULL || index > padt->size || padt->pelmt == NULL || padt->pelmt[index] == NULL)
    {
        return NULL;
    }
    return padt->copy(padt->pelmt[index]);
}

int GetAdptArraySize(PAdptArray padt)
{
    if(padt == NULL)
    {
        return -1;
    }
    return padt->size;
}

void PrintDB(PAdptArray padt)
{
    for(int i = 0; i< padt->size; i++)
    {
        if(padt->pelmt[i] != NULL)
            padt->print(padt->pelmt[i]);
    }
}
