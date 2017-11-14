/*
 * BPlusTree.h
 *
 *  Created on: Nov 14, 2017
 *      Author: xuan
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_



#include "Tree.h"


class BPlusTree : public Tree {
public:
	BPlusTree();
	~BPlusTree();
    virtual btree_node* btree_create();
    virtual btree_node* btree_node_new();
    virtual btree_node* btree_insert(btree_node *root, int target);
    virtual btree_node* btree_delete(btree_node *root, int target);
    virtual void btree_level_display(btree_node *root);

protected:
    virtual int btree_split_child(btree_node *parent, int pos, btree_node *child);
    virtual void btree_insert_nonfull(btree_node *node, int target);
    virtual void btree_merge_child(btree_node *root, int pos, btree_node *left,
    			btree_node *right);
    virtual void btree_delete_nonone(btree_node *root, int target);
    virtual int btree_search_predecessor(btree_node *root);
    virtual int btree_search_successor(btree_node *root);
    virtual void btree_shift_to_left_child(btree_node *root, int pos,
    			btree_node *y, btree_node *z);
    virtual void btree_shift_to_right_child(btree_node *root, int pos,
    			btree_node *y, btree_node *z);

};





#endif /* BPLUSTREE_H_ */
