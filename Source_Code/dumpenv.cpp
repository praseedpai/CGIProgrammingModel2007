//
//
//
// This Program dumps the environment variables and their values.
// meant to be called from caller.exe ( caller.cpp ) 
//

#include <stdio.h>
#include <string.h>

void main( int argc , char **argv , char **envp )
{

    char **lp =envp;

    int i=0;
    do {
       printf("%s\n",*(lp+i));     
       i++;
       if ( *(lp+i) == 0 )
           break;
}
     while(1);




}
