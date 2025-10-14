#include <iostream>
using namespace std;

struct StrangeMatrix {
    int first_line[3];
    int second_line[3];
    int third_line[3];
};

StrangeMatrix transpose(StrangeMatrix m) {
    StrangeMatrix result;
    
    result.first_line[0] =m.first_line[0];
    result.first_line[1] =m.second_line[0];
    result.first_line[2] =m.third_line[0];
    
    result.second_line[0] =m.first_line[1];
    result.second_line[1] =m.second_line[1];
    result.second_line[2] =m.third_line[1];

    result.third_line[0] =m.first_line[2];
    result.third_line[1] =m.second_line[2];
    result.third_line[2] =m.third_line[2];
    
    return result;
}

int main()
{
    struct StrangeMatrix m;
    cin >> m.first_line[0] >> m.first_line[1] >> m.first_line[2];
    cin >> m.second_line[0] >> m.second_line[1] >> m.second_line[2];
    cin >> m.third_line[0] >> m.third_line[1] >> m.third_line[2];
    struct StrangeMatrix t = transpose(m);
    cout << t.first_line[0] << " " << t.first_line[1] << " " << t.first_line[2] << endl;
    cout << t.second_line[0] << " " << t.second_line[1] << " " << t.second_line[2] << endl;
    cout << t.third_line[0] << " " << t.third_line[1] << " " << t.third_line[2] << endl;
    return 0;
}