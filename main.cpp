#include <iostream>
#include <string>
#include "Collector.h"
using namespace std;
class Node {

public:
    int* ValuePoint= nullptr;
    Node* NodePoint= nullptr;
    Node(int a) {
        ValuePoint=(int*) malloc(sizeof(int));
        *ValuePoint=a;

    };

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

};

class Collector {
public:
    Node* First=(Node*) malloc(sizeof(Node));
    Collector(){
        First= nullptr;
    };
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
    void insert(Node* a){
        a->NodePoint = First;
        if(First== nullptr){
            First= a;
        }else{
            First = &*a;}

    }
    void show(){
        cout<<"Garbage:\n";
        if (First!= nullptr){
            First->show();
        }
    }

};


class List{
    Node* First= nullptr;
    Collector* garbage= (Collector*)malloc(sizeof (Collector));
public:
    List(Collector a){
        *garbage=a;
    };
    void insert(int a){
        Node* get=garbage->get();
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
                Node* trash=new Node(0);
                *trash=*Delete;
                garbage->insert(trash);
                if(PostDelete!= nullptr){
                    *Delete=*PostDelete;}
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
    Collector Garbage= Collector();
    List list= List(Garbage);
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
