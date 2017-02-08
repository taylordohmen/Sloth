#include <unordered_map>
#include <iostream>
#include <string>
#include "executor.h"
#include "parser.tab.h"
#include "parsetree.h"


struct Var {
	std::string id;
	double value;
};

std::unordered_map<std::string, double> vars;


void printVars() {
	std::cout << "VARIABLES" << std::endl;
	std::unordered_map<std::string, double>::iterator it;
	for(it = vars.begin(); it != vars.end(); it++) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}


void eval_stmt(struct Node* node) {

	struct Var* var;
	std::string id;

	switch (node->type) {
		
		case ASSIGN:
			id = (node->children[0])->id;
			vars[id] = eval_expr(node->children[1]);
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
			while (eval_expr(node->children[0]) != 0) {
				eval_stmt(node->children[1]);
			}
		
		case STATEMENT:
			for (int i = 0; i < node->num_children; i++) {
				eval_stmt(node->children[i]);
			}
	}
}


double eval_expr(struct Node* node) {

	switch (node->type) {

		case VALUE:
			return node->value;
			break;
		case IDENTIFIER:
			return vars[node->id];
			break;
		case INPUT:
			std::cout << "IN INPUT BLOCK" << std::endl;
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