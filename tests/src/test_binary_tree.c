#include "CppUTest/TestHarness_c.h"

#include "binary-tree_c.h"

static struct binary_tree_node* create_node(BINARY_TREE_TYPE key) {
	struct binary_tree_node* node = init_binary_tree_node();

	node->key = key;

	return node;
}

TEST_GROUP_C_SETUP(binary_tree)
{
}

TEST_GROUP_C_TEARDOWN(binary_tree)
{
}

TEST_C(binary_tree, tests)
{
	unsigned key_array[] = {0,1,2,3,4,5,6,7,8,9,10,11};
	struct binary_tree_node* tree = create_node(key_array[0]);

	for(unsigned i=1; i < sizeof key_array/sizeof(unsigned); i++) {
		struct binary_tree_node* node = create_node(key_array[i]);
		tree->insert(tree, node);
	}

	CHECK_C(0 == tree->min(tree)->key);
	CHECK_C(11 == tree->max(tree)->key);

	struct binary_tree_node* node_6 = tree->search(tree, 6);
	struct binary_tree_node* node_6_2 = tree->delete(node_6);
	CHECK_C(node_6 == node_6_2);
	CHECK_C(tree->search(tree, 6) == NULL);
	node_6->free(node_6);

	binary_tree_free(tree);
}

