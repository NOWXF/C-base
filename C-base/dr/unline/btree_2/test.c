#include "btree.h"

int main()
{
	btree_pnode t;
	t=create_btree();

	travel("递归先序遍历：",pre_btree,t);
	travel("非递归先序遍历：",unpre_btree,t);
	travel("递归中序遍历：",mid_btree,t);
	travel("非递归中序遍历：",unmid_btree,t);
	travel("递归后序遍历：",aft_btree,t);
	travel("非递归后序遍历：",unaft_btree,t);
	travel("层遍历：",level_btree,t);

	return 0;
}
