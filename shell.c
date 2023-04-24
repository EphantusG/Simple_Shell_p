#include "main.h"

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char *buff = NULL;
	size_t buff_mem = 0;
	ssize_t read;
	const char* delim = " \t\r\n\v\f";
	char* token = NULL;
	int status;
	pid_t pid;
	argv = malloc(BUFFER_SIZE * sizeof(char *));

	/*Start of while loop*/
        while (1)
{
        int int_mode = isatty(STDIN_FILENO);

   if (int_mode == 1)
   {
     write(STDOUT_FILENO,"Enter your Command:", 20);
   }
   read = getline(&buff, &buff_mem, stdin);

   if (read == -1)
   {
	   perror("Getline:");
	   exit(EXIT_FAILURE);
   }
   argc = 0;
   token = strtok(buff,delim);
   while (token != NULL)
   {
	  printf("%s\n",token);
	  argv[argc] = token;
	  argc++;
	  token = strtok(NULL, delim);
   }
   argv[argc] = NULL;

  pid = fork();

   if (pid == -1)
   {
	   perror("Forking:");
	   exit(EXIT_FAILURE);
   }
   else if (pid == 0)
   {
	   if(execv(argv[0], argv) == -1)
	   {
		   perror("Execution:");
		   exit(EXIT_FAILURE);
	   }
	   exit(EXIT_FAILURE);
   }
   else
   {
	   waitpid(pid, &status, 0);
   }
   free(argv);
free(buff);
}
return (0);
}
