#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define DEVMEM "Building device: " STR(DEVICE_)
_Pragma(STR_HELPER(message(DEVMEM)))


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
typedef int32_t Status;

typedef struct {
    unsigned long long* argV;
    unsigned long long  argC;
    char**              logV;
    unsigned long long* logC;
    time_t              currentTime;
} State;
typedef struct Device Device;
typedef Status(*DeviceMethod)(Device*,State*);

typedef struct Device {
    uint16_t        DID; // assigned per instance of Device 
    uint16_t        Dtype; // assigned based on the registered Device
    char            CID[36]; // Character ID
    DeviceMethod    Create;
    DeviceMethod    Clock;
    DeviceMethod    Destroy;
    DeviceMethod*   OtherMethod;
    void*           data;
    char*           config;
} Device;