#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <condition_variable>

template<typename T, uint64_t SIZE = 4096, uint64_t MAX_SPIN_ON_BUSY = 40000000>
class ConcurrentQueue {
private:
    static constexpr unsigned Log2(unsigned n, unsigned p = 0) {
        return (n <= 1) ? p : Log2(n / 2, p + 1);
    }

    static constexpr uint64_t closestExponentOf2(uint64_t x) {
        return (1UL << ((uint64_t) (Log2(SIZE - 1)) + 1));
    }

    static constexpr uint64_t mRingModMask = closestExponentOf2(SIZE) - 1;
    static constexpr uint64_t mSize = closestExponentOf2(SIZE);

    static const T mEmpty;

    T mMem[mSize];
    std::mutex mLock;
    std::condition_variable mCondition;
    uint64_t mReadPtr = 0;
    uint64_t mWritePtr = 0;

public:
    const T& front() {
        std::lock_guard<std::mutex> lock(mLock);
        if (!peek()) {
            return mEmpty;
        }

        T& ret = mMem[mReadPtr & mRingModMask];

        return ret;
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(mLock);
        mReadPtr++;
        mCondition.notify_one();
    }

    bool peek() const {
        return (mWritePtr != mReadPtr);
    }

    uint64_t getCount() const {
        return mWritePtr > mReadPtr ? mWritePtr - mReadPtr : mReadPtr - mWritePtr;
    }

    bool busyWaitForPush() {
        std::unique_lock<std::mutex> lock(mLock);
        if (getCount() == mSize)
        {
            mCondition.wait(lock);
        }
        return true;
    }

    void push(const T& pItem) {
        if (!busyWaitForPush()) {
            throw std::runtime_error("Concurrent queue full cannot write to it!");
        }

        std::lock_guard<std::mutex> lock(mLock);
        mMem[mWritePtr & mRingModMask] = pItem;
        mWritePtr++;
    }

    void push(T&& pItem) {
        if (!busyWaitForPush()) {
            throw std::runtime_error("Concurrent queue full cannot write to it!");
        }

        std::lock_guard<std::mutex> lock(mLock);
        mMem[mWritePtr & mRingModMask] = std::move(pItem);
        mWritePtr++;
    }
};

template<typename T, uint64_t SIZE, uint64_t MAX_SPIN_ON_BUSY>
const T ConcurrentQueue<T, SIZE, MAX_SPIN_ON_BUSY>::mEmpty = T{ };

int main(int, char**) {
    using Functor = std::function<void()>;

    ConcurrentQueue<Functor*> queue;

    std::thread consumer([ & ] {
            while (true) {
            if (queue.peek()) {
                auto & task = queue.front();
                (*task)();
                delete task;
                queue.pop();
            }
            }
            });

    std::thread producer([ & ] {
            uint64_t counter = 0;
            while (true) {
                queue.push(new Functor([ &counter ] {
                    std::cout << "Running task " << counter++ << std::endl << std::flush;
                    }));
            }
            });

    consumer.join();
    producer.join();
    return 0;
}
