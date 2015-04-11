#include <stdio.h>
#include <stdlib.h>

#include "machine.h"

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

typedef struct myobj {
	void *handle; /* handle for mach* */
	int  type;    /* machine type */
} myobj_t;

/*
 * type を myobj_t メンバにセットする
 *
 * IN myobjp
 * IN type
 * 
 * 戻り値 0 or -1
 */
int gen_set_type(myobj_t *myobjp, int type)
 {
  int ret = 0;

  switch (type) {
	case 1: case 2:
      myobjp->type = type;
      break;
    default:
      printf("type = %d\n", type);
      perror("invalid type");
    ret = -1;
  }
  return ret;
}

/*
 * type に従って、オブジェクトを生成する
 *
 * IN  myobj_t *myobjp
 */
int gen_create(myobj_t *myobjp)
{
  void *handle;
  int ret = 0;

  switch(myobjp->type) {
	case 1:
	  handle = (void *)mach1_create();
	  break;
	case 2:
	  handle = (void *)mach2_create();
	  break;
	default:
	  perror("gen_create: invalid machine type");
      handle = NULL;
      ret = -1;
  }

  myobjp->handle = handle;

  return ret;
}

/*
 * type に従って、オブジェクトを破壊する
 *
 * IN  myobj_t *myobjp
 */
int gen_destroy(myobj_t *myobjp)
{
  int ret = 0;

  switch(myobjp->type) {
	case 1:
	  mach1_destroy((mach1_t *)myobjp->handle);
	  break;
	case 2:
	  mach2_destroy((mach2_t *)myobjp->handle);
	  break;
	default:
	  perror("gen_destroy: invalid machine type");
      myobjp->handle = NULL;
  }
  return ret;
}

/*
 * type に従って、オブジェクトにインプットする
 *
 * IN  int    type
 * IN  void * handle
 * IN  int    in
 */
int gen_in(myobj_t *myobjp, int in)
{
  int ret = 0;

  switch(myobjp->type) {
	case 1:
	  mach1_in((mach1_t *)myobjp->handle, in);
	  break;
	case 2:
	  mach2_in((mach2_t *)myobjp->handle, in);
	  break;
	default:
	  perror("gen_in: invalid machine type");
      ret = -1;
  }
  return ret;
}

/*
 * type 1, type 2 のオブジェクトを作成し、
 * 10回0をインプットしたのち、
 * オブジェクトを破壊する
 */
int main()
{
  myobj_t myobj[2];

  int i, j;

  LOGFUNC();

  /* myobj[0] is mach2, myobj[1] is mach1 */
  gen_set_type(&myobj[0], 2);
  gen_set_type(&myobj[1], 1);

  for (j = 0; j < 2; j++) {
	gen_create(&myobj[j]);
    if (!myobj[j].handle) {
      perror("create error for machine");
	}
  }

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);
    for (j = 0; j < 2; j++) {
      gen_in(&myobj[j], 0);
	}
    printf("\n");
  }

  for (j = 0; j < 2; j++) {
	gen_destroy(&myobj[j]);
  }

  return 0;
}
