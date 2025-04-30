#include "avl.hpp"

#include <iostream>

int main()
{
	AVL<float> avl{};
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(17);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(22);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(22);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(20);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(14);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(10);
	std::cout << "Size: " << avl.getSize() << '\n';
	avl.insert(25);
	std::cout << "Size: " << avl.getSize() << '\n';

	avl.inOrderTraverse();
	std::cout << '\n';
	return 0;
}
