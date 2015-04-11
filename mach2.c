#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define LOGFUNC() printf("%s(File %s Line %d):", __func__, __FILE__, __LINE__)
#else
#define LOGFUNC()
#endif

typedef struct mach2 {
  int state; /* state */
} mach2_t;

mach2_t* mach2_create(void)
{
  mach2_t *objp;

  LOGFUNC();

  objp = (mach2_t *)malloc(sizeof(mach2_t));
  objp->state = 0;

  return objp;
}

void mach2_destroy(mach2_t *objp)
{
  LOGFUNC();

  free(objp);
}

void mach2_in(mach2_t *objp, int in)
{
  int oldstate;

  LOGFUNC();

  switch (objp->state) {
    case 0:
      objp->state = 1;
      break;
    case 1:
      if(in == 0) { objp->state = 2; } else { objp->state = 4; }
      break;
    case 2:
      if(in == 0) { objp->state = 3; } else { objp->state = 1; }
      break;
    case 3:
      if(in == 0) { objp->state = 4; } else { objp->state = 2; }
      break;
    case 4:
      if(in == 0) { objp->state = 1; } else { objp->state = 3; }
      break;
    default:
      perror("mach2_in: illigal state");
  }
  printf("mach2(%d)", objp->state);
}

#ifdef DEBUG
int main()
{
  mach2_t *obj1p;
  int i, ret;

  LOGFUNC();

  obj1p = mach2_create();
  if (!obj1p) {
    perror("create error");
  }

  for (i = 0; i < 10; i++) { /* left */
    printf("%d:", i);
    mach2_in(obj1p, 0);
  }

  for (i = 0; i < 10; i++) { /* right */
    printf("%d:", i);
    mach2_in(obj1p, 1);
  }

  mach2_destroy(obj1p);
  printf("hoge");

  return 0;
}
#endif /* DEBUG */
