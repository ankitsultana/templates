#include <sys/resource.h>
int main() {
    const rlim_t Stack_size = 32L * 1024 * 1024; // At least 32 Mb Stack
    struct rlimit lim = {Stack_size, Stack_size};
    if(setrlimit(RLIMIT_STACK, &lim) == -1) assert(false);
    return 0;
}
