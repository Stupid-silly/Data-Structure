#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem;

typedef struct tree {
    struct tree *left;
    struct tree *right;
    Elem elem;
} Tree;

Tree *treeNew(Elem elem, Tree *left, Tree *right)
{
    Tree *tree = malloc(sizeof(Tree));
    tree->elem = elem;
    tree->left = left;
    tree->right = right;
    return tree;
}

//    a
//  b   c
// d e f g
Tree *treeExample0()
{
    Tree *d = treeNew('d', NULL, NULL);
    Tree *e = treeNew('e', NULL, NULL);
    Tree *f = treeNew('f', NULL, NULL);
    Tree *g = treeNew('g', NULL, NULL);
    Tree *b = treeNew('b', d, e);
    Tree *c = treeNew('c', f, g);
    Tree *a = treeNew('a', b, c);
    return a;
}

//    a
//  b   c
// d e   g
Tree *treeExample1()
{
    Tree *d = treeNew('d', NULL, NULL);
    Tree *e = treeNew('e', NULL, NULL);
    Tree *g = treeNew('g', NULL, NULL);
    Tree *b = treeNew('b', d, e);
    Tree *f = NULL;
    Tree *c = treeNew('c', f, g);
    Tree *a = treeNew('a', b, c);
    return a;
}

void treePreOrderVisit(Tree *tree)
{
    if (tree != NULL) {
        printf("%c ", tree->elem);
        treePreOrderVisit(tree->left);
        treePreOrderVisit(tree->right);
    }
}

Tree *treeCopy(Tree *tree)
{
	Tree *left;
	Tree *right ;
	if(tree!=NULL)
	{
		left=treeCopy(tree->left);
		right=treeCopy(tree->right);
		return treeNew(tree->elem, left, right);
	}
	else return NULL;
}

void treeCopyTest()
{
    Tree *tree = treeExample0();
    Tree *mirror = treeCopy(tree);

    treePreOrderVisit(tree);
    printf("\n");

    treePreOrderVisit(mirror);
    printf("\n");
}

int main()
{
    treeCopyTest();
    return 0;
}