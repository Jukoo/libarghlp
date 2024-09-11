/** @file  getoptl_ext.h  
 *  @brief extending getopt option  struct with embedded  
 *         description for each  flags 
 *  @author  Jukoo aka Umar Ba <jUmarB@protonmail.com> 

 */
#ifndef __argument_helper 
#define __argument_helper  

#include <getopt.h>

#ifdef  __cplusplus  
# define ARGHLP  extern "C"  
#else 
# define ARGHLP 
#endif 

#define  nullable NULL 

#define  MAX_BUFF   0xff
#define  USAGE_BUFF 0x1000 //! That's arbitrary 

#define  OPT_END  { nullable,0,nullable,0} 
#define  OPTX_END {OPT_END,0} 

#define  OPT_END_DEF   (struct option) OPT_END 
#define  OPTX_END_DEF  (struct optionx) OPTX_END 

#define  def(__option) \
  __option##_DEF

#ifndef BUILD_FROM_SNAME
//! By default  it  use option.val to build  short argument 
# define BUILD_FROM_SVAL
#endif 

#define ARGENTRY_SYMB 58  

//!  FORMATING 
#if !defined(HELPER_FRMT)
# define HELPER_FRMT  " -%c, --%s %s" 
#endif

#if !defined(USAGE_FRMT) 
# define USAGE_FRMT  "USAGE: %s \n"
#endif 

//! __help() macro 
#define __help__ fprintf(stdout ,"%s\n", __usage)
#define __usage__  __help__
#define __display_usage__ __help__

enum { 
  REQUIRED,
#ifdef  required_argument  
# define REQUIRED  required_argument 
#endif

  OPTIONAL 
#ifdef optional_argument 
# define OPTIONAL optional_argument 
#endif 
}; 

enum { 
   ARGREQUIERED ,   
#define ARGREQUIERED  (1 << ARGREQUIERED)
   ARGOPTIONAL 
#define ARGOPTIONAL   (1 << ARGOPTIONAL) 
}; 

#define __attribute_option(__attr__) \
  ARG#__attr__ 


typedef struct __flags_t flags_t ;  
extern char    __usage[USAGE_BUFF] ;
extern char    __shopt[MAX_BUFF] ; 
extern struct  option  __optl[MAX_BUFF] ; 
extern int     __nargp ;  //! store how many argumen used  
                    

struct  optionx { 
  struct option optlong ; 
  char   optdesc[MAX_BUFF]; 
}; 

struct synopsys_t { 
  char * header_description ;
  char * footer_description ;  
}; 

typedef struct argopt  argopt ;  

typedef  void *(*__user_arghandler)(int __ac , char *const * __av , 
    const char  * __shortopt , 
    struct option * __longoption  , 
    void * __args) ;   


struct argopt { 
  struct synopsys_t  *synopsys ; 
  struct optionx * options; 
  __user_arghandler  arghdl_cb ; 
};  
 

ARGHLP static char * get_program_basename(char *const  * __argument_vector) __nonnull((1)); 
ARGHLP static void*  set_option( char  * __shortopt ,   int __has_arg ) ; 
ARGHLP static  char * build_short_option(const struct optionx * __raw_optionx) __wur __nonnull((1)); 

ARGHLP void static build_usage_helper(char* flags_t ,
    const char * __flag_description) __nonnull((1 ,2)); 

ARGHLP char * print_help(void) ; 

ARGHLP void  *argopt_bundler ( int __argcounter  ,
    char * const *__argvector , 
    const  struct argopt *__argopt , void *__argxtra) 
  __nonnull((2,3));

ARGHLP static char * make_sysnopsys(char *__basename , 
    struct synopsys_t * __synopsys,
    char * __usage_body) __nonnull((1,2,3)) ; 

ARGHLP static struct option * extract_getopt_option(struct  option *  __g_option) __nonnull(()) ;

#endif 
