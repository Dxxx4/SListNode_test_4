#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Windows.h>

struct ListNode {
     int val;
     struct ListNode *next;
};
typedef struct ListNode ListNode;

//1.�� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£��������������

//�����ڵ�
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

//�������ڵ㣬ֻ������ֵ
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

//2.ɾ�������е��ڸ���ֵ val �����нڵ㡣
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

//3.��תһ��������
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

//4.����һ������ÿ���ڵ����һ���������ӵ����ָ�룬��ָ�����ָ�������е��κνڵ��սڵ㡣
//Ҫ�󷵻�����������ȿ�����
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

//5.��дһ�������ҵ������������ཻ����ʼ�ڵ㡣
//ע�⣺
//�����������û�н��㣬���� null.
//�ڷ��ؽ���������������뱣��ԭ�еĽṹ��
//�ɼٶ���������ṹ��û��ѭ����
//���������� O(n) ʱ�临�Ӷȣ��ҽ��� O(1) �ڴ档
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

