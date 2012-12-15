/* 
 * defs.h  
 * (based on GraphicsGems.h, by Andrew Glassner)
 */

#ifndef DEFS_H
#define DEFS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "laux.h"

/***********************/
/* one-argument macros */
/***********************/

/* absolute value of a */
#define ABS(a)          (((a)<0) ? -(a) : (a))

/* round a to nearest integer towards 0 */
#define FLOOR(a)                ((a)>0 ? (int)(a) : -(int)(-a))

/* round a to nearest integer away from 0 */
#define CEILING(a) \
((a)==(int)(a) ? (a) : (a)>0 ? 1+(int)(a) : -(1+(int)(-a)))

/* round a to nearest int */
#define ROUND(a)        ((a)>0 ? (int)(a+0.5) : -(int)(0.5-a))          

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a)         (((a)<0) ? -1 : (a)>0 ? 1 : 0)  

/* take binary sign of a, either -1, or 1 if >= 0 */
#define SGN(a)          (((a)<0) ? -1 : 0)

#define ODD(a)         ((a)&1)

#define EVEN(a)         (((a)&1)==0)

/* square a */
#define SQR(a)          ((a)*(a))       


/***********************/
/* two-argument macros */
/***********************/

/* find minimum of a and b */
#define MIN(a,b)        (((a)<(b))?(a):(b))     

/* find maximum of a and b */
#define MAX(a,b)        (((a)>(b))?(a):(b))     

/* swap a and b */
#define SWAP(A, B, TYPE) {TYPE tmp; tmp = A; A = B; B = tmp;}

/* linear interpolation from l (when a=0) to h (when a=1)*/
/* (equal to (a*h)+((1-a)*l) */
#define LERP(a,l,h)     ((l)+(((h)-(l))*(a)))

/* clamp the input to the specified range */
#define CLAMP(v,l,h)    ((v)<(l) ? (l) : (v) > (h) ? (h) : v)


/****************************/
/* memory allocation macros */
/****************************/

/* create a new instance of an array of size n  */
#define NEWARRAY(n, x)  (struct x *)(emalloc((unsigned)((n)*sizeof(struct x))))

/* create a new instance of a structure */
#define NEWSTRUCT(x)    (struct x *)(emalloc((unsigned)sizeof(struct x)))

/* create a new instance of a type */
#define NEWTYPE(x)      (x *)(emalloc((unsigned)sizeof(x)))

/* create a new instance of an array */
#define NEWTARRAY(n, x) (x *)(emalloc((unsigned)((n)*sizeof(x))))


/********************/
/* useful constants */
/********************/

#define PI              3.141592        /* the venerable pi */
#define PITIMES2        6.283185        /* 2 * pi */
#define PIOVER2         1.570796        /* pi / 2 */
#define E               2.718282        /* the venerable e */
#define SQRT2           1.414214        /* sqrt(2) */
#define SQRT3           1.732051        /* sqrt(3) */
#define GOLDEN          1.618034        /* the golden ratio */
#define DTOR            0.017453        /* convert degrees to radians */
#define RTOD            57.29578        /* convert radians to degrees */

#define MAX_INT          2147483647
#define MAX_DOUBLE       1.797693134862315708e+308
#define MAX_FLOAT        ((float)3.40282346638528860e+38)
#define MIN_DOUBLE       4.94065645841246544e-324
#define MIN_FLOAT        ((float)1.40129846432481707e-45)

#define EPS             1e-20

/************************/
/* relative comparisons */
/************************/

#define REL_EPS   1e-10

#define REL_EQ(a, b)    ((fabs((a) - (b)) > REL_EPS) ? FALSE : TRUE)
#define REL_GT(a, b)    (((a) > ((b) + REL_EPS)) ? TRUE : FALSE)
#define REL_LT(a, b)    (((a) < ((b) - REL_EPS)) ? TRUE : FALSE)

/************/
/* booleans  */
/************/

#define TRUE            1
#define FALSE           0
#define ON              1
#define OFF             0
#define UNDEFINED      -1

typedef int Boolean;                    /* boolean data type */
typedef Boolean Flag;                   /* flag data type */

typedef double Real;

#endif

