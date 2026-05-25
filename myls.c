#include "myls.h"


FLAGS flags = {};

int main(int argc, char** argv)
{
	memset(&flags, 0, sizeof(flags));
	char pathname[50] = {};
	if(argc == 1 || (argc == 2 && argv[1][0] == '-')){	
		pathname[0] = '.';	
		if(argc == 2) set_flags(&flags, argv[1]);
	}
	else{		
		
		if(argv[1][0] != '-') strcpy(pathname, argv[1]); 
		else {
			strcpy(pathname, argv[2]);
			set_flags(&flags, argv[1]);
		}
	}
	struct stat arginfo;
	stat(pathname, &arginfo);

	S_ISDIR(arginfo.st_mode) ? ls_dir(pathname, &flags) : ls_file(pathname, &flags);
	
	return 0;
}

