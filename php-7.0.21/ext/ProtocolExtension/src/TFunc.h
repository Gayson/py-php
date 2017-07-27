#include<boost/static_assert.hpp>
template <typename From, typename To>
To bitwise_cast(From from) {
    BOOST_STATIC_ASSERT(sizeof(From) == sizeof(To));

    union {
        From f;
        To t;
    } u;
    u.f = from;
    return u.t;
}
