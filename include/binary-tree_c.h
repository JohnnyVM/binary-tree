/**
 * \brief Binary tree abstract type
 */
#include <stdlib.h>
//#include <stdbool.h>//bool

#if !defined(BINARY_TREE_TYPE)
#include <stdint.h> //uintmax_t
#define BINARY_TREE_TYPE uintmax_t
#endif

struct binary_tree_payload {
	void* payload;
	size_t size;
};

/** Necesary type for implement tree operations */
struct binary_tree_node {
	BINARY_TREE_TYPE key;
	struct binary_tree_node* parent;
	struct binary_tree_node* left;
	struct binary_tree_node* right;
	struct binary_tree_payload data;

	struct binary_tree_node* (*search)(struct binary_tree_node* node, BINARY_TREE_TYPE key);
	struct binary_tree_node* (*min)(struct binary_tree_node* node);
	struct binary_tree_node* (*max)(struct binary_tree_node* node);
	struct binary_tree_node* (*root)(struct binary_tree_node* node);

	void (*insert)(struct binary_tree_node* tree, struct binary_tree_node* node);
	struct binary_tree_node* (*delete)(struct binary_tree_node* node);

	void (*free)(struct binary_tree_node* node);
	void (*free_payload)(void* payload); /**< if not null called at free */
};

/** return a prepared struct with the pointers correctly initialized and key == 0*/
struct binary_tree_node* init_binary_tree_node(void);

struct binary_tree_node* binary_tree_search(struct binary_tree_node* node, BINARY_TREE_TYPE key);
struct binary_tree_node* binary_tree_min(struct binary_tree_node* node);
struct binary_tree_node* binary_tree_max(struct binary_tree_node* node);
struct binary_tree_node* binary_tree_root(struct binary_tree_node* node);
void binary_tree_insert(struct binary_tree_node* tree, struct binary_tree_node* node);
struct binary_tree_node* binary_tree_delete(struct binary_tree_node* node);
void binary_tree_node_free(struct binary_tree_node* node);
void binary_tree_free(struct binary_tree_node* node);

