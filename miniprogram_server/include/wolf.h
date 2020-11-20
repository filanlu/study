#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <cstdlib>
using std:: unordered_map;
using std:: string;
using std:: vector;
using std:: cout;
using std:: endl;
using std:: mutex;
using std:: lock_guard;
class wolf
{
private:
    mutex _mtx;
    unordered_map<string, int> peizhi;//配置
    vector<string>card;

public:
    wolf(const unordered_map<string, int>&peizhi);
    wolf();
    wolf & operator=(const wolf&another);
    string get_card();
    ~wolf();
};