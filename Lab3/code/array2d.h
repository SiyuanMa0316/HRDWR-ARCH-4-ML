#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "array.h"

template<class T>
class Array2D {
public:
    Array2D(int size_2d = 0, int size_1d = 0);
    Array2D(const Array2D<T>& m);
    ~Array2D() {delete [] element2d;}
    int Size_2d() const {return size_2d;}
    int Size_1d() const {return size_1d;}
    Array1D<T>& operator[](int i) const;
    Array2D<T>& operator=(const Array2D<T>& m);
    Array2D<T>& resize(int size_2d = 0, int size_1d = 0);
private:
    int size_2d, size_1d;
    Array1D<T> *element2d;
};

template<class T>
Array2D<T>::Array2D(int size_2d, int size_1d) {
    this->size_1d = size_1d;
    this->size_2d = size_2d;

    element2d = new Array1D<T> [size_2d];

    for (int i = 0; i < size_2d; i++)
        element2d[i].resize(size_1d);
}

template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const {
    return element2d[i];
}

template<class T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& m)
{
    if (this != &m) {
        delete [] element2d;
        size_2d = m.Size_2d();
        size_1d = m.Size_1d();
        element2d = new Array1D<T> [size_2d];

        for (int i = 0; i < size_2d; i++)
            element2d[i] = m.element2d[i];
    }

    return *this;
}

template<class T>
Array2D<T>::Array2D(const Array2D<T>& m) {
    size_2d = m.Size_2d();
    size_1d = m.Size_1d();

    element2d = new Array1D<T> [size_2d];

    for (int i = 0; i < size_2d; i++)
        element2d[i] = m.element2d[i];
}

template<class T>
Array2D<T>& Array2D<T>::resize(int size_2d, int size_1d) {
    if (size_2d < 0 || size_1d < 0) return *this;
    delete [] element2d;
    this->size_2d = size_2d;
    this->size_1d = size_1d;

    element2d = new Array1D<T> [size_2d];
    for (int i = 0; i < size_2d; i++)
        element2d[i].resize(size_1d);

    return *this;
}
#endif //ARRAY2D_H
