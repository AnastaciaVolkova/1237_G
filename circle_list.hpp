#include <vector>
#include <initializer_list>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <cmath>
#include <memory>
#include <iostream>

using namespace std;

template<typename T>
struct Node {
    shared_ptr<Node<T>> next;
    shared_ptr<Node<T>> prev;
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
        os << n.core;
        return os;
    }
};

template<typename T>
class CircleList {
private:
    shared_ptr<Node<T>> start_;
    shared_ptr<Node<T>> end_;
    size_t size_;
public:
    CircleList(T core) {
        shared_ptr<Node<T>> n = make_shared<Node<T>>(core);
        start_ = n;
        end_ = n;
        n->next = start_;
        n->prev = end_;
        size_ = 1;
    }

    CircleList(vector<T> core){
        shared_ptr<Node<T>> n = make_shared<Node<T>>(core[0]);
        start_ = n;
        end_ = n;
        n->next = start_;
        n->prev = end_;
        size_ = 1;

        auto it = core.begin();
        it++;
        for (; it != core.end(); it++)
            Insert({ *it });

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
        iterator():x_(nullptr){};
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
        bool operator<(const iterator& it) const { return x_->my_id < it.x_->my_id; };
        operator Node<T>() { return *(x_.get()); };
        operator shared_ptr<Node<T>>(){return x_;};
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

    friend ostream& operator<<(ostream& os, CircleList<T>& cir) {
        CircleList::iterator it = cir.begin();
        while (it != cir.end()) {
            os << *it << " ";
            ++it;
        }
        os << *it;
        return os;
    }

};

// * Each node consists of cartel.
// * Possibility to join nodes.
// * Get sum.
// * Possibility to check neighbouring neighbours.
// *
template<typename T>
class CircleListAdvance: public CircleList<T> {
private:
    int m_size_; // Meeting size.
    int m_balance_v_; // Balance value.
public:
    using iterator=typename CircleList<T>::iterator;

    struct MeetingSum{
        iterator nei; // First neighbour in the meeting.
        int sum;      // Summary of meeting.
        bool operator<(const MeetingSum& ms)const {return sum < ms.sum;};
    };

    using PQueue=priority_queue<MeetingSum>;

    CircleListAdvance(initializer_list<T> ini): CircleList<T>(vector<T>(ini.begin()+1, ini.end())){
        m_size_ = *ini.begin();
        int s = 0;
        auto it = CircleList<T>::begin();
        while(it != CircleList<T>::end()){
            s += it->core;
            ++it;
        }
        s += it->core;
        m_balance_v_ = s/CircleList<T>::size();
    }

    // Computes sum for each possible meeting.
    // out: map with sum.
    void ComputeSums(PQueue& m_sums){
        auto it = CircleList<T>::begin();
        while (it != CircleList<T>::end()){
           m_sums.push({it, GetSum(it)});
            ++it;
        }

        m_sums.push({it, GetSum(it)});
        ++it;
    }

    T GetSum(typename CircleList<T>::iterator pos){
        int s = 0;
        auto it_c = pos;
        for (int i = 0; i < m_size_; i++){
            s += it_c->core;
            ++it_c;
        }
        return s;
    }

    // Make all items in meeting balanced.
    // Return iterator to unbalanced elements.
    // If meeting elements couldn't be balanced, return nullptr.
    // pos - start of the group.
    iterator Balance(iterator pos){
        int s = GetSum(pos);
        if (s < m_balance_v_*m_size_)
            return iterator(nullptr);
        for (int i = 0; i < m_size_-1; i++) {
            pos->core = m_balance_v_;
            ++pos;
        }
        pos->core = s - m_balance_v_*(m_size_-1);
        return pos;
    }
    
    int size(){return m_size_; };
};

