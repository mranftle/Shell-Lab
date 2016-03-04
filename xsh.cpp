#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "BasicTasks.h"
#include "InternalCommands.h"
#include <ctype.h>
#include <unistd.h>

using namespace std;
void xshLoop();

bool ValidateCommandLine(int argc, char *argv[]);
int main(int argc, char * argv[])
{

    ValidateCommandLine(argc, argv);
    //command loop:
    xshLoop();

return 0;
}
/*
 * Control Loop for the shell xsh
 */
void xshLoop(void)
{
  BasicTasks bt;
  InternalCommands ic;
  char *line = NULL;
  vector<string> args;
  int status;
  char * preservedLine;
  

  do {
     cout <<"xsh >> ";
     //Reading line user inputs:
     line =(char *) bt.readLine();

     //Not likely but if this is true; BAIL!
     if(line == NULL){
       cout<<"line is equal to NULL"<<endl;
      return;
     }
      //Need a deep copy.
      preservedLine = new char[strlen(line) + 1];
      strcpy(preservedLine, line);

     bt.parseLine(line,args);

     if(args.empty())
     {
#ifdef _VDEBUG
          cout <<"the command line is empty" << endl;
#endif
       
     }
     else if(args.at(0) =="exit")
     {
        return;
     }
     else if(args.at(0)=="clr")
     {
       ic.clearScreen();

     }else if(args.at(0) =="echo")
     {
       ic.echoCommand(preservedLine);
     
     }else if(args.at(0)=="show")
       ic.showCommand(args);
     {
     }else if(args.at(0) =="history")
     {
        ic.historyCommand();
     } 
	 else if(args.at(0) =="export")
	 {
		 ic.exportCmd(preservedLine);
	 }
	 else if(args.at(0) =="unexport")
	 {
		 ic.unexportCmd(preservedLine);
	 }
	 else if(args.at(0) =="environ")
	 {
		 ic.environCmd();
	 }
     else
     {
#ifdef _VDEBUG
          cout <<"args are:"<<endl;
          for(unsigned int i= 0; i < args.size(); i++)
          cout <<"["<<i<<"]: "<<args.at(i)<<endl;
#endif
     }

     ic.addCmdToHistory(preservedLine);

     status = bt.executeLine(args,ic);
     args.clear();

     delete [] line ;
     line = NULL;
     delete [] preservedLine;
     preservedLine = NULL;

  } while (status);

}

/**
 *ValidateCommandLine():
 *   validates the commandline for valid combinations of option
 *   flags and their arguments.
 */
bool ValidateCommandLine(int argc, char *argv[])
{
    char opt;
    bool  status = true;
    string filename;

     if(argc == 1)
     {  
       //return false;
     } 

     while((opt=getopt(argc,argv,"f:w:h"))!=-1)
     {  
        switch(opt)
        {
            case 'h':
  
               //show help and exit:
               status = false;
               break;
           case 'f':
               filename = optarg;
               break;
           case 'w':
              filename = optarg;

              break;
          default:
             break;
 
        } 
     } 

 
 return status;
}
