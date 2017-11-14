/*
 * BPlusTree.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: xuan
 */

#include "BPlusTree.h"
#include <stdio.h>
#include <stdlib.h>

btree_node* BPlusTree::btree_node_new() {
	btree_node *node = (btree_node*)malloc(sizeof(btree_node));
	if (NULL == node) {
		printf("btree_node_new error: malloc fail\n");
		return NULL;
	}

	for (int i = 0; i < 2 * M - 1; i++) {
		node->key[i] = 0;
	}

	for (int i = 0; i < 2 * M; i++) {
		node->p[i] = NULL;
	}

	node->num = 0;
	node->isLeaf = true;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

btree_node* BPlusTree::btree_create() {
	btree_node *root = btree_node_new();
	if (NULL == root) {
		printf("btree_node_new: NULL\n");
		return NULL;
	}

	root->next = root;
	root->prev = root;

	return root;
}

int BPlusTree::btree_split_child(btree_node *parent, int pos, btree_node *child) {
	btree_node *new_child = btree_node_new();
	if (NULL == new_child) {
		// printf("btree_split_child: has no more memory\n");
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

	if (true == child->isLeaf) {
		new_child->next = child->next;
		child->next->prev = new_child;
		new_child->prev = child;
		child->next = new_child;
	}

	return 0;
}

void BPlusTree::btree_insert_nonfull(btree_node *node, int target) {
	if (true == node->isLeaf) {
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
		while (pos > 0 && target < node->key[pos - 1]) {
			pos--;

			if (2 * M - 1 == node->p[pos]->num) {
				btree_split_child(node, pos, node->p[pos]);
				if (target > node->key[pos]) {
					pos++;
				}
			}
		}

		btree_insert_nonfull(node->p[pos], target);
	}
}

btree_node* BPlusTree::btree_insert(btree_node *root, int target) {
	if (NULL == root) {
		return NULL;
	}

	if (2 * M - 1 == root->num) {
		btree_node *node = btree_node_new();
		if (NULL == node) {
			return root;
		}

		node->isLeaf = false;
		node->p[0] = root;
		btree_split_child(node, 0, root);
		btree_insert_nonfull(node, target);
		return node;

	} else {
		btree_insert_nonfull(root, target);
		return root;
	}
}

void BPlusTree::btree_merge_child(btree_node *root, int pos, btree_node *left, btree_node *right) {
	if (true == left->isLeaf) {
		left->num = 2 * M - 2;
	}
}
