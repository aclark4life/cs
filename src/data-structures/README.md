# Data Structures in C

Basic implementations of common data structures for learning and reference.

## Structures

### Array (`array.c`)
Simple array demonstration.

**Features:**
- Static array initialization
- Iteration and printing

**Usage:**
```bash
gcc array.c -o array
./array
# Output: 1 2 3 4 5
```

### Linked List (`list.c`)
Singly linked list implementation.

**Features:**
- Node structure with data and next pointer
- List traversal and printing
- Manual memory allocation

**Usage:**
```bash
gcc list.c -o list
./list
# Output:
# 1
# 2
# 3
```

### Stack (`stack.c`)
Array-based stack with fixed capacity.

**Features:**
- Push and pop operations
- Overflow/underflow detection
- LIFO (Last In, First Out) semantics

**API:**
```c
struct Stack* createStack();
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int isEmpty(struct Stack* stack);
int isFull(struct Stack* stack);
```

**Usage:**
```bash
gcc stack.c -o stack
./stack
# Output: 30 popped from stack
```

### Queue (`queue.c`)
Circular array-based queue with fixed capacity.

**Features:**
- Enqueue and dequeue operations
- Circular buffer implementation
- FIFO (First In, First Out) semantics

**API:**
```c
struct Queue* createQueue();
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int isEmpty(struct Queue* queue);
int isFull(struct Queue* queue);
```

### Binary Tree (`tree.c`)
Binary tree with inorder traversal.

**Features:**
- Node creation
- Inorder traversal (left, root, right)
- Recursive implementation

**Usage:**
```bash
gcc tree.c -o tree
./tree
# Output: Inorder traversal: 4 2 5 1 3
```

## Building All

```bash
# Compile all data structures
for file in *.c; do
    gcc -Wall -Wextra "$file" -o "${file%.c}"
done
```

## Notes

- All implementations use simple integer data
- Fixed-size structures (MAX = 1000 for stack/queue)
- No error recovery (programs exit on error)
- Educational purposes - not production-ready

## Improvements Needed

For production use, consider:
- Generic data types (void pointers)
- Dynamic resizing
- Better error handling
- Memory leak prevention
- Thread safety
- Comprehensive test suites

## Learning Path

Recommended order:
1. **Array** - Understand basic memory layout
2. **Linked List** - Learn dynamic allocation
3. **Stack** - Understand LIFO and array-based structures
4. **Queue** - Learn circular buffers and FIFO
5. **Tree** - Understand recursion and tree traversal

