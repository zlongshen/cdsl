/*
 * tch_dlist.h
 *
 * \brief doubly linked list library (can be used as stack or queue)
 *
 *
 *  Created on: 2014. 7. 25.
 *      Author: innocentevil
 */

#ifndef CDSL_DLIST_H_
#define CDSL_DLIST_H_

#include "cdsl.h"

#if defined(__cplusplus)
extern "C" {
#endif


#ifndef DECLARE_COMPARE_FN
#define DECLARE_COMPARE_FN(fn) void* fn(void* a,void* b)
#endif

#define cdsl_dlistIsEmpty(lhead)   (((dlistEntry_t*) lhead)->head== NULL)
typedef void* (*cdsl_dlistPriorityRule)(void* a,void* b);		// should return larger or prior one between two
typedef struct cdsl_dlnode dlistNode_t;
typedef struct cdsl_dlentry dlistEntry_t;

struct cdsl_dlnode {
	dlistNode_t* prev;
	dlistNode_t* next;
};

struct cdsl_dlentry {
	dlistNode_t* tail;
	dlistNode_t* head;
};
extern void cdsl_dlistNodeInit(dlistNode_t* node);
extern void cdsl_dlistEntryInit(dlistEntry_t* lentry);
/**
 *  Queue like interface
 */
extern void cdsl_dlistEnqueuePriority(dlistEntry_t* lentry,dlistNode_t* item,cdsl_dlistPriorityRule rule);
extern void cdsl_dlistInsertAfter(dlistNode_t* ahead,dlistNode_t* item);
extern dlistNode_t* cdsl_dlistDequeue(dlistEntry_t* lentry);

/**
 *  Stack like interface
 */
extern void cdsl_dlistPutHead(dlistEntry_t* lentry,dlistNode_t* item);
extern void cdsl_dlistPutTail(dlistEntry_t* lentry,dlistNode_t* item);
extern dlistNode_t* cdsl_dlistRemoveHead(dlistEntry_t* lentry);
extern dlistNode_t* cdsl_dlistRemoveTail(dlistEntry_t* lentry);


extern BOOL cdsl_dlistRemove(dlistNode_t* item);
extern int cdsl_dlistSize(dlistEntry_t* lentry);
extern BOOL cdsl_dlistContain(dlistEntry_t* lentry,dlistNode_t* item);
extern void cdsl_dlistPrint(dlistEntry_t* lentry,cdsl_generic_printer_t prt);

#if defined(__cplusplus)
}
#endif


#endif /* TCH_LIST_H_ */
