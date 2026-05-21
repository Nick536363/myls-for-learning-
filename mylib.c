#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>


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
			case 'f':
				flags->full_path = 1;
				break;
		}
}


void print_file(const char* filename, struct stat* file_info){
    if(S_ISDIR(file_info->st_mode))
			printf("\033[1;34m%s\033[1;0m", filename);
	else if( (file_info->st_mode & S_IXUSR ) && (file_info->st_mode & S_IXGRP) && (file_info->st_mode & S_IXOTH) )
		printf("\033[1;35m%s\033[1;0m", filename);
	else if(file_info->st_mode & (S_IXUSR))
		printf("\033[1;32m%s\033[1;0m", filename);
	else
		printf("%s", filename);
}


void print_extra(struct stat* file_info)
{
	int permissions[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	printf("%zu\t", file_info->st_size);
	if(S_ISDIR(file_info->st_mode))
		putchar('d');
	else
		putchar('-');
	for(int i = 0; i <= 8; i++)
		putchar(file_info->st_mode & (permissions[i]) ? "rwxrwxrwx"[i] : '-');
	putchar('\t');
}