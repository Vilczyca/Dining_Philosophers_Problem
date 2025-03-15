#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>

class Philosopher;
class Fork;

using namespace std;

static bool finished = false;

class Fork {
public:
    mutex mtx;
};


class Philosopher {
private:
    static int staticID;
    const int ID;

    thread myThread;

    int eatingTime = 3,
        thinkingTime = 5;

    Fork* leftFork;
    Fork* rightFork;

    void doWork() {
        while (!finished) {
            think();
            tryToEat_Assymetry();
        }
    };

    bool tryToEat() {
        // left
        leftFork->mtx.lock();
        if (rightFork->mtx.try_lock()) {
            eat();
            rightFork->mtx.unlock();
            leftFork->mtx.unlock();
            return true;
        }
        leftFork->mtx.unlock();
        return false;
    };

    bool tryToEat_Assymetry() {
        if (ID % 2 == 0) {          // even
            rightFork->mtx.lock();
            leftFork->mtx.lock();
            eat();
            leftFork->mtx.unlock();
            rightFork->mtx.unlock();
        } else {                    // odd
            leftFork->mtx.lock();
            rightFork->mtx.lock();
            eat();
            rightFork->mtx.unlock();
            leftFork->mtx.unlock();
        }
        return true;
    };

    bool tryToEat_WithWaiter() {
        lock(leftFork->mtx, rightFork->mtx);
        lock_guard<mutex> leftLock(leftFork->mtx, adopt_lock);
        lock_guard<mutex> rightLock(rightFork->mtx, adopt_lock);

        eat();
        return true;
    }



    void eat() {
        // TODO: eating animation
        cout << ID << " is eating..." << endl;
        this_thread::sleep_for(3s);
    };

    void think() {
        // TODO: thinking animation
        cout << ID << " is thinking..." << endl;
        this_thread::sleep_for(2s);
    };


public:
    // Constructors and Destructors
    Philosopher() : ID(staticID++) {};
    Philosopher(Fork* leftFork, Fork* rightFork): leftFork(leftFork), rightFork(rightFork), ID(staticID++) {};
    ~Philosopher() {
        stop();
    }

    // Starts the thread
    void start() {
        myThread = thread(&Philosopher::doWork, this);
        cout << "Philosopher " << this->ID << " arrived to the dinner!" << endl;
    }

    // Stops the thread
    void stop() {
        if (myThread.joinable()) {
            myThread.join();
            cout << "Philosopher " << ID << " leaved from the dinner!" << endl;
        }
    }
};

int Philosopher::staticID = 0;

int main(int argc, char* argv[]) {
    int n = 5;  // classic number

    if (argc > 1)
        n = stoi(argv[1]);

    // Creating dinner
    vector<Fork> forks(n);
    vector<unique_ptr<Philosopher>> philosophers;

    for (int i = 0; i < n; i++) {
        philosophers.emplace_back(make_unique<Philosopher>(&forks[i], &forks[(i + 1) % n]));
        philosophers.back()->start();
    }

    cin.get();
    cout << "Dinner is over!" << endl << endl;
    finished = true;

    // Cleaning
    for (auto& philosopher : philosophers) {
        philosopher->stop();
    }
}


// https://www.youtube.com/watch?v=FYUi-u7UWgw


/*
  o
 /|\
 / \
                               o
    o        o        o       /|\
   /|\  Y   /|\     Y/|\Y    _===__________
   / \      / \      / \    |            |

  o     ,o      o      o.    o
Y/|\Y   '|\Y  Y/|\Y  Y/|'  Y/|\Y
 / \    / \    / \    / \   / \



 */