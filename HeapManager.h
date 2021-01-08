/*
 * HeapManager.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed Essam
 */

#ifndef HEAPMANAGER_H_
#define HEAPMANAGER_H_

#include <iostream>
#include <assert.h>

using namespace std;

class HeapManager
{
private:
	int bestFit(int ReqSize) ;
    struct node ;
    typedef node* link ;  //A pointer to node
    struct node
    {
        int Bsize ;      //allocated or free contiguous of blocks' size
        int flag ;       //indicate whether a contiguous of blocks is empty or not
        void* heapPtr ;  //A pointer points to the start address of an empty or allocated block
        link next ;      //A doubly linked list is used
        link prev ;      //A doubly linked list is used
    };
    link head ;          //A pointer points to the first node
    link current ;
    int BlockSize ;      //A constant size of the blocks that construct the heap
    int minimum ;        //A variable that is used in best fit algorithm
    int Bcalculated ;    //A variable that is used in best fit algorithm
    int Hsize ;          //A variable that holds the heap size
    link BestFitPtr ;    //A pointer to the best fit free location
public:
    HeapManager(int heapsize , int BlSize) ;
    void* memalloc(int ReqSize) ;
    void memfree(void* ptr) ;
    void ShowDetail() ;
};



#endif /* HEAPMANAGER_H_ */
