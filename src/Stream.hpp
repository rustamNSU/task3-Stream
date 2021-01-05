#include <initializer_list>
#include <vector>
#include <ostream>
#include <algorithm>
#include <numeric>

template<class Operation> class Operator;

struct print_to;
template<class Func> struct map;
template<class Pred> struct filter;
struct skip;
struct sum;


template<class T>
class Stream{
private:
    std::vector<T> data_;

public:
    Stream();
    Stream(std::initializer_list<T> init);
    
    template<class InputIterator>
    Stream(InputIterator begin, InputIterator end);

    template<class Container>
    Stream(const Container &cont);

    /* Operators */
    friend struct print_to;
    template<class Func> friend  struct map;
    template<class Pred> friend struct filter;
    friend struct skip;
    friend struct sum;

    template<class Operation>
    decltype(auto) operator|(Operation op);
};


template<class T>
Stream<T>::Stream() = default;


template<class T>
Stream<T>::Stream(std::initializer_list<T> init) :
        data_(init)
{
    
}


template<class T>
template<class InputIterator>
Stream<T>::Stream(InputIterator begin, InputIterator end) :
        data_(begin, end)
{

}


template<class T>
template<class Container>
Stream<T>::Stream(const Container &cont) :
        data_(cont.begin(), cont.end())
{

}


template<class T>
template<class Operation>
decltype(auto) Stream<T>::operator|(Operation op){
    return op.evaluate(*this);
}












template<class Operation>
class Operator{
    Operation op;

public:
    Operator(Operation op) : op(op){}
    template<class T>
    decltype(auto) evaluate(Stream<T>& stream){
        return op.evaluate(stream);
    }
};


template<class Operation>
class Terminator{
    Operation op;

public:
    Terminator(Operation op) : op(op){}
    template<class T>
    decltype(auto) evaluate(Stream<T>& stream){
        return op.evaluate(stream);
    }
};




/* Operators */

struct print_to{
    std::ostream& os;
    char delimiter = ' ';
    
    print_to(std::ostream& os) : os(os){}

    template<class T>
    std::ostream& evaluate(Stream<T>& stream){
        for (const auto& i : stream.data_){
            os << i << delimiter;
        }
        return os;
    }
};


template<class Func> 
struct map{
    Func func;
    map(Func func) : func(func){}

    template<class T>
    Stream<T>& evaluate(Stream<T>& stream){
        for (auto& elem: stream.data_){
            elem = func(elem);
        }
        return stream;
    }
};

template<class Pred> 
struct filter{
    Pred pred;
    filter(Pred pred) : pred(pred){}

    template<class T>
    Stream<T>& evaluate(Stream<T>& stream){
        stream.data_.erase(
            std::remove_if(stream.data_.begin(),
                           stream.data_.end(),
                           pred),
            stream.data_.end());
        return stream;
    }
};


struct skip;
struct sum{
    sum() = default;
    template<class T>
    int evaluate(Stream<T>& stream){
        return std::accumulate(stream.data_.begin(),
                               stream.data_.end(), 0);
    }
};