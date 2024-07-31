	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		LASAalloc.h
	 * 		LASAalloc class declaration.  
	 * 
	 * 		Do not change this file other than to add local varaibles and Functions.
	 *    Make any changes only in the provided block.
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include<iostream>
#include<stdlib.h>
#include "LASAalloc.h"

// Defines for LASAalloc buffer simulation.  
// Keep it simple, no changes to program break
#define INITIAL_MALLOC_SIZE 100000
#define MAX_MALLOC_SIZE 100000


using namespace std;

typedef unsigned char BYTE_t;

LASAalloc::LASAalloc()
{
	brk(INITIAL_MALLOC_SIZE);
	
	// Point to where first node will be located.
	block* firstBlock = (block*)bufferBase;
	freeList = firstBlock;
	
	// Configure first node on freeList
	firstBlock->size = (int)(bufferSize);
	firstBlock->prev_block = nullptr;
	firstBlock->next_block = nullptr; 
	firstBlock->this_block_data = (void*)((long long int)bufferBase+(long long int)sizeof(block)); 
	firstBlock->freeFlag = true; 
	
	// Show initial statistics
	cout<<"buffer Allocation: "<< bufferBase << " - " << brk(0) << endl;
	cout<<"freeList: "<< freeList << " - " << brk(0) << endl;
	cout<<"Block header size " << sizeof(block) << endl;
	cout<<"integer size " << sizeof(int) << endl;
	
	display_node(freeList);

}

LASAalloc::~LASAalloc()
{
  freeList = nullptr;
  free(bufferBase);
}

 

void LASAalloc::display_node(struct block *p)
{
		cout << "Prev: " << p->prev_block;
		cout << "\tNext: " << p->next_block;
		cout << "\tFree: " << p->freeFlag;
		cout << "\tSize: " << p->size;
		cout << "\tThis: " << p->this_block_data << endl;
		cout << endl;	
}

void LASAalloc::display(struct block *begin)
{
	struct block *p;
	if(begin==NULL)
	{
		cout<<"List is empty\n";
		return;
	}
	p=begin;
	cout<<"List is :\n";
	while(p!=NULL)
	{
		display_node(p);
		p=p->next_block;
	}
	cout<<"\n";
}


int LASAalloc::rounded(int x) {
  return ((x+7) & (-8));
}

void LASAalloc::merge(block* a, block* b) {
  a->next_block = b->next_block;
  if (b->next_block != nullptr) {
    b->next_block->prev_block = a;
  }

  a->size = a->size + b->size + 32;
}
void* LASAalloc::lalloc(int size)
{
  block* header = freeList;
  size = rounded(size);


  if (header == nullptr) {
    cout << "Out of memory" << endl;
    return nullptr;
  }
  
  while (header != nullptr) {
    if (size > header->size) {
      header = header->next_block;
      continue;
    } else {
      break;
    }
  }
  if (size + 32 >= header->size) {
    if (header->next_block == nullptr && header->prev_block == nullptr) {
      freeList = nullptr;
    } else if (header->next_block == nullptr && header->prev_block != nullptr) {
      header->prev_block->next_block = nullptr;
    } else if (header->next_block != nullptr && header->prev_block == nullptr) {
      header->next_block->prev_block = nullptr;
      freeList = header->next_block;
    } else {
      header->next_block->prev_block = header->prev_block;
      header->prev_block->next_block = header->next_block;
    }
  } else {
    auto* newBlock = (struct block*) ((BYTE_t*) header + 32 + size);
    newBlock->size = header->size - size - 32;
    newBlock->this_block_data = (BYTE_t*) newBlock + 32;
    if (header->next_block == nullptr) {
      newBlock->next_block = nullptr;
    } else {
      newBlock->next_block = header->next_block;
      header->next_block->prev_block = newBlock;
    }
    if (header->prev_block == nullptr) {
      freeList = newBlock;
    } else {
      newBlock->prev_block = header->prev_block;
      header->prev_block->next_block = newBlock;
    }
    header->size = size;
  }
  return header->this_block_data;
}


void* LASAalloc::lfree(void* userBlock)
{
	block* header = freeList;
  auto* alloc = (struct block*) ((BYTE_t*) userBlock - 32);
  cout << "error1" << endl;

  if (header == nullptr) { //empty list
    freeList = alloc;
    return nullptr;
  }
  cout << "error2" << endl;

  while (true) {
    if (header->prev_block == nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        header->prev_block = alloc;
        freeList = alloc;
        break;
      }
    } else if (header->next_block == nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        alloc->prev_block = header->prev_block;
        header->prev_block->next_block = alloc;
        header->prev_block = alloc;
      } else {
        alloc->prev_block = header;
        header->next_block = alloc;
      } break;
    } else if (header->prev_block != nullptr && header->next_block != nullptr) {
      if (alloc->this_block_data < header->this_block_data) {
        alloc->next_block = header;
        alloc->prev_block = header->prev_block;
        header->prev_block->next_block = alloc;
        header->prev_block = alloc;
        break;
      }
    }
    
    header = header->next_block;

  }
  cout << "error3" << endl;

  if (alloc->next_block != nullptr && (struct block*) ((BYTE_t*) alloc->this_block_data + alloc->size) == alloc->next_block) {
    merge(alloc, alloc->next_block);
  }
  if (alloc->prev_block != nullptr && (struct block*) ((BYTE_t*) alloc->prev_block->this_block_data + alloc->prev_block->size) == alloc) {
    merge(alloc->prev_block, alloc);
  }
  cout << "error4" << endl;

  return nullptr;
  
}

void* LASAalloc::findFit(int size)
{
	// optional
}

void* LASAalloc::split(block* target, int size)
{
	//optional
}
 


/*
 *   >>>>>>  DO NOT CHANGE THIS SECTION  <<<<<<<
 * 
 * brk()
 * Function to simulate the libc brk() function to allocate memory for a buffer
 * 
 */

void * LASAalloc::brk(int size)
{
	
	if (size !=0)
	{
		if (bufferBase == 0)
		{
			bufferBase = malloc(size);
			bufferSize = size;
		}
		else
		{
			cout<<"buffer already locked/n";
			return 0;
		}
		
	}
  return static_cast<void*>(static_cast<BYTE_t*>(bufferBase) + bufferSize);
}