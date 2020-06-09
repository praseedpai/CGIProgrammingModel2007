//
//
// This program is written to demonstrate that an executable
// inherits the environment of the parent.
//
//
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include <tchar.h>

void main( int argc , char **argv , char **envp )
{
    //
    //		

    SetEnvironmentVariable(_T("ENVESTNET"),_T("Envest Net Asset Management"));

    // Spawn the program dumpenv	
    system("dumpenv.exe");
    



}