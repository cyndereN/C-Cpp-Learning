void joseph(int n, int m){
    int a[105], k=0, p=0;
    for(int i=0 ; i<n ; i++)  a[i] = i + 1;
    while(n>1){
        p = (p+m-1)%n;  //Array starts from 0
        cout<< "Number " << ++k << ": " << a[p] << endl;

        for(int j=p+1 ; j<n ; j++)  a[j-1] = a[j];
        n--;
    }
    cout << "Last one: " << a[p] << endl;
}