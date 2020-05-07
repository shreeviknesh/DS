# DS - Data Structures
A C++ static library for implementations of the various Data Structures.

Contents
----
- [The Data Structures Implemented](#data-structures-implemented)
- [Usage (in VisualStudio)](#usage)

Data Structures Implemented
----
Given below is a list of Data Structures that are implemented (and soon to be implemented).

|Implemented?|Data Structure|Header File|
|:-:|:-:|:-:|
|<img src="https://img.shields.io/badge/-Yes-2ECC40">|Array|`Array.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Vector|`Vector.h`|
|<img src="https://img.shields.io/badge/-Yes-2ECC40">|Linked List|`LinkedList.h`|
|<img src="https://img.shields.io/badge/-Yes-2ECC40">|Doubly Linked List|`DoublyLinkedList.h`|
|<img src="https://img.shields.io/badge/-Yes-2ECC40">|Stack|`Stack.h`|
|<img src="https://img.shields.io/badge/-Yes-2ECC40">|Array Implementation of Stack|`ArrayStack.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Linked List Implementation of Stack|`LLStack.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Queue|`Queue.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Array Implementation of Queue|`ArrayQueue.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Linked List Implementation of Queue|`LLQueue.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Priority Queue|`PriorityQueue.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Double Ended Queue|`Deque.h`|
|<img src="https://img.shields.io/badge/-No-FF4136">|Binary Search Tree|`BST.h`|

Usage
----
(As part of VisualStudio Solution)
1. `git submodule add https://github.com/shreeviknesh/DS <path>` in your solution.
    - This will make updating the library in your solution easier.
    - As an alternative, you can `git clone https://github.com/shreeviknesh/DS <path>` or download the source of this repository.
1. Open the shortcut menu for the executable project in your solution explorer, then choose *Add* > *Reference*.
2. In the Add Reference dialog box, select check box DS and click OK.
3. To reference the header files in your project, you must modify the include directories path. Open the shortcut menu for the executable project in your solution explorer, then choose *Properties*.
4. In the Properties dialog box, set the *Configuration* drop-down to **All Configurations** and the *Platform* drop-down to **All Platforms.**
5. Select *Configuration Properties* > *C/C++* > *General*.
6. In the *Additional Include Directories* property, add path to `DS\includes\`
