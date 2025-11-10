#pragma once
#include "cell.h"
#include <memory>

struct Node
{
	Node(std::shared_ptr<Cell> cell, std::shared_ptr<Node> source, double c_cost, double f_cost) : cell(cell), source(source), c_cost(c_cost), f_cost(f_cost){}

	std::shared_ptr<Cell> cell;
	std::shared_ptr<Node> source;
	double c_cost = 0;
	double f_cost = 0;
	std::shared_ptr<Node> parent = nullptr;
	std::shared_ptr<Node> lchild = nullptr;
	std::shared_ptr<Node> rchild = nullptr;
};

class Tree
{
public:
	Tree();
	~Tree();

	void insert(std::shared_ptr<Cell> cell, std::shared_ptr<Node> source, double c_cost, double f_cost)
	{
		size_++;
		if (root_)
		{
			std::shared_ptr<Node> current = root_;
			std::shared_ptr<Node> temp = nullptr;

			while (temp = (c_cost + f_cost) <= (current->c_cost + current->f_cost) ? current->lchild : current->rchild)
			{
				current = temp;
			}

			temp = std::make_shared<Node>(cell, source, c_cost, f_cost);
			temp->parent = current;
			((c_cost + f_cost) <= (current->c_cost + current->f_cost) ? current->lchild : current->rchild) = temp;
		}
		else
		{
			root_ = std::make_shared<Node>(cell, source, c_cost,f_cost);
		}
	}

	std::shared_ptr<Node> head()
	{
		if (size_ == 0) return nullptr;

		std::shared_ptr<Node> current = root_;
		while (current->lchild)
			current = current->lchild;

		return current;
	}

	void pop()
	{
		if (size_ == 0) return;

		size_--;

		if (root_->lchild == nullptr)
		{
			if (root_->rchild)
			{
				root_ = root_->rchild;
				root_->parent->rchild = nullptr;
				root_->parent = nullptr;
			}
			else
			{
				root_ = nullptr;
			}
			return;
		}

		std::shared_ptr<Node> current = root_;

		while (current->lchild)
			current = current->lchild;

		if (current->lchild->rchild)
		{
			current->lchild->parent = nullptr;
			current->lchild = current->lchild->rchild;
			current->lchild->parent->rchild = nullptr;
			current->lchild->parent = current;
		}
		else
		{
			current->lchild->parent = nullptr;
			current->lchild = nullptr;
		}
	}

	bool empty() { return !size_; }
private:
	std::shared_ptr<Node> root_ = nullptr;
	int size_ = 0;
};