#include <stdio.h>
/*
 * This file contains a small program that will be linked with a compressed
 * project and the Bakery to create an executable that will decompress
 * the project, parse the Bakery, and install it.
 */
extern char _binary_bakery_start[];
extern char _binary_bakery_end[];
extern char _binary_bake_compressed_zip_start[];
extern char _binary_bake_compressed_zip_end[];

int main ()
{
  for (char* p = _binary_bake_compressed_zip_start; p != _binary_bake_compressed_zip_end; ++p) {
    putchar( *p);
  }
}