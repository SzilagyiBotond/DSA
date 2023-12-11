 #include "Set.h"
#include "SetITerator.h"

using namespace std;

Set::DLLNode::DLLNode(TElem e, Node n, Node p)
{
    info=e;
    prev=p;
    next=n;
}
//Theta(1)
Set::Set() {
    tail= nullptr;
    head= nullptr;
}
//Theta(1)

bool Set::add(TElem elem) {
    bool found=false;
    Node node=head;
    while(node!= nullptr)
    {
        if (node->info==elem) {
            found = true;
            break;
        }
        node=node->next;
    }
    if(found)
	    return false;
    Node newNode=new DLLNode(elem, nullptr,tail);
    if (head== nullptr)
    {
        head=newNode;
        tail=newNode;
    }
    else
    {
        tail->next=newNode;
        tail=newNode;
    }

    return true;
}
//Worst caseTheta(nrElements)
//Best case Theta(1)

bool Set::remove(TElem elem) {
    Node node=head;
    while (node!= nullptr and node->info!=elem)
        node=node->next;
    bool deleted=false;
    if (node!= nullptr)
    {
        if (node==head)
        {
            if (node==tail)
            {
                head= nullptr;
                tail= nullptr;
            }
            else
            {
                head=head->next;
                head->prev= nullptr;
            }
        } else if (node==tail)
        {
            tail=tail->prev;
            tail->next= nullptr;
        }
        else
        {
            node->next->prev=node->prev;
            node->prev->next=node->next;
        }
        delete[] node;
        deleted= true;
    } else
        deleted= false;

    return deleted;
}
//Best csae Theta(1)
//Worst case Theta(nrElements)
bool Set::search(TElem elem) const {
    bool found=false;
    Node node=head;
    while(node!= nullptr)
    {
        if (node->info==elem) {
            found = true;
            break;
        }
        node=node->next;
    }
    return found;
}
//Worst case Theta(nrElements)
//Best case Theta(1)
int Set::size() const {
	int i=0;
    Node node=head;
    while(node!= nullptr)
    {
        i++;
        node=node->next;
    }
	return i;
}
//Theta(nrElements)

bool Set::isEmpty() const {
    if (head== nullptr)
	    return true;
    return false;
}
//Theta(1)

Set::~Set() {
    while (head!= nullptr) {
        Node n = head;
        head=head->next;
        delete[] n;
    }
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}

 void Set::filter(Condition cond) {
    Node node=head;
     while (node!= nullptr)
     {
         Node next=node->next;
         if (!cond(node->info))
         {
             remove(node->info);
         }
         node=next;
     }
 }
//Theta(nrElements)

