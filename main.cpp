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

template<typename Test, template<typename...> class Ref>
struct is_specialization : false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : true_type {};

struct Meeting {
    int ai;
    int si;
    Meeting(int a) :ai(a), si(0) {}
    operator int() { return ai; }
    friend ostream& operator<<(ostream& os, const Meeting& m) {
        os << m.ai << " " << m.si << endl;
        return os;
    }
};

template<typename T>
struct Node {
    shared_ptr<Node> next;
    shared_ptr<Node> prev;
    long long my_id;
    static long long global_id;
    T core;
    Node(T c) :next(nullptr), prev(nullptr) {
        core = c;
        my_id = global_id;
        global_id++;
    }
    Node() = default;
    ~Node() { cout << "Node " << my_id << " is deleted." << endl; }

    friend ostream& operator<<(ostream& os, Node<T>& n) {
        if (is_specialization<T, vector>::value) {
            for (auto it : n.core)
                os << it << endl;
        } else 
            os << n;
        return os;
    }
};

template<typename T>
class CircleList {
private:
    shared_ptr<Node<T>> end_;
    shared_ptr<Node<T>> start_;
    size_t size_;
public:
    CircleList(T core) {
        T first_node_val;
        if (is_specialization<T, vector>::value) {
            first_node_val.push_back(core[0]);
        }
        else {
            first_node_val = core;
        }
        shared_ptr<Node<T>> n = make_shared<Node<T>>(first_node_val);
        start_ = n;
        end_ = n;
        n->next = start_;
        n->prev = end_;
        size_ = 1;

        if (is_specialization<T, vector>::value) {
            auto it = core.begin();
            it++;
            for (; it != core.end(); it++)
                Insert({ *it });
        }
    }

    CircleList(initializer_list<T> ini) :CircleList(*(ini.begin())) {
        auto it = ini.begin();
        it++;
        for (; it != ini.end(); it++)
            Insert(*it);
    }

    ~CircleList() {
        shared_ptr<Node<T>> cur_node = start_;
        while (cur_node != end_) {
            shared_ptr<Node<T>> tmp_node = cur_node;
            cur_node = cur_node->next;
            tmp_node->prev.reset();
            tmp_node->next.reset();
            tmp_node.reset();
        }
        cur_node->prev.reset();
        cur_node->next.reset();
        end_.reset();
        start_.reset();
    }
    size_t size() { return size_; };
    class iterator {
    private:
        shared_ptr<Node<T>> x_;
    public:
        iterator(shared_ptr<Node<T>> n) :x_(n) {};
        iterator& operator++() { x_ = x_->next; return *this; };
        iterator& operator--() { x_ = x_->prev; return *this; };
        iterator& operator+=(int a) {
            for (int i = 0; i < a; i++) { ++(*this); }
            return *this;
        };
        iterator& operator-=(int a) {
            for (int i = 0; i < a; i++) --(*this);
            return *this;
        };
        bool operator!=(const iterator& it) { return x_->my_id != it.x_->my_id; };
        bool operator==(const iterator& it) { return (x_->my_id == it.x_->my_id); };
        operator Node<T>() { return *(x_.get()); };
        shared_ptr<Node<T>> operator->() { return x_; };
        Node<T>& operator*() { return *(x_.get()); };
    };

    iterator begin() { return iterator(start_); };
    iterator end() { return iterator(end_); };

    iterator Insert(iterator pos, T core) {
        iterator my_end = end();
        if (my_end == pos) {
            return Insert(core);
        }
        else {
            iterator it = pos;
            while ((it != my_end) && (pos != it))
                ++it;
            if (it == my_end)
                return iterator(nullptr);
            shared_ptr<Node<T>> n = make_shared<Node<T>>(core);
            n->next = pos->next;
            n->prev = pos;
            pos->next->prev = n;
            pos->next = n;
            size_++;
            return iterator(n);
        }
    }
    iterator Insert(T core) {
        shared_ptr<Node<T>> n = make_shared<Node<T>>(core);
        n->next = start_;
        n->prev = end_;
        start_->prev = n;
        end_->next = n;
        end_ = n;
        size_++;
        return iterator(end_);
    }
};

template<typename T>
class CircleListAdvance : public CircleList<vector<T>> {
private:
    using Base = CircleList<vector<T>>;
    using node_iterator=Base::iterator;
    int grp_size_;
public:
    CircleListAdvance(initializer_list<T> ini) :
        CircleList<vector<T>>(initializer_list<T>(ini.begin() + 1, ini.end())),
        grp_size_(ini.begin()->ai) {
        node_iterator it = Base::begin();
        while (it != Base::end()) {
            it->core[0].si = GetMeetingSum(it);
            ++it;
        }
        it->core[0].si = GetMeetingSum(it);
    }
    int GetMeetingSum(node_iterator it) {
        int s = 0;
        for (int i = 0; i < grp_size_; i++) {
            s += it->core[0].ai;
            ++it;
        }
        return s;
    }
    friend ostream& operator<<(ostream& os, CircleListAdvance<T>& cir) {
        node_iterator it = cir.begin();
        while (it != cir.end()) {
            os << *it;
            ++it;
        }        
        os << *it;
        return os;
    }
};

// New class
// * Each node consists of cartel.
// * Possibility to join nodes.
// * Get sum.
// * Possibility to check neighbouring neighbours.
// * 

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
//#define TEST

#if defined(TEST)
template<> long long Node<int>::global_id = 0;

void TestCircle() {
    CircleList<int> cir(1);
    cir.Insert(2);
    cir.Insert(3);
    cir.Insert(4);

    {
        CircleList<int>::iterator it = cir.begin();
        it = cir.Insert(it, 10);
        it += 2;
        it = cir.Insert(it, 30);
        it += 1;
        it = cir.Insert(it, 40);
        it = cir.begin();
        it += (cir.size() - 1);
        cir.Insert(it, 50);
    }

    CircleList<int>::iterator it = cir.begin();
    for (int i = 0; i < 19; i++) {
        cout << it->core << endl;
        ++it;
    }
    cout << endl << endl;
    for (int i = 0; i < 18; i++) {
        cout << it->core << endl;
        --it;
    }
};

#endif
//void Algorithm(const Circle& cir, vector<vector<int>> solution){
//    int q = cir.GetValue();
//    map<int, int> meetings;
//    for (int i = 0; i < cir.GetSize(); i++){
//        meetings.emplace(make_pair(i, cir.GetSum(i)));
//    }
//    for (auto& i: meetings)
//        cout << i.first << " " << i.second << endl;
//    
//    cout << endl << endl;
//    while (!meetings.empty()){
//        auto t = max_element(meetings.begin(), meetings.end(), [](auto l, auto r){return l.second < r.second;});
//        cout << t->first << " " << t->second << endl;
//        // Remove meetings with participants of current meeting.
//        for (int i = t->first+1; i < t->first + cir.GetK(); i++)
//            meetings.erase(i);
//        for (int i = t->first-cir.GetK(); i < t->first; i++)
//            meetings.erase(i);
//        meetings.erase(t);
//    }
//};

#if !defined(TEST)
template<> long long Node<vector<Meeting>>::global_id = 0;
#endif

int main() {
#if !defined(TEST)
    CircleListAdvance<Meeting> cir{ 3, 2, 6, 1, 10, 3, 2 };
    cout << cir << endl;
    vector<vector<int>> solution;
    //Algorithm(cir, solution);
#else
    {
        cout << "Tests are running" << endl;
        TestCircle();
        cout << "Tests passed" << endl;
    }
#endif
    return 0;
}
