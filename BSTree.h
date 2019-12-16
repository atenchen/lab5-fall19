#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <vector>

template <class T>
class BSTree{
 private:
  class Node{
  public:
    Node* parent;
    Node* left;
    Node* right;
    T data;
    Node(T data, Node* parent){
      this->parent = parent;
      this->data = data;
      this->left = nullptr;
      this->right = nullptr;
    }
  };
  Node* root;
  bool nodeInsert(T val, Node*);
  bool nodeFind(T val, Node*);
  void deleteHelper(Node* currentNode);
  void copyHelper(Node* currentNode);
  void sortedArrayHelper(std::vector<T> &, Node*);
  void promote(Node*);
  void shortCircuit(Node*);
  void removeLeaf(Node*);
  Node* getMaxNode(Node*);
  Node* readHelper(T val, Node*);
  int heightHelper(Node*);
  Node* balanceHelper(std::vector<T>, int, int, Node*);
 public:
  BSTree(){root = nullptr;}
  ~BSTree();
  BSTree(const BSTree&);
  bool empty(){return root == nullptr;}
  bool insert(T val);
  bool find(T val);
  void sortedArray(std::vector<T>&);
  bool remove(T val);
  Node* read(T val);
  void balance();
  int height();
};
template<class T>
bool BSTree<T>::insert(T val){
  if(empty()){
    this->root = new Node(val, nullptr);
    return true;
  }
  if(find(val)){
    return false;
  }
  return nodeInsert(val,this->root);
}
template<class T>
bool BSTree<T>::nodeInsert(T val, Node* currentNode){
  if(currentNode->data > val){
    if(currentNode->left == nullptr){
      currentNode->left = new Node(val, currentNode);
      return true;
    }
    if(currentNode->left->data == val){
      return false;
    }
    else{
      return nodeInsert(val,currentNode->left);
    }
  }
  else if(currentNode->data < val){
    if(currentNode->right == nullptr){
      currentNode->right = new Node(val, currentNode);
      return true;
    }
    if(currentNode->right->data == val){
      return false;
    }
    else{
      return nodeInsert(val,currentNode->right);
    }
  }
  else if(currentNode->data == val){
    return false;
  }
  else{
    return false;
  }
}
template<class T>
bool BSTree<T>::find(T val){
  if(this->empty()){
    return false;
  }
  return nodeFind(val,this->root);
}
template <class T>
bool BSTree<T>::nodeFind(T val, Node* currentNode){
  if(currentNode->data == val){
    return true;
  }
  else if(currentNode->data > val){
    if(currentNode->left == nullptr){
      return false;
    }
    if(currentNode->left->data == val){
      return true;
    }
    else{
      return nodeFind(val,currentNode->left);
    }
  }
  else if(currentNode->data < val){
    if(currentNode->right == nullptr){
      return false;
    }
    if(currentNode->right->data == val){
      return true;
    }
    else{
      return nodeFind(val,currentNode->right);
    }
  }
  else{
    return true;
  }
}
template <class T>
BSTree<T>::~BSTree(){
  deleteHelper(this->root);
  root = nullptr;
}
template <class T>
void BSTree<T>::deleteHelper(Node * currentNode){
  if(currentNode != nullptr){
    deleteHelper(currentNode->left);
    deleteHelper(currentNode->right);
    delete currentNode;
  }
}
template <class T>
BSTree<T>::BSTree(const BSTree &old_tree){
  root = nullptr;
  copyHelper(old_tree.root);
}
template <class T>
void BSTree<T>::copyHelper(Node* currentNode){
  if(currentNode != nullptr){
    this->insert(currentNode->data);
    copyHelper(currentNode->left);
    copyHelper(currentNode->right);
  }
}
template <class T>
void BSTree<T>::sortedArray(std::vector<T> &list){
  if(root != nullptr){
    sortedArrayHelper(list, this->root);
  }
}
template <class T>
void BSTree<T>::sortedArrayHelper(std::vector<T> &list, Node* currentNode){
  if(currentNode->left != nullptr){
    sortedArrayHelper(list,currentNode->left);
  }
  list.push_back(currentNode->data);
  if(currentNode->right !=nullptr){
    sortedArrayHelper(list,currentNode->right);
  }
}
template <class T>
bool BSTree<T>::remove(T val){
  if(!find(val)){
    return false;
  }
  Node* removeNode = read(val);
  if(removeNode == nullptr){
    return false;
  }
  if(removeNode->left == nullptr && removeNode->right == nullptr){
    removeLeaf(removeNode);
    return true;
  }
  else if(removeNode->left == nullptr ||removeNode->right == nullptr){
    shortCircuit(removeNode);
    return true;
  }
  else{
    promote(removeNode);
    return true;
  }
}
template <class T>
typename BSTree<T>::Node* BSTree<T>::read(T val){
  if(empty()){
    return nullptr;
  }
  return readHelper(val,this->root);
}
template <class T>
typename BSTree<T>::Node* BSTree<T>::readHelper(T val, Node* currentNode){
  if(currentNode->data == val){
    return currentNode;
  }
  else if(currentNode->data > val){
    if(currentNode->left == nullptr){
      return nullptr;
    }
    if(currentNode->left->data == val){
      return currentNode->left;
    }
    else{
      return readHelper(val,currentNode->left);
    }
  }
  else if(currentNode->data < val){
    if(currentNode->right == nullptr){
      return nullptr;
    }
    if(currentNode->right->data == val){
      return currentNode->right;
    }
    else{
      return readHelper(val,currentNode->right);
    }
  }
  else{
    return nullptr;
  }
}
template <class T>
void BSTree<T>::removeLeaf(Node* removeNode){
  if(this->root == removeNode){
    delete removeNode;
    root = nullptr;
  }
  else if(removeNode->parent->left == removeNode){
    removeNode->parent->left = nullptr;
    delete removeNode;
  }
  else if(removeNode->parent->right == removeNode){
    removeNode->parent->right = nullptr;
    delete removeNode;
  }
}
template <class T>
void BSTree<T>::shortCircuit(Node* removeNode){
  if(this->root == removeNode){
    if(removeNode->left != nullptr){
      removeNode->left->parent = nullptr;
      root = removeNode->left;
    }
    else{
      removeNode->right->parent = nullptr;
      root = removeNode->right;
    }
  }
  else if(removeNode->parent->left == removeNode){
    if(removeNode->left != nullptr){
      removeNode->parent->left = removeNode->left;
      removeNode->left->parent = removeNode->parent;
    }
    else{
      removeNode->parent->left = removeNode->right;
      removeNode->right->parent = removeNode->parent;
    }
  }
  else if(removeNode->parent->right == removeNode){
    if(removeNode->left != nullptr){
      removeNode->parent->right = removeNode->left;
      removeNode->left->parent = removeNode->parent;
    }
    else{
      removeNode->parent->right = removeNode->right;
      removeNode->right->parent = removeNode->parent;
    }
  }
  delete removeNode;
}
template <class T>
void BSTree<T>::promote(Node* removeNode){
  Node* swap = getMaxNode(removeNode);
  removeNode->data = swap->data;
  if(swap->left == nullptr && swap->right == nullptr){
    removeLeaf(swap);
  }
  else if(swap->left == nullptr || swap->right == nullptr){
    shortCircuit(swap);
  }
}
template <class T>
typename BSTree<T>::Node* BSTree<T>::getMaxNode(Node* removeNode){
  Node* swap = removeNode->left;
  while(swap->right != nullptr){
    swap = swap->right;
  }
  return swap;
}
template <class T>
int BSTree<T>::height(){
  return heightHelper(this->root);
}
/*template <class T>
int BSTree<T>::heightHelper(Node* currentNode){
  int leftHeight = 0;
  int rightHeight = 0;
  if(currentNode->left != nullptr){
    leftHeight = 1 + heightHelper(currentNode->left);
  }
  if(currentNode->right != nullptr){
    rightHeight = 1 + heightHelper(currentNode->right);
  }
  if(a>b){
    return a;
  }
  else{
    return b;
  }
  }*/
template <class T>
int BSTree<T>::heightHelper(Node * n){
  if(n == nullptr){
    return -1;
  }
  else{
    int leftHeight = heightHelper(n->left);
    int rightHeight = heightHelper(n->right);
    if(leftHeight>rightHeight){
      return leftHeight+1;
    }
    else{
      return rightHeight+1;
    }
  }
}
template <class T>
void BSTree<T>::balance(){
  std::vector<T>vec;
  sortedArray(vec);
  for(auto data: vec){
    remove(data);
  }
  this->root = balanceHelper(vec,0,vec.size()-1,nullptr);
}
template <class T>
typename BSTree<T>::Node* BSTree<T>::balanceHelper(std::vector<T> vec, int start, int end, Node* parent){
  if(start > end){
    return nullptr;
  }
  int median = (start + end)/2;
  Node* middle = new Node(vec.at(median),parent);
  middle->left = balanceHelper(vec, start,median-1,middle);
  middle->right = balanceHelper(vec,median + 1,end,middle);
  return middle;
}
#endif
