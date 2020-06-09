// A simple CGI program
// This program demonstrates Session
//  
//
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <time.h>


//
//  
//
//
using namespace std;

char *GetCookieValueForKey( const char *keyvalue );

//
//
//
//
//
//
//

class STATE_DATA;
class PAIR;

STATE_DATA *session_state = 0;
STATE_DATA *application_state=0;
char szSessionFileName[255];
static int FOO = 10;
//
//
// Data structure to store Name/Value pair
//
//
//
struct PAIR
{
  char Name[255];
  char value[1024];
  PAIR() {
     memset(Name,0,sizeof(Name));
     memset(value,0,sizeof(value));
  }    

};

//
// A Class to store State
//
//
//
//

class STATE_DATA
{

   // Hard coded - in a production setting make it dynamic	
   PAIR entry[1000];
   int i;


  public :
    //
    // Empty constructor
    //
    STATE_DATA() 
    { memset(entry , 0, sizeof(PAIR)*1000);
      i=0;
    }

    //
    //
    //
    //
    int GetCount() { return i; }

    //
    // Get an entry given the index
    //
    PAIR *GetEntry( int k )
    {
        if ( k < i ) {
	   PAIR *ret =new PAIR();
	   strcpy(ret->Name,entry[k].Name);
	   strcpy(ret->value,entry[k].value);
	   return ret;
	}

        return 0;        
    }
    //
    // Add a name/value pair to the dictionary
    //
    //	
    bool Add(char *name , char *value )      
    {
         strcpy(entry[i].Name, name);
         strcpy(entry[i].value, value);
	 i++ ;
 	 return true;
    }
    //
    // Add a name/value pair to the dictionary
    //	
    bool Add(char *name,int a )
     {
	char buf[100];
	sprintf(buf,"%d",a);
        return Add(name,buf); 
     }
    //
    //
    //
    // 	
    bool Add(char *name,double a )
     {
	char buf[100];
	sprintf(buf,"%g",a);
        return Add(name,buf); 
     }

    //
    // Look up a name and return the value
    // 	

    char *Lookup( char *name ) {
        int k=0;
	while (k<i)
        { 
	  if ( stricmp(entry[k].Name,name) == 0 )
                  return entry[k].value;
   

           k++;
        }

    }

    //
    //  Save the stuff to the file name
    // 
    bool Save(char *filename ) 
    {
        FILE *fp = fopen(filename,"wt");

        if ( fp == 0 ) return false;

        int cnt = GetCount();

        for(int j=0; j<cnt; ++j )
        {
          PAIR *p = GetEntry(j);
          fprintf(fp,"%s=%s\n",p->Name,p->value );
          delete p;
        }          

        fclose(fp);	

    }

    bool Load(char *filename ) 
    {

        
        FILE *fp = fopen(filename,"rt");

        if ( fp == 0 ) 
                return false;


        

	while (!feof(fp))
        {
            char linebuff[255];
    	    fgets(linebuff,255,fp);
            PAIR *p = PeelNameValue(linebuff);
            Add(p->Name, p->value); 

	}

        fclose(fp);	 


    }


    PAIR *PeelNameValue( char *buf )
    {
       char *name = strdup(buf);
       char *tname = strstr(name,"=");
       if (tname == 0 )
              return new PAIR();  
	*tname++=0; 	
       PAIR *p = new PAIR();
       strcpy(p->Name,name);
       name = strchr(tname,'\n');
       *name=0;    	 
       strcpy(p->value,tname);
       return p; 


    }


};


//
//
//   Emit the Header and cookie data
//
//
void EmitHTTPHeader(char *cookievalue)
{
 
     int i = 0;
     char szTempName[255];
     memset(szTempName,0,255); 


       
     if ( cookievalue != 0 && *cookievalue != 0 ) 
     {
         i = atoi(cookievalue)+1;

     }


     char *ptr = GetCookieValueForKey("SESSIONID");

     if ( ptr == 0 ) { 
         
         // Create a temporary file. 
         unsigned long uRetVal = GetTempFileName("C:\\TEMP\\", // directory for tmp files
                            "SESSION_",                              // temp file name prefix 
                            0,                                             // create unique name 
                             szTempName);  // buffer for name 

              

     }

     else {

         strcpy(szTempName,ptr);
         strcpy(szSessionFileName,ptr);  
         
         
     }

     session_state->Load(szSessionFileName);      
          
        
     printf("HTTP/1.0 200 OK\n");
     printf("Set-Cookie: COUNTER=%d;\n",i);
     printf("Set-Cookie: SESSIONID=%s\n",szTempName);
     printf("Content-type: text/html\n\n\n");
     printf("Filename is %s\n",szTempName);
    

}

//
//
// Retrieve the value corresponding to the key
//
//
//

char *GetCookieValueForKey( const char *keyvalue )
{
   char * ret_val = getenv("HTTP_COOKIE");

   if ( ret_val == 0)
          return 0;


   char *strptr = strstr(ret_val,keyvalue);

   if (strptr == 0 ) 
        return 0;

   while ( *strptr != 0 && *strptr != '=' )
                strptr++;

   if ( strptr == 0 )
          return 0;

   strptr++;

   ret_val = (char *) malloc(255);

	if ( ret_val == 0 ) return 0;

   char *sret = ret_val;       

   while ( *strptr != 0 && *strptr != ';' )
              *ret_val++ = *strptr++;   

   if ( *strptr == ';' )
	*ret_val = 0;

   return sret;


}

//
//
//
//
//
//
//

char *GetQueryString()
{
   
   char *lp = getenv("QUERY_STRING");

   if ( lp == 0) return "No env";

   return strdup(lp);

}

//
//
// Start the session
//
//

void StartSession()
{
     session_state = new STATE_DATA(); 
     application_state = new STATE_DATA();

     if ( application_state != 0 )
        application_state->Load("C:\\Temp\\APPLICATION_STATE.BIN");   

        


    char buffer[255];
    srand(time(NULL));
    Sleep(2000); 
    int ds =(int)(rand());  
    sprintf(buffer,"APPLICATION_%d",ds);

    if ( application_state )
        application_state->Add(buffer,ds);


     
         
     EmitHTTPHeader(GetCookieValueForKey("COUNTER"));
}

//
// Save The session Data
//
//

void StopSession()
{

   if ( session_state ) {
       session_state->Add("filename",szSessionFileName); 
       session_state->Save(szSessionFileName);
        
       session_state->Save("C:\\temp\\session_dump.txt");  
   }

    


   if ( application_state )
       application_state->Save("C:\\TEMP\\APPLICATION_STATE.bin");
}



void DumpEnvironment(STATE_DATA *se)
{
   int cnt = se->GetCount();

   for(int j=0; j<cnt; ++j )
   {
          PAIR *p = se->GetEntry(j);

          if ( *(p->Name) != 0  )
             fprintf(stdout,"<H1>%s=%s</H1>\n",p->Name,p->value );
          delete p;
   }             


}

//
//
//
//  user entry point 
//
//
void main( int argc , char **argv )
{



       StartSession(); 

        char *lpstrMethod = getenv("REQUEST_METHOD");

	
        if ( lpstrMethod == 0 )
 		return; 

       
          
      


        if ( strnicmp(lpstrMethod,"GET",3) == 0 )
        {
		printf("<form method=\"get\" action=\"http://localhost/cgi/session_demo.exe\">");
		printf("<input name=\"value1\" value=\"test1\">");
		printf("<input name=\"value2\" value=\"test2\">");
		printf("<input name=\"value3\" value=\"test3\">");
		printf("<input type=\"submit\">");
                

                
               cout << "------------------------ Application data\n " << endl; 
               DumpEnvironment(application_state); 


               cout << "------------------------ Session data \n" << endl; 

                srand(time(NULL));
                int ds =(int)(rand());  
                char buffer[255];  

                sprintf(buffer,"SESSION_%d",ds);

                char *sp = GetQueryString();
                    
                if ( session_state )
                       session_state->Add(buffer,sp==0?"No":sp); 
               DumpEnvironment(session_state); 
               
 
		printf("</form>\n");


        }
        
        
	StopSession();        
	return ;

}