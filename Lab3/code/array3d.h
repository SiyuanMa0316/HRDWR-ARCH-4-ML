#ifndef ARRAY3D_H
#define ARRAY3D_H

#include "array2d.h"

template<class T>
class Array3D {
public:
    Array3D(int size_3d = 0, int size_2d = 0, int size_1d = 0);
    Array3D(const Array3D<T>& m);
    ~Array3D() {delete [] element3d;}
    int Size_3d() const {return size_3d;}
    int Size_2d() const {return size_2d;}
    int Size_1d() const {return size_1d;}
    Array2D<T>& operator[] (int i) const;
    Array3D<T>& operator=(const Array3D<T>& m);
    Array3D<T>& resize(int size_3d = 0, int size_2d = 0, int size_1d = 0);
private:
    int size_3d, size_2d, size_1d;
    Array2D<T> *element3d;
};

template<class T>
Array3D<T>::Array3D(int size_3d, int size_2d, int size_1d) {
    this->size_3d = size_3d;
    this->size_2d = size_2d;
    this->size_1d = size_1d;

    element3d = new Array2D<T> [size_3d];

    for (int i = 0; i < size_3d; i++)
        element3d[i].resize(size_2d, size_1d);
}

template<class T>
Array2D<T>& Array3D<T>::operator[] (int i) const {
    return element3d[i];
}

template<class T>
Array3D<T>& Array3D<T>::operator=(const Array3D<T>& m)
{
    if (this != &m) {
        delete [] element3d;
        size_3d = m.Size_3d();
        size_2d = m.Size_2d();
        size_1d = m.Size_1d();
        element3d = new Array2D<T> [size_3d];

        for (int i = 0; i < size_3d; i++)
            element3d[i] = m.element3d[i];
    }

    return *this;
}


template<class T>
Array3D<T>::Array3D(const Array3D<T>& m) {
    size_3d = m.Size_3d();
    size_2d = m.Size_2d();
    size_1d = m.Size_1d();

    element3d = new Array2D<T> [size_3d];

    for (int i = 0; i < size_3d; i++)
        element3d[i] = m.element3d[i];
}

template<class T>
Array3D<T>& Array3D<T>::resize(int size_3d, int size_2d, int size_1d) {
    if (size_3d < 0 || size_2d < 0 || size_1d < 0) return *this;
    delete [] element3d;

    this->size_3d = size_3d;
    this->size_2d = size_2d;
    this->size_1d = size_1d;

    element3d = new Array2D<T> [size_3d];
    for (int i = 0; i < size_3d; i++)
        element3d[i].resize(size_2d, size_1d);

    return *this;
}

#endif //ARRAY3D_H
