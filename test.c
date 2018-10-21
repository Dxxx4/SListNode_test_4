#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Windows.h>

struct ListNode {
     int val;
     struct ListNode *next;
};
typedef struct ListNode ListNode;

//1.在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

//交换节点
//void sort(ListNode* head, ListNode* tail){
//	ListNode* pivot = head;
//    ListNode* cur = head->next;
//    ListNode* div = head->next;
//    ListNode* curPrv = head;
//    ListNode* divPrv = head;
//    if(head == tail || head->next == tail){
//        return;
//    }
//    
//    while(cur != tail){
//        if(cur->val <= pivot->val){
//            if(cur == div){
//                cur = cur->next;
//                div = div->next;
//                curPrv = curPrv->next;
//                divPrv = divPrv->next;
//            }
//            else{
//                divPrv->next = div->next;
//                div->next = cur->next;
//                curPrv->next = div;
//                cur->next = divPrv->next;
//                divPrv->next = cur;
//                divPrv = divPrv->next;
//                div = cur->next;
//                curPrv = curPrv->next;
//                cur = curPrv->next;
//            }
//        }
//        else{
//            curPrv = curPrv->next;
//            cur = cur->next;
//        }
//    }
//    if(pivot == divPrv){
//        ;
//    }
//    else{
//        head = head->next;
//        pivot->next = div;
//        divPrv->next = pivot;
//    }
//    
//    sort(head, pivot);
//    sort(pivot->next, tail);
//}

//不交换节点，只交换数值
void sort(ListNode* head, ListNode* tail){
	ListNode* pivot = head;
    ListNode* cur = head->next;
    ListNode* div = head;
    int tmp;

    if(head == tail || head->next == tail){
        return;
    }
    
    while(cur != tail){
        if(cur->val <= pivot->val){
            div = div->next;
            tmp = cur->val;
            cur->val = div->val;
            div->val = tmp;
            cur = cur->next;
        }
        else{
            cur = cur->next;
        }
    }
    if(div->val <= pivot->val){
        tmp = div->val;
        div->val = pivot->val;
        pivot->val = tmp;
        pivot = div;
    }
    
    sort(head, pivot);
    sort(pivot->next, tail);
}


struct ListNode* sortList(struct ListNode* head) {
    sort(head, NULL);
    return head;
}

//2.删除链表中等于给定值 val 的所有节点。
struct ListNode* removeElements(struct ListNode* head, int val) {
    if(head == NULL){
        return head;
    }
    ListNode* node = head;
    ListNode* prv;
    ListNode* del;
    while(node != NULL){
        if(node->val == val){
            if(node == head){
                del = node;
                head = head->next;
                node = head;
            }
            else{
                del = node;
                prv->next = node->next;
                node = prv->next;
            }
            free(del);
        }
        else{
            prv = node;
            node = node->next;
        }
    }
    return head;
}

//3.反转一个单链表。
struct ListNode* reverseList(struct ListNode* head) {
    ListNode* node;
    ListNode* pnew = NULL;
    while(head != NULL){
        node = head;
        head = head->next;
        node->next = pnew;
        pnew = node;
    }
    return pnew;
}

//4.给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
//要求返回这个链表的深度拷贝。
struct RandomListNode {
    int label;
    struct RandomListNode *next;
    struct RandomListNode *random;
};
typedef struct RandomListNode RListNode;

struct RandomListNode *copyRandomList(struct RandomListNode *head) {
    if(head == NULL){
        return;
    }
    RListNode* node = head;
    while(node != NULL){
        RListNode* pnew = (RListNode*)malloc(sizeof(RListNode));
        pnew->label = node->label;
        pnew->next = node->next;
        node->next = pnew;
        node = pnew->next;
    }
    node = head;
    RListNode* copy = node->next;
    while(node != NULL){
        if(node->random != NULL){
            copy->random = node->random->next;
        }
        else{
            copy->random = NULL;
        }
        node = node->next->next;
        if(node != NULL){
            copy = copy->next->next;
        }
    }
    RListNode* newhead = head->next;
    copy = newhead;
    RListNode* old = head;
    RListNode* oldnode = head->next->next;
    if(copy->next != NULL){
        node = newhead->next->next;
        while(oldnode != NULL){
            old->next = oldnode;
            copy->next = node;
            oldnode = oldnode->next->next;
            old = old->next;
            copy = copy->next;
            if(oldnode == NULL){
                break;
            }
            node = node->next->next;
        }
    }
    old->next = NULL;
    copy->next = NULL;
    
    return newhead;
}

//5.编写一个程序，找到两个单链表相交的起始节点。
//注意：
//如果两个链表没有交点，返回 null.
//在返回结果后，两个链表仍须保持原有的结构。
//可假定整个链表结构中没有循环。
//程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if(headA == NULL || headB == NULL){
        return NULL;
    }
    ListNode* node;
    int lA = 0;
    int lB = 0;
    for(node = headA; node != NULL; node = node->next){
        lA++;
    }
    for(node = headB; node != NULL; node = node->next){
        lB++;
    }
    ListNode* beginA = headA;
    ListNode* beginB = headB;
    if(lA > lB){
        int flag = lA - lB;
        while(flag){
            beginA = beginA->next;
            flag--;
        }
    }
    if(lA < lB){
        int flag = lB - lA;
        while(flag){
            beginB = beginB->next;
            flag--;
        }
    }
    while(beginA != NULL && beginB != NULL){
        if(beginA == beginB){
            return beginA;
        }
        beginA = beginA->next;
        beginB = beginB->next;
    }
    return NULL;
}


int main()
{
	ListNode* l1 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* l2 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* l3 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* l4 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* head;


	l1->val = 4;
	l2->val = 2;
	l3->val = 1;
	l4->val = 3;

	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	l4->next = NULL;

	head = sortList(l1);

	system("pause");
	return 0;
}

