/* $Header$ */


#include <stdio.h>	/* for stderr, fprintf, FILE, fopen, fread */
#include "md5.h"


#define BUFSIZE 1024


#ifdef __STD_C__
void usage(char *progname);
int main(int argc, char **argv);

#else
void usage();
int main();

#endif


void usage(progname)
char *progname;
{
  fprintf(stderr, "usage: %s [input file]\n", progname);
  fprintf(stderr, "\n");
  fprintf(stderr, "RSA Data Security, Inc. MD5 Message-Digest Algorithm\n");
  fprintf(stderr, "Hash a file using the MD5 algorithm.\n");
  fprintf(stderr, "Output 4 32-bit (8 digit) hexadecimal numbers.\n");
  fprintf(stderr, "Input from file, if given, or from stdin.\n");
}


int main(argc, argv)
int argc;
char **argv;
{
  FILE *infile;
  char buf[BUFSIZE];
  int  numread;
  MD5_CTX mdContext;

  switch (argc) {
  case 1:
    infile = stdin;
    break;
  case 2:
    if (argv[1][0] == '-' && argv[1][1] == '?' && argv[1][2] == 0) {
      usage(argv[0]);
      exit(1);
    }
    if (NULL == (infile = fopen(argv[1], "r"))) {
      perror("fopen");
      exit(2);
    }
    break;
  default:
    usage(argv[0]);
    exit(1);
    break;
  }

  MD5Init(&mdContext);
  do {
    numread = fread(buf, 1, BUFSIZE, infile);
    MD5Update(&mdContext, buf, numread);
  } while (numread > 0);
  MD5Final(&mdContext);
  printf(
    "%.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x\n",
    mdContext.digest[ 0],
    mdContext.digest[ 1],
    mdContext.digest[ 2],
    mdContext.digest[ 3],
    mdContext.digest[ 4],
    mdContext.digest[ 5],
    mdContext.digest[ 6],
    mdContext.digest[ 7],
    mdContext.digest[ 8],
    mdContext.digest[ 9],
    mdContext.digest[10],
    mdContext.digest[11],
    mdContext.digest[12],
    mdContext.digest[13],
    mdContext.digest[14],
    mdContext.digest[15]
  );
  exit(0);
}


