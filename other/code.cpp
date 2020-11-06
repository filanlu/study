#include<iostream>
#include <algorithm>
#include <vector>
using namespace std;
int specialArray(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int left = 0,right = nums.size()-1;
        int ret = 1;
       if(right == -1 || !nums[right])return -1; 
        while(left < right){
            if(ret > nums[left]) left++;
            else{
                if((right - left + 1) > ret) ret++;
                else if((right - left + 1) == ret) return ret;
                else return -1;
            }
        }
        return ret;
    }
int main(){
vector<int> nums ={1,1,2};
int res = specialArray(nums);
cout<<res;
}
