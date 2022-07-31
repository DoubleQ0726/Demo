#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>

#define qq20

#ifdef qq01
int main()
{
    std::string str = "192.168.1.1";

    std::regex expression("([0-9]+).([0-9]+).([0-9]+)");
    std::smatch what;

    if(std::regex_search(str, what, expression))
    {
        std::cout << what.size() << std::endl;
        for(size_t i = 0; i < what.size(); i++)
        {
            if(what[i].matched)
            {
                std::cout << what[i] << std::endl;
            }
        }
    }
    return 0;
}
#endif


//单例模式
#ifdef qq02
// 双检查锁单例模式
template<typename T>
class Singleton
{
public:
    static T* GetInstance()
    {
        if (s_instance == nullptr)
        {
            std::unique_lock<std::mutex> lock(s_mutex);
            if (s_instance == nullptr)
            {
                s_instance = std::unique_ptr<T>(new T());
            }
        }
        return s_instance.get();
    }
private:
    static std::unique_ptr<T> s_instance;
    static std::mutex s_mutex;
};
template<typename T>
std::unique_ptr<T> Singleton<T>::s_instance;
template<typename T>
std::mutex Singleton<T>::s_mutex;


struct Student
{
    friend class Singleton<Student>;
    Student()
    {

    }

    void Init(const std::string& name, int age)
    {
        m_name = name;
        m_age = age;
    }

    std::string m_name;
    int m_age;
};

int main(int argc, char** argv)
{
    Student* st = Singleton<Student>::GetInstance();
    st->Init("szq", 25);
    std::cout << "name = " << st->m_name << " age = " << st->m_age << std::endl;
    std::cout << st << std::endl;

    Student* stCopy = Singleton<Student>::GetInstance();
    std::cout << "name = " << stCopy->m_name << " age = " << stCopy->m_age << std::endl;
    std::cout << stCopy << std::endl;

    return 0;
}
#endif

//排序一览
#ifdef qq03
int partation(std::vector<int>& arrs, int left, int right)
{
    int num = arrs[left];
    while (left < right)
    {
        while (left < right && num <= arrs[right])
        {
            --right;
        }
        arrs[left] = arrs[right];
        while (left < right && num >= arrs[left])
        {
            ++left;
        }
        arrs[right] = arrs[left];
    }
    arrs[left] = num;
    return left;
}

void quickSort(std::vector<int>& arrs, int left, int right)
{
    if (left < right)
    {
        int mid = partation(arrs, left, right);
        quickSort(arrs, left, mid - 1);
        quickSort(arrs, mid + 1, right);
    }
}

void adjustDown(std::vector<int>& arrs, int index, int size)
{
    int l = 2 * index + 1;
    int num = arrs[index];
    for (; l < size; index = l, l = 2 * index + 1)
    {
        if (l + 1 < size && arrs[l] < arrs[l + 1])
            ++l;
        if (l < size && arrs[l] > num)
        {
            arrs[index] = arrs[l];
        }
        else
            break;
    }
    arrs[index] = num;
}

void makeHeap(std::vector<int>& arrs)
{
    int size = arrs.size();
    for (int i = size / 2 - 1; i >= 0; --i)
    {
        adjustDown(arrs, i, size);
    }
}

void Merge(std::vector<int>& arrs, int left, int mid, int right, std::vector<int>& temp)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right)
    {
        if (arrs[i] <= arrs[j])
            temp[k++] = arrs[i++];
        else
            temp[k++] = arrs[j++];
    }

    while (i <= mid)
    {
        temp[k++] = arrs[i++];
    }
    while (j <= right)
    {
        temp[k++] = arrs[j++];
    }
    //复制回原数组
    k = 0;
    while (left <= right)
    {
        arrs[left++] = temp[k++]; 
    }
}

void MergeSort(std::vector<int>& arrs, int left, int right, std::vector<int>& temp)
{
    int mid = (left + right) / 2;
    if (left < right)
    {
        MergeSort(arrs, left, mid, temp);
        MergeSort(arrs, mid + 1, right, temp);
        Merge(arrs, left, mid, right, temp);
    }
}

int main(int argc, char** argv)
{
    std::vector<int> arrs = {5, 6, 8, 2, 3, 9, 7, 15};
    int size = arrs.size();
    //冒泡排序  54321
    // for (int i = 0; i < size - 1; ++i)
    // {
    //     bool flag = false;
    //     for (int j = 0; j < size - i - 1; ++j)
    //     {
    //         if (arrs[j] > arrs[j + 1])
    //         {
    //             std::swap(arrs[j], arrs[j + 1]);
    //             flag = true;
    //         }
    //     }
    //     if (!flag)
    //         break;
    // }

    //插入排序 54321
    // for (int i = 1; i < size; ++i)
    // {
    //     for (int j = i - 1; j >= 0; --j)
    //     {
    //         if (arrs[j] > arrs[j + 1])
    //             std::swap(arrs[j], arrs[j + 1]);
    //     }
    // }

    //希尔排序(不稳定)
    // for (int d = size / 2; d >= 1; d = d / 2)
    // {
    //     for (int i = d; i < size; i += d)
    //     {
    //         for (int j = i - d; j >= 0; j -= d)
    //         {
    //             if (arrs[j] > arrs[j + d])
    //                 std::swap(arrs[j], arrs[j + d]);
    //         }
    //     }
    // }

    //选择排序(不稳定) 54321
    // for (int i = 0; i < size; ++i)
    // {
    //     int min = i;
    //     for (int j = i; j < size; ++j)
    //     {
    //         if (arrs[min] > arrs[j])
    //             min = j;
    //     }
    //     std::swap(arrs[i], arrs[min]);
    // }

    //快速排序(不稳定)
    //quickSort(arrs, 0, size - 1);

    //堆排序(不稳定)
    // makeHeap(arrs);
    // for (int i = size - 1; i >= 1; --i)
    // {
    //     std::swap(arrs[0], arrs[i]);
    //     adjustDown(arrs, 0, i);
    // }

    //归并排序
    std::vector<int> temp(arrs);
    MergeSort(arrs, 0, size - 1, temp);
    for (auto& item : arrs)
    {
        std::cout << item << std::endl;
    }

    return 0;
}
#endif

//Unix时间戳
#ifdef qq04
//2020-6-25 19:11:50 ==> Unix TimeStamp
time_t GetUnixTimeStamp()
{
    int times[6] = {2020, 6, 25, 19, 11, 50};
    time_t timeStamp = 0;
    struct tm time;
    time.tm_year = times[0] - 1900;
    time.tm_mon = times[1] - 1;
    time.tm_mday = times[2];
    time.tm_hour = times[3];
    time.tm_min = times[4];
    time.tm_sec = times[5];
    timeStamp = mktime(&time);
    return timeStamp;
}

void UnixTimeStampToTime(time_t timeStamp)
{
    struct tm* time;
    time = localtime(&timeStamp);
    std::cout << time->tm_year + 1900 << "-" << time->tm_mon + 1 << "-" << time->tm_mday << " "
              << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << std::endl;
}

int main(int argc, char** argv)
{
    time_t result = GetUnixTimeStamp();
    std::cout << result << std::endl;
    UnixTimeStampToTime(result);
    return 0;
}
#endif

//知识点梳理
#ifdef qq05

#define OFFSETOF(s, m) (size_t)&(((s*)(0))->m)
int main(int argc, char** argv)
{
    struct alignas(4) Info2 
    {
        uint8_t a;
        uint16_t b;
        uint8_t c;
    };
    // int *p = new int(10);
    // int *ptr = (int*)malloc(2 * sizeof(double));
    // std::cout << ptr << std::endl;
    // std::cout << *p << std::endl;
    // std::cout << sizeof(Info2) << std::endl;
    // char test[5]={"test"};
    // std::cout << test << std::endl;
    struct S
    {
        int x;
        char y;
        int z;
        double a;
    };
    std::cout << alignof(S) << std::endl;   //8
    std::cout << sizeof(S) << std::endl;    //24
    std::cout << OFFSETOF(S, x) << std::endl; // 0
    std::cout << OFFSETOF(S, y) << std::endl; // 4
    std::cout << OFFSETOF(S, z) << std::endl; // 8
    std::cout << OFFSETOF(S, a) << std::endl; //16

    struct A
    {
        char c;
        int a;
    };
    std::cout << alignof(A) << std::endl;   //4
    return 0;
}
#endif

//线段树(query + update)
#ifdef qq06
#define MAX_LEN 1000

void BuildSegmentTree(std::vector<int>& arrs, std::vector<int>& tree, int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = arrs[start];
        return;
    }

    int mid = (start + end) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;

    BuildSegmentTree(arrs, tree, leftNode, start, mid);
    BuildSegmentTree(arrs, tree, rightNode, mid + 1, end);
    tree[node] = tree[leftNode] + tree[rightNode];
}

void UpdateSegmentTree(std::vector<int>& arrs, std::vector<int>& tree, int node, int start, int end, int idx, int value)
{
    if (start == end)
    {
        arrs[idx] = value;
        tree[node] = value;
        return;
    }
    int mid = (start + end) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;

    if (idx <= mid && idx >= start)
    {
        UpdateSegmentTree(arrs, tree, leftNode, start, mid, idx, value);
    }
    else
    {
        UpdateSegmentTree(arrs, tree, rightNode, mid + 1, end, idx, value);
    }

    tree[node] = tree[leftNode] + tree[rightNode];
}

int QuerySegmentTree(std::vector<int>& arrs, std::vector<int>& tree, int node, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left <= start && end <= right)
        return tree[node];
    if (start == end)
        return tree[node];
    int mid = (start + end) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;
    int sumLeft = QuerySegmentTree(arrs, tree, leftNode, start, mid, left, right);
    int sumRight = QuerySegmentTree(arrs, tree, rightNode, mid + 1, end, left, right);
    return sumLeft + sumRight;
}


int main(int argc, char** argv)
{
    std::vector<int> arrs = {1, 3, 5, 7, 9, 11};
    int size = arrs.size();
    std::vector<int> tree(MAX_LEN, 0);
    
    BuildSegmentTree(arrs, tree, 0, 0, size - 1);

    for (int i = 0; i < 15; ++i)
    {
        std::cout << tree[i] << std::endl;
    }

    UpdateSegmentTree(arrs, tree, 0, 0, size - 1, 4, 6);
    for (int i = 0; i < 15; ++i)
    {
        std::cout << tree[i] << std::endl;
    }

    int sum = QuerySegmentTree(arrs, tree, 0, 0, size - 1, 2, 5);
    std::cout << sum << std::endl;
    return 0;
}
#endif

//并查集判断无向图是否有环
#ifdef qq07

int FindRoot(int x, std::vector<int>& parent)
{
    int xRoot = x;
    while (parent[xRoot] != -1)
    {
        xRoot = parent[xRoot];
    }
    return xRoot;
}

int Union(int x, int y, std::vector<int>& parent, std::vector<int>& rank)
{
    int xRoot = FindRoot(x, parent);
    int yRoot = FindRoot(y, parent);
    if (xRoot == yRoot)
        return 0;
    else
    {
        if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else
        {
            rank[yRoot]++;
            parent[xRoot] = yRoot;
        }
        return 1;
    }
}

int main(int argc, char** argv)
{
    std::vector<int> parent(6, -1);
    std::vector<int> rank(6, 0);
    std::vector<std::vector<int>> edges = 
    {
        {0, 1}, {1, 2}, {1, 3},
        {3, 4}, {2, 5}, {5, 4}
    };

    for (int i = 0; i < 6; ++i)
    {
        int x = edges[i][0];
        int y = edges[i][1];
        if (Union(x, y, parent, rank) == 0)
        {
            std::cout << "Cycle detected!" << std::endl;
            exit(0);
        }
    }
    std::cout << "No Cycle Found" << std::endl;
    return 0;
}
#endif

//多线程打印
//01020304...
#ifdef qq08
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>
class ZeroAndEvenOdd
{
public:
	ZeroAndEvenOdd(int num)
		: n(num), ze(false), other(false) {}

	void printZero()
	{
		for (int i = 0; i < n; ++i)
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [&]() {
				return (!ze && !other);
			});
            std::cout << 0;
            std::cout.flush();
            ze = true;
            other = true;
            cv.notify_all();
		}
	}

	void printEven()
	{
		for (int i = 0; i < n; ++i)
		{
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() {
                return (ze && count % 2 == 0 && other);
            });
            std::cout << count;
            std::cout.flush();
            ze = false;
            ++count;
            other = false;
            cv.notify_all();
		}
	}

	void printOdd()
	{
		for (int i = 0; i < n; ++i)
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [&]() {
				return (ze && count % 2 != 0 && other);
			});
			std::cout << count;
            std::cout.flush();
			ze = false;
			other = false;
			++count;
			cv.notify_all();
		}
	}

private:
	int n;
	bool ze;
	bool other;
	std::condition_variable cv;
	std::mutex mtx;
	static int count;
};

int ZeroAndEvenOdd::count = 1;

int main()
{
    int n = 0;
    std::cin >> n;
	ZeroAndEvenOdd zeo(5);
	std::thread th1(&ZeroAndEvenOdd::printZero, &zeo);
	std::thread th2(&ZeroAndEvenOdd::printOdd, &zeo);
	std::thread th3(&ZeroAndEvenOdd::printEven, &zeo);

	th1.join();
	th2.join();
	th3.join();
    return 0;
}
#endif


//BitMap
#ifdef qq09
class BitMap
{
public:
    explicit BitMap(int capacity)
        : m_capacity(capacity)
    {
        m_bits = new char[m_capacity];
    }

    ~BitMap()
    {
        delete[] m_bits;
    }

    void Add(int num)
    {
        int index = num / 8;
        int position = num % 8;
        m_bits[index] |= 1 << position;
    }

    bool Contain(int num)
    {
        int index = num / 8;
        int position = num % 8;
        return (m_bits[index] & (1 << position)) != 0;
    }

    void Clear(int num)
    {
        int index = num / 8;
        int position = num % 8;
        m_bits[index] &= ~(1 << position);
    }
public:
    int m_capacity;
    char* m_bits;
};

int main()
{
    std::vector<int> arrs = {7, 2, 3 , 1, 5, 14};
    BitMap bitmap(2);
    int len = arrs.size();
    for (int i = 0; i < len; ++i)
    {
        bitmap.Add(arrs[i]);
    }

    for (int i = 0; i < bitmap.m_capacity; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if ((bitmap.m_bits[i] & (1 << j)) & (1 << j))
            {
                std::cout << i * 8 + j << std::endl;
            }
        }
    }
    return 0;
}
#endif

//宏定义练习
#ifdef qq10
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>

#define GETMID(a, b, c) (a + b + c - std::max(std::max(a, b), c) - std::min(std::min(a, b), c))
#define OFFSETOF(s, m) (size_t)&(((s*)(0))->m)

int main() 
{
    // char hname[128];
    // struct hostent *hent;
    // int i;

    // gethostname(hname, sizeof(hname));

    // //hent = gethostent();
    // hent = gethostbyname(hname);

    // printf("hostname: %s/naddress list: ", hent->h_name);
    // for(i = 0; hent->h_addr_list[i]; i++) {
    //     printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    // }

    int a = GETMID(4, 2, 3);
    std::cout << a << std::endl;
    return 0;
}
#endif

//图的遍历及Dijkstra算法
#ifdef qq11

std::unordered_map<char, std::vector<char>> graph = {
    {'A', {'B', 'C'}},
    {'B', {'A', 'C', 'D'}},
    {'C', {'A', 'B', 'D', 'E'}},
    {'D', {'B', 'C', 'E', 'F'}},
    {'E', {'C', 'D'}},
    {'F', {'D'}}
};

void BFS(std::unordered_map<char, std::vector<char>>& graph, char start)
{
    std::unordered_set<char> seen;
    std::queue<char> que;
    que.push(start);
    seen.insert(start);
    while (!que.empty())
    {
        char vertex = que.front();
        que.pop();
        auto& nodes = graph[vertex];
        for (auto& item : nodes)
        {
            if (seen.count(item) == 0)
            {
                que.push(item);
                seen.insert(item);
            }
        }
        std::cout << vertex << std::endl;
    }
}

//广度优先生成树
void BFSTree(std::unordered_map<char, std::vector<char>>& graph, char start, std::unordered_map<char, char>& parent)
{
    parent[start] = '#';
    std::unordered_set<char> seen;
    seen.insert(start);

    std::queue<char> que;
    que.push(start);
    while (!que.empty())
    {
        char vertex = que.front();
        que.pop();
        auto& nodes = graph[vertex];
        for (auto& item : nodes)
        {
            if (seen.count(item) == 0)
            {
                parent[item] = vertex;
                seen.insert(item);
                que.push(item);
            }
        }
    }
}

void DFS(std::unordered_map<char, std::vector<char>>& graph, char start)
{
    std::unordered_set<char> seen;
    std::stack<char> st;
    st.push(start);
    seen.insert(start);
    while (!st.empty())
    {
        char vertex = st.top();
        st.pop();
        auto& nodes = graph[vertex];
        for (auto& item : nodes)
        {
            if (seen.count(item) == 0)
            {
                st.push(item);
                seen.insert(item);
            }
        }
        std::cout << vertex << std::endl;
    }
}

std::unordered_map<char, std::vector<std::pair<char, int>>> graphRank = {
    {'A', {{'B', 5}, {'C', 1}}},
    {'B', {{'A', 5}, {'C', 2}, {'D', 1}}},
    {'C', {{'A', 1}, {'B', 2}, {'D', 4}, {'E', 8}}},
    {'D', {{'B', 1}, {'C', 4}, {'E', 3}, {'F', 6}}},
    {'E', {{'C', 8}, {'D', 3}}},
    {'F', {{'D', 6}}}
};


void Dijkstra(std::unordered_map<char, std::vector<std::pair<char, int>>>& graphRank, char start, 
                std::unordered_map<char, char>& parent, std::unordered_map<char, int>& distance)
{
    struct CMP
    {
        bool operator()(std::pair<int, char>& a, std::pair<int, char>& b)
        {
            return a.first > b.first;
        }
    };
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, CMP> que;
    std::unordered_set<char> seen;
    que.push({0, start});
    parent[start] = '#';
    while (!que.empty())
    {
        auto pair = que.top();
        que.pop();
        int dist = pair.first;
        char vertex = pair.second;
        seen.insert(vertex);

        auto& nodes = graphRank[vertex];
        for (auto& item : nodes)
        {
            if (seen.count(item.first) == 0)
            {
                if (dist + item.second < distance[item.first])
                {
                    que.push({dist + item.second, item.first});
                    parent[item.first] = vertex;
                    distance[item.first] = dist + item.second;
                }
            }
        }
    }
}

int main()
{
    //BFS(graph, 'E');
    //DFS(graph, 'E');

    // std::unordered_map<char, char> parent;
    // BFSTree(graph, 'E', parent);
    // for (auto& item : parent)
    // {
    //     std::cout << item.first << ": " << item.second << std::endl;
    // }
    // char ch = 'B';
    // while (ch != '#')
    // {
    //     std::cout << ch << std::endl;
    //     ch = parent[ch];
    // }

    std::unordered_map<char, char> parent;
    std::unordered_map<char, int> distance;
    distance['A'] = 0;
    for (auto& item : graphRank)
    {
        if (item.first != 'A')
            distance[item.first] = INT_MAX;
    }
    Dijkstra(graphRank, 'A', parent, distance);

    for (auto& item : parent)
    {
        std::cout << item.first << ": " << item.second << std::endl;
    }
    for (auto& item : distance)
    {
        std::cout << item.first << ": " << item.second << std::endl;
    }
    return 0;
}
#endif

//GDB
#ifdef qq12
// #include <stdio.h>
// #include <pthread.h>
// void *thread_func(void *p_arg)
// {
//         while (1)
//         {
//                 sleep(10);
//         }
// }
// int main(void)
// {
//         pthread_t t1, t2;

//         pthread_create(&t1, NULL, thread_func, (void*)"Thread 1");
//         pthread_create(&t2, NULL, thread_func, (void*)"Thread 2");

//         sleep(1000);
//         return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// typedef struct
// {
//         int a;
//         int b;
//         int c;
//         int d;
//         pthread_mutex_t mutex;
// }ex_st;

// int main(void) 
// {
//         ex_st st = {1, 2, 3, 4, PTHREAD_MUTEX_INITIALIZER};
//         printf("%d,%d,%d,%d\n", st.a, st.b, st.c, st.d);
//         return 0;
// }

// #include <stdio.h>
// namespace Foo
// {
//   void foo()
//   {
//   }
// }

// namespace
// {
//   void bar()
//   {
//   }
// }
// int func(int a, int b)
// {
// 	int c = a * b;
// 	printf("c is %d\n", c);
//     return 0;
// }

// int main(void) 
// {
// 	func(1, 2);
// 	return 0;
// }

// #include <stdio.h>
	
// int main(void)
// {
//         int i = 0;
// 		int sum = 0;

// 		for (i = 1; i <= 200; i++)
// 		{
// 			sum += i;
// 		}
	
// 		printf("%d\n", sum);
//         return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// int main(void) {
//     pid_t pid;

//     pid = fork();
//     if (pid < 0)
//     {
//         exit(1);
//     }
//     else if (pid > 0)
//     {
//         printf("Parent\n");
//         exit(0);
//     }
//     printf("Child\n");
//     return 0;
// }

// #include <stdio.h>
// #include <wchar.h>

// int main(void)
// {
//         char str1[] = "abcd";
//         wchar_t str2[] = L"abcd";
//         std::cout << str1 << ", " << str2 << std::endl;
//         return 0;
// }

// #include <iostream>
// #include <vector>

// using namespace std;

// int main ()
// {
//     vector<int> vec(10); // 10 zero-initialized elements

//     for (int i = 0; i < (int)vec.size(); i++)
//       vec[i] = i;

//     cout << "vec contains:";
//     for (int i = 0; i < (int)vec.size(); i++)
//       cout << ' ' << vec[i];
//     cout << '\n';

//     int i = 0;
//     char a[100];
//     for (i = 0; i < (int)sizeof(a); i++)
//     {
//             a[i] = i;
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// int a = 0;
// int b = 0;
// void *thread1_func(void *p_arg)
// {
//         while (1)
//         {
//                 a++;
//                 sleep(1);
//         }
// }

// void *thread2_func(void *p_arg)
// {
//         while (1)
//         {
//                 b++;
//                 sleep(1);
//         }
// }


// void reverse(std::string str)
// {

// }
// int main(void)
// {
//         pthread_t t1, t2;

//         pthread_create(&t1, NULL, thread1_func, (void*)"Thread 1");
//         pthread_create(&t2, NULL, thread2_func, (void*)"Thread 2");

//         sleep(1000);
//         return 0;
// }

#include <stdio.h>
#include <signal.h>

void handler(int sig);

void handler(int sig)
{
    signal(sig, handler);
    printf("Receive signal: %d\n", sig);
}

int main(void) 
{
    signal(SIGINT, handler);
    signal(SIGALRM, handler);
    
    while (1)
    {
            sleep(1);
    }
    return 0;
}
#endif

//迷宫问题
#ifdef qq13

//迷宫最短路径
int BFS(std::vector<std::vector<char>>& graph, int startX, int startY, int endX, int endY)
{
    int row = graph.size();
    int col = graph[0].size();
    std::queue<std::pair<int, int>> que;
    std::set<std::pair<int, int>> seen;
    std::vector<int> directions = {-1, 0, 1, 0, -1};
    que.push({startX, startY});
    seen.insert({startX, startY});

    std::vector<std::vector<int>> distance(row, std::vector<int>(col, INT_MAX));
    distance[startX][startY] = 1;

    bool isFound = false;

    while (!que.empty())
    {
        auto point = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i)
        {
            int x = point.first + directions[i];
            int y = point.second + directions[i + 1];
            if (x >= 0 && x < col && y >= 0 && y < row && graph[x][y] != '1' && seen.count({x, y}) == 0)
            {
                que.push({x, y});
                seen.insert({x, y});
                distance[x][y] = distance[point.first][point.second] + 1;
                if (x == endX && y == endY)
                {
                    isFound = true;
                    break;
                }
            }
        }
        if (isFound)
            break;
    }
    return distance[endX][endY] == INT_MAX ? -1 : distance[endX][endY];
}

//迷宫总路径数
int result = 0;
std::vector<int> directions = {-1, 0, 1, 0, -1};
void DFS(std::vector<std::vector<char>>& graph, int startX, int startY, int endX, int endY, std::vector<std::vector<bool>>& isVisited)
{
    if (startX < 0 && startX >= (int)graph.size() && startY < 0 && startY >= (int)graph[0].size())
    {
        return;
    }
    if (startX == endX && startY == endY)
    {
        ++result;
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int x = startX + directions[i];
        int y = startY + directions[i + 1];
        if (x >= 0 && x < (int)graph.size() && y >= 0 && y < (int)graph[0].size() && graph[x][y] != '1' && isVisited[x][y] == false)
        {
            isVisited[x][y] = true;
            DFS(graph, x, y, endX, endY, isVisited);
            isVisited[x][y] = false;
        }
    }
}

int main()
{
    std::vector<std::vector<char>> graph = 
    {
        {'0', '1', '0', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '0', '0'},
        {'0', '0', '0', '1'}
        // {'0', '1', '0'},
        // {'0', '0', '0'},
        // {'0', '1', '0'}
    };
    
    int res = BFS(graph, 0, 0, 2, 2);
    std::cout << res << std::endl;

    // std::vector<std::vector<bool>> isVisited(graph.size(), std::vector<bool>(graph[0].size(), false));
    // DFS(graph, 0, 0, 2, 2, isVisited);
    // std::cout << result << std::endl;
}
#endif


//KMP算法
#ifdef qq14

void GetNext(std::string& pattern, std::vector<int>& next)
{
    next[0] = 0;
    int len = 0;
    int i = 1;
    while (i < (int)pattern.size())
    {
        if (pattern[i] == pattern[len])
        {
            ++len;
            next[i] = len;
            ++i;
        }
        else
        {
            if (len > 0)
                len = next[len - 1];
            else
            {
                next[i] = len;
                ++i;
            }
        }
    }

    for (int i = (int)next.size() - 1; i > 0; --i)
    {
        next[i] = next[i - 1];
    }
    next[0] = -1;
}

void KMP(std::string& strs, std::string& pattern)
{
    std::vector<int> next(pattern.size(), 0);
    GetNext(pattern, next);

    int i = 0;
    int j = 0;
    while (i < (int)strs.size())
    {
        if (j == (int)pattern.size() - 1 && pattern[j] == strs[i])
        {
            std::cout << "Found Pattern at " << i - j << std::endl;
            j = next[j]; 
        }

        if (strs[i] == pattern[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
            if (j == -1)
            {
                ++i;
                ++j;
            }
        }
    }
}

int main()
{
    std::string strs = "ABABABCABAABABABAB";
    std::string pattern = "ABABCABAA";
    std::vector<int> next(pattern.size(), 0);

    KMP(strs, pattern);
    return 0;
}
#endif

//质数的求法
#ifdef qq15
bool isPrim(int num)
{
    if (num < 2)
        return false;
    if (num == 2)
        return true;
    for (int i = 2; i < num; ++i)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void PrintPrim()
{
    // for (int i = 1; i < 100; ++i)
    // {
    //     if (isPrim(i))
    //         std::cout << i << std::endl;
    // }

    std::vector<bool> isPrim(101, true);
    isPrim[0] = false;
    isPrim[1] = false;
    for (int i = 2; i < 101; ++i)
    {
        if (isPrim[i])
        {
            std::cout << i << std::endl;
            for (int j = 2 * i; j < 101; j += i)
            {
                isPrim[j] = false;
            }
        }
    }
}


int main()
{
    PrintPrim();
    return 0;
}
#endif

//最长连续子数组中所有数字和的必须小于或等于k
#ifdef qq16
int GetResult(std::vector<int>& nums, int k)
{
    int result = 0;
    std::vector<int> length(nums.size(), 0);
    std::vector<int> sums(nums.size(), 0);

    int len = 0;
    int sum = 0;
    for (int i = 0; i < (int)nums.size(); ++i)
    {
        sum += nums[i];
        if (sum <= k)
        {
            ++len;
            length[i] = len;
            sums[i] = sum;
        }
        else
        {
            sum -= nums[i - len];
            length[i] = len;
            sums[i] = sum;
        }
    }

    for (int i = 0; i < (int)nums.size(); ++i)
    {
        if (sums[i] <= k)
        {
            result = std::max(result, length[i]);
        }
    }
    return result;
}

int main()
{
    std::vector<int> nums = {3, 1, 2, 1};
    int res = GetResult(nums, 4);
    std::cout << res << std::endl;
    return 0;
}
#endif

//翻转二进制数
//00111011==>1101100
#ifdef qq17
int Reverse(int a)
{
    int m_1 = 0x55555555;
    int m_2 = 0x33333333;
    int m_4 = 0x0f0f0f0f;
    int m_8 = 0x00ff00ff;
    int m_16 = 0x0000ffff;

    int b = ((a & m_16) << 16) + ((a >> 16) & m_16);
    int c = ((b & m_8) << 8) + ((b >> 8) & m_8);
    int d = ((c & m_4) << 4) + ((c >> 4) & m_4);
    int e = ((d & m_2) << 2) + ((d >> 2) & m_2);
    int f = ((e & m_1) << 1) + ((e >> 1) & m_1);
    return f;
}
int main()
{
    int a = 9999;
    int b = Reverse(a);
    int c = Reverse(b);
    std::cout << "a = " << a << ", c = " << c << std::endl;
    return 0;
}
#endif

#ifdef qq18
#include <iostream>
class A{
public:
    int a;
    A():a(0x1) {}
    virtual void foo(){ std::cout << "A::foo()" << std::endl; }
    void bar(){ std::cout << "A::bar()" << std::endl; }
};
class B: public A{
public:
    int b;
    B():A(),b(0x2) {}
    void foo(){ std::cout << "B::foo()" << std::endl; }
};
class C: public B{
public:
    int c;
    C():B(), c(0x3) {}
    void foo(){ std::cout << "C::foo()" << std::endl; }
};
int main() {
    A a; B b; C c; B *p = &c;
    p->foo();
    std::cout << sizeof(int) << " " << sizeof(int*) << std::endl;
    return 0;
}
#endif

//计算罗马数字
#ifdef qq19
#define N 7
char digits[N] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int values[N] = {1, 5, 10, 50, 100, 500, 1000};

int digitsToValues(char ch)
{
    for (int i = 0; i < N; ++i)
    {
        if (digits[i] == ch)
        {
            return values[i];
        }
    }
    return 0;
}

int findMaxIndex(char str[], int L, int R)
{
    int max = digitsToValues(str[L]);
    int maxIndex = L;
    for (int i = L; i < N; ++i)
    {
        int num = digitsToValues(str[i]);
        if (num > max)
        {
            max = num;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int romanToNumber(char str[], int L, int R)
{
    if (L == R)
    {
        return digitsToValues(str[L]);
    }
    else if (L > R)
    {
        return 0;
    }
    else
    {
        int maxIndex = findMaxIndex(str, L, R);
        int max = digitsToValues(str[maxIndex]);
        int left = romanToNumber(str, L, maxIndex - 1);
        int right = romanToNumber(str, maxIndex + 1, R);
        return max - left + right;
    }
}

int main()
{
    char str[] = "MCMLIV";
    int res = romanToNumber(str, 0, 5);
    std::cout << res << std::endl;
    return 0;
}
#endif

//ip地址转换
// 10.0.3.193
// 167969729

// 167773121
// 10.3.3.193
#ifdef qq20
int ipToInt(std::string& ip)
{
    int res = 0;
    size_t lastPos = ip.find_first_not_of('.', 0);
    size_t pos = ip.find_first_of('.', lastPos);
    int flag = 24;
    while (lastPos != std::string::npos || pos != std::string::npos)
    {
        res += ((atoi(ip.substr(lastPos, pos - lastPos).c_str())) << flag);
        lastPos = ip.find_first_not_of('.', pos);
        pos = ip.find_first_of('.', lastPos);
        flag -= 8;
    }
    return res;
}

std::string intToIp(int num)
{
    std::stringstream ss;
    ss << ((num & 0xff000000) >> 24) << "." 
       << ((num & 0x00ff0000) >> 16) << "." 
       << ((num & 0x0000ff00) >> 8) << "." 
       << (num & 0x000000ff);
    return ss.str();
}

int main()
{
    std::string str = "10.0.3.193";
    int num = 167773121;
    int res = ipToInt(str);
    std::cout << res << std::endl;
    std::string ip = intToIp(num);
    std::cout << ip << std::endl;
}
#endif