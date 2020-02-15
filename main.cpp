#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <numeric>
#include <map>
#include <queue>
#include <tuple>
#include <cmath>
#include <memory>

using namespace std;

template<typename T>
struct Node{
    Node* next;
    Node* prev;
    static long long id;
    T core;
    Node(T c){
        core = c;
        id++;
    }
};

template<typename T> 
class CircleList{
private:
    Node<T>* end_;
    Node<T>* start_;
    size_t size_;
public:
    CircleList(T core){
        Node<T>* n = new Node<T>(core);
        start_ = n;
        end_ = n;
        n->next = start_;
        n->prev = end_;
    }
    size_t size(){return size_;};
    class iterator{
    private:
        Node<T>* x_;
    public:
        iterator(Node<T>* n):x_(n){};
        iterator& operator++(){ x_ = x_->next; return *this;};
        iterator& operator--(){ x_ = x_->prev; return *this;};
        iterator& operator+=(int a){
            for (int i = 0; i < a; i++) ++(*this);
            return *this;
        };
        iterator& operator-=(int a){
            for (int i = 0; i < a; i++) ++(*this);
            return *this;
        };
        bool operator!=(iterator& it){return x_->id != it.x_->id;};
        bool operator==(iterator& it){return x_->id ==it.x_->id;};
        operator Node<T>* (){return x_;};
        Node<T>* operator->(){return x_;};
    };

    iterator begin(){return iterator(start_);};
    iterator end(){return iterator(end_);};

    iterator Insert(iterator pos, T core){
        iterator it = begin();
        if (pos == end()){
            Insert(core);
        }
        else{
            while((it != end())&&(pos != it))
                ++it;
            if (it == end())
               return nullptr;
        }
        Node<T>* n = new Node<T>(core);        
        n->next = pos->next;
        n->prev = pos;
        pos->next->prev = n;
        pos->next = n;
        size_++;            
        return iterator(n);
    }
    iterator Insert(T core){
        Node<T>* n = new Node<T>(core);
        n->next=start_;
        n->prev=end_;
        start_->prev = n;
        end_->next = n;
        end_ = n;
        size_++;
        return iterator(end_);
    }

};

/*
class Circle{
private:
    vector<int> a_; // Number of stones.
    int k_; // Size of meeting.
public:
    Circle(initializer_list<int> ka){
        auto it = ka.begin();
        k_ = *it++;
        a_.resize(ka.size()-1);
        copy(ka.begin()+1, ka.end(), a_.begin());
    };
    int GetSum (int pos) const{
        int n = a_.size();
        int k = 0;
        int s = 0;
        while(k < k_){
            s += a_[pos];
            k++;
            pos++;
            if (pos == n)
                pos = 0;
        }
        return s;
    };
    int GetValue() const {return accumulate(a_.begin(), a_.end(), 0)/a_.size();};
    int GetSize() const {return a_.size();};
    int GetK() const {return k_;};
    bool IsIntersect(int i, int j) const {
        int dif = abs(i - j)/a_.size();
        return dif < k_;
    };
};
*/

template<> long long Node<int>::id = 0;

void Algorithm(/*const Circle& cir, vector<vector<int>> solution*/){
    CircleList<int> cir(1);
    
    cir.Insert(2);
    cir.Insert(3);
    cir.Insert(4);

    {
        CircleList<int>::iterator it = cir.begin();
        it = cir.Insert(it, 10);
        it+=2;
        it = cir.Insert(it, 30);
        it += 1;
        it = cir.Insert(it, 40);
        it = cir.begin();
        it += (cir.size() - 1);
        cir.Insert(it, 50);
    }

    CircleList<int>::iterator it = cir.begin();
    for (int i = 0; i < 19; i++){
        cout << it->core << endl;
        ++it;
    }
    cout << endl << endl;
    for (int i = 0; i < 18; i++){
        cout << it->core << endl;
        --it;
    }
    

    /*int q = cir.GetValue();
    map<int, int> meetings;
    for (int i = 0; i < cir.GetSize(); i++){
        meetings.emplace(make_pair(i, cir.GetSum(i)));
    }
    for (auto& i: meetings)
        cout << i.first << " " << i.second << endl;
    
    cout << endl << endl;
    while (!meetings.empty()){
        auto t = max_element(meetings.begin(), meetings.end(), [](auto l, auto r){return l.second < r.second;});
        cout << t->first << " " << t->second << endl;
        // Remove meetings with participants of current meeting.
        for (int i = t->first+1; i < t->first + cir.GetK(); i++)
            meetings.erase(i);
        for (int i = t->first-cir.GetK(); i < t->first; i++)
            meetings.erase(i);
        meetings.erase(t);
    }i*/
};

int main(){
    //Circle cir{3, 2, 6, 1, 10, 3, 2};
    //vector<vector<int>> solution;
    //Algorithm(cir, solution);
    Algorithm();
    return 0;
}
