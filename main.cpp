/*
 * main.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: xuan
 */


#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	BTree bt;
	int arr[] = {18, 31, 21, 10, 15, 48, 45, 50, 52, 23, 30, 20};

	for (unsigned int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bt.insert(arr[i]);
	}

	bt.level_display();

	return 0;
}

