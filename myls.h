#pragma once
#include <sys/stat.h>
typedef struct 
{
	unsigned show_hidden: 1;
	unsigned ext_info: 1;
} FLAGS;

void set_flags(FLAGS*, const char*);
void print_file(const char*, struct stat*);
void print_extra(struct stat*);