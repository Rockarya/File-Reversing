#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<string.h>
typedef long long ll;

const ll N=1e6;

int main(ll argc,char *argv[])
{
  ll p1,p2,p3,fd1,fd2,offset,count,i,f,total;
  char y[50]="Yes\n",n[50]="No\n",ch='%';
  struct stat new,old,dir;
  p1=stat(argv[1],&new);
  p2=stat(argv[2],&old);   
  p3=stat(argv[3],&dir);

  //CHECKING THAT FILE IS REVERSED CORRECTLY OR NOT

  fd1= open(argv[2],O_RDONLY,00400);
  fd2 = open(argv[1], O_RDWR , 00400 | 00200);   
  f=0;
  if(fd2 < 0) 
  {
    perror("Error in openeing the new file\n");
  }
  else if(fd1 < 0)
  {
    perror("Error in opening the old file\n");
  }
  else
  {
    f=1;
    offset = lseek(fd1, 0, SEEK_END);    //go to the end of the file
    total=offset/N;
    if(offset%N!=0)
    {
      total++;
    }
    count=1;
    total+=count;
    while (offset > 0)    //code for checking the reversed file and original file
    { 
      char string1[1000005]={'\0'};
      char string2[1000005]={'\0'};
      if(offset<N)
      {
        lseek(fd1,0,SEEK_SET);
        read(fd1,string1,offset);

        lseek(fd2,N*(count-1),SEEK_SET);
        read(fd2,string2,offset);

        for(i=0;i<offset;i++)
        {
          if(string1[i]!=string2[offset-1-i])
          {
            f=0;
            break;
          }
        }

        offset=0;

      }
      else
      {
        lseek(fd1,-N*count,SEEK_END);
        offset-=N;
        read(fd1,string1,N);

        lseek(fd2,N*(count-1),SEEK_SET);
        read(fd2,string2,N);

        for(i=0;i<N;i++)
        {
          if(string1[i]!=string2[N-i-1])
          {
            f=0;
            break;
          }
        }
      }

      if(f==0)
      {
        break;
      }

      count++;

      //code for printing percentage of accomplishment of process
      long double percentage;
      percentage=(long double)count/total;
      percentage*=100.0;
      char buffer[100]={'\0'};
      sprintf(buffer,"%0.2Lf%c",percentage,ch);  //used for formatting strings
      write(1,buffer,sizeof(buffer));
      system("clear");    //clears the console
    }
  }
  close(fd1);  //close the files
  close(fd2);


    //NEW FILE PERMISSIONS
    write(1,"Permissions on newfile:\n\n",sizeof("Permissions on newfile:\n\n"));
    if(p1==-1)
    {
        write(1,"Error occured while accessing newfile permissions!\n",sizeof("Error occured while accessing newfile permissions!\n"));
    }
    else
    {
        //WE LANDED ON NEW FILE SUCCESSFULLY WHICH MEANS THAT ASSIGNMENT FOLDER EXISTS
        write(1,"Directory is created: Yes\n",sizeof("Directory is created: Yes\n"));

        //FILE IS REVERSED OR NOT
        write(1,"Whether file contents are reversed in newfile: ",sizeof("Whether file contents are reversed in newfile: "));
        if(f==1)
        {
          write(1,y,sizeof(y));
        }
        else
        {
          write(1,n,sizeof(n));
        }

        //USER PERMISSIONS
        write(1,"User has read permissions on newfile: ",sizeof("User has read permissions on newfile: "));
        if(new.st_mode & S_IRUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has write permissions on newfile: ",sizeof("User has write permissions on newfile: "));
        if(new.st_mode & S_IWUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has execute permissions on newfile: ",sizeof("User has execute permissions on newfile: "));
        if(new.st_mode & S_IXUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //GROUP PERMISSIONS
        write(1,"Group has read permissions on newfile: ",sizeof("Group has read permissions on newfile: "));
        if(new.st_mode & S_IRGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has write permissions on newfile: ",sizeof("Group has write permissions on newfile: "));
        if(new.st_mode & S_IWGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has execute permissions on newfile: ",sizeof("Group has execute permissions on newfile: "));
        if(new.st_mode & S_IXGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //Others PERMISSIONS
        write(1,"Others has read permissions on newfile: ",sizeof("Others has read permissions on newfile: "));
        if(new.st_mode & S_IROTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has write permissions on newfile: ",sizeof("Others has write permissions on newfile: "));
        if(new.st_mode & S_IWOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has execute permissions on newfile: ",sizeof("Others has execute permissions on newfile: "));
        if(new.st_mode & S_IXOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
    }

    //OLD FILE PERMISSIONS
    write(1,"\nPermissions on oldfile:\n\n",sizeof("Permissions on oldfile:\n\n"));
    if(p2==-1)
    {
        write(1,"Error occured while accessing oldfile permissions!\n\n",sizeof("Error occured while accessing oldfile permissions!\n\n"));
    }
    else
    {
        //USER PERMISSIONS
        write(1,"User has read permissions on oldfile: ",sizeof("User has read permissions on oldfile: "));
        if(old.st_mode & S_IRUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has write permissions on oldfile: ",sizeof("User has write permissions on oldfile: "));
        if(old.st_mode & S_IWUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has execute permissions on oldfile: ",sizeof("User has execute permissions on oldfile: "));
        if(old.st_mode & S_IXUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //GROUP PERMISSIONS
        write(1,"Group has read permissions on oldfile: ",sizeof("Group has read permissions on oldfile: "));
        if(old.st_mode & S_IRGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has write permissions on oldfile: ",sizeof("Group has write permissions on oldfile: "));
        if(old.st_mode & S_IWGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has execute permissions on oldfile: ",sizeof("Group has execute permissions on oldfile: "));
        if(old.st_mode & S_IXGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //Others PERMISSIONS
        write(1,"Others has read permissions on oldfile: ",sizeof("Others has read permissions on oldfile: "));
        if(old.st_mode & S_IROTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has write permissions on oldfile: ",sizeof("Others has write permissions on oldfile: "));
        if(old.st_mode & S_IWOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has execute permissions on oldfile: ",sizeof("Others has execute permissions on oldfile: "));
        if(old.st_mode & S_IXOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
    }

    //DIRECTORY PERMISSIONS
    write(1,"\nPermissions on directory:\n\n",sizeof("\nPermissions on directory:\n\n"));
    if(p3==-1)
    {
        write(1,"Error occured while accessing directory permissions!\n",sizeof("Error occured while accessing directory permissions!\n"));
    }
    else
    {
        //USER PERMISSIONS
        write(1,"User has read permissions on directory: ",sizeof("User has read permissions on directory: "));
        if(dir.st_mode & S_IRUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has write permissions on directory: ",sizeof("User has write permissions on directory: "));
        if(dir.st_mode & S_IWUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"User has execute permissions on directory: ",sizeof("User has execute permissions on directory: "));
        if(dir.st_mode & S_IXUSR)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //GROUP PERMISSIONS
        write(1,"Group has read permissions on directory: ",sizeof("Group has read permissions on directory: "));
        if(dir.st_mode & S_IRGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has write permissions on directory: ",sizeof("Group has write permissions on directory: "));
        if(dir.st_mode & S_IWGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Group has execute permissions on directory: ",sizeof("Group has execute permissions on directory: "));
        if(dir.st_mode & S_IXGRP)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }

        //Others PERMISSIONS
        write(1,"Others has read permissions on directory: ",sizeof("Others has read permissions on directory: "));
        if(dir.st_mode & S_IROTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has write permissions on directory: ",sizeof("Others has write permissions on directory: "));
        if(dir.st_mode & S_IWOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
        write(1,"Others has execute permissions on directory: ",sizeof("Others has execute permissions on directory: "));
        if(dir.st_mode & S_IXOTH)
        {
            write(1,y,sizeof(y));
        }
        else
        {
            write(1,n,sizeof(n));
        }
    }
    return 0;
}