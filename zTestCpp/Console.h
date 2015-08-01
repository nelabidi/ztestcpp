//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  Console.h
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////



#ifndef Console_h__
#define Console_h__


#ifdef _WIN32

inline std::ostream& FAIL_COLOR(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& PASS_COLOR(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}
//white
inline std::ostream& DEFAULT_COLOR(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}


#else

#define FAIL_COLOR
#define PASS_COLOR
#define DEFAULT_COLOR


#endif // _WIN32




#endif // Console_h__