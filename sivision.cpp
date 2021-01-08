//============================================================================
// Name        : sivision.cpp
// Author      : mohamed essam
// Version     :
// Copyright   : Your copyright notice
// Description : HeapManager
//============================================================================

#include <iostream>
#include "HeapManager.h"
#include <windows.h>


using namespace std;




/*Declaration and defenition for timing calculation*/

LARGE_INTEGER ClockFrequency ;  //The QuadPart member of the object ClockFrequency receives the current performance-counter frequency, in counts per second
LARGE_INTEGER StartTime;        //The QuadPart member of the object StartTime receives the current performance-counter value, in counts.
LARGE_INTEGER EndTime ;	        //The QuadPart member of the object EndTime receives the current performance-counter value, in counts.
#define DeltaSeconds ((float)(EndTime.QuadPart - StartTime.QuadPart))/ClockFrequency.QuadPart

/*End of declaration and definition for timing calculation*/

typedef void * voidptr;
#define TestNo 2

int main() {
#if(TestNo == 1)
	{
		/*Simple test to illustrate correct allocating*/
	HeapManager Test1(1,2);//Allocating 1 MegaByte with block size equal to 2 bytes.
	voidptr ptr1,ptr2,ptr3,ptr4,ptr5,ptr6,ptr7;
	ptr1 = Test1.memalloc(2);
	ptr2 = Test1.memalloc(2);
	ptr3 = Test1.memalloc(2);
	ptr4 = Test1.memalloc(4);
	ptr5 = Test1.memalloc(2);
	ptr6 = Test1.memalloc(5000);
	ptr7 = Test1.memalloc(50000);



Test1.ShowDetail();
}
#elif(TestNo == 2)
	{/*Test to illustrate correct allocating and freeing of memory,
	with also allocating an aggregate size of allocation larger than heap size,
	but due to the intermediate calls of memfree, it is still possible to allocate the requested size.*/
		HeapManager Test2(1,2);//Allocating 1 MegaByte with block size equal to 2 bytes.
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5,ptr6,ptr7,ptr8;
		ptr1 = Test2.memalloc(2);
		ptr2 = Test2.memalloc(2);
		ptr3 = Test2.memalloc(2);
		ptr4 = Test2.memalloc(4);
		ptr5 = Test2.memalloc(2);
		ptr6 = Test2.memalloc(5000);
		ptr7 = Test2.memalloc(50000);
		Test2.memfree(ptr2);
		Test2.memalloc(4);
		Test2.memfree(ptr4);
		Test2.memalloc(4);
		ptr8 = Test2.memalloc(993560);
		Test2.memalloc(2);
		Test2.memfree(ptr8);
		Test2.memalloc(993558);
		Test2.ShowDetail();
	}
#elif(TestNo == 3)
	{//Test to calculate average time of memalloc & memfree
		HeapManager Test3(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		 QueryPerformanceFrequency(&ClockFrequency) ;
		 QueryPerformanceCounter(&StartTime) ;
		 ptr1 = Test3.memalloc(20) ;
		 ptr2 = Test3.memalloc(200);
		ptr3 = Test3.memalloc(2000);
		 ptr4 = Test3.memalloc(20000);
		ptr5 = Test3.memalloc(200000);//These allocations took
		 QueryPerformanceCounter(&EndTime) ;
		 cout<<"Average time of each memalloc is equal to: "<<DeltaSeconds/5<<" seconds"<<endl ;
		 QueryPerformanceFrequency(&ClockFrequency) ;
		 QueryPerformanceCounter(&StartTime) ;
			  Test3.memfree(ptr1) ;
			  Test3.memfree(ptr2);
			  Test3.memfree(ptr3);
			  Test3.memfree(ptr4);
			  Test3.memfree(ptr5);
			  QueryPerformanceCounter(&EndTime) ;
			 cout<<"Average time of each memfree is equal to: "<<DeltaSeconds/5<<" seconds"<<endl ;

	}
#elif(TestNo == 4)
	{//Testing case 1 for the free block aggregator
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(5000);
		ptr2 = Test4.memalloc(5000);
		ptr3 = Test4.memalloc(5000);
		ptr4 = Test4.memalloc(5000);
		Test4.memfree(ptr3);
		Test4.ShowDetail();
		Test4.memfree(ptr4);
		Test4.ShowDetail();
		Test4.memfree(ptr1);
				Test4.ShowDetail();
				Test4.memfree(ptr2);
				Test4.ShowDetail();

	}
#elif(TestNo == 5)
	{//Testing case 2 for the free block aggregator
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(5000);
		ptr2 = Test4.memalloc(5000);
		ptr3 = Test4.memalloc(5000);
		ptr4 = Test4.memalloc(5000);
		Test4.memfree(ptr2);
		Test4.ShowDetail();
		Test4.memfree(ptr1);
		Test4.ShowDetail();
		Test4.memfree(ptr4);
			Test4.ShowDetail();
			Test4.memfree(ptr3);
			Test4.ShowDetail();


	}
#elif(TestNo == 6)
	{//Testing case 3 for the free block aggregator
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(5000);
		ptr2 = Test4.memalloc(5000);
		ptr3 = Test4.memalloc(5000);
		ptr4 = Test4.memalloc(5000);
		Test4.memfree(ptr3);
		Test4.ShowDetail();
		Test4.memfree(ptr1);
		Test4.ShowDetail();
		Test4.memfree(ptr2);
			Test4.ShowDetail();
			Test4.memfree(ptr4);
						Test4.ShowDetail();



	}
#elif(TestNo == 7)
	{//Testing case 3 for the free block aggregator
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(5000);
		ptr2 = Test4.memalloc(5000);
		ptr3 = Test4.memalloc(5000);
		ptr4 = Test4.memalloc(5000);
		Test4.memfree(ptr3);
		Test4.ShowDetail();
		Test4.memfree(ptr4);
		Test4.ShowDetail();
		Test4.memfree(ptr1);
			Test4.ShowDetail();
			Test4.memfree(ptr2);
						Test4.ShowDetail();



	}
#elif(TestNo == 8)
	{//Trying to allocate more size than the heap can handle.
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(1048576/2);
		ptr2 = Test4.memalloc(1048576/2);
		ptr3 = Test4.memalloc(1);
		ptr4 = Test4.memalloc(10);
	Test4.ShowDetail();



	}
#elif(TestNo == 9)
	{//Trying to allocate something that would take 2 blocks with only 1 block left
		HeapManager Test4(1,2);
		voidptr ptr1,ptr2,ptr3,ptr4,ptr5;
		ptr1 = Test4.memalloc(1048576/2);
		ptr2 = Test4.memalloc(1048576/2-2);
		ptr3 = Test4.memalloc(3);
	Test4.ShowDetail();



	}
#endif

	return 0;
}
