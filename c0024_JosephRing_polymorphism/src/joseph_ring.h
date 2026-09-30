#ifndef JOSEPH_VAR
#define JOSEPH_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/single_circular_linkedlist.h"

int *joseph_ring_implement_with_array(int *, int, int, int, int *);
NODE **joseph_ring_implement_with_single_circular_linkedlist(SCLinkedlist *,
                                                             int, int, int,
                                                             NODE **);

#endif
