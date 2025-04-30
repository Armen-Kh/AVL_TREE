#ifndef AVL_HPP
#define AVL_HPP

#include <cstddef>
#include <iostream>
#include <utility>

template <class DATATYPE>
class AVL;

template <typename DATATYPE>
class AVLNode
{
public:
	DATATYPE getData()
	{
		return m_data;
	}

	int getBalanceFactor()
	{
		int leftChildHeight  = (m_leftChild) ? m_leftChild->m_height : -1;
		int rightChildHeight = (m_rightChild) ? m_rightChild->m_height : -1;
		return leftChildHeight - rightChildHeight;
	}

	friend int height(AVLNode<DATATYPE>* node) {
		if(!node) {
			return -1;
		}
		return node->m_height;
	}

	friend AVLNode<DATATYPE>* leftRotate(AVLNode<DATATYPE>* n) {
		std::cout << "\tLeft rotation done for node with " << n->m_data << " data!\n";
		AVLNode<DATATYPE>* nr = n->m_rightChild;
		AVLNode<DATATYPE>* nrl = nr->m_leftChild;
		nr->m_leftChild = n;
		n->m_rightChild = nrl;
		
		n->m_height = std::max(height(n->m_leftChild), height(n->m_rightChild)) + 1;
		nr->m_height = std::max(height(nr->m_leftChild), height(nr->m_rightChild)) + 1;
		return nr;
	} 

	friend AVLNode<DATATYPE>* rightRotate(AVLNode<DATATYPE>* n) {
		std::cout << "\tRight rotation done for node with " << n->m_data << " data!\n";
		AVLNode<DATATYPE>* nl = n->m_leftChild;
		AVLNode<DATATYPE>* nlr = nl->m_rightChild;
		nl->m_rightChild = n;
		n->m_leftChild = nlr;
		
		n->m_height = std::max(height(n->m_leftChild), height(n->m_rightChild)) + 1;
		nl->m_height = std::max(height(nl->m_leftChild), height(nl->m_rightChild)) + 1;
		return nl;
	} 

private:
	friend class AVL<DATATYPE>;

	AVLNode(const DATATYPE& data)
		: m_data(data)
		, m_leftChild(nullptr)
		, m_rightChild(nullptr)
		, m_height(0)
	{
		std::cout << "AVL node created with " << m_data << " data\n";
	}
	
private:
	DATATYPE m_data;
	AVLNode<DATATYPE>* m_leftChild;
	AVLNode<DATATYPE>* m_rightChild;
	std::size_t m_height;	
};

template <typename DATATYPE>
class AVL
{
public:
	AVL() : m_size(0), m_root(nullptr)
	{
		std::cout << "Empty AVL Tree created!\n";
	}

	~AVL()
	{
		std::cout << "AVL Tree destroyed!\n";
		clearAssistant(m_root);
	}

	std::pair<AVLNode<DATATYPE>*, bool> insert(const DATATYPE& data)
	{
		std::cout << "Adding node with " << data << " data\n";
		insertAssistant(m_root, data);
		return lastInserted;
	}

	bool remove(const DATATYPE& data)
	{
		std::cout << "Removing node with " << data << " data\n";
		return removeAssistant(data);
	}

	AVLNode<DATATYPE>* find(const DATATYPE& data)
	{
		std::cout << "Finding node with " << data << " data\n";
		return findAssistant(data);
	}

	void clear()
	{
		std::cout << "AVL Tree cleared!\n";
		clearAssistant(m_root);
	}

	int getSize()
	{
		return m_size;
	}
	
	void inOrderTraverse()
	{
		std::cout << "In order traversal data: ";
		inOrderTraverseAssistant(m_root);	
	}

private:
	AVLNode<DATATYPE>* insertAssistant(AVLNode<DATATYPE>* node, const DATATYPE& data)
	{
		if(!node) {
			if(!m_size) {
				m_root = new AVLNode<DATATYPE>(data);
			} else {
				node = new AVLNode<DATATYPE>(data);
			}
			++m_size;
			lastInserted = std::make_pair(node, true);
			return node;
		}
 
		std::pair<AVLNode<DATATYPE>*, bool> p;
		if(node->m_data > data) {
			node->m_leftChild = insertAssistant(node->m_leftChild, data);
		} else if(node->m_data < data) {
			node->m_rightChild = insertAssistant(node->m_rightChild, data);
		} else {
			std::cout << "Node with " << data << " already exists\n";
			lastInserted = std::make_pair(node, false);
			return node;
		}
		
		node->m_height = std::max(height(node->m_leftChild), height(node->m_rightChild)) + 1;
		bool rotationPerformed {false};

		//RR Case
		if(node->getBalanceFactor() < -1 && node->m_rightChild->getBalanceFactor() < 0) {
			node = leftRotate(node);
			rotationPerformed = true;
		} 
	
		//RL Case
		if(node->getBalanceFactor() < -1 && node->m_rightChild->getBalanceFactor() > 0) {
			node->m_rightChild = rightRotate(node->m_rightChild);
			node = leftRotate(node);
			rotationPerformed = true;
		} 
	
		//LL Case
		if(node->getBalanceFactor() > 1 && node->m_leftChild->getBalanceFactor() > 0) {
			node = rightRotate(node);
			rotationPerformed = true;
		} 
	
		//LR Case
		if(node->getBalanceFactor() > 1 && node->m_leftChild->getBalanceFactor() < 0) {
			node->m_leftChild = leftRotate(node->m_leftChild);
			node = rightRotate(node);
			rotationPerformed = true;
		} 
	
		if(rotationPerformed && (m_root == node->m_leftChild || m_root == node->m_rightChild) ) {
			m_root = node;
		}
		return node;
	}
	
	bool removeAssistant(const DATATYPE& data)
	{
		return true;
	}
	
	AVLNode<DATATYPE>* findAssistant(const DATATYPE& data)
	{
		return nullptr;
	}
	
	void clearAssistant(AVLNode<DATATYPE>* m_root)
	{
	}
	
	void inOrderTraverseAssistant(AVLNode<DATATYPE>* node)
	{
		if(node) {
			inOrderTraverseAssistant(node->m_leftChild);
			std::cout << node->m_data << ' ';
			inOrderTraverseAssistant(node->m_rightChild);
		}
	}	

	std::pair<AVLNode<DATATYPE>*, bool> lastInserted;
	std::size_t m_size;
	AVLNode<DATATYPE>* m_root;
};

#endif

