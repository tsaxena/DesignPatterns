#if !defined (_Eval_Visitor_CPP)
#define _Eval_Visitor_CPP

#include "Component_Node.h"
#include "Leaf_Node.h"
#include "Composite_Negate_Node.h"
#include "Composite_Add_Node.h"
#include "Composite_Subtract_Node.h"
#include "Composite_Divide_Node.h"
#include "Composite_Multiply_Node.h"
#include "Tree.h"

#include "Eval_Visitor.h"

/// Dtor
Eval_Visitor::~Eval_Visitor (){
}

/// visit method for Leaf_Node<int> instance
void Eval_Visitor::visit(const LEAF_NODE& node){
	stack_.push(node.item());
}

/// visit method for Composite_Negate_Node<int> instance
void Eval_Visitor::visit(const COMPOSITE_NEGATE_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	stack_.push(-temp);
}

/// visit method for Composite_Add_Node<int> instance
void Eval_Visitor::visit(const COMPOSITE_ADD_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	temp=temp+stack_.top();
	stack_.pop();

	stack_.push(temp);
}

/// visit method for Composite_Subtract_Node<int> instance
void Pre_Order_Eval_Visitor::visit(const COMPOSITE_SUBTRACT_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	temp=temp-stack_.top();
	stack_.pop();
	stack_.push(temp);
}


/// visit method for Composite_Divide_Node<int> instance
void Pre_Order_Eval_Visitor::visit(const COMPOSITE_DIVIDE_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	temp=temp/stack_.top();
	stack_.pop();
	stack_.push(temp);
}


/// visit method for Composite_Subtract_Node<int> instance
void Eval_Visitor::visit(const COMPOSITE_SUBTRACT_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	int temp1=stack_.top();
	stack_.pop();
	stack_.push(temp1-temp);
}

/// visit method for Composite_Multiply_Node<int> instance
void Eval_Visitor::visit(const COMPOSITE_MULTIPLY_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	temp=temp*stack_.top();
	stack_.pop();
	stack_.push(temp);
}
/// visit method for Composite_Divide_Node<int> instance
void Eval_Visitor::visit(const COMPOSITE_DIVIDE_NODE& node){
	int temp=stack_.top();
	stack_.pop();
	int temp1=stack_.top();
	stack_.pop();
	stack_.push(temp1/temp);
}

// yeilds the output of the visit
int Eval_Visitor::yield(){
	return stack_.top();
}

/// Ctor
Post_Order_Eval_Visitor::Post_Order_Eval_Visitor(){
}

/// Dtor
Post_Order_Eval_Visitor::~Post_Order_Eval_Visitor(){
}

/// Ctor
Pre_Order_Eval_Visitor::Pre_Order_Eval_Visitor(){
}

/// Dtor
Pre_Order_Eval_Visitor::~Pre_Order_Eval_Visitor(){
}

#endif //_Eval_Visitor_CPP
