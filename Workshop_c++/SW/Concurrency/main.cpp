#include <iostream>
#include <fstream>
#include <future>
#include <vector>
#include <QElapsedTimer>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <thread>
#include <cassert>
#include <mutex>
#include <random>

int task1()
{
    /*
    for(int i=0; i<1000; ++i)
    {
        std::string filename = "test" + std::to_string(i);
        std::ofstream file;
        file.open (filename);
        file << "Writing this to a file.\n";
        file.close();
    }
    */

    std::vector<std::string> filenames;
    for(int i=0; i<1000; ++i)
    {
        std::string filename = "test" + std::to_string(i);
        filenames.push_back(filename);
    }

    std::vector<std::future<int>> futures;

    QElapsedTimer timer;
    timer.start();
    for(auto& filename : filenames)
    {
        futures.push_back(std::async(std::launch::deferred, [](const std::string& filename) -> int{
            std::ifstream file;
            file.open(filename);
            std::string str((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
            return str.size();
        }, filename));
    }

    int count = 0;
    for(auto& future : futures)
    {
        count += future.get();
    }

    std::cout << "count: " << count << " elapsed: " << timer.elapsed() << std::endl;

    return 0;
}

int task2()
{
    const unsigned threads = std::thread::hardware_concurrency();

    std::cout << "nubmer of hardware threads " << threads << std::endl;

    std::srand(std::time(0)); // use current time as seed for random generator

    std::vector<int> numbers;

    const int size = 100000000;

    for(int i=0; i<size; ++i)
    {
        numbers.push_back(std::rand() % 1000 + 1);
    }

    auto countFunc = [&numbers](auto begin, auto end){
        int odds = 0;
        for(auto it = begin; it != end; ++it)
        {
            if(*it % 2 != 0)
                ++odds;
        }
        return odds;
    };

    std::vector<std::future<int>> futures;

    const int chunksize = numbers.size() / threads;

    QElapsedTimer timer;
    timer.start();

    int temp = 0;
    for(int i=0; i<threads; ++i)
    {
        auto begin = numbers.begin() + temp;
        auto end = std::min(begin + chunksize, numbers.end());
        futures.push_back(std::async(std::launch::async, countFunc, begin, end));
        temp += chunksize;
    }

    int count = 0;
    for(auto& future : futures)
    {
        count += future.get();
    }
    std::cout << "odds count: " << count << " elapsed: " << timer.elapsed() << std::endl;

    return 0;
}

struct SpinLock
{
    std::atomic<bool> locked{false};

    void lock() {
        bool expected = false;
        while(!locked.compare_exchange_strong(expected, true)){ expected = false; }
    }

    void unlock() {
        assert(locked);
        locked = false;
    }
};

void task3()
{
    int sharedVar = 0;
    SpinLock lock;

    const int loop = 100000;

    auto incr = [&](){
        for(int i=0; i<loop; i++){
            std::lock_guard<SpinLock> g(lock);
            sharedVar++;
        }
    };
    auto decr = [&](){
        for(int i=0; i<loop; i++){
            std::lock_guard<SpinLock> g(lock);
            sharedVar--;
        }
    };

    std::thread t1(incr);
    std::thread t2(decr);

    t1.join();
    t2.join();

    std::cout << sharedVar << std::endl;
}

struct ListElement
{
    ListElement* next{nullptr};
};

void task5()
{
    std::atomic<ListElement*> head(new ListElement);

    auto add = [&](){
        ListElement *element = new ListElement;
        element->next = head;
        while(!head.compare_exchange_weak(element->next, element)) { element->next = head; }
    };

    const int numElements = 100000;

    auto insert = [&](){
        for(int i=0; i<numElements; ++i)
            add();
    };

    std::thread t1(insert);
    std::thread t2(insert);

    t1.join();
    t2.join();

    //! Walk the list to count elements
    ListElement *element = head;
    int count = 0;
    while(element != nullptr)
    {
        count++;
        element = element->next;
    }

    std::cout << "list length: " << count << std::endl;
}

struct BankAccount
{
    int balance = 0;
    std::mutex lock;
};

void transfer(BankAccount& a, BankAccount& b, int amount)
{
    std::lock(a.lock, b.lock);
    std::lock_guard<std::mutex> g1(a.lock, std::adopt_lock);
    std::lock_guard<std::mutex> g2(b.lock, std::adopt_lock);

    a.balance -= amount;
    b.balance += amount;

}


void bankTask()
{
    const int num = 100000;
    BankAccount accounts[num];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, 5000);

    const int loop = 100000;

    auto threadFunc =[&]{
        for(int i=0; i<loop; ++i)
        {
            auto account1 = std::begin(accounts) + std::rand() % num;
            auto account2 = accounts + std::rand() % num;
            while(account2 == account1) account2 = std::begin(accounts) + std::rand() % num;

            transfer(*account1, *account2, 1);
        }
    };

    std::vector<std::thread> threads;

    const int numThreads = 100;

    for(int i=0; i<numThreads; ++i)
        threads.push_back(std::thread(threadFunc));

    for(auto &thread : threads)
        if (thread.joinable())
            thread.join();

    int sum = 0;
    for(int i=0; i<num; ++i)
        sum += accounts[i].balance;

    std::cout << "total sum: " << sum << std::endl;
}

int main(int argc, char *argv[])
{
    //task1();
    //task2();
    //task3();
    bankTask();
    return 0;
}




