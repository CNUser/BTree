/*
 * BTree.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: xuan
 */

#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

btree_node* BTree::btree_node_new() {
	btree_node *node = (btree_node *)malloc(sizeof(btree_node));
	if (NULL == node) {
		return  NULL;
	}

	for (int i = 0; i < 2 * M - 1; i++) {
		node->key[i] = 0;
	}

	for (int i = 0; i < 2 * M; i++) {
		node->p[i] = NULL;
	}

	node->num = 0;
	node->isLeaf = true;

	return node;
}

btree_node* BTree::btree_create() {
	btree_node *root = btree_node_new();
	if (NULL == root) {
		return NULL;
	}

	return root;
}

int BTree::btree_split_child(btree_node *parent, int pos, btree_node *child) {
	btree_node *new_child = btree_node_new();
	if (NULL == new_child) {
		return -1;
	}

	new_child->isLeaf = child->isLeaf;
	new_child->num = M - 1;

	for (int i = 0; i < M - 1; i++) {
		new_child->key[i] = child->key[i + M];
	}

	if (false == child->isLeaf) {
		for (int i = 0; i < M; i++) {
			new_child->p[i] = child->p[i + M];
		}
	}

	child->num = M - 1;

	for (int i = parent->num; i > pos; i--) {
		parent->p[i + 1] = parent->p[i];
	}

	parent->p[pos + 1] = new_child;

	for (int i = parent->num - 1; i >= pos; i--) {
		parent->key[i + 1] = parent->key[i];
	}

	parent->key[pos] = child->key[M - 1];

	parent->num += 1;
	return 0;
}

// node->num < 2 * M - 1
void BTree::btree_insert_nonfull(btree_node *node, int target) {
	if (true == node->isLeaf) {
		// find in leaf node
		int pos = node->num;
		while (pos >= 1 && target < node->key[pos - 1]) {
			node->key[pos] = node->key[pos - 1];
			pos--;
		}

		node->key[pos] = target;
		node->num += 1;
		btree_node_num += 1;

	} else {
		int pos = node->num;
		while (pos > 0 && target < node->key[pos]) {
			pos--;
		}

		if (2 * M - 1 == node->p[pos]->num) {
			btree_split_child(node, pos, node->p[pos]);
			if (target > node->key[pos]) {
				pos++;
			}
		}

		btree_insert_nonfull(node->p[pos], target);
	}
}

btree_node* BTree::btree_insert(btree_node *root, int target) {
	if (NULL == root) {
		return NULL;
	}

	// special process for root, if root has full nodes，increase tree height
	if (2 * M - 1 == root->num) {
		btree_node *node = btree_node_new();
		if (NULL == node) {
			printf("insert fail: btree_node_new");
			return root;
		}

		node->isLeaf = false;
		node->p[0] = root;
		btree_split_child(node, 0, root);
		btree_insert_nonfull(root, target);
		return node;

	} else {
		btree_insert_nonfull(root, target);
		return root;
	}
}

// merge y, root->key[pos], z into y, free z, y and z has M - 1 nodes
void BTree::btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z) {
	// put nodes of z into the lower half of y
	y->num = 2 * M -1;
	y->key[M - 1] = root->key[pos];

	for (int i = M; i < 2 * M - 1; i++) {
		y->key[i] = z->key[i - M];
	}

	if (false == z->isLeaf) {
		for (int i = M; i < 2 * M; i++) {
			y->p[i] = z->p[i - M];
		}
	}

	// put root->key[pos] into y，update key and pointer of root
	for (int i = pos + 1; i < root->num; i++) {
		root->key[i - 1] = root->key[i];
		root->p[i] = root->p[i + 1];
	}

	root->num -= 1;
	free(z);
}

btree_node* BTree::btree_delete(btree_node *root, int target) {
	// while root only has two child, and the two child only has (M-1) keys,
	// merger root and the two child
	// reduce height only in this scenario
	if (1 == root->num) {
		btree_node *y = root->p[0];
		btree_node *z = root->p[1];
		if (NULL != y && NULL != z &&
				M - 1 == y->num && M - 1 == z->num) {
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;

		} else {
			btree_delete_nonone(root, target);
			return root;

		}

	} else {
		btree_delete_nonone(root, target);
		return root;
	}
}
