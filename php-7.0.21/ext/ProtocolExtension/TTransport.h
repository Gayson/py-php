#ifndef _CPP_CONVERT_TTRANSPORT_H_
#define _CPP_CONVERT_TTRANSPORT_H_

#include "TException.h"
#include "TType.h"
#include <string>
namespace CPPConvert {
namespace CPPTransport {
class TTransport {
public:
    virtual bool isOpen() {
        return false;
    }
    virtual void open() throw(CPPException::CPPTException) = 0;
    virtual void close() = 0;
    virtual bool peek() {
        return isOpen();
    }

    virtual std::string read(ui8* buf, ui32 len) = 0;
    virtual std::string readAll(ui8* buf, ui32 len);

    virtual void write(const uint8_t* buf, uint32_t len) throw();
    virtual void flush() throw();

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
private:
};
};
};

#endif
