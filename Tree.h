/*
 * Tree.h
 *
 *  Created on: Nov 12, 2017
 *      Author: xuan
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>

#define M 5

typedef struct btree_node {
	int key[2 * M - 1];
	struct btree_node *p[2 * M];
	int num;
	bool isLeaf;
	struct btree_node *prev; // for B+tree
	struct btree_node *next; // for B+tree
} btree_node;

typedef struct storage_node {
	btree_node bnode;
	int index[M];
} storage_node;

typedef struct storage_struct {
	storage_node *snode;
	int len;
} storage_struct;

class Tree {
protected:
	btree_node *root;
	// FILE *pfile;
	int btree_node_num;

public:
	Tree() {
		btree_node_num = 0;
	};

	virtual ~Tree() {
		btree_node_num = 0;
		delete root;
	};

	void insert(int target) {
		root = btree_insert(root, target);
	};

	void level_display() {
		btree_level_display(root);
	};

	void del(int target) {
		root = btree_delete(root, target);
	};

	int getNodeNum() {
		return btree_node_num;
	};

protected:

	/**
	 * create a btree root
	 * return the pointer of btree root
	 */
	virtual btree_node *btree_create() = 0;

	/**
	 * allocate a new btree node
	 * return the pointer of new node
	 */
	virtual btree_node *btree_node_new() = 0;

	/**
	 * insert to tree
	 * @param root: tree root
	 * @param target: to insert
	 * @return: new root of tree
	 */
	virtual btree_node* btree_insert(btree_node *root, int target) = 0;

	/**
	 * delete value from btree
	 * @param root: btree root
	 * @param target:
	 * @return:
	 */
	virtual btree_node* btree_delete(btree_node *root, int target) = 0;

	/**
	 * level print the tree
	 * @param root
	 */
	virtual void btree_level_display(btree_node *root) = 0;

	/**
	 * save the tree
	 * @param root
	 */
	virtual void save(btree_node *root) = 0;

	/**
	 * split child if num of key in child exceed 2 * M - 1
	 *
	 * @param parent: parent of child
	 * @param pos: p[pos] points to child
	 * @param child: the node to be splited
	 *
	 * @return : success 0, fail -1
	 */
	virtual int btree_split_child(btree_node *parent, int pos,
			btree_node *child) = 0;

	/**
	 * insert a value into btree
	 * @param node:
	 * @param target: value to insert
	 */
	virtual void btree_insert_nonfull(btree_node *node, int target) = 0;

	/**
	 * merge y, z and root->key[pos] to left
	 * this happens while y and z both have M-1 keys
	 * @param root: parent root
	 * @param pos: postion of y
	 * @param y: left node to merge
	 * @param z: right node to merge
	 */
	virtual void btree_merge_child(btree_node *root, int pos, btree_node *left,
			btree_node *right);

	/**
	 * delete value from btree
	 * root has at least M keys
	 * @param root: btree root
	 * @param target: target to delete
	 */
	virtual void btree_delete_nonone(btree_node *root, int target) = 0;

	/**
	 * find leftmost value
	 * @param root: root of tree
	 * @return: the leftmost value
	 */
	virtual int btree_search_predecessor(btree_node *root) = 0;

	/**
	 * find the rightmost value
	 * @param root: root of tree
	 * @return: the rightmost value
	 */
	virtual int btree_search_successor(btree_node *root) = 0;

	/**
	 * shift a value from z to y
	 * @param root: btree root
	 * @param pos: position of y
	 * @param y: left node
	 * @param z: right node
	 */
	virtual void btree_shift_to_left_child(btree_node *root, int pos,
			btree_node *y, btree_node *z) = 0;

	/**
	 * shift a value from y to z
	 * @param root: btree root
	 * @param pos: position of y
	 * @param y: left node
	 * @param z: right node
	 */
	virtual void btree_shift_to_right_child(btree_node *root, int pos,
			btree_node *y, btree_node *z) = 0;

};

#endif /* TREE_H_ */
