int numOccurences(list<int>& cont, int elemToCount){
    int counter = 0;
    list<int>::iterator iter;
    for(iter = cont.begin(); iter != cont.end(); ++iter){
        if(*iter == elemToCount)
            ++counter;
    }

    return counter;
}