//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  MatcherBase.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef MatcherBase_h__
#define MatcherBase_h__


namespace ztest {

    struct MatcherBase
    {

        MatcherBase(const char *file, int line) :
            _line(line),
            _file(file),
            _result(false),
            _not(false)
        {}

        void throwException(const char * from, const char *message)
        {
            if (!_result)
            {
                std::string msg(from);
                msg += " Failed with: " + std::string(message);
                throw Exception(msg, _file, _line);
            }
        }

        void not()
        {
            _not = !_not;
        }

    protected:
        bool applyNot(bool result)
        {
            bool retVal = _not ? !result : result;
            _not = false;
            return retVal;
        }

        bool       _not;
        const char* _file;
        int         _line;
        bool        _result;
    };


}//end namespace ztest



#endif // MatcherBase_h__