/*
 * cdsl_hash_test.c
 *
 *  Created on: 2015. 8. 29.
 *      Author: innocentevil
 */

#include "cdsl_hash_test.h"
#include "cdsl_hash.h"
#include "cdsl_nrbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef HASH_TEST_FILE
#define HASH_TEST_FILE			"hash_inputsample.txt"
#endif

static nrbtreeRoot_t root;
struct hash_result {
	nrbtreeNode_t	rbnode;
	unsigned long hash;
	char input[20];
};

extern BOOL cdsl_hashDoTest(void){
	FILE* fp = fopen(HASH_TEST_FILE,"r");
	cdsl_nrbtreeRootInit(&root);
	struct hash_result* result;
	int collisionCnt = 0;
	while(!feof(fp)){
		result =  (struct hash_result*) malloc(sizeof(struct hash_result));
		if(fscanf(fp,"%s\n",result->input) < 0)
			exit(-1);
		result->hash = sbdm_hash((unsigned char*)result->input);
		cdsl_nrbtreeNodeInit(&result->rbnode,result->hash);
		cdsl_nrbtreeInsert(&root,&result->rbnode);
	}



	return FALSE;
}
