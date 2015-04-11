#include <stdio.h>
#include <stdlib.h>

#include "machine.h"

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

/*
 * type に従って、オブジェクトを生成する
 *
 * IN  int    type
 * OUT void * handle
 */
void *gen_create(int type)
{
  void *handle;

  switch(type) {
	case 1:
	  handle = (void *)mach1_create();
	  break;
	case 2:
	  handle = (void *)mach2_create();
	  break;
	default:
	  perror("gen_create: invalid machine type");
      handle = NULL;
  }
  return handle;
}

/*
 * type に従って、オブジェクトを破壊する
 *
 * IN  int    type
 * IN  void * handle
 */
void *gen_destroy(int type, void *handle)
{

  switch(type) {
	case 1:
	  mach1_destroy((mach1_t *)handle);
	  break;
	case 2:
	  mach2_destroy((mach2_t *)handle);
	  break;
	default:
	  perror("gen_destroy: invalid machine type");
      handle = NULL;
  }
  return;
}

/*
 * type に従って、オブジェクトにインプットする
 *
 * IN  int    type
 * IN  void * handle
 * IN  int    in
 */
void *gen_in(int type, void *handle, int in)
{

  switch(type) {
	case 1:
	  mach1_in((mach1_t *)handle, in);
	  break;
	case 2:
	  mach2_in((mach2_t *)handle, in);
	  break;
	default:
	  perror("gen_in: invalid machine type");
      handle = NULL;
  }
  return handle;
}

/*
 * type 1, type 2 のオブジェクトを作成し、
 * 10回0をインプットしたのち、
 * オブジェクトを破壊する
 */
int main()
{
  void *handle[2];
  int i, j;

  LOGFUNC();

  for (j = 0; j < 2; j++) {
	handle[j] = gen_create(j+1);
    if (!handle[j]) {
      perror("create error for machine");
	}
  }

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);
    for (j = 0; j < 2; j++) {
      gen_in(j+1, handle[j], 0);
	}
    printf("\n");
  }

  for (j = 0; j < 2; j++) {
	gen_destroy(j+1, handle[j]);
  }

  return 0;
}
