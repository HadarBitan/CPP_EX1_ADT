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
    //aloocate a memory for the struct
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
    //check if the struct is null, if it is null then there isn't something to delete and we finish
    if(padt == NULL)
    {
        return;
    }
    //if the struct exists but the the array is null then all we left to do is free the struct
    if(padt->pelmt == NULL)
    {
        free(padt);
        return;
    }
    //if everything exists then we have to free all the elements according to the delete function of the ADT array
    //after we delete all the elements properly we free the array of element and the struct itself
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
    //in this function we get an index, an element and an ADT array struct
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
    //here we have to properly free and delete the old array so we need to use ahe array's delete function if we get a non null elemnt
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
    // Delete Previous Element if exists and Set New Elem
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
    //in this function we get an index and a struct and return the element in the index
    //error checks, if the struct is null or its' array is null to the index is not in our bounds or the element itself is null then return null
    if(padt == NULL || index > padt->size || padt->pelmt == NULL || padt->pelmt[index] == NULL)
    {
        return NULL;
    }
    return padt->copy(padt->pelmt[index]);
}

int GetAdptArraySize(PAdptArray padt)
{
    //if the ADT array in null we return -1 else we get the size from the struct
    if(padt == NULL)
    {
        return -1;
    }
    return padt->size;
}

void PrintDB(PAdptArray padt)
{
    //In this function we print all the elements in the array according to the print function belong to the array
    for(int i = 0; i< padt->size; i++)
    {
        //checking if the element is null, if it is null we dont print it
        if(padt->pelmt[i] != NULL)
            padt->print(padt->pelmt[i]);
    }
}
