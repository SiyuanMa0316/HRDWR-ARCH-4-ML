#ifndef ARRAY4D_H
#define ARRAY4D_H

#include "array3d.h"

template<class T>
class Array4D {
public:
    Array4D(int size_4d = 0, int size_3d = 0, int size_2d = 0, int size_1d = 0);
    Array4D(const Array4D<T>& m);
    ~Array4D() {delete [] element4d;}
    int Size_4d() const {return size_4d;}
    int Size_3d() const {return size_3d;}
    int Size_2d() const {return size_2d;}
    int Size_1d() const {return size_1d;}
    Array3D<T>& operator[] (int i) const;
    Array4D<T>& operator=(const Array4D<T>& m);
    Array4D<T>& resize(int size_4d = 0, int size_3d = 0, int size_2d = 0, int size_1d = 0);
private:
    int size_4d, size_3d, size_2d, size_1d;
    Array3D<T> *element4d;
};

template<class T>
Array4D<T>::Array4D(int size_4d, int size_3d, int size_2d, int size_1d) {
    this->size_4d = size_4d;
    this->size_3d = size_3d;
    this->size_2d = size_2d;
    this->size_1d = size_1d;

    element4d = new Array3D<T> [size_4d];

    for (int i = 0; i < size_4d; i++)
        element4d[i].resize(size_3d, size_2d, size_1d);
}

template<class T>
Array3D<T>& Array4D<T>::operator[] (int i) const {
    return element4d[i];
}

template<class T>
Array4D<T>& Array4D<T>::operator=(const Array4D<T>& m)
{
    if (this != &m) {
        delete [] element4d;
        size_4d = m.Size_4d();
        size_3d = m.Size_3d();
        size_2d = m.Size_2d();
        size_1d = m.Size_1d();
        element4d = new Array3D<T> [size_4d];

        for (int i = 0; i < size_4d; i++)
            element4d[i] = m.element4d[i];
    }

    return *this;
}

template<class T>
Array4D<T>::Array4D(const Array4D<T>& m) {
    size_4d = m.Size_4d();
    size_3d = m.Size_3d();
    size_2d = m.Size_2d();
    size_1d = m.Size_1d();

    element4d = new Array3D<T> [size_4d];

    for (int i = 0; i < size_4d; i++)
        element4d[i] = m.element4d[i];
}

template<class T>
Array4D<T>& Array4D<T>::resize(int size_4d, int size_3d, int size_2d, int size_1d) {

    if (size_4d < 0 || size_3d < 0 || size_2d < 0 || size_1d < 0) return *this;
    delete [] element4d;

    this->size_4d = size_4d;
    this->size_3d = size_3d;
    this->size_2d = size_2d;
    this->size_1d = size_1d;

    element4d = new Array3D<T> [size_4d];
    for (int i = 0; i < size_4d; i++)
        element4d[i].resize(size_3d, size_2d, size_1d);

    return *this;
}

#endif //ARRAY4D_H
