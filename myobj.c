#include <stdio.h>
#include <stdlib.h>

#include "machine.h"
#include "arraylist.h"

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
 * IN  void * objp
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
  elem_t  elema[10]; /* XXX MAGIC NUMBER XXX */
  myobj_t *p;

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

  /* elem array */
  for (i = 0; i < 10; i++) elema[i].member = NULL;
  
  list_insert(elema, (char *)&myobj[0]);
  list_insert(elema, (char *)&myobj[1]);
  
  printf("elema->member[%p %p], myobj[%p %p]\n", elema[0].member, elema[1].member,
                                                 &myobj[0], &myobj[1]);

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);

    if (i == 5) list_delete(elema, (char *)&myobj[0]);
    if (i == 7) list_insert(elema, (char *)&myobj[0]);
      
    for (j = 0; j < 10; j++) {
      if (elema[j].member) {
        gen_in((myobj_t *)elema[j].member, 0);
      }
	}
    printf("\n");
  }

  for (j = 0; j < 2; j++) {
	gen_destroy((myobj_t *)elema[j].member);
  }

  return 0;
}
