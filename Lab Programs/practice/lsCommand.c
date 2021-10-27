#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>

int main(int argc, char* argv[]){

    DIR *dp = NULL;
    struct dirent *de;
    struct stat st;
    struct passwd *pwd;
    struct group *grp;

    dp = opendir(argv[1]);

    while((de = readdir(dp)) != NULL){
        stat(de->d_name, &st);

        if(argv[2])
        printf("%llu ", st.st_ino);

        if(S_ISREG(st.st_mode)) printf("-");
        else if(S_ISDIR(st.st_mode)) printf("d");
        else if(S_ISBLK(st.st_mode)) printf("b");
        else if(S_ISCHR(st.st_mode)) printf("c");
        else if(S_ISFIFO(st.st_mode)) printf("f");
        else if(S_ISLNK(st.st_mode)) printf("l");
        else if(S_ISSOCK(st.st_mode)) printf("s");
        else printf("u");

        if(st.st_mode & S_IRUSR) printf("r");
        else printf("-");
        if(st.st_mode & S_IWUSR) printf("w");
        else printf("-");
        if(st.st_mode & S_IXUSR) printf("x");
        else printf("-");

        if(st.st_mode & S_IRGRP) printf("r");
        else printf("-");
        if(st.st_mode & S_IWGRP) printf("w");
        else printf("-");
        if(st.st_mode & S_IXGRP) printf("x");
        else printf("-");

        if(st.st_mode & S_IROTH) printf("r");
        else printf("-");
        if(st.st_mode & S_IWOTH) printf("w");
        else printf("-");
        if(st.st_mode & S_IXOTH) printf("x");
        else printf("-");

        printf(" %2d ", st.st_nlink);

        pwd = getpwuid(st.st_uid);
        grp = getgrgid(st.st_gid);

        printf(" %s ", pwd->pw_name);
        printf(" %s ", grp->gr_name);

        printf(" %5llu ", st.st_size);
        printf(" %.*s ", 12, (ctime(&st.st_mtime)+4));

        printf(" %s\n", de->d_name);

    }

    closedir(dp);

    return 0;
}
