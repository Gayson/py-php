#ifndef _CPP_CONVERT_TBUFFERDTRANSPORT_H_
#define _CPP_CONVERT_TBUFFERDTRANSPORT_H_

#include "../TException.h"
#include "../TType.h"
#include "TTransport.h"
#include <string>
namespace CPPConvert {
namespace CPPTransport {
class TBufferdTransport: public TTransport {
public:
    TBufferdTransport(ui32 buf_size)
        : TTransport() {
        this->buf_size_ = buf_size;
        this->len_ = 0;
        this->buf_ = (ui8 *)malloc(buf_size + 1);
        this->time_ = 0;
        this->read_len_ = 0;
    }

    ~TBufferdTransport() {
        free(this->buf_);
    }

    bool isOpen() override {
        return true;
    }
    void open() throw(CPPException::CPPTException) override {};
    void close() override {};
    bool peek() override {
        return isOpen();
    }

    void read(ui8 *buf, ui32 len) override {
        throw CPPException::CPPTException::CPPTException();
    };
    void readAll(ui8 *buf, ui32 len) override {
        if (this->read_len_ + len <= this->len_) {
            memcpy(buf, this->buf_ + this->read_len_, len);
            this->read_len_ += len;
        }
    };

    void write(const ui8 *buf, ui32 len) throw() override {
        if (len + this->len_ >= this->buf_size_) {
            ui32 tlen = this->buf_size_ - this->len_;
            memcpy(buf_ + len_, buf, tlen);
            flush();
            buf += tlen;
            len -= tlen;
        }
        memcpy(this->buf_ + len_, buf, len);
        len_ += len;
    };
    void flush() throw() override {
        this->printBuf();
        this->len_ = 0;
    };

    void printBuf() {
        this->time_++;
        this->buf_[this->len_] = '\0';
    }

    const ui8 *borrow(ui8 *buf, ui32 *len) override {
        return NULL;
    }

    void consume(ui32 len) override {
        return;
    }

protected:
private:
    ui8 *buf_;
    ui32 len_;
    ui32 buf_size_;

    ui32 read_len_;

    int time_;
};
};
};

#endif
