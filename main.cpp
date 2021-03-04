#include <iostream>
#include <string>
#include "Collector.h"
using namespace std;
class Collector;
class Node {

public:
    int* ValuePoint= nullptr;
    Node* NodePoint= nullptr;
    void* operator new(std::size_t);
    Node(int a) {
        ValuePoint = (int *) malloc(sizeof(int));
        *ValuePoint = a;
    }

    void operator delete (void* a) ;

    void show(){
    if(ValuePoint!= nullptr){
        cout<<"["<<*ValuePoint<<"]";}
    if(NodePoint!= nullptr){
        NodePoint->show();
    }else{
        cout<<"\n";
        return;
    }
    }

    Node* Del(int a) {
        if(NodePoint== nullptr){
            return this;
        }
        if(*NodePoint->ValuePoint==a){
            return this;
        }else{
            return NodePoint->Del(a);
        }
    };

};

class Collector {
public:
    Node* First=(Node*) malloc(sizeof(Node));
    Collector(){
        First= nullptr;
    };

    void insert(Node* a){
        a->NodePoint = First;
        if(First== nullptr){
            First= a;
        }else{
            First = &*a;}

    }
    void show() {
        cout << "Garbage:\n";
        if (First != nullptr) {
            First->show();
        }
    }
    Node* get(){
            Node* get;
            if(First==nullptr){
                First=(Node*) malloc(sizeof(Node));
                *First= Node(0);
            }
            if (First->NodePoint!= nullptr){
                get=First;
                First=First->NodePoint;
            } else{
                get=First;
                First= nullptr;
            }
            return get;
        }

};

Collector *Garbage= new Collector();

void* Node::operator new(std::size_t) {
    if(Garbage->First!= nullptr){
        return Garbage->get();
    }else{
        Node *node=(Node*) malloc(sizeof(int));
        return node;
    }


}

void Node::operator delete(void* a) {
    Garbage->insert(static_cast<Node *>(a));
}

class List{
    Node* First= nullptr;
    Collector* garbage= Garbage;
public:
    List()= default;;
    void insert(int a){
        Node* get=new Node(a);
        *get->ValuePoint=a;
        get->NodePoint = First;
        First = get;
    };
    void del(int a){
        if(First!= nullptr){
            if (*First->ValuePoint==a){
                Node* PrevDelete=First->NodePoint;
                garbage->insert(First);
                First=PrevDelete;
            }else{
                Node* PrevDelete=First->Del(a);
                Node* Delete=PrevDelete->NodePoint;
                if(Delete== nullptr){
                    return;
                }
                Node* PostDelete=Delete->NodePoint;
                delete Delete;
                if(PostDelete!= nullptr){
                    PrevDelete->NodePoint=PostDelete;}
                else{
                   PrevDelete->NodePoint= nullptr;
                }
            }
        }
    }
    void show(){
        garbage->show();
        cout<<"List:\n";
        if(First!= nullptr){
            First->show();
        }
    }
};

int main() {
    cout <<("hello \n");
    string Action;
    List list= List();
    while (true){
        list.show();
        cout<<("waiting for a command \n");
        cin >>Action;
        string Operator=Action.substr(0,3);
        Action= Action.substr(4,Action.size()-3);
        if (Operator=="add"){
            list.insert(stoi(Action));
        }else if(Operator=="del"){
            list.del(stoi( Action));
        }else if(Operator=="stp"){
            cout<<"stop\n";
            return 0;
        }else{
            cout<< "(add ###)/(del ###)/(stp ###) \n";
        }

    }
    return 0;
}
