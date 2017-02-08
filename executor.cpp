#include <unordered_map>
#include <iostream>
#include "executor.h"
#include "parser.tab.h"
#include "parsetree.h"


struct Var {
	char* id;
	double value;
};

std::unordered_map<char*, double> vars;


void eval_stmt(struct Node* node) {

	struct Var* var;
	char* id;

	switch (node->type) {
		
		case ASSIGN:
			id = (node->children[0])->id;
			vars[id] = node->value;
			break;

		case PRINT:
			std::cout << eval_expr(node->children[0]) << std::endl;
			break;

		case IF:
			if (node->num_children == 3) {
				if (eval_expr(node->children[0]) != 0) {
					eval_stmt(node->children[1]);
				}
				else {
					eval_stmt(node->children[2]);
				}
			}
			else if (node->num_children == 2) {
				if (eval_expr(node->children[0]) != 0) {
					eval_stmt(node->children[1]);
				}
			}
			break;

		case WHILE:
			while (node->children[0] != 0) {
				eval_stmt(node->children[1]);
			}
		
		case STATEMENT:
			for (int i = 0; i < node->num_children; i++) {
				eval_stmt(node->children[i]);
			}
	}
}

// int val(string id) {
// 	for (int i = 0; i < vars.size(); i++) {
// 		if (vars[i]->id == id) {
// 			return vars[i]->value;
// 		}
// 	}
// }


double eval_expr(struct Node* node) {

	switch (node->type) {

		case VALUE:
			return node->value;
			break;
		case IDENTIFIER:
			return vars[node->id];
			break;
		case INPUT:
			double s; std::cin >> s;
			return s;
			break;
		case OPAREN:
			return (double)(eval_expr(node->children[0]));
			break;
		case NOT:
			return (double)!(eval_expr(node->children[0]));
			break;
		case DIVIDE:
			return (double)(eval_expr(node->children[0]) / eval_expr(node->children[1]));
			break;
		case TIMES:
			return (double)(eval_expr(node->children[0]) * eval_expr(node->children[1]));
			break;
		case MINUS:
			return (double)(eval_expr(node->children[0]) - eval_expr(node->children[1]));
			break;
		case PLUS:
			return (double)(eval_expr(node->children[0]) + eval_expr(node->children[1]));
			break;
		case GREATEREQ:
			return (double)(eval_expr(node->children[0]) >= eval_expr(node->children[1]));
			break;
		case GREATER:
			return (double)(eval_expr(node->children[0]) > eval_expr(node->children[1]));
			break;
		case NEQUALS:
			return (double)(eval_expr(node->children[0]) != eval_expr(node->children[1]));
			break;
		case EQUALS:
			return (double)(eval_expr(node->children[0]) == eval_expr(node->children[1]));
			break;
		case LESSEQ:
			return (double)(eval_expr(node->children[0]) <= eval_expr(node->children[1]));
			break;
		case AND:
			return (double)(eval_expr(node->children[0]) && eval_expr(node->children[1]));
			break;
		case OR:
			return (double)(eval_expr(node->children[0]) || eval_expr(node->children[1]));
			break;
	}
}