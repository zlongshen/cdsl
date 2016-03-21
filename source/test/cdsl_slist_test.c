/*
 * cdsl_slist_test.c
 *
 *  Created on: 2015. 5. 31.
 *      Author: innocentevil
 */



#include <stdio.h>
#include "cdsl_slist_test.h"
#include "cdsl_rbtree_test.h"


typedef struct card {
	slistNode_t	list_head;
	int card_num;
}card_t;


static card_t Cards[TEST_SIZE];
static DECLARE_COMPARE_FN(card_compare);
static void printCard(void* card);
static slistEntry_t listEntry;


BOOL cdsl_slistDoTest(void){
	int i = 0;
	cdsl_slistEntryInit(&listEntry);

	for(;i < TEST_SIZE;i++){
		Cards[i].card_num = i;
		cdsl_slistNodeInit(&Cards[i].list_head);
		cdsl_slistEnqueuePriority(&listEntry,(slistNode_t*) &Cards[i],card_compare);
	}
	card_t* card = NULL;
	int last_num = TEST_SIZE;
	for(i = 0;i < TEST_SIZE;i++)
	{
		card = (card_t*) cdsl_slistDequeue(&listEntry);
		if(last_num < card->card_num)
			return FALSE;
		last_num = card->card_num;
	}
	return TRUE;
}


static DECLARE_COMPARE_FN(card_compare){
	if(!a)
		return b;
	if(!b)
		return a;
	return ((card_t*) b)->card_num > ((card_t*) a)->card_num? b : a;
}

static void printCard(void* card){
	if(!card)
		return;
	printf("Card : %d\n",((card_t*)card)->card_num);
}

