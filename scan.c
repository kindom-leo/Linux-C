#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024
void stepIntoDir(char* dir,void (*func)(char*)){
	char name[MAX_PATH]={};
	struct dirent* dp;
	DIR* dfd;
	
	if(( dfd = opendir(dir)) == NULL){
		fprintf(stderr,"can't open %s\n",dir);
		return;
	}

	while ((dp = readdir(dfd)) != NULL){
		if (strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0){
			continue;
		}
		if (strlen(dir) + strlen(name) + 2 > sizeof(name)){
			fprintf(stderr,"stepIntoDir : name %s %s too long",dir,dp->d_name);
		}else {
			sprintf(name, "%s/%s",dir,dp->d_name);
			(*func)(name);
		}
	}
	closedir(dfd);
}

void Print(char* name){
	struct stat st;
	
	if (stat(name,&st) == -1){
		fprintf(stderr,"Print: Can't access %s\n",name);
		return;
	}
	if((st.st_mode & S_IFMT) == S_IFDIR){
		stepIntoDir(name,Print);
	}
	printf("%10ld  %s\n",st.st_size,name);
}









int main(int argc,char** argv){
	if(argc < 2){
		Print(".");
	}else{
		while(--argc > 0){
			Print(*++argv);
		}
	}
	return 0;
}
