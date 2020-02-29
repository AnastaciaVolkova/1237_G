//#include "CircleList.hpp"
/*template<typename T>
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
**/
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
//template<> long long Node<vector<Meeting>>::global_id = 0;
#endif

int main() {
    
#if !defined(TEST)
    //CircleListAdvance<Meeting> cir{ 3, 2, 6, 1, 10, 3, 2 };
    //cout << cir << endl;
    //vector<vector<int>> solution;
    //Algorithm(cir, solution);
#else
#endif
    return 0;
}
