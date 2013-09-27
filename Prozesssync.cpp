//============================================================================
// Name        : Prozesssync.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

}


int maint(void) {

	   int pid, j, i;

	   pid = fork();

	   if (pid == 0)
	   {
	      /* Kindprozess
	       * wenn fork eine 0 zurückgibt, befinden wir uns im Kindprozess
	       */
	      for (j=0; j < 10; j++)
	      {
	        printf ("Kindprozess:  %d (PID: %d)\n", j, getpid());
	        sleep (1);
	      }
	      exit (0);
	   }
	   else if (pid > 0)
	   {
	      /* Elternprozess
	       * Gibt fork einen Wert größer 0 zurück, so ist dies die PID des Kindprozesses
	       */
	      for (i=0; i < 10; i++)
	      {
	         printf ("Elternprozess: %d (PID: %d)\n", i, getpid());
	         sleep (1);
	      }
	   }
	   else
	   {
	      /* Wird ein negativer Wert zurückgegeben, ist ein Fehler aufgetreten */
	      fprintf (stderr, "Error");
	      exit (1);
	   }
	   return 0;
	}
