#include <iostream>
#include <cstdlib>

void* 
aligned_malloc(size_t required_bytes, size_t alignment) 
{
    int offset = sizeof(void*) + alignment - 1;
    void* raw_ptr = malloc(required_bytes + offset);
    size_t out = (size_t)raw_ptr + offset;
    void** out_ptr = (void**)(out & -alignment);
    out_ptr[-1] = raw_ptr;
    return out_ptr;
}

void 
aligned_free(void* aligned_ptr) 
{
    void* raw_ptr = ((void**)aligned_ptr)[-1];
    free( raw_ptr );
}

int 
main()
{
    auto p = aligned_malloc(1000, 256);
    std::cout << p << std::endl;
    aligned_free(p);
    return 0;
}