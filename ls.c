#include "my_shell.h"

void f_ls(char **ls, char **contents, char **path_contents)
{
    // char **contents = malloc(1000);
    // char **path_contents = malloc(1000);
    struct dirent *dir;
    struct passwd *user_id;
    struct group *grp_id;
    DIR *folder;
    char mtime[4096];
    struct stat files[100];
    int hidden = 0; int long_list = 0;
    int param = 0; //whether -l/a/la/al is specified
    int num_contents = 0; //number of contents
    if(ls[2][0] == '-')
    {
        param++;
        for(int i = 1; (i < 3) & (ls[2][i] != '\0'); i++)
        {
            if(ls[2][i] == 'a') hidden = 1;
            if(ls[2][i] == 'l') long_list = 1;
        }
    }
    if(ls[3][0] == '-')
    {
        param++;
        for(int i = 1; (i < 3) & (ls[3][i] != '\0'); i++)
        {
            if(ls[3][i] == 'a') hidden = 1;
            if(ls[3][i] == 'l') long_list = 1;
        }
    }

    int arg_no = 2 + param; //index from which directories begin
    if(!strcmp(ls[arg_no], ""))
    {
        ls[arg_no][0] = '.';
        ls[arg_no][1] = '\0';
    }
    for (int i = arg_no; strcmp(ls[i], ""); i++)
    {
        folder = opendir(ls[i]);
        if(folder == NULL) 
        {
             printf("Error: The directory '%s' doesn not exist.\n", ls[i]);
             continue;
        }
        for(int j = 0; (dir = readdir(folder)) != NULL; j++, num_contents++)
        {
            contents[j] = dir->d_name;
            strcpy(path_contents[j], ls[i]); strcat(path_contents[j], "/");
            strcat(path_contents[j], contents[j]);
        }
        int skip = 0;
        long long int block_size = 0;
        /**
        for (int j = 0; j < num_contents; j++)
        {
            // if(!S_ISDIR(files[i].st_mode))
                block_size += files[i].st_blksize;
        }
        printf("total %lld\n", block_size);
        */
        for (int j = 0; j < num_contents; j++)
        {
            stat(path_contents[j], &files[i]);
            if(hidden == 0)
            {
                if(contents[j][0] == '.')
                {
                    // printf("%s\n", contents[j]);
                    // skip = 1;
                    continue;
                }
            }
            //printf("%s\n", path_contents[j]); //prints perfectly
            if(long_list)
            {
                //Important: Non-existent directory error handled above, so no need here.
                printf( (S_ISDIR(files[i].st_mode)) ? "d" : "-");
                printf( (files[i].st_mode & S_IRUSR) ? "r" : "-");
                printf( (files[i].st_mode & S_IWUSR) ? "w" : "-");
                printf( (files[i].st_mode & S_IXUSR) ? "x" : "-");
                printf( (files[i].st_mode & S_IRGRP) ? "r" : "-");
                printf( (files[i].st_mode & S_IWGRP) ? "w" : "-");
                printf( (files[i].st_mode & S_IXGRP) ? "x" : "-");
                printf( (files[i].st_mode & S_IROTH) ? "r" : "-");
                printf( (files[i].st_mode & S_IWOTH) ? "w" : "-");
                printf( (files[i].st_mode & S_IXOTH) ? "x" : "-");
                printf("\t%ld", files[i].st_nlink);

                user_id = getpwuid(files[i].st_uid);
                printf("\t%s", user_id->pw_name);
                
                grp_id = getgrgid(files[i].st_gid);
                printf("\t%s", grp_id->gr_name);
                printf("\t%ld", files[i].st_size);
                time_t raw_time = files[i].st_mtime;
                struct tm local_time;
                localtime_r(&raw_time, &local_time);
                strftime(mtime, sizeof(mtime), "%b %d", &local_time);
                printf("\t%s", mtime);
                strftime(mtime, sizeof(mtime), "%H:%M", &local_time);
                printf("\t%s", mtime);
                printf("\t%s\n", contents[j]);
            }
            else
            {
                printf("%s\n", contents[j]);
            }
        }
        
    }
}
