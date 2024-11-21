#include <iostream>
using namespace std;

// 定义共用体
union Data {
    int i;       // 整型成员
    float f;     // 浮点型成员
    char c;      // 字符型成员
};

int main() {
    Data data;

    data.i = 42;      // 设置整型值
    cout << "Integer: " << data.i << endl;

    data.f = 3.14;    // 设置浮点型值
    cout << "Float: " << data.f << endl;

    data.c = 'A';     // 设置字符型值
    cout << "Char: " << data.c << endl;

    // 访问前一个成员的值（未定义行为，可能输出错误）
    cout << "Integer after modifying Char: " << data.i << endl;

    return 0;
}
