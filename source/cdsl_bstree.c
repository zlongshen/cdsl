/*
 * tch_btree.c
 *
 *  Created on: 2014. 9. 12.
 *      Author: innocentevil
 */


#include "cdsl_bstree.h"
#include "base_tree.h"
#include "cdsl.h"
#include <stddef.h>


static bstreeNode_t* move_up_rightmost_rc(bstreeNode_t* node);
static bstreeNode_t* move_up_leftmost_rc(bstreeNode_t* node);

void cdsl_bstreeRootInit(bstreeRoot_t* rootp)
{
	if(rootp == NULL)
		return;
	rootp->entry = NULL;
}


void cdsl_bstreeNodeInit(bstreeNode_t* node,trkey_t key)
{
	if(node == NULL)
		return;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
}


bstreeNode_t* cdsl_bstreeInsert(bstreeRoot_t* rootp,bstreeNode_t* item){
	if((rootp == NULL) || (item == NULL))
		return NULL;
	if(rootp->entry == NULL)
	{
		rootp->entry = item;
		return rootp->entry;
	}

	item->left = NULL;
	item->right = NULL;
	bstreeNode_t* current = rootp->entry;

	while(current)
	{
		if(current->key < item->key)
		{
			if(!current->right)
			{
				current->right = item;
				return item;
			}
			current = current->right;
		}
		else
		{
			if(!current->left)
			{
				current->left = item;
				return item;
			}
			current = current->left;
		}
	}
	return NULL;
}

bstreeNode_t* cdsl_bstreeLookup(bstreeRoot_t* rootp,trkey_t key)
{
	if(rootp == NULL)
		return NULL;
	bstreeNode_t* current = rootp->entry;
	while(current)
	{
		if(current->key < key)
			current = current->right;
		else if(current->key > key)
			current = current->left;
		else
			return current;
	}
	return NULL;
}

bstreeNode_t* cdsl_bstreeDelete(bstreeRoot_t* rootp,trkey_t key)
{
	bstreeNode_t* todelete = NULL;
	if((rootp == NULL) || (rootp->entry == NULL))
		return NULL;
	bstreeNode_t** current = &rootp->entry;
	while((*current) && ((*current)->key != key))
	{
		if((*current)->key < key)
		{
			current = &(*current)->right;
		}
		else
		{
			current = &(*current)->left;
		}
	}

	todelete = *current;
	if (todelete->left)
	{
		*current = move_up_rightmost_rc(todelete->left);
		(*current)->right = todelete->right;
	}
	else if(todelete->right)
	{
		*current = move_up_leftmost_rc(todelete->right);
		(*current)->left = todelete->left;
	}
	else
	{
		*current = NULL;
	}
	return todelete;
}

bstreeNode_t* cdsl_bstreeDeleteMin(bstreeRoot_t* rootp) {
	if(!rootp)
		return NULL;

	bstreeNode_t* lm = rootp->entry;
	bstreeNode_t** lmp = &rootp->entry;

	while(lm->left) {
		lmp = &lm->left;
		lm = lm->left;
	}
	if(lm->right) {
		*lmp = move_up_leftmost_rc(lm->right);
	} else {
		*lmp = NULL;
	}
	return lm;
}

bstreeNode_t* cdsl_bstreeDeleteMax(bstreeRoot_t* rootp) {
	if(!rootp)
		return NULL;
	bstreeNode_t* rm = rootp->entry;
	bstreeNode_t** rmp = &rootp->entry;

	while(rm->right) {
		rmp = &rm->right;
		rm = rm->right;
	}
	if(rm->left) {
		*rmp = move_up_rightmost_rc(rm->left);
	} else {
		*rmp = NULL;
	}
	return rm;
}


static bstreeNode_t* move_up_rightmost_rc(bstreeNode_t* node)
{
	if(!node)	return NULL;
	if(!node->right)	return node;

	/** recursively do this (0 is null termination)
	 *       p             b
	 *      / \    ->     / \
	 *     a   b         p   0
	 *        / \       / \
	 *       c   0     a   c
	 */
	bstreeNode_t* rightmost = move_up_rightmost_rc(node->right);
	node->right = rightmost->left;
	rightmost->left = node;
	return rightmost;
}

static bstreeNode_t* move_up_leftmost_rc(bstreeNode_t* node)
{
	if(!node) 	return NULL;
	if(!node->left) 	return node;

	/** recursively do this (0 is null termination)
	 *        p              a
	 *       / \            / \
	 *      a   b   ->     0   p
	 *     / \                / \
	 *    0   d              d   b
	 */
	bstreeNode_t* leftmost = move_up_leftmost_rc(node->left);
	node->left = leftmost->right;
	leftmost->right = node;
	return leftmost;
}

