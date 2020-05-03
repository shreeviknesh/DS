# DS - Data Structures
A C++ static library for implementations of the various Data Structures.

Contents
----
- [Data Structures Implemented](#data-structures-implemented)
- [Usage](#usage)

Data Structures Implemented
----
- [x] `Stack.h` - Linked List Stack
- [x] `ArrayStack.h` - Array Implementation of Stack
- [ ] `LinkedList.h` - Linked List
- [ ] `DoublyLinkedList.h` - Doubly Linked List
- [ ] `Queue.h` - Queue
- [ ] `ArrayQueue.h` - Array Implementation of Queue
- [ ] `PriorityQueue.h` - Priority Queue
- [ ] `Deque.h` - Double Ended Queue
- [ ] `BST.h` - Binary Search Tree

Usage
----
(As part of VisualStudio Solution)
1. `git submodule add https://github.com/shreeviknesh/DS <path>` in your solution.
    - This will make updating the library in your solution easier.
    - As an alternate, you can `git clone https://github.com/shreeviknesh/DS <path>` or download the source of this repository.
1. Open the shortcut menu for the executable project in your solution explorer, then choose *Add* > *Reference*.
2. In the Add Reference dialog box, select check box DS and click OK.
3. To reference the header files in your project, you must modify the include directories path. Open the shortcut menu for the executable project in your solution explorer, then choose *Properties*.
4. In the Properties dialog box, set the *Configuration* drop-down to **All Configurations** and the *Platform* drop-down to **All Platforms.**
5. Select *Configuration Properties* > *C/C++* > *General*.
6. In the *Additional Include Directories* property, add path to `DS\includes\`
