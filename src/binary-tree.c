#include <assert.h> //asert
#include <stdint.h> //uintmax_t

#include "binary-tree_c.h"

struct binary_tree_node* init_binary_tree_node(void) {
	struct binary_tree_node* node = calloc(1, sizeof(struct binary_tree_node));

	node->search = &binary_tree_search;
	node->min = &binary_tree_min;
	node->max = &binary_tree_max;
	node->root = &binary_tree_root;
	node->insert = &binary_tree_insert;
	node->delete = &binary_tree_delete;
	node->free = &binary_tree_node_free;

	return node;
}

struct binary_tree_node* binary_tree_search(struct binary_tree_node* node, uintmax_t key) {
	if(node == NULL) { return NULL; }

	while(node != NULL && key != node->key) {
		if(node->key < key){
			node = node->left;
		} else {
			node = node->right;
		}
	}

	return node;
}

struct binary_tree_node* binary_tree_min(struct binary_tree_node* node) {
	if(node == NULL) { return NULL; }

	while(node->left != NULL) {
		node = node->left;
	}

	return node;
}

struct binary_tree_node* binary_tree_max(struct binary_tree_node* node) {
	if(node == NULL) { return NULL; }

	while(node->right != NULL) {
		node = node->right;
	}

	return node;
}

struct binary_tree_node* binary_tree_root(struct binary_tree_node* node) {
	if(node == NULL) { return NULL; }

	while(node->parent != NULL) {
		node = node->parent;
	}

	return node;
}

void binary_tree_node_free(struct binary_tree_node* node) {
	if(node == NULL) {
		return;
	}

	if(node->free_payload != NULL) {
		node->free_payload(node->data.payload);
	}

	free(node);
}

void binary_tree_free(struct binary_tree_node* node) {
	if(node == NULL) {
		return;
	}

	binary_tree_free(node->left);
	binary_tree_free(node->right);

	binary_tree_node_free(node);
}

void binary_tree_insert(struct binary_tree_node* T, struct binary_tree_node* z) {
	if(T == NULL || z == NULL) { return; }

	struct binary_tree_node* y = NULL;
	struct binary_tree_node* x = T->root(T);

	while(x != NULL) {
		y = x;
		if(z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;
	if(y == NULL) {
		T->parent = z;
	} else if(z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
}

static void transplant(struct binary_tree_node* u, struct binary_tree_node* v) {
	assert(u != NULL);
	if(u->parent == NULL) {  // u is the root
		u->parent = v;
	} else if(u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	if(v != NULL) {
		v->parent = u->parent;
	}
}

struct binary_tree_node* binary_tree_delete(struct binary_tree_node* z) {
	if(z->left == NULL) {
		transplant(z, z->right);

	} else if(z->right == NULL) {
		transplant(z, z->left);

	} else {
		struct binary_tree_node* y = binary_tree_min(z->right);
		if(y->parent != z) {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}

	return z;
}
