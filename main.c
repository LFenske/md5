static char *SCCSID = "@(#)$Header$";


#include <stdio.h>	/* for stderr, fprintf, FILE, fopen, fread, EOF */
#include <stdlib.h>	/* for getopt */
#include <unistd.h>	/* for getopt */
#include <string.h>     /* for strlen */
#include "global.h"
#include "md5.h"


#define BUFSIZE 1024


#ifdef __STD_C__
void usage(char *progname);
void dofile(FILE *infile, char *inname);
int main(int argc, char **argv);

#else
void usage();
void dofile();
int main();

#endif


void usage(progname)
char *progname;
{
  fprintf(stderr, "usage: %s [-f filelist] | [input file]...\n", progname);
  fprintf(stderr, "\n");
  fprintf(stderr, "RSA Data Security, Inc. MD5 Message-Digest Algorithm\n");
  fprintf(stderr, "Hash a file using the MD5 algorithm.\n");
  fprintf(stderr, "Output 4 32-bit (8 digit) hexadecimal numbers.\n");
  fprintf(stderr, "Input from file(s), if given, or from stdin, or from filelist.\n");
}


void dofile(infile, inname)
FILE *infile;
char *inname;
{
  char buf[BUFSIZE];
  int  numread;
  MD5_CTX mdContext;
  unsigned char digest[16];

  MD5Init(&mdContext);
  do {
    numread = fread(buf, 1, BUFSIZE, infile);
    MD5Update(&mdContext, buf, numread);
  } while (numread > 0);
  MD5Final(digest, &mdContext);
  printf(
    "%.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x",
    digest[ 0],
    digest[ 1],
    digest[ 2],
    digest[ 3],
    digest[ 4],
    digest[ 5],
    digest[ 6],
    digest[ 7],
    digest[ 8],
    digest[ 9],
    digest[10],
    digest[11],
    digest[12],
    digest[13],
    digest[14],
    digest[15]
  );
  if (inname != NULL)
    printf(": %s", inname);
  printf("\n");
  fflush(stdout);
}


int main(argc, argv)
int argc;
char **argv;
{
  char *inname, *listname;
  FILE *infile, *listfile;

  int c;
  extern char *optarg;
  extern int optind, opterr, optopt;

  listname = NULL;
  while (EOF != (c = getopt(argc, argv, "f:"))){
    switch (c) {
    case 'f':
      listname = optarg;
      if (listname[0] == '-' && listname[1] == 0) {
	listfile = stdin;
      } else {
	if (NULL == (listfile = fopen(listname, "r"))) {
	  perror("fopen list file");
	  exit(2);
	}
      }
      break;
    case '?':
      usage(argv[0]);
      exit(1);
    }
  }

  if (listname == NULL) {
    if (optind == argc) {
      dofile(stdin, NULL);
    } else {
      for ( ; optind < argc; optind++) {
	inname = argv[optind];
	if (inname[0] == '-' && inname[1] == 0) {
	  infile = stdin;
	  inname = NULL;
	} else {
	  if (NULL == (infile = fopen(inname, "r"))) {
	    perror("fopen");
	    exit(2);
	  }
	}
	dofile(infile, inname);
	fclose(infile);
      }
    }
  } else {
    char inname[1024];
    int  len;
    while (NULL != fgets(inname, sizeof(inname), listfile)) {
      len = strlen(inname);
      if (inname[len-1] != '\n') {
	fprintf(stderr, "file name too long\n");
	exit(2);
      }
      inname [len-1] = 0;
      if (NULL == (infile = fopen(inname, "r"))) {
	perror("fopen");
	exit(2);
      }
      dofile(infile, inname);
      fclose(infile);
    }
  }

  exit(0);
}


