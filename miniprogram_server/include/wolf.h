#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <cstdlib>
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::string;
using std::unordered_map;
using std::vector;

class wolf
{
private:
    mutex _mtx;
    unordered_map<string, int> peizhi; //配置
    vector<string> card;

public:
    wolf(const unordered_map<string, int> &peizhi);
    wolf();
    wolf &operator=(const wolf &another);
    string get_card();
    int size();
    ~wolf();
};
void delete_room(int roomid, unordered_map<int, wolf> &room); //房间号，狼人房。
