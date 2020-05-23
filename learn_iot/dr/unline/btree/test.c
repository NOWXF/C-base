#include "btree.h"

int main()
{
	btree_pnode t;
	t=create_btree();

	printf("先序遍历：");
	pre_btree(t);
	printf("\n");
	printf("中序遍历：");
	mid_btree(t);
	printf("\n");
	printf("后序遍历：");
	aft_btree(t);
	printf("\n");
	printf("层遍历：");
	level_btree(t);
	printf("\n");
	return 0;
}
