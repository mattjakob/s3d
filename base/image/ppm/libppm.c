/* libppm1.c - ppm utility library
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/* See libpbm.c for the complicated explanation of this 32/64 bit file
   offset stuff.
*/
#define _FILE_OFFSET_BITS 64
#define _LARGE_FILES  

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "ppm.h"

// 1

gray pgm_getrawsample(FILE * const file, gray const maxval) 
{
  if (maxval < 256) {
    /* The sample is just one byte.  Read it. */
    return(pm_getrawbyte(file));
  } else {
    /* The sample is two bytes.  Read both. */
    unsigned char byte_pair[2];
    size_t pairs_read;

    pairs_read = fread(&byte_pair, 2, 1, file);
    if (pairs_read == 0) 
      pm_error("EOF /read error while reading a long sample");
    /* This could be a few instructions faster if exploited the internal
       format (i.e. endianness) of a pixval.  Then we might be able to
       skip the shifting and oring.
    */
    return((byte_pair[0]<<8) | byte_pair[1]);
  }
}


void ppm_readppminitrest(FILE *const file, int *const colsP, int *const rowsP, pixval *const maxvalP) 
{
  unsigned int maxval;

  /* Read size. */
  *colsP = (int)pm_getuint(file);
  *rowsP = (int)pm_getuint(file);

  /* Read maxval. */
  maxval = pm_getuint(file);
  if (maxval > PPM_OVERALLMAXVAL)
    pm_error("maxval of input image is too large.  ");
  if (maxval == 0)
    pm_error("maxval of input image is zero.");

  *maxvalP = maxval;
}



void ppm_readppminit(FILE *const fileP, int *const colsP, int *const rowsP, pixval *const maxvalP, int *const formatP) 
{
  /* Check magic number. */
  *formatP = pm_readmagicnumber(fileP);
  switch (PPM_FORMAT_TYPE(*formatP)) {
  case PPM_TYPE:
    ppm_readppminitrest(fileP, colsP, rowsP, maxvalP);
    break;
  default:
    pm_error("bad magic number - not a ppm file");
  }
}


void ppm_readppmrow(FILE*  const fileP,pixel* const pixelrow, int const cols, pixval const maxval, int const format) 
{
  switch (format) {
  case PPM_FORMAT: {
    unsigned int col;
    for (col = 0; col < cols; ++col) {
      pixval const r = pm_getuint(fileP);
      pixval const g = pm_getuint(fileP);
      pixval const b = pm_getuint(fileP);
      PPM_ASSIGN(pixelrow[col], r, g, b);
    }
  }
    break;
  case RPPM_FORMAT: {
    unsigned int col;
    for (col = 0; col < cols; ++col) {
      pixval const r = pgm_getrawsample(fileP, maxval);
      pixval const g = pgm_getrawsample(fileP, maxval);
      pixval const b = pgm_getrawsample(fileP, maxval);
      PPM_ASSIGN(pixelrow[col], r, g, b);
    }
  }
    break;
  default:
    pm_error("Invalid format code");
  }
}



pixel** ppm_readppm(FILE *const fileP, int *const colsP, int *const rowsP, pixval *const maxvalP) 
{
  pixel** pixels;
  int row;
  int format;

  ppm_readppminit(fileP, colsP, rowsP, maxvalP, &format);

  pixels = ppm_allocarray(*colsP, *rowsP);

  for (row = 0; row < *rowsP; ++row)
    ppm_readppmrow(fileP, pixels[row], *colsP, *maxvalP, format);

  return pixels;
}

// 2

void ppm_writeppminit(FILE* const fileP, int const cols,  int  const rows, pixval const maxval, int const forceplain) 
{
  int const plainFormat = forceplain || pm_plain_output;

  if (maxval > PPM_OVERALLMAXVAL && !plainFormat) 
    pm_error("too-large maxval passed to ppm_writeppminit()");
  fprintf(fileP, "%c%c\n%d %d\n%d\n", PPM_MAGIC1, plainFormat || maxval >= 1<<16 ? PPM_MAGIC2 : RPPM_MAGIC2, cols, rows, maxval );
#ifdef VMS
  if (!plainFormat)
    set_outfile_binary();
#endif
}

static void putus(unsigned short n, FILE *file ) 
{
  if ( n >= 10 )
    putus( n / 10, file );
  (void) putc( n % 10 + '0', file );
}

void pgm_writerawsample(FILE *file, const gray val, const gray maxval) 
{
  if (maxval < 256) {
    /* Samples fit in one byte, so write just one byte */
    int rc;
    rc = putc(val, file);
    if (rc == EOF)
      pm_error("Error writing single byte sample to file");
  } else {
    /* Samples are too big for one byte, so write two */
    int n_written;
    unsigned char outval[2];
    /* We could save a few instructions if we exploited the internal
       format of a gray, i.e. its endianness.  Then we might be able
       to skip the shifting and anding.
    */
    outval[0] = val >> 8;
    outval[1] = val & 0xFF;
    n_written = fwrite(&outval, 2, 1, file);
    if (n_written == 0) 
      pm_error("Error writing double byte sample to file");
  }
}


static void ppm_writeppmrowraw(FILE *file, pixel *pixelrow, int cols, pixval maxval ) 
{
  register int col;
  register pixval val;

  for ( col = 0; col < cols; ++col )  {
    val = PPM_GETR( pixelrow[col] );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "r value out of bounds" );
#endif /*DEBUG*/
    pgm_writerawsample( file, val, maxval );
    val = PPM_GETG( pixelrow[col] );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "g value out of bounds ");
#endif /*DEBUG*/
    pgm_writerawsample( file, val, maxval );
    val = PPM_GETB( pixelrow[col] );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "b value out of bounds" );
#endif /*DEBUG*/
    pgm_writerawsample( file, val, maxval );
  }
}


static void ppm_writeppmrowplain(FILE *file, pixel *pixelrow, int cols, pixval maxval ) 
{
  register int col, charcount;
  register pixel* pP;
  register pixval val;

  charcount = 0;
  for ( col = 0, pP = pixelrow; col < cols; ++col, ++pP ) {
    if ( charcount >= 65 ) {
      (void) putc( '\n', file );
      charcount = 0;
    }  else if ( charcount > 0 ) {
      (void) putc( ' ', file );
      (void) putc( ' ', file );
      charcount += 2;
    }
    val = PPM_GETR( *pP );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "r value out of bounds" );
#endif /*DEBUG*/
    putus( val, file );
    (void) putc( ' ', file );
    val = PPM_GETG( *pP );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "g value out of bounds " );
#endif /*DEBUG*/
    putus( val, file );
    (void) putc( ' ', file );
    val = PPM_GETB( *pP );
#ifdef DEBUG
    if ( val > maxval )
      pm_error( "b value out of bounds " );
#endif /*DEBUG*/
    putus( val, file );
    charcount += 11;
  }
  if ( charcount > 0 )
    (void) putc( '\n', file );
}


void ppm_writeppmrow(FILE *const fileP, pixel *const pixelrow, int const cols, pixval  const maxval, int const forceplain) 
{
  if (forceplain || pm_plain_output || maxval >= 1<<16) 
    ppm_writeppmrowplain(fileP, pixelrow, cols, maxval);
  else 
    ppm_writeppmrowraw(fileP, pixelrow, cols, maxval);
}



void ppm_writeppm(FILE *const file, pixel** const pixels, int const cols, int const rows, pixval  const maxval, int const forceplain)  
{
  int row;
  ppm_writeppminit(file, cols, rows, maxval, forceplain);
    
  for (row = 0; row < rows; ++row)
    ppm_writeppmrow(file, pixels[row], cols, maxval, forceplain);
}
