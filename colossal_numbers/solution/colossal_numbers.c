/* Author: Wiktoria Ksel
 *
 * Program description:
 *
 * The program implements some of the arithmetic operations 
 * on natural numbers encoded as trees.
 * A number is represented by a tree whose structure corresponds to binary expansion.
 * The value of the number in decimal is sum for all of the children of 
 * 2^{value of the child}.
 * 
 *
 * 
 * Supported operations are:
 * 	- input of numbers in tree form : {"1" <number>} "0"
 * 	  and putting it on a stack
 * 	- addition (+)
 * 	- multiplication (*)
 * 	- 2^number (^)
 * 	- duplication of the top stack element (:)
 * 	- output of the normalizes top stack element (.)
 *
 * All arithmetic is performed structually on trees without using 
 * built-in integer arithmetic.
 */
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* ==== Structures ==== */

/* Single digit in the number (num); 
 * Num is a list of most-significant-bit first nodes.
 */
struct node {
  bool bit;
  struct node *next;
};
typedef struct node node;

/* Tree node representing a number.
 * 
 * The first node of the tree is a "fake root", which allows for easier functions.
 * The value is stored in num. The NULL at the end corresponds to 
 * the 0 that closes the number.
 */
struct tree {
  node *num;		// Binary encoding of the subtree.
  struct tree *rson;	// First child.
  struct tree *brother;	// Next sibling.
};
typedef struct tree tree;

/* Stack node storing a pointer to a tree.
 *
 */
struct node_of_tree {
  tree *val;
  struct node_of_tree *next;
};
typedef struct node_of_tree node_of_tree;

struct stack {
  node_of_tree *top;
};
typedef struct stack stack;


/* ==== Freeing memory ==== */ 

void free_num(node *n) {
  while (n) {
    node *next = n->next;
    free(n);
    n = next;
  }
}

void free_tree(tree *t) {
  if (t == NULL)
    return;

  free_tree(t->rson);
  free_tree(t->brother);
  free_num(t->num);

  free(t);
}

void free_stack(stack *s) {
  while (s->top != NULL) {
    node_of_tree *n = s->top;
    s->top = n->next;
    free_tree(n->val); // free the tree stored on stack
    free(n);           // free stack wrapper
  }
}


/* ==== Helper functions for linked lists of nodes ==== */

// Creates disconnected node with value b.
node *create_node(bool b) {
  node *n = (node *)malloc(sizeof(node));
  n->bit = b;
  n->next = NULL;

  return n;
}

// Adds 2 numbers stored in linked lists of nodes.
node *add_num(node *l1, node *l2) {
  node *n = create_node(1);
  node *start = l1;

  if (l1 == NULL) 
    start = n;
  else {
    while (l1->next) 
      l1 = l1->next;
    l1->next = n;
  }

  while (l2 != NULL) {
    node *tmp = create_node(l2->bit);
    n->next = tmp;
    n = tmp;
    l2 = l2->next;
  }

  n->next = create_node(0);
  n->next->next = NULL;

  return start;
}

/* Compares two binary numbers represented as linked lists.
 *
 * Returns:
 * 	1 if  num1 > num2
 * 	0 if  num1 == num2
 * 	-1 if num1 < num2
 */
int compare(node *num1, node *num2) {
  while (num1 != NULL && num2 != NULL) {
    if (num1->bit > num2->bit)
      return 1;
    else if (num1->bit < num2->bit)
      return -1;

    num1 = num1->next;
    num2 = num2->next;
  }

  if (num1 == NULL && num2 == NULL)	return 0;
  if (num1 == NULL)	return -1;
  return 1;
}

node *copy_num(const node *n) {
  if (n == NULL)
    return NULL;

  node *head = create_node(n->bit);
  node *cur = head;
  n = n->next;

  while (n != NULL) {
    cur->next = create_node(n->bit);
    cur = cur->next;
    n = n->next;
  }

  return head;
}


/* ==== Helper functions for trees ==== */

// Adds son as rson to the root.
void add_son(tree *root) {
  tree *t = (tree *)malloc(sizeof(tree));
  t->rson = NULL;
  t->num = NULL;
  t->brother = root->rson;
  root->rson = t;
}

// Creates new tree from a given list of digits.
// '1' indicates descent in the recursion and any other character
// {'0', '\n', EOF} terminates it.
//
// The number (stored in num) is constructed from children
// after the subtree is built.
void create_tree(tree *root) {
  add_son(root);
  tree *cur = root->rson;

  char c;
  while ((c = (char)getchar()) == '1') 
    create_tree(cur);
  

  if (root->rson != NULL) 
    root->num = add_num(root->num, root->rson->num);
  
}

tree *copy_tree(tree *t) {
  if (t == NULL)
    return NULL;

  tree *c = (tree *)malloc(sizeof(tree));
  c->num = copy_num(t->num);
  c->rson = copy_tree(t->rson);
  c->brother = copy_tree(t->brother);

  return c;
}

/*
 * Appends a block representing a child number to the base number.
 * The block is encoded as: 1 <child_num_bits> 0.
 *
 * Used when rebuilding a number from normalized children.
 */
node *append_block(node *base, node *child_num) {
  node *start = base;
  node *cur;

  if (start == NULL) {
    start = create_node(1);
    cur = start;
  } 
  else {
    cur = start;
    while (cur->next != NULL)
      cur = cur->next;

    cur->next = create_node(1);
    cur = cur->next;
  }

  // Copy child_num.
  while (child_num != NULL) {
    cur->next = create_node(child_num->bit);
    cur = cur->next;
    child_num = child_num->next;
  }

  cur->next = create_node(0);
  return start;
}

/*
 * Rebuilds the binary number of a tree node from its children.
 * Each child gives one encoded block to the resulting number.
 */
node *rebuild_num_from_children(tree *t) {
  node *result = NULL;

  for (tree *c = t->rson; c != NULL; c = c->brother) 
    result = append_block(result, c->num);

  return result;
}

void normalize(tree *root);

/*
 * Inserts a tree node into a sorted sibling list.
 *
 * If a node with equal number already exists,
 * a carry is generated by adding a null son and normalizing.
 */
tree *insert_sorted(tree *head, tree *elem) {
  if (head == NULL) {
    elem->brother = NULL;
    return elem;
  }

  int c = compare(elem->num, head->num);

  if (c > 0) {
    elem->brother = head;
    return elem;
  }

  if (c == 0) {
    add_son(head);
    normalize(head);
    free_tree(elem);
    return head;
  }

  tree *cur = head;
  while (cur->brother != NULL) {
    c = compare(elem->num, cur->brother->num);
    if (c >= 0)
      break;
    cur = cur->brother;
  }

  if (cur->brother != NULL && c == 0) {
    add_son(cur->brother);
    normalize(cur->brother);
    free_tree(elem);
    return head;
  }

  elem->brother = cur->brother;
  cur->brother = elem;

  return head;
}

// Checks if there are two equal sons. 
// Assumes that the list in non-descending.
bool has_adjacent_duplicates(tree* root) {
    for (tree* c = root->rson; c != NULL && c->brother != NULL; c = c->brother) {
        if (compare(c->num, c->brother->num) == 0)
            return true;
    }

    return false;
}

void sort_sons_asc(tree *root) {
  if (root == NULL || root->rson == NULL)
    return;

  tree *sorted = NULL;
  tree *cur = root->rson;

  while (cur != NULL) {
    tree *next = cur->brother;
    cur->brother = NULL;
    sorted = insert_sorted(sorted, cur);
    cur = next;
  }

  root->rson = sorted;

  while (has_adjacent_duplicates(root))
	  sort_sons_asc(root);
}

/*
 * Normalizes the tree so that it represents a valid number.
 *
 * Normalization enforces these invariants:
 *   1. All children are normalized.
 *   2. Children are sorted in ascending order of their num value.
 *   3. No two children have equal numeric value.
 *
 * If two children have the same value then we add them together and normalize.
 */
void normalize(tree *root) {
  if (root == NULL)
    return;

  for (tree *c = root->rson; c != NULL; c = c->brother)
    normalize(c);

  sort_sons_asc(root);

  if (root->num != NULL) 
    free_num(root->num);

  root->num = rebuild_num_from_children(root);
}


/* ==== Stack operations ==== */

// Pushes a tree onto the stack.
void push(stack *s, tree *root) {
  node_of_tree *tmp = s->top;
  node_of_tree *nowy = (node_of_tree *)malloc(sizeof(node_of_tree));

  s->top = nowy;
  nowy->next = tmp;
  nowy->val = root;
}

// Pops the tree from the stack, prints the value and frees the memory.
void pop(stack *s) {
  if (s == NULL || s->top == NULL)
    return;

  node_of_tree *tnode = s->top;
  tree *t = tnode->val;
  s->top = tnode->next; 

  if (t == NULL || t->rson == NULL) 	// NULL is treated as 0 in these trees.
    printf("0");
  else {
    tree *child = t->rson;
    node *n = child->num;

    while (n != NULL) {
      printf("%d", n->bit);
      n = n->next;
    }

    printf("0");
  }
  printf("\n");

  free_tree(t);
  free(tnode);
}

// Duplicates top stack element.
void double_top(stack *s) {
  tree *t = s->top->val;
  tree *nowy = copy_tree(t);
  push(s, nowy);
}

// Converts top s element 'x' to '2^x'.
void power(stack *s) {
  tree *root = s->top->val;
  tree *new_root = (tree *)malloc(sizeof(tree));

  new_root->brother = NULL;
  new_root->rson = root;
  new_root->num = NULL;

  normalize(new_root);
  s->top->val = new_root;
}

// Sums top 2 stack elements. Assumes that they exist.
// Pops them from the stack and pushes their sum.
void sum(stack *s) {
  if (s == NULL || s->top == NULL || s->top->next == NULL)
    return;

  node_of_tree *n1 = s->top;
  tree *t1 = n1->val;
  node_of_tree *n2 = n1->next;
  tree *t2 = n2->val;

  s->top = n2->next;

  // New fake root.
  tree *root = (tree *)malloc(sizeof(tree));
  root->brother = NULL;
  root->num = NULL;

  // New fake child, can be interpreted as real root.
  tree *fake = (tree *)malloc(sizeof(tree));
  fake->brother = NULL;
  fake->num = NULL;
  fake->rson = NULL;

  root->rson = fake;

  tree *last = NULL;

  // Attach children of t1.
  if (t1->rson != NULL && t1->rson->rson != NULL) {
    fake->rson = t1->rson->rson;
    last = fake->rson;

    while (last->brother != NULL)
      last = last->brother;
  }

  // Attach children of t2.
  if (t2->rson != NULL && t2->rson->rson != NULL) {
    if (fake->rson == NULL)
      fake->rson = t2->rson->rson;
    else 
      last->brother = t2->rson->rson;
  }

  // Detach children so old trees can be freed.
  if (t1->rson != NULL)
    t1->rson->rson = NULL;
  if (t2->rson != NULL)
    t2->rson->rson = NULL;

  normalize(root);

  free_tree(t1);
  free_tree(t2);
  free(n1);
  free(n2);

  push(s, root);
}

// Multiplies two top stack elements. Assumes that they exist.
// Pops them from the stack and pushes the result.
void multiply(stack *s) {
  if (s == NULL || s->top == NULL || s->top->next == NULL)
    return;

  node_of_tree *n1 = s->top;
  node_of_tree *n2 = n1->next;
  tree *t1 = n1->val;
  tree *t2 = n2->val;
  s->top = n2->next;

  tree *father1 = t1->rson;
  tree *father2 = t2->rson;

  stack tmp;
  tmp.top = NULL;

  tree *a_start = father1->rson;
  tree *b_start = father2->rson;
  
  // Multiplying by 0.
  if (a_start == NULL || b_start == NULL) { 
    tree *zero = (tree *)malloc(sizeof(tree));
    zero->brother = NULL;
    zero->num = NULL;

    tree *fake = (tree *)malloc(sizeof(tree));
    fake->brother = NULL;
    fake->num = NULL;
    fake->rson = NULL;

    zero->rson = fake;

    free_tree(t1);
    free_tree(t2);
    free(n1);
    free(n2);

    push(s, zero);
    return;
  }

  // Normal multiplication.
  for (tree *a = a_start; a != NULL; a = a->brother) {
    for (tree *b = b_start; b != NULL; b = b->brother) {

      tree *fa = (tree *)malloc(sizeof(tree));
      fa->num = NULL;
      fa->brother = NULL;
      fa->rson = copy_tree(a);

      tree *fb = (tree *)malloc(sizeof(tree));
      fb->num = NULL;
      fb->brother = NULL;
      fb->rson = copy_tree(b);

      push(&tmp, fa);
      push(&tmp, fb);

      sum(&tmp);
      power(&tmp);
    }
  }

  while (tmp.top != NULL && tmp.top->next != NULL)
    sum(&tmp);

  node_of_tree *last = tmp.top;
  tree *result = last->val;
  free(last);
  tmp.top = NULL;

  free_tree(t1);
  free_tree(t2);
  free(n1);
  free(n2);

  push(s, result);
}

/* Reads characters from standard input and performs
 * appropriate operations on tree-encoded natural numbers.
 */
int main() {
  stack s;
  char c;
  s.top = NULL;

  while ((c = (char)getchar()) != EOF) {
    switch (c) {
    case '+':
      sum(&s);
      c = (char)getchar();
      break;

    case '.':
      pop(&s);
      c = (char)getchar();
      break;

    case ':':
      double_top(&s);
      c = (char)getchar();
      break;

    case '^':
      power(&s);
      c = (char)getchar();
      break;

    case '*':
      multiply(&s);
      c = (char)getchar();
      break;

    default:
      ungetc(c, stdin);

      tree *root = (tree *)malloc(sizeof(tree));
      root->brother = NULL;
      root->rson = NULL;
      root->num = NULL;

      create_tree(root);
      normalize(root);
      push(&s, root);

      c = (char)getchar();
    }
  }

  free_stack(&s);

  return 0;
}
