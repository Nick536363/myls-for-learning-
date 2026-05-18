#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "myls.h"
#include <stdlib.h>
#include <sys/stat.h>

FLAGS flags = {};

int main(int argc, char** argv)
{
	memset(&flags, 0, sizeof(flags));
	
	char current_file[100] = {};	
	char dirname[50] = {};
	DIR* dirptr;
	struct dirent* dir;
	int total_info[2] = {};
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


	dirptr = opendir(dirname);

	if(dirptr == NULL){
		perror(argv[1]);
		return -1;
	}
	
	
	while((dir = readdir(dirptr)) != NULL){
		if(dir->d_name[0] == '.' && !flags.show_hidden)
			continue;	
		struct stat ext_info;
		sprintf(current_file, "%s/%s", dirname, dir->d_name);	
		stat(current_file, &ext_info);
		if(flags.ext_info){
			total_info[0]++;		
			printf("%zu\t", ext_info.st_size);
			total_info[1] += ext_info.st_size;
			if(ext_info.st_mode & (1 << 14))
				putchar('d');
			for(int i = 0; i <= 8; i++)
				putchar(ext_info.st_mode & (1 << (8-i)) ? "rwxrwxrwx"[i] : '-');
			putchar('\t');
		}
		if(ext_info.st_mode & (1 << 14))
			printf("\033[1;34m%s\033[1;0m", current_file);
		else if( (ext_info.st_mode & (1 << 6)) && (ext_info.st_mode & (1 << 3)) && (ext_info.st_mode & 1) )
			printf("\033[1;35m%s\033[1;0m", current_file);
		else if(ext_info.st_mode & (1 << 6))
			printf("\033[1;32m%s\033[1;0m", current_file);
		else
			printf("%s", current_file);
		putchar('\n');
		
	}
	if(flags.ext_info) printf("\033[1;31mTotal:\033[1;0m\n%d files\n%d bytes\n", total_info[0], total_info[1]);
	
	closedir(dirptr);
	return 0;
}


void set_flags(FLAGS* flags, const char* args)
{
	for(int flag = 1; flag < strlen(args); flag++)
		switch(args[flag]){
			case 'a':
				flags->show_hidden = 1;
				break;
			case 'l':
				flags->ext_info = 1;
				break;
		}
}
