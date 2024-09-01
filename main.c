#include <stdio.h> 
#include <stdlib.h> 
#include <getopt.h> 

#include "getoptl_ext.h" 

struct optionx optlx[] ={ 
  {{"help", no_argument , nullable, 'h'} , "\t\tprint help of the program"}, 
  {{"version",no_argument,nullable, 'v'} , "\t\tprint the version of the program"},
  {{"input", required_argument,nullable, 'i'} , "<file>\tinput of the program"},
  {{"output",optional_argument,nullable, 'o'} , "[file]\toutput of the program"},
  OPTX_END 
};

#define  HEADER "This is just an exemple ...\n\
  to test how to use it"


#define FOOTER "\
GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n\
Full documentation <https://www.gnu.org/software/coreutils/cat>\n\
or available locally via: info '(coreutils) cat invocation'"

struct synopsys_t  s =  {
   .header_description = HEADER , 
   .footer_description = FOOTER
}; 


char * argparse(int ac  ,char * const * av , const char *shortopt ,  struct option * opts) 
{
  int p  = 0  ; 
  
  while( (p  = getopt_long(ac , av,  shortopt ,  opts ,  0)) != ~0 ) 
  {
    switch(p) 
    {
      case  'h': 
        __help() ;
        break; 
      case 'v':  
        dprintf(1,  "hi\n") ; 
        break; 

    }
  }
  
  
}
int main (int ac , char **av)
{
  struct argopt argp = {
    .synopsys = &s, 
    .options   = optlx, 
    .ucustom=  argparse
  } ; 
    
  argopt_bundler(ac , av ,&argp) ; 
  

  return EXIT_SUCCESS ; 
}
