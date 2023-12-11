#ifndef DEVMAP_H
#define DEVMAP_H

#include <stdint.h>

void *devmap(int addr, int len);
void devmap_open(int addr, int len);

uint32_t devmap_readl(int offset);
void devmap_writel(int offset, uint32_t value);
void devmap_close(int len);
void devmap_unmap(void *virt_addr, int len);

#endif // DEVMAP_H