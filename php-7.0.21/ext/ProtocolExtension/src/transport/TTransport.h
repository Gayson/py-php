#ifndef _CPP_CONVERT_TTRANSPORT_H_
#define _CPP_CONVERT_TTRANSPORT_H_

#include "../TException.h"
#include "../TType.h"
#include <string>
namespace CPPConvert {
namespace CPPTransport {
class TTransport {
public:
    virtual ~TTransport() {}

    virtual bool isOpen() {
        return false;
    }
    virtual void open() throw(CPPException::CPPTException) = 0;
    virtual void close() = 0;
    virtual bool peek() {
        return isOpen();
    }

    virtual void read(ui8* buf, ui32 len) = 0;
    virtual void readAll(ui8* buf, ui32 len) = 0;

    virtual void write(const ui8* buf, ui32 len) throw() = 0;
    virtual void flush() throw() = 0;

    /**
     * 原Thrift CPP TProtocol函数，PHP TProtocol不存在，因此留一个接口。
     */

    virtual const ui8 *borrow(ui8 *buf, ui32 *len) {
        return NULL;
    }

    virtual void consume(ui32 len) {
        return;
    }

protected:
    TTransport() {}
private:
};

};
};

#endif
