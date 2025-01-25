## 二分查找
### 704

```c++
class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int l = 0, h = len - 1, mid = (l + h) >> 1;

        while (l < h) {
            mid = (l + h) >> 1;
            if(nums[mid] == target)
                return mid;
            else if (nums[mid] < target) {
                l = mid + 1;
            }
            else
                h = mid - 1;
        }
        return nums[l] == target ? l : -1;
    }
};
```

### 744

```c++
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int len = letters.size();
        int l = 0, h = len - 1, mid = (l + h) >> 1;

        while(l < h){
            mid = (l + h) >> 1;
            if(letters[mid] > target){
                h = mid;
            }
            else{
                l = mid + 1;
            }
        }
        return letters[h] > target ? letters[h] : letters[0];
    }
};
```

## 链表

### 206

```c++
class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;

        while (cur) {
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};
```

### 142

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* f = head; //2
        ListNode* s = head; //1

        while(f != nullptr && f -> next != nullptr){
            f = f -> next -> next;
            s = s -> next;
            if(f == s){
                ListNode* k1 = head;
                ListNode* k2 = f;
                while(k1 != k2){
                    k1 = k1 -> next;
                    k2 = k2 -> next;
                }
                return k1;
            }
        }
        return nullptr;
    }
};
```

## 归并排序

### LCR 170

```c++
class Solution {
public:
    int gb(vector<int>& a, vector<int>& b, int l, int r) {
        if (l >= r) {
            return 0;
        }
        int mid = (l + r) >> 1;
        int cnt = gb(a, b, l, mid) + gb(a, b, mid + 1, r);
        int i = l, j = mid + 1;
        int pos = l;

        while (i <= mid && j <= r) {
            if (a[i] > a[j]) {
                b[pos++] = a[j++];
                cnt += (mid - i + 1);
            } else {
                b[pos++] = a[i++];
            }
        }
        while (i <= mid) {
            b[pos++] = a[i++];
        }
        while (j <= r) {
            b[pos++] = a[j++];
        }
        copy(b.begin() + l, b.begin() + r + 1, a.begin() + l);
        return cnt;
    }
    int reversePairs(vector<int>& record) {
        int len = record.size();
        vector<int> b(len, 0);
        return gb(record, b, 0, len - 1);
    }
};
```

## 快速排序

### 912

```c++
class Solution {
public:
    int dpos(vector<int>& nums, int l, int h) {
        int pivot = nums[l];
        
        while (l < h) {
            while (nums[h] >= pivot && l < h) {
                h--;
            }
            nums[l] = nums[h];
            while (nums[l] <= pivot && l < h) {
                l++;
            }
            nums[h] = nums[l];
        }
        nums[l] = pivot;
        return l;
    }
    //官方题解中的取随机数为pivot，发现不用这个就一直时间超限
    int rdpos(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;
        swap(nums[r], nums[i]);
        return dpos(nums, l, r);
    }
    void quickSort(vector<int>& nums, int l, int h) {
        while (l < h) {
            int pos = rdpos(nums, l, h);
            if (pos - 1 < h - pos) {
                quickSort(nums, l, pos - 1);
                l = pos + 1;
            }
            else {
                quickSort(nums, pos + 1, h);
                h = pos - 1;
            }
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        int l = 0, h = nums.size() - 1;
        quickSort(nums, l, h);
        return nums;
    }
};
```

## 二叉树

### 104

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int t = 0;
        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()) {
            int size = qu.size();
            t++;
            for (int i = 0; i < size; i++) {
                TreeNode* node = qu.front();
                qu.pop();
                if (node->left) qu.push(node->left);
                if (node->right) qu.push(node->right);
            }
        }
        return t;
    }
};
```

### 101

```c++
class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right != nullptr) return false;
        else if (left != nullptr && right == nullptr) return false;
        else if (left == nullptr && right == nullptr) return true;
        else if (left->val != right->val) return false;
        bool out = compare(left->left, right->right); 
        bool in = compare(left->right, right->left);    
        bool ans = out && in;                    
        return ans;
    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        else return compare(root->left, root->right);
    }
};
```

### 105

```c++
```

### 106

```c++

```

## 回溯算法

### 78

```c++
class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>nums, int startIndex){
        result.push_back(path);
        if(startIndex > nums.size() - 1){
            return;
        }
        for(int i = startIndex; i <= nums.size() - 1; i++){
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
        return;
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
```

### 46

```c++
class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums, vector<int>& flag){
        if(path.size() == nums.size()){
            result.push_back(path);
            return;
        }
        for(int i = 0; i <= nums.size()-1; i++){
            if(flag[i]) continue;
            flag[i] = 1;
            path.push_back(nums[i]);
            backtracking(nums, flag);
            path.pop_back();
            flag[i] = 0;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> flag(nums.size(), 0);
        backtracking(nums, flag);
        return result;
    }
};
```

### 47

```c++
class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums, vector<int>& flag) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i <= nums.size() - 1; i++) {
            if (flag[i] || (i > 0 && nums[i] == nums[i-1] && flag[i-1] == 0))
                continue;
            flag[i] = 1;
            path.push_back(nums[i]);
            backtracking(nums, flag);
            path.pop_back();
            flag[i] = 0;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> flag(nums.size(), 0);
        sort(nums.begin(), nums.end());
        backtracking(nums, flag);
        return result;
    }
};
```

### 51

```c++
class Solution {
public:
    vector<vector<string>> result;
    int qc(int row, int col, vector<string> &sc, int n) {
        for (int i = 0; i < row; i++) {
            if (sc[i][col] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (sc[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (sc[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void backtracking(vector<string> &sc, int n, int row) {
        if (row == n) {
            result.push_back(sc);
            return;
        }
        for (int j = 0; j < n; j++) {
            if (qc(row, j, sc, n)) {
                sc[row][j] = 'Q';
                backtracking(sc, n, row + 1);
                sc[row][j] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
       vector<string> sc(n, string(n, '.'));
        backtracking(sc, n, 0);
        return result;
    }
};
```



## 动态规划

### 53

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int res = dp[0];

        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            if (dp[i] > res)
                res = dp[i];
        }
        return res;
    }
};
```

### 300

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1)
            return nums.size();
        vector<int> dp(nums.size(), 1);
        int res = 0;

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            if (dp[i] > res)
                res = dp[i];
        }
        return res;
    }
};
```

### 70

```c++
class Solution {
public:
    int climbStairs(int n) {
        if(n == 1 || n == 0) return 1;
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; i++){
            dp[i] = dp[i-1] +dp[i-2];
        }
        return dp[n];
    }
};
```

### 55

```c++
```

### 5

```c++
```

### 322

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, 1e9);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) { 
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j - coins[i]] != 1e9) {
                    dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
                }
            }
        }
        if (dp[amount] == 1e9) return -1;
        return dp[amount];
    }
};
```

























