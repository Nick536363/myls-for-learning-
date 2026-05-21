#include "myls.h"


FLAGS flags = {};

int main(int argc, char** argv)
{
	memset(&flags, 0, sizeof(flags));
	char dirname[50] = {};
	if(argc == 1 || (argc == 2 && argv[1][0] == '-')){	
		dirname[0] = '.';	
		if(argc == 2) set_flags(&flags, argv[1]);
	}
	else{		
		
		if(argv[1][0] != '-') strcpy(dirname, argv[1]); 
		else {
			strcpy(dirname, argv[2]);
			set_flags(&flags, argv[1]);
		}
	}

	ls_dir(dirname, &flags);
	
	return 0;
}

