/*
 * HeapManager.cpp
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed Essam
 */


#include "HeapManager.h"

HeapManager::HeapManager(int heapsize , int BlSize)
{
	assert(("Heap size can't be negative or equal zero" , heapsize > 0)) ;
	assert(("Block size can't be negative or equal zero" , BlSize > 0)) ;
	assert(("Block size can't be larger than heap size" ,heapsize*1024*1024 >= BlSize)) ;
	assert(("Insert correct size of a block" , ((heapsize*1024*1024) % BlSize)==0 )) ;
    char* MyHeap = new char[heapsize*1024*1024] ;
    BlockSize=BlSize ;
    link addednode = new node ;
    head=addednode ;
    assert(addednode != NULL) ;
    head->heapPtr= MyHeap ;            //heapPtr of the first node points to the heap's top
    head->Bsize=heapsize*1024*1024 ;
    head->flag=0 ;                     //The node flag indicates that the heap now is empty
    head->prev=NULL ;
    head->next=NULL ;
    Hsize=heapsize*1024*1024 ;
}


int HeapManager::bestFit(int ReqSize)
{
    link FindPtr = head ;    //points to the first best fit location
    minimum=Hsize ;
    int temp ;
    int success=0 ;          //The return of the function is 0 or 1 or 2
    /* function to occupy the whole block */
    for(int i=1 ;  ;i++)
    {
        if(ReqSize <= BlockSize*i)
        {
            Bcalculated=BlockSize*i ;
            break ;
        }
    }
    //____________________________________//
    while(FindPtr != NULL)
    {
        if(FindPtr->flag==1)        //if a contiguous blocks are allocated, continue search
        {
            FindPtr = FindPtr->next ;
            continue ;
        }
        else
        {
            if(FindPtr->Bsize==Bcalculated)
            {
            	//if the contiguous blocks are empty and have the same size, return 1
                BestFitPtr=FindPtr ;
                return 1 ;
            }
            /*calculate the best fit free location through the whole heap*/
            else
            {
                if(FindPtr->Bsize > Bcalculated)
                {
                    temp=FindPtr->Bsize ;
                    success=2 ;
                }
                if(temp <= minimum)
                {
                    minimum=temp ;
                    BestFitPtr=FindPtr ;
                }
            }
            //___________________________________________________________//
        }
        FindPtr=FindPtr->next ;
    }

    return success ;
}

void* HeapManager::memalloc(int ReqSize)
{
    int y=bestFit(ReqSize) ; //search for the best fitting location for the required size
    if(y==0)                // no allocation is occurred
    {
        cout<<"could not allocate the size "<<ReqSize<<endl ;
        return NULL ;
    }
    else if (y==1)        //if the free location is just equal to the required no. of blocks
    {
        BestFitPtr->Bsize=Bcalculated ;
        BestFitPtr->flag=1 ;
        return (BestFitPtr->heapPtr) ;
    }
    else if (y==2)    //If the free location is bigger than the required no. of blocks
    {
        BestFitPtr->flag=1 ;
        link addednode = new node ;
        assert(addednode != NULL) ;
        addednode->flag=0 ;
        addednode->Bsize = BestFitPtr->Bsize - Bcalculated ;
        BestFitPtr->Bsize = Bcalculated ;
        addednode->heapPtr = BestFitPtr->heapPtr + BestFitPtr->Bsize ;
        if(BestFitPtr->next != NULL)
        	BestFitPtr->next->prev = addednode ;
        addednode->next = BestFitPtr -> next ;
        addednode->prev = BestFitPtr ;
        BestFitPtr->next = addednode ;
        return (BestFitPtr->heapPtr) ;
    }
    else
    {
        cout<<"How!"<<endl ;
    }
}

void HeapManager::memfree(void* ptr)
{
	assert(("The pointer points to NULL", ptr != NULL)) ;
	/*search for the address of the block that is required to be free */
    current=head ;
    while(current!=NULL)
    {
        if(current->heapPtr==ptr)
        {
            break ;
        }
        current=current->next ;
    }
    //________________________________________________________________//
    if(current==NULL)
        cout<<"No such address is found"<<endl ;
    /* Memory aggregation */
    /* if the next block is free */
    else if ((current->next!=NULL) && (current->next->flag==0))
    {
    	current->flag = 0 ;
    	current ->Bsize +=current->next->Bsize ;
    	if( current->next->next == NULL)
    	{
    		link deletion = current->next ;
    		delete deletion ;
    		current->next=NULL ;
    	}
    	else
    	{
    		link deletion = current->next ;
    		current->next->next->prev = current ;
    		current->next = current->next->next ;
    		delete deletion ;
    	}
    	if((current->prev !=NULL) && (current->prev->flag==0))
    	{
    		current->prev->Bsize += current->Bsize ;
    		if(current->next != NULL)
    			current->next->prev = current->prev ;
    		current->prev->next = current->next ;
    		delete current ;
    	}
    }
    /* if the previous block is free */
    else if((current->prev != NULL) &&(current->prev->flag==0))
    {
    	current->prev->Bsize += current->Bsize ;
    	if( current->next != NULL)
    		current->next->prev = current->prev ;
    	current->prev->next = current->next ;
    	delete current ;
    }
    /* if there is no block aggregation reuired */
    else
    {
        current->flag=0 ;
    }
}

void HeapManager::ShowDetail()
{
    link show ;
    show=head ;
    char *st1="Free" ;
    char *st2="Allocated" ;
    cout<<"Start Address:       Size:       Status:"<<endl ;
    while(show != NULL)
    {
        if(show->flag==0)
            cout<<show->heapPtr<<"              "<<show->Bsize<<"           "<<st1<<endl ;
        else
            cout<<show->heapPtr<<"              "<<show->Bsize<<"           "<<st2<<endl ;

        show=show->next ;
    }
}



