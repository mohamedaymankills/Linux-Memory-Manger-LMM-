# Custom Heap Memory Manager

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

### Prerequisites

- A C compiler (e.g., `gcc`).
- A UNIX-like operating system (Linux, macOS, etc.) that supports the `sbrk()` system call.

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/your-username/custom-heap-memory-manager.git
cd custom-heap-memory-manager
