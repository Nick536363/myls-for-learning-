#include "myls.h"


FLAGS flags = {};

int main(int argc, char** argv)
{
	memset(&flags, 0, sizeof(flags));
	char current_file[100] = {};
	char dirname[50] = {};
	DIR* dirptr;
	struct dirent* dir;
	int files_cnt = 0;
	size_t files_size = 0;
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
		snprintf(current_file, sizeof(current_file), "%s/%s", dirname, dir->d_name);	
		if(stat(current_file, &ext_info) == -1){
			perror(flags.full_path ? current_file : dir->d_name);
			continue;
		}
		if(flags.ext_info){
			print_extra(&ext_info);
			files_cnt++;
			files_size += ext_info.st_size;
		}
		if(flags.full_path) print_file(current_file, &ext_info);
		else print_file(dir->d_name, &ext_info);
		putchar('\n');
	}
	if(flags.ext_info) printf("\033[1;31mTotal:\033[1;0m\n%d files\n%ld bytes\n", files_cnt, files_size);
	
	closedir(dirptr);
	return 0;
}




