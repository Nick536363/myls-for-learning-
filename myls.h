#pragma once

typedef struct 
{
	unsigned show_hidden: 1;
	unsigned ext_info: 1;
} FLAGS;

void set_flags(FLAGS*, const char*);
