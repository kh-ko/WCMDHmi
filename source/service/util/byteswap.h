#ifndef BYTESWAP_H
#define BYTESWAP_H

#define SWAP_SHORT(d,s) {((char *)&d)[0] = ((char *)&s)[1]; ((char *)&d)[1] = ((char *)&s)[0];}
#define SWAP_SHORT_RETURN(x) (((x << 8) & 0xff00) | ((x >> 8) & 0xff))
#define SWAP_INT(d,s)   {((char *)&d)[0] = ((char *)&s)[1]; ((char *)&d)[1] = ((char *)&s)[0]; ((char *)&d)[2] = ((char *)&s)[3]; ((char *)&d)[3] = ((char *)&s)[2];}

#endif // BYTESWAP_H
