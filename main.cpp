#include <set>
#include "circle_list.hpp"

template<>
long long Node<int>::global_id = 0;

int main() {
    CircleListAdvance<int> cir = {3, 2, 6, 1, 10, 3, 2};
    CircleListAdvance<int>::PQueue mm;
    cir.ComputeSums(mm);
    set<CircleListAdvance<int>::iterator> me_inv; // Meetings which sums were invalidated.

    CircleListAdvance<int>::MeetingSum a;

    while (!mm.empty()) {
        a = mm.top();
        mm.pop();

        if (me_inv.find(a.nei) == me_inv.end()){
            cir.Balance(a.nei);
            CircleListAdvance<int>::iterator it = a.nei;
            ++it;
            for(int i = 1; i < cir.size(); i++){
                mm.push({it, cir.GetSum(it)});
                ++it;
            }
            cout << cir << endl;
        }
    }
    return 0;
}
