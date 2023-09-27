#include <iostream>
#include <pthread.h>

class ThreadRAII {
    public:
        ThreadRAII(void* (*startRoutine)(void*), void* arg) {
            int result = pthread_create(&threadId, nullptr, startRoutine, arg);
        }

        ~ThreadRAII() {
            if (threadId != 0) 
                pthread_join(threadId, nullptr);
        }

        ThreadRAII(ThreadRAII&&) = delete;
        ThreadRAII& operator=(ThreadRAII&&) = delete;

    private:
        pthread_t threadId;
};

void* threadFunction(void* arg) {
    int* value = reinterpret_cast<int*>(arg);
    //int* value = static_cast<int*>(arg);
    std::cout << "Thread: Received value " << *value << std::endl;
    return nullptr;
}

int main() {
    int data = 42;

    {
        ThreadRAII thread(threadFunction, &data);
    }

    /**

    pthread_t threadId;
    pthread_create(&threadId, nullptr, threadFunction, &data);
    pthread_join(threadId, nullptr);
    delete threadId;
    
    */

    std::cout << "Main: Thread has finished executing." << std::endl;
    return 0;
}
