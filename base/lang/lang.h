#ifndef LANG_H
#define LANG_H

#include "geom.h"

#define V_NULL	  0
#define V_NUM	  1
#define V_STR	  2
#define V_NOD	  3
#define V_PVL	  4
#define V_PRV	  5

#define T_PREP    0
#define T_EXEC    1
#define T_QUERY   -1

typedef struct Val {
  int type;	
  union {                 
    double       d;	
    char        *s;
    struct Node *n;
    void        *v;
  } u;			        
} Val;

typedef struct Pval {
  struct Pval  *next;	
  char	       *name;
  struct Val    val;
} Pval;

typedef struct Node {
  struct Val   (*func)(int, Pval *);
  struct Pval  *plist;
} Node;


Val     pv_value(int type, double num, char *str, Node *nl);
Pval   *pv_append(Pval *pvlist, Pval *pv);
Pval   *pv_make(char *name, Val v);

void    pvl_to_array(Pval *pvl, double *a, int n);
Vector3 pvl_to_v3(Pval *pvl);
Vector3 pvl_get_v3(Pval *pvl, char *pname, Vector3 defval);
Real    pvl_get_num(Pval *pvl, char *pname, Real defval);
void    pvl_free(Pval *plist);

Node    *t_node(Val (*f)(int, Pval *), Pval *p);
Val     t_pvl(int c, Pval *pl);
Val     t_eval(Node *n);
Val     t_nd_eval(Node *n);

void lang_file(FILE *fd);
void lang_defun(char *name, Val (*fval)());
int  lang_parse(void);
Val  lang_eval(void);
Val  lang_nd_eval(void);
Node *lang_ptree(void);

#endif
