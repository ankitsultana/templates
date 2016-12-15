template<typename T>
void fastWalshHadarmard(T *data, int dim) {
    if(dim == 0) return ;
    int n = 1 << (dim - 1);
    fastWalshHadarmard(data, dim - 1);
    fastWalshHadarmard(data + n, dim - 1);
    for(int i = 0; i < n; i++) {
        T u = data[i], v = data[i + n];
        data[i] = u - v;
        data[i + n] = u + v;
    }
}
template<typename T>
void inverseFastWalshHadamard(T *data, int dim) {
    if(dim == 0) return ;
    int n = 1 << (dim - 1);
    inverseFastWalshHadamard(data, dim - 1);
    inverseFastWalshHadamard(data + n, dim - 1);
    for(int i = 0; i < n; i++) {
        T u = data[i], v = data[i + n];
        data[i] = u + v;
        data[i + n] = v - u;
    }
}
