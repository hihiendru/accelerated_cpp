#ifndef GUARD_Vec_h
#define GUARD_Vec_h

#include <memory>
#include <algorithm>
#include <iostream>

template <class T>
class Vec{
  public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    // constructor 
    Vec(){create();}
    explicit Vec(size_type n, const T& val=T()){create(n,val);}

    // copy constructor / initialization
    Vec(const Vec& v){create(v.begin(),v.end());}

    // assignment operator
    Vec& operator=(const Vec&);

    // destructor
    ~Vec(){uncreate();}

    // size and index
    size_type size() const {return avail - data;}
    T& operator[](size_type i){return data[i];}            // read+write
    const T& operator[](size_type i)const{return data[i];} // read only

    // functions that return iterators
    iterator begin(){return data;}
    iterator end(){return avail;}
    const_iterator begin()const{return data;}
    const_iterator end()const{return avail;}

    // dynamic vecs
    void push_back(const T& val){
      if(avail==limit){
        grow();
      }
      unchecked_append(val);
    }
    
    // helper funcitons
    std::ostream& print_vec(std::ostream&);

  private:
    iterator data;  // first elem in vec
    iterator avail; // one past last elem in vec
    iterator limit; // one past allocated memory

    // memory allocation facility
    std::allocator<T> alloc;  // obj to handle mem allocation
    
    //allocation and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator,const_iterator);

    // destroy elemens in array, free memory
    void uncreate();

    // support functions for push_back
    void grow();
    void unchecked_append(const T&);
};

template<class T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs){
  // check self-assignment
  if(this != &rhs){
    //free lhs mem and create to mem
    uncreate();
    create(rhs.begin(),rhs.end());
  }
  return *this;
}

template <class T> void Vec<T>::create(){
  data = avail = limit = 0; // null pointers
}

template <class T> void Vec<T>::create(size_type n, const T& val){
  data = alloc.allocate(n);
  limit = avail = data + n;
  std::uninitialized_fill(data, limit, val);  
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j){
  data = alloc.allocate(j-i);
  limit = avail = std::uninitialized_copy(i,j,data);
}

template <class T> void Vec<T>::uncreate(){
  if(data){
    //destroy data in reverse - to match delete[] behaviour
    iterator iter = avail;
    while(iter != data)
      alloc.destroy(--iter);
    // return space that was allocated
    alloc.deallocate(data,limit-data);
  }
  data = limit = avail = 0;
}

template <class T> void Vec<T>::grow(){
  // allocate twice currently used space
  size_type new_size = std::max(2 * (limit-data),ptrdiff_t(1));
  // allocate new space, copy old data to new space
  iterator new_data = alloc.allocate(new_size);
  iterator new_avail = std::uninitialized_copy(data,limit,new_data);
  // free up old space
  uncreate();
  data = new_data;
  avail = new_avail;
  limit = data + new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val){
  alloc.construct(avail++,val);
}

template <class T> std::ostream& Vec<T>::print_vec(std::ostream& os){
  if(avail > data){
    iterator iter = data;
    std::cout << "[";
    while(iter < avail){
      os << *iter++;
      if(iter!=avail){
        os << ", ";
      }
    }
    os << "]" << std::endl;
  }
  return os;
}

#endif