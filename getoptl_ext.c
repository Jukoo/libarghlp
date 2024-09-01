#include <stdlib.h> 
#include <unistd.h> 
#include <getopt.h> 
#include <libgen.h>
#include <stdio.h> 
#include <string.h>
#include <wchar.h> 

#include  "getoptl_ext.h"

char __usage[USAGE_BUFF] = { 0 } ; 
char __shopt[MAX_BUFF] ={0}; 
struct option  __optl[MAX_BUFF]; 
int __nargp = 0 ; 

struct __flags_t{ 
  char *long_flags ; 
  char short_flags ; 
};


char * get_program_basename(char *const  * argvector)  
{
     return  __xpg_basename( *argvector)   ;  
}

char * build_short_option(const  struct optionx * optxlist) 
{
  struct option * opt = nullable;
  struct optionx * optx = (struct  optionx *)  optxlist ;
  
  
  char * shortopts = calloc(MAX_BUFF ,sizeof(char*)) ;
  if (!shortopts) 
    return nullable ; 

  int  optindex = 0 ; 
  int  soptindex= 0 ; 
  while( ((optx+optindex))->optlong.name != nullable) 
  {
    opt = &(optx+optindex)->optlong;
    *(__optl+optindex)= *opt;

#ifdef BUILD_FROM_SNAME
    *(shortopts+soptindex)= opt->name[0] ;
#else 
    *(shortopts+soptindex)=  opt->val;
#endif 

    //! just used  to  easy build of  --longflags   -l 
    flags_t  flags =  { .long_flags=(char*)opt->name , .short_flags=*(shortopts+soptindex) }  ; 

    build_usage_helper((char *)&flags, (optxlist+optindex)->optdesc) ; 
    switch (opt->has_arg) 
    {
       case required_argument:  
         soptindex++; 
         memset((shortopts+soptindex),ARGIN , ARGREQUIERED);
         break;
       case optional_argument: 
         memset((shortopts+ ++soptindex),ARGIN ,ARGOPTIONAL);
         soptindex++; 
         break; 
       case no_argument:
         break; 
    }
    optindex++ ; 
    soptindex++; 
    explicit_bzero(opt , sizeof(*opt)) ; 
  }
  memcpy(__shopt , shortopts , strlen(shortopts)) ; 
  free(shortopts) ; 
  *(__optl+optindex)= def(OPT_END) ;
  __nargp =  optindex++ +1  ;

  return __shopt ; 
}

void static build_usage_helper(char * flags, const char * flag_description) 
{
  char s[MAX_BUFF]=  {0}; 
  flags_t  *f = (flags_t*) flags ; 
  sprintf(s , USAGE_FRMT,  f->short_flags ,  f->long_flags , flag_description) ; 
 
  if (!strrchr(s,0xa)) 
     strcat(s,"\n") ; 
  
  strcat(__usage ,s) ;   

}

static char * make_synopsys(char * bn , struct synopsys_t * synopsys , char * usage_body) 
{
  if(!synopsys) 
    return usage_body ; 
  

  char usage_tmp[USAGE_BUFF] =  {0} ; 
  //! Save the usage body  
  memcpy(usage_tmp , usage_body ,  strlen(usage_body)) ;   

  //!clean usage body 
  explicit_bzero(usage_body ,USAGE_BUFF) ; 
  
  char *header = synopsys->header_description ; 
  char *footer = synopsys->footer_description ;  

  sprintf(usage_body , "USAGE: %s \n" , bn) ;   
  
  if (header!= nullable) {
    //!just replace the  '\n' if header  if not null for
    //! better readability 
    char * remove_sn = strrchr(usage_body , 0xa) ; 
    *remove_sn = 0 ; 
    
    sprintf((usage_body+strlen(usage_body)) , "%s \n\n", header) ; 
  }
  
  memcpy((usage_body+strlen(usage_body)), usage_tmp , strlen(usage_tmp)) ;
  
  if(footer != nullable)
    sprintf((usage_body+strlen(usage_body)) , "\n%s", footer) ; 
  
  return usage_body ; 
}

char *argopt_bundler ( int ac    , char * const * av  ,  const struct  argopt *  argopt ) 
{
  char * bn  = get_program_basename(av) ;
  char *sopt = build_short_option(argopt->options);
  char * helper = make_synopsys( bn , argopt->synopsys , __usage) ;  
 
  struct option  getopt_option[__nargp];  
  
  if (!extract_getopt_option(getopt_option)) 
    return nullable ; 
  
  argopt->ucustom(ac , av , sopt,  getopt_option);  

}


static struct option * extract_getopt_option(struct  option * g_opt) 
{
  if(  0 >= __nargp ) 
    return nullable ; 

  int i = ~0 ; 
  while(++i < __nargp  ) 
     *(g_opt+i) =  *(__optl+i); 

  return g_opt ;  
}
