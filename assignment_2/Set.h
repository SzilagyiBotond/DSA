#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;
typedef bool(*Condition)(TElem);
class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    private:
//
//		Node* head;
//        Node* tail;
//        Node* nodes;
//        int capacity;
//        int nrElements;
        struct DLLNode;
        typedef DLLNode *Node;
        Node head;
        Node tail;

    public:
        //implicit constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set, and it was not added)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        bool search(TElem elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;

        // destructor
        ~Set();

        void filter(Condition cond);

};
struct Set::DLLNode{
    TElem info;
    Node prev;
    Node next;
    DLLNode(TElem e, Node n ,Node p);
};




