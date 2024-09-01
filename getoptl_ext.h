/** @file  getoptl_ext.h  
 *  @brief extending getopt option  struct with embedded  
 *         description for each  flags 
 */
#ifndef __getoptl_extender  
#define __getoptl_extender

#include <getopt.h>

#ifdef  __cplusplus  
# define GOPTLX  extern "C"  
#else 
# define GOPTLX 
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

struct  optionx { 
  struct option optlong ; 
  char   optdesc[MAX_BUFF]; 
}; 

struct synopsys_t { 
  char * header_description ;
  char * footer_description ;  
}; 

typedef struct argopt  argopt ;  

typedef  char*(*__user_argpcb)(int __ac , char *const * __av , 
    const char  * __shortopt , 
    struct option * __longoption)
   __nonnull((2,3,4)); 


struct argopt { 
  struct synopsys_t  *synopsys ; 
  struct optionx * options; 
  __user_argpcb ucustom;
};  

typedef struct __flags_t flags_t ;  
extern char    __usage[USAGE_BUFF] ;
extern char    __shopt[MAX_BUFF] ; 
extern struct  option  __optl[MAX_BUFF] ; 
extern int     __nargp ;  //! store how many argumen used  
                    
#ifndef BUILD_FROM_SNAME
//! By default  it  use option.val to build  short argument 
# define BUILD_FROM_SVAL
#endif 

#define ARGIN 0x3a  //':' 
enum { 
   ARGREQUIERED ,   
#define ARGREQUIERED  (1 << ARGREQUIERED)
   ARGOPTIONAL 
#define ARGOPTIONAL   (1 << ARGOPTIONAL) 
};

#define USAGE_FRMT  " -%c, --%s %s" 

#define __help() fprintf(stdout ,"%s\n", __usage)  
 

/** @fn  static char * get_program_basename(char *const*)
 *  @brief  get program basenam 
 *  
 *  @param char *const * 
 *  @return  string\0
 **/
GOPTLX static char * get_program_basename(char *const  * __argument_vector) __nonnull((1)); 

/**
 *
 * @brief  build short options from  optionx struct 
 */
GOPTLX char * build_short_option(const struct optionx * __raw_optionx) __wur __nonnull((1)); 

GOPTLX void static build_usage_helper(char* flags_t ,
    const char * __flag_description) __nonnull((1 ,2)); 

GOPTLX char * print_help(void) ; 

GOPTLX char *argopt_bundler ( int __argcounter  ,
    char * const *__argvector , 
    const  struct argopt *__argopt ) 
  __nonnull((2,3));

GOPTLX static char * make_sysnopsys(char *__basename , 
    struct synopsys_t * __synopsys,
    char * __usage_body) __nonnull((1,2,3)) ; 

GOPTLX static struct option * extract_getopt_option(struct  option *  __g_option) __nonnull(()) ;

#endif 
