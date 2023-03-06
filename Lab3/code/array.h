#ifndef ARRAY_H
#define ARRAY_H

template<class T>
class Array1D {
public:
    Array1D(int size_1d = 0);
    Array1D(const Array1D<T>& v);
    ~Array1D() {delete [] element;}
    T& operator[](int i) const;
    Array1D<T>& operator=(const Array1D<T>& v);
    int Size_1d() {return size_1d;}
    Array1D<T>& resize(int size_1d = 0);
private:
    int size_1d;
    T *element;
};

template<class T>
Array1D<T>::Array1D(int size_1d) {
    this->size_1d = size_1d;
    element = new T[size_1d];
}

template<class T>
Array1D<T>::Array1D(const Array1D<T>& v) {
    size_1d = v.Size_1d();
    element = new T[size_1d];
    for (int i = 0; i < size_1d; i++)
        element[i] = v.element[i];
}

template<class T>
T& Array1D<T>::operator[](int i) const {
    return element[i];
}

template<class T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T>& v)
{
    if (this != &v) {
        size_1d = v.Size_1d();
        delete [] element;
        element = new T[size_1d];
        for (int i = 0; i < size_1d; i++)
            element[i] = v.element[i];
    }
    return *this;
}

template<class T>
Array1D<T>& Array1D<T>::resize(int size_1d) {
    if (size_1d < 0) return *this;
    delete [] element;
    this->size_1d = size_1d;
    element = new T [size_1d];
    return *this;
}

#endif //_ARRAY_H
