static char *hSCCSID = "@(#)$Header$";
/************************************************************
 ** md5.h -- header file for implementation of MD5                    **
    RSA Data Security, Inc. MD5 Message-Digest Algorithm              **
    Created: 2/17/90 RLR                                              **
    Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version               **
    Revised (for MD5): RLR 4/27/91                                    **
 ***********************************************************/
/* typedef a 32-bit type */
typedef unsigned long int UINT4;

/* Data structure for MD5 (Message-Digest) computation */
typedef struct {
  UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
  UINT4 buf[4];                                    /* scratch buffer */
  unsigned char in[64];                              /* input buffer */
  unsigned char digest[16];     /* actual digest after MD5Final call */
} MD5_CTX;

void MD5Init ();
void MD5Update ();
void MD5Final ();

/************************************************************
 ** End of md5.h                                                      **
 ***********************************************************/
