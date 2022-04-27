#ifndef PAGER_H
#define PAGER_H
#include "node.h"


typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
    uint32_t num_pages;
} Pager;

void *get_page(Pager *pager, uint32_t page_number);
Pager *pager_open(char * filename);
void page_flush(Pager *pager, uint32_t page_number);

#endif