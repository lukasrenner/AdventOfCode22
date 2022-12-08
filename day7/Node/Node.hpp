#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <numeric>

struct Node;

using NodePtr = std::shared_ptr<Node>;
using NodeList = std::list<NodePtr>;

struct Node {
  Node() = default;
  Node(Node *p, int s, std::string n) : parent_{p}, size_{s}, name_{n} {}
  NodeList nodes_;
  Node *parent_;
  int size_{0};
  std::string name_;
  bool IsDir_{false};
  void AddNodes(NodeList ns) {
    IsDir_ = true;
    for (auto node : ns) {
      node->parent_ = this;
    }
    nodes_.splice(nodes_.end(), ns);
  }

  int CalcSize() {
    if (IsDir_) {
      int res{0};
      for (auto nptr : nodes_) {
        res += nptr->CalcSize();
      }
      size_ = res;
      return res;
    } else {
      return size_;
    }
  }

  std::list<int> ReportDirSizes() {
    std::list<int> resList{size_};
    for (auto nptr : nodes_) {
      if (!nptr->IsDir_)
        continue;
      else
        resList.splice(resList.begin(), nptr->ReportDirSizes());
    }
    return resList;
  }
};

struct Tree {
  Tree() : root_node_(0, 0, "/") {}
  Node root_node_;
  Node *current_node_{&root_node_};

  void GoToRoot() {
    std::cout << "Going to the root node" << std::endl;
    current_node_ = &root_node_;
  }
  void GoDirUp() {
    std::cout << "Going one dir up" << std::endl;
    if (current_node_ != &root_node_) {
      current_node_ = current_node_->parent_;
    } else {
      std::cerr << "Cant move up from /" << std::endl;
    }
  }

  void MoveToDir(std::string dir) {
    std::cout << "Moving to dir " << dir << std::endl;
    bool found{false};
    for (auto node : current_node_->nodes_) {
      if (node->name_ == dir) {
        current_node_ = node.get();
        found = true;
      }
    }
    if (!found) {
      std::cerr << "Cant move to '" << dir << "'" << std::endl;
    }
  }
  void AddNodes(NodeList ns) {
    std::cout << "Adding nodes to current node" << std::endl;
    for (auto n : ns) {
      n->parent_ = current_node_;
    }
    current_node_->AddNodes(ns);
    current_node_->IsDir_ = true;
  }

  std::list<int> GetAllDirSizes() {
    root_node_.CalcSize();
    return root_node_.ReportDirSizes();
  }
};

#endif