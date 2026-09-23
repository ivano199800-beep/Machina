
#pragma once
#define NON_STANDARD 1
#include <stdint.h>
#include "default_function.h"
struct device_registry {
  struct {
    uint32_t count;
    uint32_t capacity;
    uint32_t* types;
  } instance;
  struct {
    uint32_t count;
    uint32_t capacity;
    struct device_entry* entries;
  } device;
};
struct device_entry {
  struct device_registry* dvrg;
  default_function tick;
  default_function acir;
  default_function rset;
  uint64_t         acbt;
  void* data;
};
struct device {
  struct device_registry* dvrg;
  int32_t instance_id;
};

void init_device_registry(struct device_registry* oRegistry);
uint32_t device_type_register(struct device_registry* iRegistry , struct device_entry* iEntry);
struct device device_create_instance(struct device_registry* iRegistry , uint32_t device_type);
long device_rset(struct device_registry* iRegistry , struct device device , ...);
long device_acir(struct device_registry* iRegistry , struct device device , ...);
long device_tick(struct device_registry* iRegistry , struct device device , ...);
void nuke_device_registry(struct device_registry* iRegistry);


