/**************************************************************************
                                  libpm.c
***************************************************************************
  This is the most fundamental Netpbm library.  It contains routines
  not specific to any particular Netpbm format.

  Some of the subroutines in this library are intended and documented
  for use by Netpbm users, but most of them are just used by other
  Netpbm library subroutines.

  Before May 2001, this function was served by the libpbm library
  (in addition to being the library for handling the PBM format).

**************************************************************************/
#define _SVID_SOURCE
    /* Make sure P_tmpdir is defined in GNU libc 2.0.7 (_XOPEN_SOURCE 500
       does it in other libc's.
    */
#define _XOPEN_SOURCE 500    /* Make sure ftello, fseeko are defined */
#define _LARGEFILE_SOURCE 1  /* Make sure ftello, fseeko are defined */
#define _LARGEFILE64_SOURCE 1 
#define _FILE_OFFSET_BITS 64
    /* This means ftello() is really ftello64() and returns a 64 bit file
       position.  Unless the C library doesn't have ftello64(), in which 
       case ftello() is still just ftello().

       Likewise for all the other C library file functions.

       And off_t and fpos_t are 64 bit types instead of 32.  Consequently,
       pm_filepos_t might be 64 bits instead of 32.
    */
#define _LARGE_FILES  
    /* This does for AIX what _FILE_OFFSET_BITS=64 does for GNU */
#define _LARGE_FILE_API
    /* This makes the the x64() functions available on AIX */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#ifdef __DJGPP__
  #include <io.h>
#endif

#include "mallocvar.h"
#include "ppm.h"

static const char* pm_progname;
/* Programs should produce output in plain format */
int pm_plain_output;

char
pm_getc(FILE * const file) {
    int ich;
    char ch;

    ich = getc(file);
    if (ich == EOF)
        pm_error("EOF / read error reading a byte");
    ch = (char) ich;
    
    if (ch == '#') {
        do {
	    ich = getc(file);
	    if (ich == EOF)
            pm_error("EOF / read error reading a byte");
	    ch = (char) ich;
	    } while (ch != '\n' && ch != '\r');
	}
    return ch;
}

/* This is useful for PBM files.  It used to be used for PGM and PPM files
   too, since the sample size was always one byte.  Now, use pbm_getrawsample()
   for PGM and PPM files.
*/

unsigned char
pm_getrawbyte(FILE * const file) {
    int iby;

    iby = getc(file);
    if (iby == EOF)
        pm_error("EOF / read error reading a one-byte sample");
    return (unsigned char) iby;
}


unsigned int
pm_getuint(FILE * const ifP) {
/*----------------------------------------------------------------------------
   Read an unsigned integer in ASCII decimal from the file stream
   represented by 'ifP' and return its value.

   If there is nothing at the current position in the file stream that
   can be interpreted as an unsigned integer, issue an error message
   to stderr and abort the program.

   If the number at the current position in the file stream is too
   great to be represented by an 'int' (Yes, I said 'int', not
   'unsigned int'), issue an error message to stderr and abort the
   program.
-----------------------------------------------------------------------------*/
    char ch;
    unsigned int i;

    do {
        ch = pm_getc(ifP);
	} while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

    if (ch < '0' || ch > '9')
        pm_error("junk in file where an unsigned integer should be");

    i = 0;
    do {
        unsigned int const digitVal = ch - '0';

        if (i > INT_MAX/10 - digitVal)
            pm_error("ASCII decimal integer in file is too large to be processed.  ");
        i = i * 10 + digitVal;
        ch = pm_getc(ifP);
    } while (ch >= '0' && ch <= '9');

    return i;
}

/* Variable-sized arrays. */

char*
pm_allocrow(int const cols, int const size) {
    char * itrow;

    itrow = malloc( cols * size );
    if ( itrow == NULL )
        pm_error( "out of memory allocating a row" );
    return itrow;
    }

void
pm_freerow(char * const itrow) {
    free( itrow );
}

void
pm_perror(const char reason[] ) {
    const char* e;

#ifdef A_STRERROR
    e = strerror(errno);
#else /* A_STRERROR */
    e = sys_errlist[errno];
#endif /* A_STRERROR */

    if ( reason != 0 && reason[0] != '\0' )
        pm_error( reason );
    else
        pm_error( e );
    }



void 
pm_error(const char format[]) {
    fprintf(stderr, "%s: ", pm_progname);
    fprintf(stderr, format);
    fputc('\n', stderr);
    exit(1);
}

/* Variable-sized arrays. */


char**
pm_allocarray(int const cols, int const rows, int const size )  {
/*----------------------------------------------------------------------------
   Allocate an array of 'rows' rows of 'cols' columns each, with each
   element 'size' bytes.

   We use a special format where we tack on an extra element to the row
   index to indicate the format of the array.

   We have two ways of allocating the space: fragmented and
   unfragmented.  In both, the row index (plus the extra element) is
   in one block of memory.  In the fragmented format, each row is
   also in an independent memory block, and the extra row pointer is
   NULL.  In the unfragmented format, all the rows are in a single
   block of memory called the row heap and the extra row pointer is
   the address of that block.

   We use unfragmented format if possible, but if the allocation of the
   row heap fails, we fall back to fragmented.
-----------------------------------------------------------------------------*/
    char** rowIndex;
    char * rowheap;

    MALLOCARRAY(rowIndex, rows + 1);
    if ( rowIndex == NULL )
        pm_error("out of memory allocating row index (%u rows) for an array");
    rowheap = malloc( rows * cols * size );
    if ( rowheap == NULL ) {
        /* We couldn't get the whole heap in one block, so try fragmented
           format.
        */
        unsigned int row;
        
        rowIndex[rows] = NULL;   /* Declare it fragmented format */

        for (row = 0; row < rows; ++row) {
            rowIndex[row] = pm_allocrow(cols, size);
            if (rowIndex[row] == NULL)
                pm_error("out of memory allocating Row of an array");
        }
    } else {
        /* It's unfragmented format */
        unsigned int row;
        rowIndex[rows] = rowheap;  /* Declare it unfragmented format */

        for (row = 0; row < rows; ++row)
            rowIndex[row] = &(rowheap[row * cols * size]);
    }
    return rowIndex;
}

void
pm_freearray(char ** const rowIndex, 
             int     const rows) {

    void * const rowheap = rowIndex[rows];

    if (rowheap != NULL)
        free(rowheap);
    else {
        unsigned int row;
        for (row = 0; row < rows; ++row)
            pm_freerow(rowIndex[row]);
    }
    free(rowIndex);
}


int 
pm_readmagicnumber(FILE * const ifP) {
    int ich1, ich2;

    ich1 = getc(ifP);
    ich2 = getc(ifP);
    if (ich1 == EOF || ich2 == EOF)
      pm_error( "Error reading magic number from Netpbm image stream.  ");
    return ich1 * 256 + ich2;
}


