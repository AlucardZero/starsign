#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/mman.h>

#define RWX_PROT (PROT_WRITE | PROT_READ | PROT_EXEC)

// Align address to page boundary
#define PAGEBOUND(p) ((void*)((p) - (p)%getpagesize()))


void starsign_select();
pid_t try_fork();

