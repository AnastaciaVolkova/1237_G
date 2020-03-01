#include <set>
#include "circle_list.hpp"

template<>
long long Node<int>::global_id = 0;

int main() {
    CircleListAdvance<int> cir = {3, 2, 6, 1, 10, 3, 2};
    CircleListAdvance<int>::PQueue mm;
    cir.ComputeSums(mm);
    set<CircleListAdvance<int>::MeetingSum> me_inv; // Meetings which sums were invalidated.
    set<CircleListAdvance<int>::iterator> nei_inv; // Neighbours who already has taken part in meetings.

    CircleListAdvance<int>::MeetingSum a;

    while (!mm.empty()) {
        a = mm.top();
        mm.pop();

        if (me_inv.find({ a.nei, a.sum }) == me_inv.end()) {
            cir.Balance(a.nei);
            CircleListAdvance<int>::iterator it = a.nei;
            nei_inv.insert(it);
            ++it;
            for(int i = 1; i < cir.size(); i++){
                me_inv.insert(a);
                nei_inv.insert(it);
                mm.push({it, cir.GetSum(it)});
                ++it;
            }
            cout << cir << endl;
        }
    }
    return 0;
}
