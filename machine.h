#ifndef MACHINE_H
#define MACHINE_H

struct mach1;			/* ’è‹`‚Í mach1.c */
typedef struct mach1 mach1_t;
mach1_t* mach1_create(void);
void     mach1_destroy(mach1_t *);
void     mach1_in(mach1_t *, int);

struct mach2;			/* ’è‹`‚Í mach2.c */
typedef struct mach2 mach2_t;
mach2_t* mach2_create(void);
void     mach2_destroy(mach2_t *);
void     mach2_in(mach2_t *, int);

#endif /* MACHINE_H */