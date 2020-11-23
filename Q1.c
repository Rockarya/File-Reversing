#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<string.h>
typedef long long int ll;

const ll N=1e6;

int main(ll argc,char *argv[]) 
{
	ll fd1, fd2,check,i,j,count,len,last,k,l;    
	char c,ch='%';  
	char temp_name[100005]={'\0'},file_name[100005]="Assignment/";      //finally output file will be in Assignment folder so writing it's name beforehand
	ll offset,total_bytes,current_size;    

	len=strlen(argv[1]);
	if(argv[1][0]=='/')
	{
		//absolute path is used
		last=-1;
		for(i=0;i<len;i++)
		{
			if(argv[1][i]=='/')
			{
				last=i;
			}
		}
		if(last==-1)
		{
			perror("There is an error in writing absolute file path\n");
			exit(1);
		}
		else
		{
			k=0;
			if((ll)argv[1][last+1]==34 && (ll)argv[1][len-1]==34)			//for double quotes
			{
				for(i=last+2;i<len-1;i++)
				{
					temp_name[k]=argv[1][i];
					k++;
				}
			}
			else if((ll)argv[1][last+1]==39 && (ll)argv[1][len-1]==39)		//for single quotes
			{
				for(i=last+2;i<len-1;i++)
				{
					temp_name[k]=argv[1][i];
					k++;
				}
			}
			else
			{
				for(i=last+1;i<len;i++)
				{
					if(argv[1][i]!=92)
					{
						temp_name[k]=argv[1][i];
						k++;
					}
				}
			
			}
		}
	} 
	else 
	{
		//relative path
		k=0;
		if((ll)argv[1][0]==34 && (ll)argv[1][len-1]==34)			//for double quotes
		{
			for(i=1;i<len-1;i++)
			{
				temp_name[k]=argv[1][i];
				k++;
			}
		}
		else if((ll)argv[1][0]==39 && (ll)argv[1][len-1]==39)		//for single quotes
		{
			for(i=1;i<len-1;i++)
			{
				temp_name[k]=argv[1][i];
				k++;
			}
		}
		else
		{
			for(i=0;i<len;i++)
			{
				if(argv[1][i]!=92)			//if filename contains '\' character for specifying space in the name of the file,then ignore it(next character will definetely going to be a space)
				{
					temp_name[k]=argv[1][i];
					k++;
				}
			}
		}
	}
	l=strlen(file_name);		
	for(i=0;i<k;i++)
	{
		file_name[l]=temp_name[i];
		l++;
	}
	fd1 = open(argv[1],O_RDONLY,00400);      //open file to read.argv[1] is basically the command line file given to us
	chmod(argv[1],00400);					//providing read only permission to the user of input file 

	if (fd1 < 0)
	{
	    perror("Error in opening the input file\nReheck the path(absolute/relative) provided by you is correct or not\nCheck given file exist or not\n");
	    exit(1);
	}

	check=mkdir("Assignment",0777);		//creating the Assignment directory and it will leave as it is if it already exists

	chmod("Assignment",00700);			//granting read,write and execute permissions to the user of Assignment folder 

	fopen(file_name,"w");				//clearing the output file if it already has some content(to handle the case if the output file already exist)
	fd2 = open(file_name, O_RDWR | O_CREAT, 00400 | 00200);   
	chmod(file_name,00400 | 00200);				//providing permission of read and write to the USER

	if(fd2 < 0) 
	{
	    perror("Error in creating the reversed text file\n");
	    exit(1);
	}
	
	offset = lseek(fd1, 0, SEEK_END);    //go to the end of the file
	total_bytes=offset;
	count=1;
	while (offset > 0) 		//code for reversing the input file
	{ 
		char string[1000005]={'\0'};
		if(offset<N)
		{
			lseek(fd1,0,SEEK_SET);		//DO NOT USE SEEK_CUR!!!
			read(fd1,string,offset);
			i=0;
			j=offset-1;
			while(i<j)
			{
				c=string[i];
				string[i]=string[j];
				string[j]=c;
				i++;
				j--;
			}
			write(fd2,string,offset);
			offset=0;
		}
		else
		{
			lseek(fd1,-N*count,SEEK_END);
			offset-=N;
			read(fd1,string,N);
			i=0;
			j=N-1;
			while(i<j)
			{
				c=string[i];
				string[i]=string[j];
				string[j]=c;
				i++;
				j--;
			}
			write(fd2,string,N);
			count++;
		}

		//code for printing percentage of process accomplishment on console and clearing it too
		struct stat per;	//pointer to stat struct 
		stat(file_name,&per);	//stat system call
		current_size=per.st_size;
		long double percentage;
		percentage=(long double)current_size/total_bytes;
		percentage*=100.0;
		char buffer[100]={'\0'};
		sprintf(buffer,"%0.2Lf%c",percentage,ch);	//used for formatting strings
		write(1,buffer,sizeof(buffer));
		system("clear");		//clears the console
		
	}
	close(fd1);  //close the files
	close(fd2);
return 0;
}
