
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "data"

typedef struct treenode {
  int data;
  struct treenode *left, *right;
} TREENODE;

TREENODE *makenode(int n);
void decorate(TREENODE *tree, TREENODE *leaf);
void inorder(TREENODE *tree, int level);
void preorder(TREENODE *tree, int level);
void postorder(TREENODE *tree, int level);
int sum(TREENODE *tree);
int maxdepth(TREENODE *tree);
int find(int key, TREENODE *tree);
void freetree(TREENODE *tree);

int main(int argc, char *argv[])
{
  TREENODE *root;
  TREENODE *ptr;
  int x, key;
  FILE *fd;

  fd = fopen(FILENAME,"r");
  if(fd == NULL){
    fprintf(stderr,"unable to open %s\n", FILENAME);
    exit(0);
  }
// reading the numbers, one at time

  root = 0;
  while(fscanf(fd,"%d", &x) == 1){
    if(root == NULL){                // done once, first time through
      root = makenode(x);
    } else {
      ptr = makenode(x);             // create a node to hang on the tree
      decorate(root,ptr);            // hangs the node in the right place
    }
  }
  fclose(fd);
  for(;;){
    printf("? ");
    if(scanf("%d", &key) != 1)
      break;
    if(find(key, root))
      printf("found\n");
    else
      printf("not found\n");
  }
  freetree(root);
}
TREENODE *makenode(int n)
{
  TREENODE *p;

  p = malloc(sizeof(TREENODE));
  p->data = n;
  p->left = p->right = 0;  // both pointers are made NULL
  return p;
}

// hang the leaf on the tree, in the right place for a BST

void decorate(TREENODE *tree, TREENODE *leaf)
{
  for(;;){
    if(leaf->data < tree->data){  // The leaf goes somewhere to the left.
      if(tree->left == NULL){     // If there is no tree to the left then
        tree->left = leaf;        // the new node IS the tree to the left.
        return;
      }
      tree = tree->left;          // the leaf goes somewhere deeper
    } else {
      if(tree->right == NULL){    // identical code, but on the right
        tree->right = leaf;
        return;
      }
      tree = tree->right;
    }
  }
}
int find(int key, TREENODE *tree)
{
  if(tree == NULL)
    return 0;
  for(;;){
    if(key == tree->data)
      return 1;
    if(key < tree->data){      // key must be on left
      if(tree->left == NULL)
        return 0;
      tree = tree->left;
    } else {                   // key must be on the right
      if(tree->right == NULL)
        return 0;
      tree = tree->right;
    }
  }
}
void inorder(TREENODE *tree, int level)
{
  if(tree != NULL){
    inorder(tree->left, level+1);
    printf("%2d%6d\n", level, tree->data);
    inorder(tree->right, level+1);
  }
}
void preorder(TREENODE *tree, int level)
{
  if(tree != NULL){
    printf("%d\n", tree->data);
    preorder(tree->left, level+1);
    preorder(tree->right, level+1);
  }
}
void postorder(TREENODE *tree, int level)
{
  if(tree != NULL){
    postorder(tree->left, level+1);
    postorder(tree->right, level+1);
    printf("%2d%6d\n", level, tree->data);
  }
}
int sum(TREENODE *tree)
{
  if(tree == NULL)
    return 0;
  return tree->data + sum(tree->left) + sum(tree->right);
}
int maxdepth(TREENODE *tree)
{
  int leftdepth, rightdepth;

  if(tree == NULL)
    return 0;
  leftdepth  = maxdepth(tree->left);
  rightdepth = maxdepth(tree->right);
  return (leftdepth > rightdepth) ? leftdepth + 1 : rightdepth + 1;
}
void freetree(TREENODE *tree)
{
  if(tree != NULL){
    freetree(tree->left);
    freetree(tree->right);
    free(tree);
  }
}
