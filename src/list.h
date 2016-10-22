#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>

typedef struct IntList IntList;

IntList* IntList_create(void);
void IntList_destroy(IntList* self);
bool IntList_add(IntList* self, int value);
bool IntList_remove(IntList* self, int value);
bool IntList_get(IntList* self, int index);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H_
