#ifndef _CPP_CONVERT_TTYPE_H_
#define _CPP_CONVERT_TTYPE_H_

enum TMessageType {
    T_CALL       = 1,
    T_REPLY      = 2,
    T_EXCEPTION  = 3,
    T_ONEWAY     = 4
};

enum TType {
    T_STOP       = 0,
    T_VOID       = 1,
    T_BOOL       = 2,
    T_BYTE       = 3,
    T_I08        = 3,
    T_I16        = 6,
    T_I32        = 8,
    T_U64        = 9,
    T_I64        = 10, T_DOUBLE     = 4, T_STRING     = 11,
    T_UTF7       = 11,
    T_STRUCT     = 12,
    T_MAP        = 13,
    T_SET        = 14,
    T_LIST       = 15,
    T_UTF8       = 16,
    T_UTF16      = 17
};

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef short i16;
typedef unsigned short ui16;

typedef int   i32;
typedef unsigned int ui32;

typedef char  i8;
typedef unsigned char ui8;

typedef long long i64;
typedef unsigned long long ui64;

#endif

/* thrift endian handle */
#ifndef __THRIFT_BYTE_ORDER
# if defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && defined(BIG_ENDIAN)
#  define __THRIFT_BYTE_ORDER BYTE_ORDER
#  define __THRIFT_LITTLE_ENDIAN LITTLE_ENDIAN
#  define __THRIFT_BIG_ENDIAN BIG_ENDIAN
# else
#  include <boost/config.hpp>
#  include <boost/detail/endian.hpp>
#  define __THRIFT_BYTE_ORDER BOOST_BYTE_ORDER
#  ifdef BOOST_LITTLE_ENDIAN
#   define __THRIFT_LITTLE_ENDIAN __THRIFT_BYTE_ORDER
#   define __THRIFT_BIG_ENDIAN 0
#  else
#   define __THRIFT_LITTLE_ENDIAN 0
#   define __THRIFT_BIG_ENDIAN __THRIFT_BYTE_ORDER
#  endif
# endif
#endif

#if __THRIFT_BYTE_ORDER == __THRIFT_BIG_ENDIAN
# if !defined(THRIFT_ntohll)
#  define THRIFT_ntohll(n) (n)
#  define THRIFT_htonll(n) (n)
# endif
# if defined(__GNUC__) && defined(__GLIBC__)
#  include <byteswap.h>
#  define THRIFT_htolell(n) bswap_64(n)
#  define THRIFT_letohll(n) bswap_64(n)
#  define THRIFT_htolel(n) bswap_32(n)
#  define THRIFT_letohl(n) bswap_32(n)
#  define THRIFT_htoles(n) bswap_16(n)
#  define THRIFT_letohs(n) bswap_16(n)
# else /* GNUC & GLIBC */
#  define bswap_64(n) \
      ( (((n) & 0xff00000000000000ull) >> 56) \
      | (((n) & 0x00ff000000000000ull) >> 40) \
      | (((n) & 0x0000ff0000000000ull) >> 24) \
      | (((n) & 0x000000ff00000000ull) >> 8)  \
      | (((n) & 0x00000000ff000000ull) << 8)  \
      | (((n) & 0x0000000000ff0000ull) << 24) \
      | (((n) & 0x000000000000ff00ull) << 40) \
      | (((n) & 0x00000000000000ffull) << 56) )
#  define bswap_32(n) \
      ( (((n) & 0xff000000ul) >> 24) \
      | (((n) & 0x00ff0000ul) >> 8)  \
      | (((n) & 0x0000ff00ul) << 8)  \
      | (((n) & 0x000000fful) << 24) )
#  define bswap_16(n) \
      ( (((n) & ((unsigned short)0xff00ul)) >> 8)  \
      | (((n) & ((unsigned short)0x00fful)) << 8)  )
#  define THRIFT_htolell(n) bswap_64(n)
#  define THRIFT_letohll(n) bswap_64(n)
#  define THRIFT_htolel(n) bswap_32(n)
#  define THRIFT_letohl(n) bswap_32(n)
#  define THRIFT_htoles(n) bswap_16(n)
#  define THRIFT_letohs(n) bswap_16(n)
# endif /* GNUC & GLIBC */
#elif __THRIFT_BYTE_ORDER == __THRIFT_LITTLE_ENDIAN
#  define THRIFT_htolell(n) (n)
#  define THRIFT_letohll(n) (n)
#  define THRIFT_htolel(n) (n)
#  define THRIFT_letohl(n) (n)
#  define THRIFT_htoles(n) (n)
#  define THRIFT_letohs(n) (n)
# if defined(__GNUC__) && defined(__GLIBC__)
#  include <byteswap.h>
#  define THRIFT_ntohll(n) bswap_64(n)
#  define THRIFT_htonll(n) bswap_64(n)
# elif defined(_MSC_VER) /* Microsoft Visual C++ */
#  define THRIFT_ntohll(n) ( _byteswap_uint64((ui64)n) )
#  define THRIFT_htonll(n) ( _byteswap_uint64((ui64)n) )
# elif !defined(THRIFT_ntohll) /* Not GNUC/GLIBC or MSVC */
#  define THRIFT_ntohll(n) ( (((ui64)ntohl((ui32)n)) << 32) + ntohl((ui32)(n >> 32)) )
#  define THRIFT_htonll(n) ( (((ui64)htonl((ui32)n)) << 32) + htonl((ui32)(n >> 32)) )
# endif /* GNUC/GLIBC or MSVC or something else */
#else /* __THRIFT_BYTE_ORDER */
# error "Can't define THRIFT_htonll or THRIFT_ntohll!"
#endif

/**
 * global none str
 */

#ifndef _UNIQUE_STR_
#define _UNIQUE_STR_

class NetWorkEndian {
public:
    virtual ui16 toWire16(ui16 x) = 0;

    virtual ui32 toWire32(ui32 x) = 0;

    virtual ui64 toWire64(ui64 x) = 0;

    virtual ui16 fromWire16(ui16 x) = 0;

    virtual ui32 fromWire32(ui32 x) = 0;

    virtual ui64 fromWire64(ui64 x) = 0;
};


class TNetworkBigEndian : public NetWorkEndian {
public:
    ui16 toWire16(ui16 x) override   {
        return htons(x);
    }
    ui32 toWire32(ui32 x) override   {
        return htonl(x);
    }
    ui64 toWire64(ui64 x) override   {
        return THRIFT_htonll(x);
    }
    ui16 fromWire16(ui16 x) override {
        return ntohs(x);
    }
    ui32 fromWire32(ui32 x) override {
        return ntohl(x);
    }
    ui64 fromWire64(ui64 x) override {
        return THRIFT_ntohll(x);
    }
};

// On most systems, this will be a bit faster than TNetworkBigEndian
class TNetworkLittleEndian : public NetWorkEndian {
public:
    ui16 toWire16(ui16 x) override   {
        return THRIFT_htoles(x);
    }
    ui32 toWire32(ui32 x) override   {
        return THRIFT_htolel(x);
    }
    ui64 toWire64(ui64 x) override   {
        return THRIFT_htolell(x);
    }
    ui16 fromWire16(ui16 x) override {
        return THRIFT_letohs(x);
    }
    ui32 fromWire32(ui32 x) override {
        return THRIFT_letohl(x);
    }
    ui64 fromWire64(ui64 x) override {
        return THRIFT_letohll(x);
    }
};

#endif


/* byte to other */

union b2i16 {
    ui8 b[2];
    i16 val;
};

union b2i32 {
    ui8 b[4];
    i32 val;
};

union b2i64 {
    ui8 b[8];
    i64 val;
};

/* 并不是想象中的double val, 而是ui64, 序列化之前变成了ui64 */
union b2dub {
    ui8 b[8];
    ui64 val;
};

#ifdef __GNUC__
#define LIKELY(val) (__builtin_expect((val), 1))
#define UNLIKELY(val) (__builtin_expect((val), 0))
#else
#define LIKELY(val) (val)
#define UNLIKELY(val) (val)
#endif

#endif
