# List-based FIFO queue implementation
  
#### INSTRUCTION
The task is to implement FIFO queue using doubly or singly linked list. It is an extension of XOR linked list assignment XOR linked list and the list implemented for that assignment can be reused; but also an STL <list> list can be used.  
In addition to the functions of the XOR list (ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD) from the XOR list assignment XOR linked list the list implements:  
  
SIZE - liczba elementów listy.  
The queue is a data structure that uses list and provides functions corresponding to the following commands:  
  
PUSH N - add element N to the end of the queue.  
POP - remove the first element from the queue.  
PRINT_QUEUE - print the queue from the first element to the lastly added.  
COUNT - the number of elements in queue ≤ SIZE.  
GARBAGE_SOFT - change the values of all elements of the list that do not belong to the queue to 0.  
GARBAGE_HARD - remove all elements from the list that does not belong to the queue.  
The FIFO queue extends the list to the pointers to the beginning (FRONT) and the end (BACK) of the queue. After inserting an element to the queue the pointer to the end of the queue (BACK) has to be changed so it will point to the next element of the list. After removing an element from the queue (FRONT) pointer has to start pointing at the element after the previously pointer by (FRONT). Notice, that by both removing and adding the element the queue has to “follow the list”. To avoid memory loss and to be able to reuse one can use a cyclical list or after reaching the end of the queue start from the beginning. Also, one has to handle exceptions: inserting an element to an empty queue (no elements), adding elements to full list (the number of elements of the queue equal to the number of elements of the list), or trying to remove elements from an empty queue.  
When the list is empty (no elements in it) the pointers point to nullptr. When adding an element (PUSH N) to the queue and the list is empty, then before executing the operation one element has to be added to the list. Similarly, the list has to be extended when the list is not empty, but all the elements are occupied by the queue. Inserted element should be inserted before the element pointed by pointer to the end of the queue (BACK).  
  
From time to time it might be useful to remove the elements that do not contain elements from the queue. Such a situation may occur if there were many insertions and after the insertions there was a sequence of pops. The situation is quite common in queuing systems. Consider for example STOS system. Normally the queues are empty or contains a few tasks. But near the deadlines they may grow considerably, which can overload the system and crash it. The operation to shrink the size of the list is implemented by GARBAGE_HARD.  
  
#### INPUT
Some number of commands for the list or for the queue.
  
#### OUTPUT
The results of the operations of commands on the queue or directly on the list characterized by some state. Initially the list and the queue are empty, later their state depends on the commands. Some commands do not generate any output, but influence the state of the list and indirectly the queue and for the consecutive commands which print some in formations.
