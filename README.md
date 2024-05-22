## keygen

This tool generate one private and his address/publickey compressed and uncompressed at request.

you can specify the bit size from 1 to 256 with `-b value` where `value` is the number of bits in your key.
if you don't specify this value the bit may vary from 1 to 256, this will depend only of the RNG

Also you can select the random source for this key `-s source`, where `sourse` is one of the next values.
The default source is `urandom`

- `urandom` to use the linux device `/dev/urandom`
- `random` to use the linux device `/dev/random`
- `openssl` to use the RND build in openssl library
- `getrandom` to use the linux kernet funtcion getrandom, this may be equivalen to urandom in some kernels
- `gcrypt` to use RND build in gcrypt library 

example:

```
rage0930$ ./keygen
KEY (Secret: DON'T SHARE THIS VALUE): 18f619c4d16057d362ddfce772f551d46a2390517698226cff6e5bf67ac4b324
publickey uncompressed: 04af6e50db92ce378c29df0ed9a04d3431bc06762aa37ec3ab42af14708363059616992ab8abb4bd8cfcc7d8c8d40331d419f426d7fc8490efb1af47b6316d7a1b
address uncompressed 1CXHD79mKUxUDruD2iEJxs8XBwiJwYGmTR
publickey compressed: 03af6e50db92ce378c29df0ed9a04d3431bc06762aa37ec3ab42af147083630596
address compressed 1PTA5NaUfu5xU5pEmEfobsZbRuWvs4Sik3

```

## sharedsecret

In cryptography is important to have a shared secret with the person who you are communicating.
But is also very important to have a way to communicate this secret without disclose it to all the world.

This tool calculate that shared secret with your privatekey and the publickey of the other person.

Alice (you) want to send a encrypted file to Bob (Other person)
Alice have his own privatekey and Alice know the Publickey of Bob.

Alice use this tool to calcualte the share secret to be use to encrypt the file.

Alice example Keys:
Private key: 18f619c4d16057d362ddfce772f551d46a2390517698226cff6e5bf67ac4b324 (Unknow for Bob and everyone else)
Public key : 03af6e50db92ce378c29df0ed9a04d3431bc06762aa37ec3ab42af147083630596 (Public)

Bob example Keys:
Private key: bc9e78f140a76cbdcdbecc5ab0ec38b4db710edfa40dea342712c8a695fe8b22 (Unknow for Alice and everyone else)
Public key : 022c8191049a3f2816bc95077b91caed87900d0cd2af3757004531face9c3b6082 (Public)

Alice run the program:

```
./sharedsecret
A: private key (hex): 18f619c4d16057d362ddfce772f551d46a2390517698226cff6e5bf67ac4b324
B: public key : 022c8191049a3f2816bc95077b91caed87900d0cd2af3757004531face9c3b6082
Secret between A and B: 22fb667f3bc1a2153e3cef75df0ce757a1c86051c07ace6b0c30dc87f3358511 (DON'T SHARE, THIS IS SECRET)
```

Bob run the program:

```
./sharedsecret
A: private key (hex): bc9e78f140a76cbdcdbecc5ab0ec38b4db710edfa40dea342712c8a695fe8b22
B: public key : 03af6e50db92ce378c29df0ed9a04d3431bc06762aa37ec3ab42af147083630596
Secret between A and B: 22fb667f3bc1a2153e3cef75df0ce757a1c86051c07ace6b0c30dc87f3358511 (DON'T SHARE, THIS IS SECRET)
```
Alice and  Bob get the same shared secret only sharing their own PUBLIC keys to each other.

Alice procced to encrypt their secret file `input.txt` with the password `22fb667f3bc1a2153e3cef75df0ce757a1c86051c07ace6b0c30dc87f3358511`

openssl aes-256-cbc -salt -pbkdf2 -in input.txt -out input.txt.enc

Bob decrypt the secret file with the command using the same password `22fb667f3bc1a2153e3cef75df0ce757a1c86051c07ace6b0c30dc87f3358511`:

openssl aes-256-cbc -d -salt -pbkdf2 -in input.txt.enc -out message.txt

Note for cryptographers this is just a basic proof of concept, i know that the comunication channel can be compromised, 
there are mitm attacks, there is no authentication or integrity of the data etc...

## rehashaddress

A NON standard, deterministic private key generator from a password or passphrase.

what is the objective of this tool? just provide a easy way to generate deterministics privatekeys from a selected password or passphrase and number of rehashes

Advice: USE A SECURE PASSWORD

Example of use

Generate 2 privatekeys and his address after 100 thausand of rehahes

```./rehashaddress -p "}78~Et=jPQP5}MVVj2fc0X38{~I}?c" -n 2 -m 100000```

Output:

```
[I] Password: }78~Et=jPQP5}MVVj2fc0X38{~I}?c
[I] n: 2
[I] m: 100000
Privatekey: ca12010ce2daaf02611d440acd42e8bc791881375c58197cf56995059b28e797
Compress publickey: 035f149fb58e6eb5a7bcc812c1f72e5c9a3ee7ea151991a31a4d3e98e5ace25568
Compress address: 16Ln3w1JLD8s7rNni37A7SiVmVPHXEHFWF
Uncompress publickey: 045f149fb58e6eb5a7bcc812c1f72e5c9a3ee7ea151991a31a4d3e98e5ace2556850fc0b339809eda8cc9f74ee698ed018049b0cfbefe72e66dbc256622f1662d7
Uncompress address: 1NKUnTCtN3Pbm3wEVsFZFuotKkjPPi4g3B
Privatekey: 1037ea7cc723e34f3d81d9e01b5b1df081d47312a3d549b67fd635424446c1b0
Compress publickey: 026813442784ee62c0d69dcf244f91518e85f4a796a1b967758aef1b7d88abd23b
Compress address: 1JWH4qYemWFJAULUtcx1QiboDAD64Bb718
Uncompress publickey: 046813442784ee62c0d69dcf244f91518e85f4a796a1b967758aef1b7d88abd23bd7e12a189fa7d6a80154cbf29999b74bece7bfcca8a70e3df92d8ece238e8700
Uncompress address: 1Ho9VcvHcdu5Xrkv3pcME5zaPvyje1AWnM
```

Please check the comments in the source code `rehashaddress.c`


## calculatefromkey

A easy way to check the address and publickeys from a privatekey 

what is the objective of this tool? just to check a privatekey and his address and publickey

Example of use

```./calculatefromkey ca12010ce2daaf02611d440acd42e8bc791881375c58197cf56995059b28e797```

Output:

```
privatekey: ca12010ce2daaf02611d440acd42e8bc791881375c58197cf56995059b28e797
publickey compressed: 035f149fb58e6eb5a7bcc812c1f72e5c9a3ee7ea151991a31a4d3e98e5ace25568
public address compressed 16Ln3w1JLD8s7rNni37A7SiVmVPHXEHFWF
publickey uncompressed: 045f149fb58e6eb5a7bcc812c1f72e5c9a3ee7ea151991a31a4d3e98e5ace2556850fc0b339809eda8cc9f74ee698ed018049b0cfbefe72e66dbc256622f1662d7
public address uncompressed 1NKUnTCtN3Pbm3wEVsFZFuotKkjPPi4g3B
```

## calculatefrompublickey

A easy way to check the address from a publickey

What is the objetive of this tool? just check wha are the address from a publickey.

Example of use

```./calculatefromkey ca12010ce2daaf02611d440acd42e8bc791881375c58197cf56995059b28e797```

Output:

```
address 16Ln3w1JLD8s7rNni37A7SiVmVPHXEHFWF
```

## keydivision

This is just a proof of concept program just to show how we can divide publickeys.

The result from exact divisions is the same like any decimal number but if the division is not exact the result will be in an unknow place in the curve

Example of use: Divide a publickey bewteen 4 three times in a row:


```./keydivision -p 03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070 -n 3 -d 4```

Output:

```
03f694cbaf2b966c1cc5f7f829d3a907819bc70ebcc1b229d9e81bda2712998b10
02e80fea14441fb33a7d8adab9475d7fab2019effb5156a792f1a11778e3c0df5d
033ab6bde10cd3ac0cd06883fa66f0b0e3eb1309c0534b812286e2a30ca540db99
```

explanation:
the target publickey `03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070` have privatekey `0x1000000000000000000000000000000`

each line of the output are the result of divide the publickey by 4 lets to check this example with keymath

## keymath

Keymath is basically an arithmetic calculator por publickeys with only four operations:

- addition
- subtration
- multiplication by an scalar number
- division by an scalar number

previous example:

```./keymath 03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070 / 4```

output:
```Result: 03f694cbaf2b966c1cc5f7f829d3a907819bc70ebcc1b229d9e81bda2712998b10```


this is the first line of the keydivision example, their privatekey is `0x1000000000000000000000000000000` bewteen 4 equals to `0x400000000000000000000000000000`


```./keymath 03f694cbaf2b966c1cc5f7f829d3a907819bc70ebcc1b229d9e81bda2712998b10 / 4```

output:
```Result: 02e80fea14441fb33a7d8adab9475d7fab2019effb5156a792f1a11778e3c0df5d```

from here you can do your calculations by your self

### multiplication by an scalar number

The multiplication and the division only can be done with a number you can't multiply or divide two publickeys

```./keymath 033ab6bde10cd3ac0cd06883fa66f0b0e3eb1309c0534b812286e2a30ca540db99 x 64```


```Result: 03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070```

## modmath

this is an arithmetic calculator but all operations are modulo N, this is Modulo `0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141`

Did you remember that i write before: "not exact the result will be in an unknow place in the curve" I lie, we can know more or less where those result are but even with this information we can't find values when we don't know the PrivateKey value.

```./modmath 1 / 2```

Output:

```Result: 7fffffffffffffffffffffffffffffff5d576e7357a4501ddfe92f46681b20a1```

```./modmath 3 / 2```

Output:

```Result: 7fffffffffffffffffffffffffffffff5d576e7357a4501ddfe92f46681b20a2```

if you see those privatekeys are sequentially, Lest to divide the publickeys of `1` and `3` by `2`

```./keymath 0279be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798 / 2```

output:
```Result: 0200000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63```


```./keymath 02f9308a019258c31049344f85f89d5229b531c845836f99b08601f113bce036f9 / 2```

output:
```Result: 02c62c910e502cb615a27c58512b6cc2c94f5742f76cb3d12ec993400a3695d413```

Know you can comprobate that the publickeys of `7fffffffffffffffffffffffffffffff5d576e7357a4501ddfe92f46681b20a1` and `7fffffffffffffffffffffffffffffff5d576e7357a4501ddfe92f46681b20a2` are

`0200000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63`
`02c62c910e502cb615a27c58512b6cc2c94f5742f76cb3d12ec993400a3695d413`

can you calcualte what is the publickey of `7fffffffffffffffffffffffffffffff5d576e7357a4501ddfe92f46681b20a0` with keymath?

```./keymath 0200000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63 - 1```

output:
```Result: 0300000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63```

## addr2rmd

This tool decode legacy address to rmd160 hashes

Example of use:

```./addr2rmd -i examples/unsolvedpuzzles.txt  -o examples/unsolvedpuzzles.rmd```

`-i` input file `-o` output file, if the -o option is omited the


## verifymsg

This tool help to verify te signature for a bitcoin message.

Example of use:
```
./verifymsg -m 1E9YwDtYf9R29ekNAfbV7MvB4LNv7v3fGa -a 1NChfewU45oy7Dgn51HwkBFSixaTnyakfj -s "HCsBcgB+Wcm8kOGMH8IpNeg0H4gjCrlqwDf/GlSXphZGBYxm0QkKEPhh9DTJRp2IDNUhVr0FhP9qCqo2W0recNM="

The signature match with the address and it is valid

-----BEGIN BITCOIN SIGNED MESSAGE-----
1E9YwDtYf9R29ekNAfbV7MvB4LNv7v3fGa
-----BEGIN BITCOIN SIGNATURE-----
1NChfewU45oy7Dgn51HwkBFSixaTnyakfj
HCsBcgB+Wcm8kOGMH8IpNeg0H4gjCrlqwDf/GlSXphZGBYxm0QkKEPhh9DTJRp2IDNUhVr0FhP9qCqo2W0recNM=
```

Also it have some VERBOSE mode `-v`

Example:
```
./verifymsg -m 1E9YwDtYf9R29ekNAfbV7MvB4LNv7v3fGa -a 1NChfewU45oy7Dgn51HwkBFSixaTnyakfj -s "HCsBcgB+Wcm8kOGMH8IpNeg0H4gjCrlqwDf/GlSXphZGBYxm0QkKEPhh9DTJRp2IDNUhVr0FhP9qCqo2W0recNM=" -v
Final X, Y : 2b0172007e59c9bc90e18c1fc22935e8341f88230ab96ac037ff1a5497a61646 105ecd499fa11dffe894dead6759ab732baf593b6a4da4b7a7294d5afffa02b7
Final R: 2b0172007e59c9bc90e18c1fc22935e8341f88230ab96ac037ff1a5497a61646
Final S: 058c66d1090a10f861f434c9469d880cd52156bd0584ff6a0aaa365b4ade70d3
Final Z: d6a75acdff18b0a8103f867c6cab8c12ec8ac250dfa8dcdb4f89d8e553270115
Calculated address: 1NChfewU45oy7Dgn51HwkBFSixaTnyakfj
Calculated publickey uncompressed: 044e01f16fe203dbfd8110fd636f42e69bd2fa9e0fef913f00554e4412cb1cae070296f95c6b64f3fdcb7ee9dc838f20b992077e839703b3c2c5427e90e5afd0d1
Calculated publickey compressed: 034e01f16fe203dbfd8110fd636f42e69bd2fa9e0fef913f00554e4412cb1cae07

The signature match with the address and it is valid

-----BEGIN BITCOIN SIGNED MESSAGE-----
1E9YwDtYf9R29ekNAfbV7MvB4LNv7v3fGa
-----BEGIN BITCOIN SIGNATURE-----
1NChfewU45oy7Dgn51HwkBFSixaTnyakfj
HCsBcgB+Wcm8kOGMH8IpNeg0H4gjCrlqwDf/GlSXphZGBYxm0QkKEPhh9DTJRp2IDNUhVr0FhP9qCqo2W0recNM=
-----END BITCOIN SIGNATURE-----
```