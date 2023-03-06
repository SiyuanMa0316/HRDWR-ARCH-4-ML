#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <queue>

template <class T>
class Stream {
public:
    Stream();
    ~Stream() { delete(mQueue); }
    void write(T data);
    int empty() { return mQueue->empty(); }
    T read();
    void clear();
private:
    std::queue<T> *mQueue;
};

template <class T>
Stream<T>::Stream() {
    mQueue = new std::queue<T>();
    while (!mQueue->empty())
        mQueue->pop();
}

template <class T>
void Stream<T>::write(T data) {
    mQueue->push(data);
}

template <class T>
T Stream<T>::read() {
    T value = mQueue->front();
    mQueue->pop();
    return value;
}

template <class T>
void Stream<T>::clear() {
    while (!mQueue->empty())
        mQueue->pop();
}

#endif //STREAM_UTILS_H
