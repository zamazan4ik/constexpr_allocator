#define _LIBCPP_HAS_NO_ASAN
#define _LIBCPP_NO_EXCEPTIONS
#include "include/modif_memory"
#include "include/modif_vector"

#include <assert.h>

template <class T, unsigned N = 100>
struct constexpr_allocator {
    T data[N] = {};
    unsigned used = 0;
    using value_type = T;
    using pointer = T*;

    constexpr pointer allocate(unsigned s) {
        pointer ret = data + used;
        used += s;
        return ret;
    }

    template< class U, class... Args >
    constexpr void construct( U* p, Args&&... args ) {
        *p = T(std::forward<Args>(args)...);
    }

    template< class U >
    constexpr void destroy( U* ) {}

    constexpr void deallocate(T* p, unsigned n ) {
        if (data + used - n == p)
            used -= n;
    }

    static constexpr bool allocator_auto_cleanup = true;
};


constexpr bool vector_testing_constexpr(unsigned size) {
    std::vector<unsigned, constexpr_allocator<unsigned>> compile_time;
    for (unsigned i = 0; i <= size; ++ i)
        compile_time.push_back(i);

    compile_time.emplace_back(0);
    compile_time.pop_back();

    return compile_time.back() == size;
}


constexpr auto vector_constexpr_return(unsigned size) {
    std::vector<int, constexpr_allocator<int>> compile_time;
    for (unsigned i = 0; i <= size; ++ i)
        compile_time.push_back(i);

    compile_time.emplace_back(0);
    compile_time.pop_back();

    auto cpy = std::move(compile_time);

    return cpy;
}

int main()
{
    std::vector<int> runtime = {1, 2, 3, 4};
    runtime.push_back(5);
    assert(runtime.back() == 5);

    constexpr auto r = vector_testing_constexpr(5);
    static_assert(r, "");

    // constexpr std::vector<int, constexpr_allocator<int>> vec = vector_constexpr_return(3) ;
}
