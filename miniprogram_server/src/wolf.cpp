#include "../include/wolf.h"

wolf::wolf() {}

wolf::wolf(const unordered_map<string, int> &hapi)
{
    srand(time(0));
    peizhi = hapi;
    for (auto p : peizhi)
    {
        while (p.second != 0)
        {
            card.push_back(p.first);
            --p.second;
        }
    }
    int size = card.size();
    for (int i = 0; i < size; ++i)
    {
        int j = rand() % (size - i) + i;
        std::swap(card[i], card[j]);
    }
    for (auto s : card)
    {
        cout << s << endl;
    }
}
wolf &wolf::operator=(const wolf &another)
{
    if (this == &another)
    {
        return *this;
    }
    else
    {
        this->peizhi = another.peizhi;
        this->card = another.card;
        return *this;
    }
}
string wolf::get_card()
{
    lock_guard<mutex> _lg(_mtx);
    string s = *(card.end() - 1);
    card.pop_back();
    return s;
}
int wolf::size()
{
    return card.size();
}
void delete_room(int roomid, unordered_map<int, wolf> &room) //房间号，狼人房。
{
    room.erase(roomid);
}
wolf::~wolf()
{
}