//////////////////////////////////////////////////////////////////////////
//
// PROJECT:  zTestC++ (zTestCpp) C++ Testing framework
// FILE:  Capture.h
// PURPOSE: ostream capturing
// DATE: 2015/08/16
// NOTES:
//
//////////////////////////////////////////////////////////////////////////



#ifndef Capture_h__
#define Capture_h__


namespace ztest {


    struct Capture
    {
        Capture(std::ostream& o)
            : _target(o)
        {
            _stringstream << "";
            _oldbuf = _target.rdbuf(_stringstream.rdbuf());
        }
        std::string get() const
        {
            return _stringstream.str();
        }

        ~Capture()
        {
            _target.rdbuf(_oldbuf);
        }

    private:
        std::ostream&   _target;
        std::streambuf*  _oldbuf;
        std::stringstream _stringstream;
    };



}



#endif // Capture_h__