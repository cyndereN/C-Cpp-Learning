template <typename InputIterator, typename UnaryPredicate>
int numOccurencesGen(InputIterator start, InputIterator end, UnaryPredicate predicate) {

    int counter = 0;
    InputIterator iter;
    for(iter = start; iter != end; ++iter) {
        if(predicate(*iter))
            ++counter;
    }
    return counter;

}

template<typename DataType>
inline bool lessThanTwo(DataType val) { return val < 2; }

template<typename DataType>
inline bool isEven(DataType val) { return val % 2 == 0; }

template<typename DataType>
inline bool isPastBedTime(DataType val) { return val.hour >= 4; }
