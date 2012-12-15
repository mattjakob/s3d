#include        "image.h"

int main(int argc, char *argv[])
{
  char *filein = "stdin";
  char *fileout = "stdout";
  Image *i;

  if (argc == 3) {
    filein = argv[1];
    fileout = argv[2];
  } else {
    printf("tst in out\n");
    exit(1);
  }

  i = img_read(filein);
  img_write(i, fileout, 0);
  exit(0);
}
