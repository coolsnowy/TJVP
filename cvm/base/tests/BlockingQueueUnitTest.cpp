#include "BlockingQueue.h"

#include <iostream>
#include <thread>
using namespace std;

void dequeue(BlockingQueue<int> &bq)
{
    while (1) {
        cout << bq.dequeue() << endl;
    }
}

void enqueue(BlockingQueue<int> &bq)
{
    for (int i=0; i<1000; i++) {
        bq.enqueue(i);
    }
 
}
int main()
{
    BlockingQueue<int> bq;
    thread t(bind(dequeue, ref(bq)));
    enqueue(bq);
    t.join();
    return 0;
}
