#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	lines=nrLines;
    columns=nrCols;
    firstFree=0;
    capacity=2;
    values=new TElem[capacity];
    left=new int[capacity];
    right=new int[capacity];
    root=-1;
    nrColumn=new int[columns];
    for (int i = 0; i < columns; ++i) {
        nrColumn[i]=0;
    }
    positions=new std::pair<int,int>[capacity];
    for (int i = 0; i < capacity; ++i) {
        values[i]=NULL_TELEM;
        left[i]=-1;
        right[i]=-1;
        positions[i]=NULL_position;
    }
}
//Theta(1)

int Matrix::nrLines() const {
	return lines;
}
//Theta(1)

int Matrix::nrColumns() const {
	return columns;
}
//Theta(1)

TElem Matrix::element(int i, int j) const {

    if(i<0 or j<0 or i>=lines or j>=columns)
        throw exception();
    bool found=false;
    int current=root;
    while(current!=-1 && !found){
        if (positions[current].first==i && positions[current].second==j)
            found= true;
        else if (this->relation(i,j,positions[current].first,positions[current].second))
            current=left[current];
        else
            current=right[current];
    }
    if (found)
        return values[current];
    return NULL_TELEM;
}
//Theta(logFirstFree)
TElem Matrix::modify(int i, int j, TElem e) {
    if(i<0 or j<0 or i>=lines or j>=columns)
        throw exception();
    if (firstFree==capacity)
        resize();
    if (root==-1)
    {
        root=0;
        firstFree++;
        values[root]=e;
        positions[root]=std::pair<int,int>(i,j);
        nrColumn[j]+=1;
        return NULL_TELEM;
    }
    TElem toReturn=NULL_TELEM;
    addElem(i,j,e,root,-1,toReturn);
    return toReturn;

}
//Theta(logFirstFree) - Best case
//Theta(FirstFree) - Worst case
void Matrix::addElem(int i, int j, TElem e, int pos,int father,TElem& torReturn) {
    if (pos==-1) {
        values[firstFree] = e;
        positions[firstFree]=std::pair<int,int>(i,j);
        nrColumn[j]+=1;
        if (relation(i, j, positions[father].first, positions[father].second))
            left[father]=firstFree;
        else
            right[father]=firstFree;
        firstFree++;
        torReturn=NULL_TELEM;
    } else {
        if (positions[pos].first == i && positions[pos].second == j) {
            torReturn = values[pos];
            values[pos] = e;
        } else {
            if (relation(i, j, positions[pos].first, positions[pos].second))
                addElem(i, j, e, left[pos], pos, torReturn);
            else
                addElem(i, j, e, right[pos], pos, torReturn);

        }
    }
}
//Theta(logFirstFree)
void Matrix::resize() {
    TElem* newValues=new TElem[capacity*2];
    position* newPositions=new position[capacity*2];
    int* newLeft=new int[capacity*2];
    int* newRight=new int[capacity*2];
    for (int i = 0; i < capacity*2; ++i) {
        newValues[i]=NULL_TELEM;
        newPositions[i]=NULL_position;
        newLeft[i]=-1;
        newRight[i]=-1;
    }
    for (int i = 0; i < capacity; ++i) {
        newValues[i]=values[i];
        newPositions[i].first=positions[i].first;
        newPositions[i].second=positions[i].second;
        newLeft[i]=left[i];
        newRight[i]=right[i];
    }
    capacity=capacity*2;
    delete[] values;
    delete[] positions;
    delete[] left;
    delete[] right;
    values=newValues;
    left=newLeft;
    right=newRight;
    positions=newPositions;
}
//Theta(capacity*2)
bool Matrix::relation(int i1, int j1, int i2, int j2) const {
    if (i1==i2)
        return j2<=j1;
    return i2<i1;
}
//Theta(1)
Matrix::~Matrix() {
    delete[] values;
    delete[] positions;
    delete[] left;
    delete[] right;
}

int Matrix::numberOfNonZeroElems(int col)const {
    if (col>=columns || col<0)
        throw exception();
//    int nr=0;
//    for(int i=0;i<firstFree;i++){
//        if (positions[i].second==col)
//            nr++;
//    }
//    return nr;9
    return nrColumn[col];
}
//Theta(1)

