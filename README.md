The assumptions which i have made are:

1)For the input file provided i have assumed that only user has access to it and it is in read_only mode.
2)I have used perror for basic error handling.
3)For code based understanding i have used comments in my code for most of the system calls and algorithms which i have used.
4)For Q2 i am also printing the percentage of process accomplishment alongwith the file permissions.
5)Please be patient with the code.It takes a while after 100% to retrun to the output.

For Question 1:
			Algorithm for reversing the file :-			
	For revesing the file i have used a string of size 1e6.
	Basically what i am doing is storing last 1e6 characters 
	of file in my string and then reverting the string and
	then writing this string back to my featured output 
	file.We will continue this process until all characters 
	of input file are covered.

For Question 2:
			For particulary the case where i have to check that output file is reverted or not :-
			
1)I am again applying the same algorithm just as before and also using the same string size of 1e6.
2)But here i am using 2 strings(for storing 1e6 bytes of both input and output file) and a flag too(assigning value 1 to it initially).
3)For the input file, i am using the string1 and storing the last 1e6 bytes in it and reverting it.
4)For the output file which we got, i am using string2 for storing first 1e6 bytes in it.
5)I will iterate in a loop till i cover whole length of file.
6)For each iteration of loop i will check all the characters of the 2 strings.
7)If any of the character mismatches then i will break the loop instantly and set the flag to 0.
8)According to flag value i will be outputting, that file is reverted or not.(if flag is 1 then yes otherwise no)

Use this command to generate large text files: < /dev/urandom tr -dc "\t\n [:alnum:]" | head -c1000 > foo.txt
						This 1000 represents size in bytes and foo.txt is the file name(provide path carefully)
