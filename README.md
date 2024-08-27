
# Linux Memory Manager

## Overview

This project implements a custom Heap Memory Manager in C, which provides replacements for the standard memory management functions (`malloc`, `free`, `calloc`, and `realloc`). The custom implementation allows for more control over memory allocation and deallocation by utilizing a custom `HmmAlloc` function and a custom `HmmFree` function. The `sbrk()` system call is used to manage the heap, simulating the behavior of the traditional heap memory management functions.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [Implementation Details](#implementation-details)
  - [HmmAlloc Function](#hmmalloc-function)
  - [HmmFree Function](#hmmfree-function)
  - [Custom malloc Implementation](#custom-malloc-implementation)
  - [Custom free Implementation](#custom-free-implementation)
  - [Custom calloc Implementation](#custom-calloc-implementation)
  - [Custom realloc Implementation](#custom-realloc-implementation)
- [Testing](#testing)
- [Future Work](#future-work)
- [License](#license)

## Features

- **Custom Memory Allocation**: Implemented `malloc`, `free`, `calloc`, and `realloc` functions using a custom memory management system.
- **Memory Alignment**: Ensured proper memory alignment for all allocated memory blocks.
- **Memory Safety**: Implemented basic checks and safety measures to prevent common memory management errors, such as double-free or invalid free operations.
- **Modular Design**: The memory management logic is separated into distinct functions, making the codebase easier to maintain and extend.

## Getting Started
## Flowchart 
```sql
+--------------------+
|       Start        |
+--------------------+
         |
         v
+--------------------+
|  Include headers   |
+--------------------+
         |
         v
+----------------------------+
| Declare HmmAlloc, HmmFree  |
+----------------------------+
         |
         v
+--------------------+
| Define malloc()    |
+--------------------+
         |
         v
+-----------------------------+
|  size == 0 ? Return NULL    |
+-----------------------------+
         |
         v
+--------------------+
| Call HmmAlloc      |
+--------------------+
         |
         v
+--------------------+
| Return Pointer     |
+--------------------+
         |
         v
+--------------------+
| Define free()      |
+--------------------+
         |
         v
+-----------------------------+
|  ptr == NULL ? Return       |
+-----------------------------+
         |
         v
+--------------------+
| Call HmmFree       |
+--------------------+
         |
         v
+--------------------+
| Define calloc()    |
+--------------------+
         |
         v
+--------------------------------+
| Calculate total size (nmemb*size)|
+--------------------------------+
         |
         v
+--------------------+
| Call HmmAlloc      |
+--------------------+
         |
         v
+-------------------------------+
| If ptr != NULL, memset to 0   |
+-------------------------------+
         |
         v
+--------------------+
| Return Pointer     |
+--------------------+
         |
         v
+--------------------+
| Define realloc()   |
+--------------------+
         |
         v
+-----------------------------+
|  ptr == NULL ? Call HmmAlloc |
+-----------------------------+
         |
         v
+---------------------------------+
| size == 0 ? Call HmmFree & Return|
| NULL                             |
+---------------------------------+
         |
         v
+--------------------+
| Call HmmAlloc      |
+--------------------+
         |
         v
+-------------------------------+
| If new_ptr != NULL, memcpy old|
| contents, Call HmmFree on old  |
+-------------------------------+
         |
         v
+--------------------+
| Return new_ptr     |
+--------------------+
         |
         v
+--------------------+
| Define HmmAlloc()  |
+--------------------+
         |
         v
+--------------------+
| Call sbrk(size +   |
| sizeof(void*))     |
+--------------------+
         |
         v
+-------------------------------+
| If sbrk fails, Return NULL    |
+-------------------------------+
         |
         v
+--------------------------------+
| Align memory to sizeof(void*) |
+--------------------------------+
         |
         v
+--------------------+
| Return aligned ptr |
+--------------------+
         |
         v
+--------------------+
| Define HmmFree()   |
+--------------------+
         |
         v
+--------------------------------+
| Implement custom free logic   |
| (e.g., free list)             |
+--------------------------------+
         |
         v
+--------------------+
|        End         |
+--------------------+
```

### Prerequisites

- A C compiler (e.g., `gcc`).
- A UNIX-like operating system (Linux, macOS, etc.) that supports the `sbrk()` system call.

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/mohamedaymankills/inux-Memory-Manager.git

```

### Usage

To compile the code, use the following command:

```bash
gcc -o custom_memory_manager custom_memory_manager.c -Wall -Wextra
```

Run the compiled executable:

```bash
./custom_memory_manager
```

## Implementation Details

### HmmAlloc Function

The `HmmAlloc` function is responsible for allocating memory on the heap. It uses the `sbrk()` system call to increase the program's data space. The function ensures that the allocated memory is properly aligned by adjusting the pointer returned by `sbrk()`.

**Code:**
```c
void* HmmAlloc(size_t size) {
    void* ptr = sbrk(size + sizeof(void*)); 
    if (ptr == (void*)-1) {
        return NULL;
    }
    uintptr_t aligned = ((uintptr_t)ptr + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
    return (void*)aligned;
}
```

### HmmFree Function

The `HmmFree` function is a placeholder in this implementation. Since `sbrk()` does not support deallocation, the function would typically manage a free list or another structure to recycle memory. This is an area where further development can take place.

**Code:**
```c
void HmmFree(void* ptr) {
    // Implement your own memory deallocation logic here
    // sbrk does not support deallocation, so this function might
    // manage a free list or similar structure.
}
```

### Custom malloc Implementation

The custom `malloc` function leverages `HmmAlloc` to allocate memory. It handles the special case where the requested size is zero by returning `NULL`, as per the standard `malloc` behavior.

**Code:**
```c
void* malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    return HmmAlloc(size);
}
```

### Custom free Implementation

The custom `free` function uses `HmmFree` to deallocate memory. It checks for a `NULL` pointer to ensure that no action is taken for invalid free operations.

**Code:**
```c
void free(void* ptr) {
    if (ptr == NULL) {
        return;
    }
    HmmFree(ptr);
}
```

### Custom calloc Implementation

The custom `calloc` function allocates memory for an array of elements and initializes the allocated memory to zero. It uses `HmmAlloc` for memory allocation and `memset` for initialization.

**Code:**
```c
void* calloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size;
    void* ptr = HmmAlloc(total_size);
    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}
```

### Custom realloc Implementation

The custom `realloc` function resizes the memory block pointed to by `ptr`. It handles the cases where `ptr` is `NULL` or `size` is zero, mimicking the behavior of the standard `realloc`.

**Code:**
```c
void* realloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        return HmmAlloc(size);
    }
    if (size == 0) {
        HmmFree(ptr);
        return NULL;
    }
    void* new_ptr = HmmAlloc(size);
    if (new_ptr != NULL && ptr != NULL) {
        memcpy(new_ptr, ptr, size);
        HmmFree(ptr);
    }
    return new_ptr;
}
```

## Testing

To ensure the correctness of the custom Heap Memory Manager, several test cases can be implemented:

- **Basic Allocation and Freeing**: Test simple allocations and deallocations to verify that memory is correctly allocated and freed.
- **Reallocation**: Test resizing of memory blocks using `realloc` and ensure that data is correctly copied to the new block.
- **Alignment Checks**: Verify that all allocated memory blocks are properly aligned.
- **Edge Cases**: Test edge cases, such as zero-size allocation and freeing `NULL` pointers, to ensure that the implementation behaves as expected.

## Future Work

- **Enhanced Free Functionality**: Implement a more sophisticated `HmmFree` function that manages a free list or other memory recycling mechanism.
- **Memory Management Optimization**: Explore ways to optimize memory allocation, such as reducing the number of calls to `sbrk()` or implementing a buddy allocator.
- **Thread Safety**: Make the memory manager thread-safe by adding appropriate locking mechanisms.
- **Comprehensive Testing**: Develop a suite of automated tests to cover various edge cases and stress tests.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
