/*
Generate N deterministic privatekeys, publickey and legacy address from a password or passphrase, after M rehash of the given password

Examples:

Generate 1 privatekey and his address after 0 rehashes:
./rehashaddress -p "3'W-CB7;>bRMzH<zyE5~Woh=_O>#eX" -n 1 -m 0

Generate 10 privatekeys and his address after 1 million of rehahes
./rehashaddress -p "}78~Et=jPQP5}MVVj2fc0X38{~I}?c" -n 10 -m 100000

Generate 5 privatekeys and his addrtess after 1337 rehash
./rehashaddress -p "JA,af>9oY2M~8ni0G=S.IKBMb)vNmt" -n 5 -m 1337

Miscellaneous

Password: secret 

0 rehashes is the sha256("secret")
1 rehashes is the sha256(sha256("secret")), in this case is the hash sha256 of the binary value of the sha256("secret")
2 rehashes is the sha256(sha256(sha256("secret"))).... and so on

Please for "m" don't use those values 0 or 1 million or even 1337 use your own lucky number less than 2^31 around 2 billions

Please for the password or passphrase use Complex password with more than 30 characters and don't use common passphrases in any language even for dead languages or fictional languages.

And please dont forget your password

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "util.h"

#include "gmpecc.h"
#include "base58/libbase58.h"
#include "rmd160/rmd160.h"
#include "sha256/sha256.h"


const char *EC_constant_N = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141";
const char *EC_constant_P = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";
const char *EC_constant_Gx = "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
const char *EC_constant_Gy = "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";
int FLAG_N = 0,FLAG_M = 0,FLAG_P = 0;

void generate_straddress(struct Point *publickey,bool compress,char *dst);
void generate_strrmd160(struct Point *publickey,bool compress,char *dst);
void generate_strpublickey(struct Point *publickey,bool compress,char *dst);

struct Elliptic_Curve EC;
struct Point G;
struct Point DoublingG[256];

int main(int argc, char **argv)	{
	struct Point publickey;
	mpz_t privatekey;
	int n,m,i,l;
	char bin_hash[32];
	char str_hash[65];
	char str_publickey[131];
	char str_address[50];
	char c;
	while ((c = getopt(argc, argv, "p:n:m:")) != -1) {
		switch(c) {
			case 'p':
				printf("[I] Password: %s\n",optarg);
				l = strlen(optarg);
				sha256(optarg, l, bin_hash);
				FLAG_P = 1;
			break;
			case 'n':
				n = (int) strtol(optarg,NULL,10);
				printf("[I] n: %i\n",n);
				FLAG_N = 1;
			break;
			case 'm':
				m = (int) strtol(optarg,NULL,10);
				printf("[I] m: %i\n",m);
				FLAG_M = 1;
			break;
		}
	}
	if(!(FLAG_P && FLAG_N && FLAG_M))	{
		fprintf(stderr,"[E] Missing parameter\n");
		exit(0);
	}
	mpz_init_set_str(EC.p, EC_constant_P, 16);
	mpz_init_set_str(EC.n, EC_constant_N, 16);
	mpz_init_set_str(G.x , EC_constant_Gx, 16);
	mpz_init_set_str(G.y , EC_constant_Gy, 16);
	init_doublingG(&G);
	
	
	mpz_init(privatekey);
	mpz_init(publickey.y);
	mpz_init(publickey.x);
	
	i = 0;
	while(i < m )	{
		sha256(bin_hash, 32, bin_hash);
		i++;
	}
	
	i = 0;
	while(i < n	)	{
		tohex_dst(bin_hash,32,str_hash);
		mpz_set_str(privatekey,str_hash,16);
		printf("Privatekey: %s\n",str_hash);
		
		Scalar_Multiplication(G,&publickey,privatekey);
		generate_strpublickey(&publickey,true,str_publickey);
		generate_straddress(&publickey,true,str_address);
		printf("Compress publickey: %s\n",str_publickey);
		printf("Compress address: %s\n",str_address);
		
		generate_strpublickey(&publickey,false,str_publickey);
		generate_straddress(&publickey,false,str_address);
		printf("Uncompress publickey: %s\n",str_publickey);
		printf("Uncompress address: %s\n",str_address);
		
		sha256(bin_hash, 32, bin_hash);
		i++;
	}
}

void generate_strpublickey(struct Point *publickey,bool compress,char *dst)	{
	memset(dst,0,132);
	if(compress)	{
		if(mpz_tstbit(publickey->y, 0) == 0)	{	// Even
			gmp_snprintf (dst,67,"02%0.64Zx",publickey->x);
		}
		else	{
			gmp_snprintf(dst,67,"03%0.64Zx",publickey->x);
		}
	}
	else	{
		gmp_snprintf(dst,131,"04%0.64Zx%0.64Zx",publickey->x,publickey->y);
	}
}

void generate_straddress(struct Point *publickey,bool compress,char *dst)	{
	char str_publickey[131];
	char bin_publickey[65];
	char bin_sha256[32];
	char bin_digest[60];
	size_t pubaddress_size = 42;
	memset(dst,0,42);
	if(compress)	{
		if(mpz_tstbit(publickey->y, 0) == 0)	{	// Even
			gmp_snprintf (str_publickey,67,"02%0.64Zx",publickey->x);
		}
		else	{
			gmp_snprintf(str_publickey,67,"03%0.64Zx",publickey->x);
		}
		hexs2bin(str_publickey,bin_publickey);
		sha256(bin_publickey, 33, bin_sha256);
	}
	else	{
		gmp_snprintf(str_publickey,131,"04%0.64Zx%0.64Zx",publickey->x,publickey->y);
		hexs2bin(str_publickey,bin_publickey);
		sha256(bin_publickey, 65, bin_sha256);
	}
	RMD160Data((const unsigned char*)bin_sha256,32, bin_digest+1);
	
	/* Firts byte 0, this is for the Address begining with 1.... */
	
	bin_digest[0] = 0;
	
	/* Double sha256 checksum */	
	sha256(bin_digest, 21, bin_digest+21);
	sha256(bin_digest+21, 32, bin_digest+21);
	
	/* Get the address */
	if(!b58enc(dst,&pubaddress_size,bin_digest,25)){
		fprintf(stderr,"error b58enc\n");
	}
}
