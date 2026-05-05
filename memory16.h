#pragma once
#ifndef DEVICE_MEMORY
#define DEVICE_MEMORY
#define DEVICE_ MEMORY
#define VERSION_ 0
#define WORD_ 16
#include "devices.h"
typedef struct {
    uint8_t wordSize;
    uint8_t (*data)[WORD_ / 8];
} MemoryPage;

typedef struct {
    size_t PageSize;
    size_t count , capacity;
    MemoryPage* pages;
    unsigned long long state;
} MemoryData;

Device* NewBaseMemory(const char* config);
Status CreateMemory(Device* self , State* state);
Status ClockMemory(Device* self , State* state);
Status DestroyMemory(Device* self , State* state);
#endif