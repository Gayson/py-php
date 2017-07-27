#ifndef _CPP_CONVERT_CPPEXCEPTION_H_
#define _CPP_CONVERT_CPPEXCEPTION_H_
#include <exception>
namespace CPPConvert {
namespace CPPException {
class CPPTException: public std::exception {
public:
    virtual const char* what() const throw() {
        return "CPPException";
    }
};
};
};

#endif
