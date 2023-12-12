// Maps a address space and lets you read/write to it.


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>



void *mapped_base;
int fd;
void *virtmem;

void *devmap(int addr, int len) {
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("open failed\n");
        return NULL;
    }
    
    off_t offset = addr & ~(sysconf(_SC_PAGE_SIZE) - 1);
    mapped_base = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
   
    if (mapped_base == MAP_FAILED) {
        printf("mmap failed\n");
        close(fd);
        return NULL;
    }
    return mapped_base + (addr - offset);
}



void devmap_open(int addr, int len) {
    
    virtmem = devmap(addr, len);

    
    if (virtmem == NULL) {
        printf("devmap failed\n");
        }
}




uint32_t devmap_readl(int offset) {
     
        if(virtmem == NULL) {
            printf("devmap not open for read\n");
            return 0;
        }
        

    return *(volatile uint32_t *)(virtmem+offset);
}

void devmap_writel(int offset, uint32_t value) {
    if(mapped_base == NULL) {
        printf("devmap not open for write\n");
        return;
    }

    *(volatile uint32_t *)(virtmem+offset) = value;
}

void devmap_close(int len) {
    if(mapped_base != NULL) {
        devmap_unmap(mapped_base, len);
        mapped_base = NULL;
    }

    
}


void devmap_unmap(void *virt_addr, int len) {
    
   if(mapped_base != NULL) {
        //printf("closing with munmap\n");
        munmap (virt_addr, len);
        close(fd);
   }
}