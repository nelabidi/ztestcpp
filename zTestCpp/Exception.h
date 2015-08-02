//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestCpp
// FILE:  Exception.h
// PURPOSE: define ztest::Exception class
// DATE: 2015/08/01
// NOTES: depends on std::expection, std::string, std::stringstream
//
//////////////////////////////////////////////////////////////////////////

#ifndef Exception_h__
#define Exception_h__

#if _MSC_VER < 1200
#define nullptr 0
#endif


namespace ztest {

    struct Exception : public std::runtime_error
    {
        Exception(const char* message, const char *file = nullptr, int line = 0)
            : std::runtime_error(message),
              _line(line)
        {
            _file = (file != nullptr) ? file : "";
        }
        Exception(const std::string message, const char *file = nullptr, int line = 0)
            : std::runtime_error(message),
              _line(line)
        {
            _file = (file != nullptr) ? file : "";
        }

        std::string getFile() const
        {
            return _file;
        }
        int getLine() const
        {
            return _line;
        }
        std::string where() const
        {
            std::stringstream ss;
            ss << getFile() << "(" << getLine() << ")";
            return ss.str();
        }
        virtual ~Exception() throw() {}
    private:
        std::string _file;
        int         _line;
    };

}



#endif // Exception_h__