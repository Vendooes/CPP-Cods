#include <iostream>
using namespace std;
struct Vector {
    int x, y, z;
};
Vector sum(Vector a,Vector b) {
    Vector result;
    result.x =a.x +b.x;
    result.y =a.y +b.y;
    result.z =a.z +b.z;
    return result;
}
const int N = 10;
int main()
{
    Vector res = {0, 0, 0};

    for (int i=0; i<N; i++)
    {
        Vector tmp;
        cin >> tmp.x >> tmp.y >> tmp.z;
        res = sum(res, tmp);
    }
    cout << res.x << " " << res.y << " "<< res.z << endl;
    return 0;
}