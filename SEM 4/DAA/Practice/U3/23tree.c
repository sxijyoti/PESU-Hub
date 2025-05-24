// O(logn)

/*
search a key value in a 2-3 tree

searchEle(tree, k):
    if tree == NULL:
        return false
    if tree -> data == k:
        return true
    if tree -> data > k:
        return searchEle(tree -> left, k)
    else:
        return searchEle(tree -> right, k)
return false


Function Search(node, key):
If node is NULL:
Return "Key not found"
If key == node.key1 OR (node has two keys AND key == node.key2):
Return "Key found"
If key < node.key1:
Return Search(node.left, key) // Go to left child
Else if node has two keys AND key > node.key2:
Return Search(node.right, key) // Go to right child
Else:
Return Search(node.middle, key) // Go to middle child

*/


/*
insert a key value into a 2-3 tree
insertEle(tree, k):
    if tree == NULL:
        return createNode(k)
    if tree -> data == k:
        return tree
    if tree -> data > k:
        tree -> left = insertEle(tree -> left, k)
    else:
        tree -> right = insertEle(tree -> right, k)
    return tree

Algorithm for insertion:
Function Insert(node, key):
If node is a leaf:
Insert key into node in sorted order
If node now has three keys:
Return Split(node)
Else:
Return node
If key < node.key1:
newChild, newKey = Insert(node.left, key)
Else if node has two keys AND key > node.key2:
newChild, newKey = Insert(node.right, key)
Else:
newChild, newKey = Insert(node.middle, key)

If newChild is not NULL:
Insert newKey into node in sorted order
Attach newChild to the correct position
If node now has three keys:
Return Split(node)
Return node, NULL
Function Split(node):
Create newNode
newNode.key1 = node.key2
If node has children:
newNode.left = node.middle
newNode.right = node.right
Return newNode, node.key1 // Promote
middle key

*/


/*
Function Delete(node, key):
//Case 1:
If node is NULL:
Return NULL
If key is in a leaf node:
Remove key from node
If node has no keys left:
HandleUnderflow(node)
Return node

// Case 2:
If key is in an internal node:
inorderSuccessor = FindMin(node.right)
node.key1 = inorderSuccessor
Delete(node.right, inorderSuccessor)
Else if key < node.key1:
Delete(node.left, key)
Else if node has two keys AND key >
node.key2:
Delete(node.right, key)
Else:
Delete(node.middle, key)
If node has underflow:
HandleUnderflow(node)
Return node

//Case 3:
Function HandleUnderflow(node):
If sibling has extra key:
Borrow key from sibling (Redistribution)
Else:
Merge node with sibling


*/