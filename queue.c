#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *newHead = malloc(sizeof(struct list_head));

    if (!newHead)
        return NULL;

    INIT_LIST_HEAD(newHead);

    return newHead;
}

/* Free all storage used by queue */
void q_free(struct list_head *head) {}

struct list_head *create_new_head(char *s)
{
    struct list_head *newHead =
        (struct list_head *) malloc(sizeof(struct list_head));

    // newHead memory allocation failed
    if (!newHead)
        return false;

    element_t *newElement = (element_t *) malloc(sizeof(element_t));

    // newElement memory allocation failed
    if (!newElement)
        return false;

    // initialize value and node for newElement
    newElement->value = s;
    newElement->list = *newHead;

    return newHead;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    struct list_head *newHead = create_new_head(s);

    // track first node in queue (excluding head)
    struct list_head *nextHead = head->next;

    head->next = newHead;
    newHead->prev = head;

    // empty queue: nextHead points to head itself
    if (nextHead == head) {
        head->prev = newHead;
        newHead->next = head;
    } else {
        nextHead->prev = newHead;
        newHead->next = nextHead;
    }

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    struct list_head *newHead = create_new_head(s);

    // struct list_head * tailNode = head;

    // for (; tailNode->next != head; tailNode = tailNode->next);

    // instead of iterating through queue, access tail node directly from head
    // (doubly linked-list, head->prev == tailNode)
    struct list_head *tailNode = head->prev;

    head->prev = newHead;
    newHead->next = head;

    // empty queue -> same as insert head
    if (tailNode == head) {
        head->next = newHead;
        newHead->prev = head;
    } else {
        tailNode->next = newHead;
        newHead->prev = tailNode;
    }

    return true;
}

inline size_t min(size_t val1, size_t val2)
{
    return ((val1 < val2) ? (val1) : (val2));
}

inline void rejoin_neighbors(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    // empty queue -> cannot remove element
    // if (head->next == head)
    if (list_empty(head))
        return NULL;

    // retrieve element data of first node using helper macro function
    element_t *elementData = list_entry(head->next, element_t, list);

    // prev of next of first node should point to head
    // next of head should point to next of first node
    rejoin_neighbors(head, head->next->next);

    // store string from element data into buffer
    memcpy(sp, elementData->value,
           min(bufsize, strlen(elementData->value)) * sizeof(char));

    return elementData;

    // struct list_head *cur = head;

    // element_t *elementData, *nextNode, *prevNode;

    // for (; cur->next != head; cur = cur->next) {
    //     elementData = list_entry(cur, element_t, list);
    //     if (!strcmp(elementData->value, sp)) {
    //         prevNode = cur->prev;
    //         nextNode = cur->next;
    //         prevNode->next = nextNode;
    //         nextNode->prev = prevNode;
    //         return elementData;
    //     }
    // }
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    // cannot remove tail if queue empty
    // if (head->prev == head)
    if (list_empty(head))
        return NULL;

    element_t *elementData = list_entry(head->prev, element_t, list);

    rejoin_neighbors(head->prev->prev, head);

    // store string from element data into buffer
    memcpy(sp, elementData->value,
           min(bufsize, strlen(elementData->value)) * sizeof(char));

    return elementData;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    int len = 0;
    struct list_head *li;
    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
