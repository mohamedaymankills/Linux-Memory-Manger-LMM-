#include <stdio.h>
#include <unistd.h>   // For sbrk() system call, which is used to control memory allocation
#include <string.h>   // For memcpy(), used for memory copying
#include <stddef.h>   // For size_t type, which is used for memory size calculations
#include <stdint.h>   // For uintptr_t type, which is used for pointer arithmetic

// Declaration of custom memory management functions
// These functions will be implemented later in the code or in another file

void* HmmAlloc(size_t size);  // Function to allocate memory
void HmmFree(void* ptr);      // Function to deallocate memory

// Function to implement malloc using the custom HmmAlloc function

void* malloc(size_t size) 
{
    // If the requested size is zero, malloc should return NULL as per the C standard
    if (size == 0) 
    {
        return NULL;
    }
    // Use HmmAlloc to allocate the requested amount of memory
    return HmmAlloc(size);
}

// Function to implement free using the custom HmmFree function
void free(void* ptr) 
{
    // If the pointer is NULL, free should do nothing as per the C standard
    if (ptr == NULL) 
    {
        return; // Simply return without doing anything
    }
    // Use HmmFree to deallocate the memory pointed to by ptr
    HmmFree(ptr);
}

// Function to implement calloc using the custom HmmAlloc function
// Calloc allocates memory for an array of nmemb elements of size bytes each and initializes all bytes to zero
void* calloc(size_t nmemb, size_t size) 
{
    // Calculate the total size required for the array
    size_t total_size = nmemb * size;
    
    // Use HmmAlloc to allocate the total memory needed
    void* ptr = HmmAlloc(total_size);
    
    // If allocation is successful, initialize all allocated memory to zero
    if (ptr != NULL) 
    {
        memset(ptr, 0, total_size);
    }
    // Return the pointer to the allocated memory (or NULL if allocation failed)
    return ptr;
}

// Function to implement realloc using the custom HmmAlloc and HmmFree functions
// Realloc changes the size of the memory block pointed to by ptr to size bytes
void* realloc(void* ptr, size_t size) 
{
    // If the original pointer is NULL, realloc behaves like malloc
    if (ptr == NULL) 
    {
        return HmmAlloc(size); // Allocate new memory
    }
    // If the new size is zero, realloc behaves like free and returns NULL
    if (size == 0) {
        HmmFree(ptr); // Free the old memory
        return NULL;  // Return NULL to indicate that memory has been freed
    }

    // Allocate new memory block of the requested size
    void* new_ptr = HmmAlloc(size);
    
    // If allocation is successful and the original pointer is not NULL
    if (new_ptr != NULL && ptr != NULL) {
        // Copy the contents of the old memory block to the new one
        memcpy(new_ptr, ptr, size);
        // Free the old memory block
        HmmFree(ptr);
    }
    // Return the pointer to the new memory block (or NULL if allocation failed)
    return new_ptr;
}

// Example implementation of HmmAlloc and HmmFree using sbrk()
// Note: These are basic examples and should be replaced with your actual memory management implementation

// Global variable to store the base address of the heap
// Initialized to NULL initially

void* heap_base = NULL;

// Implementation of HmmAlloc using sbrk

void* HmmAlloc(size_t size) {
    // Use sbrk to allocate the requested memory size plus extra space for alignment
    void* ptr = sbrk(size + sizeof(void*)); 
    
    // If sbrk fails, it returns (void*)-1, so return NULL to indicate failure
    if (ptr == (void*)-1) {
        return NULL;
    }
    
    // Align the pointer to a multiple of sizeof(void*) to ensure proper memory alignment
    uintptr_t aligned = ((uintptr_t)ptr + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
    
    // Return the aligned memory address as the result of HmmAlloc
    return (void*)aligned;
}

// Dummy implementation of HmmFree
// In this example, HmmFree does not actually free memory because sbrk does not support deallocation

void HmmFree(void* ptr) 
{
    // Implement your own memory deallocation logic here
    // For example, you could manage a free list or use another strategy to recycle freed memory
    
    // Note: Since sbrk does not provide a way to return memory to the system, this function might
    // only mark memory as free or manage a custom memory structure for reuse
}

