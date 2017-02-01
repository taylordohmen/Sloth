#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parsetree.h"
#include "parser.tab.h"


struct Node* make_node(int type, double value, char* id) {

	struct Node* node = malloc(sizeof(struct Node));

	node -> type = type;
	node -> value = value;
	strcpy(node -> id, id);
	node -> num_children = 0;

	for (int i = 0; i < MAX_CHILDREN; i++) {
		node -> children[i] = NULL;
	}

	return node;
}


void attach_node(struct Node* parent, struct Node* child) {

	parent -> children[parent -> num_children] = child;
	parent -> num_children++;
	// assert(parent -> num_children <= MAX_CHILDREN);
}


void print_tree(struct Node* node, int tabs) {
  int i;

  /* base case */
  if(!node) return;

  /* print leading tabs */
  for(i = 0; i < tabs; i++) {
    printf("    ");
  }

  switch(node->type) {
    case IDENTIFIER: printf("IDENTIFIER: %s\n", node->id); break;
    case VALUE: printf("VALUE: %lf\n", node->value); break;
    case PLUS: printf("PLUS:\n"); break;
    case MINUS: printf("MINUS:\n"); break;
    case DIVIDE: printf("DIVIDE:\n"); break;
    case TIMES: printf("TIMES:\n"); break;
    case LESS: printf("LESS THAN:\n"); break;
    case GREATER: printf("GREATER:\n"); break;
    case LESSEQ: printf("LESS EQUAL:\n"); break;
    case GREATEREQ: printf("GREATER EQUAL:\n"); break;
    case EQUALS: printf("EQUALS:\n"); break;
    case NEQUALS: printf("NOT EQUALS:\n"); break;
    case AND: printf("AND:\n"); break;
    case OR: printf("OR:\n"); break;
    case NOT: printf("NOT:\n"); break;
    case ASSIGN: printf("ASSIGN:\n"); break;
    case IF: printf("IF:\n"); break;
    case WHILE: printf("WHILE:\n"); break;
    case PRINT: printf("PRINT:\n"); break;
    case INPUT: printf("INPUT:\n"); break;
    case STATEMENT: printf("STATEMENT:\n"); break;
    default:
      printf("Error, %d not a valid node type.\n", node->type);
      exit(1);
  }

  /* print all children nodes underneath */
  for(i = 0; i < node->num_children; i++) {
    print_tree(node->children[i], tabs + 1);
  }
}