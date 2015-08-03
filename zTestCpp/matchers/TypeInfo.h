//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TypeInfo.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef TypeInfo_h__
#define TypeInfo_h__



namespace ztest {

    namespace detail {


        typedef struct unknown_type
        {
            static const char* name()
            {
                return  "[unknown type]";
            }
        } unknown_type;

        template<typename T>
        struct const_type
        {
            static const bool is_constant = false;
        };
        template<typename T>
        struct const_type < const T >
        {
            static const bool is_constant = true;
        };

        template<typename T>
        struct ref_type
        {
            static const bool is_ref = false;
        };

        template<typename T>
        struct ref_type < T & >
        {
            static const bool is_ref = true;
        };


        template<typename T>
        struct type_info_base : unknown_type
        {
            static const bool is_string = false;
            static const bool is_integral = false;
            static const bool is_float = false;
            static const bool is_numeric = is_integral || is_float;

            static const bool is_ptr = ptr_type<T>::is_ptr;
            static const bool is_ref = ref_type<T>::is_ref;
            static const bool is_constant = const_type<T>::is_constant;

        };


        typedef struct string_type
        {
            static const bool is_string = true;
            static const bool is_integral = false;
            static const bool is_float = false;
            static const bool is_numeric = is_integral || is_float;

            static const char* name()
            {
                return  "string";
            }

        } string_type;

        template<typename T> struct ptr_type
        {
            static const bool is_ptr = false;
        };

        template<typename T>
        struct ptr_type < T * >
        {
            static const bool is_ptr = true;


        };




        template<>
        struct type_info_base <char * > : string_type, ptr_type<char*>
        {
        };

        template<>
        struct type_info_base<const char*> : string_type, ptr_type<const char *>
        {

        };
        template<>
        struct type_info_base<std::string> : string_type
        {
        };
        template<>
        struct type_info_base<const std::string> : string_type
        {
        };


        template<typename T>
        struct type_info : type_info_base < T >
        {
            typedef T type;
        };

        template<typename T>
        struct type_info<T &> : type_info < T  >
        {
            //typedef T type;
            static const bool is_ref = true;
        };

        template<typename T>
        struct type_info< const T> : type_info <  T >
        {
            //typedef T type;
            static const bool is_constant = true;

        };

        /*template<>
        struct type_info< unsigned> : type_info_base < unsigned >
        {
            //typedef T type;
            static const bool is_constant = true;

        };*/




        template<typename T>
        struct type_kind
        {
            typedef enum TypeKind
            {
                UNKNOWN_TYPE = 0,
                STRING_TYPE,
                INT_TYPE,
                FLOAT_TYPE,

            } TypeKind;

            static const TypeKind _kind = type_info<T>::is_string ? STRING_TYPE
                                          : type_info<T>::is_integral ? INT_TYPE
                                          : type_info<T>::is_float ? FLOAT_TYPE
                                          : UNKNOWN_TYPE;

            template<TypeKind>
            struct type_kind_selector
            {
                typedef typename type_info<T>::type kind;
            };

            template<>
            struct type_kind_selector < STRING_TYPE >
            {
                typedef struct string_type kind;
            };

            template<>
            struct type_kind_selector < INT_TYPE >
            {
                typedef struct int_type kind;
            };

            template<>
            struct type_kind_selector < FLOAT_TYPE >
            {
                typedef struct float_type kind;
            };

            typedef typename type_kind_selector<_kind>::kind  value;

        };


        typedef struct int_type
        {
            static const char* name()
            {
                return  "integral";
            }
        } int_type;

        typedef struct float_type
        {
            static const char* name()
            {
                return  "floating point";
            }
        } float_type;



#define MAKE_TYPEINFO(t,i,f) \
     template<>  struct type_info < t> : type_info_base < t >  { \
        static const char* name() { return #t; } \
        static const bool is_integral = i; \
        static const bool is_float = f;  \
        static const bool is_numeric = f || i;  \
        };

        MAKE_TYPEINFO(bool, true, false)
        MAKE_TYPEINFO(char, true, false)
        MAKE_TYPEINFO(short, true, false)
        MAKE_TYPEINFO(long, true, false)
        MAKE_TYPEINFO(int, true, false)
        MAKE_TYPEINFO(long long, true, false)

        MAKE_TYPEINFO(float, false, true)
        MAKE_TYPEINFO(double, false, true)
        MAKE_TYPEINFO(long double, false, true)

        //unsinged / signed
        MAKE_TYPEINFO(unsigned char, true, false)
        MAKE_TYPEINFO(unsigned short, true, false)
        MAKE_TYPEINFO(unsigned long, true, false)
        MAKE_TYPEINFO(unsigned int, true, false)
        MAKE_TYPEINFO(unsigned long long, true, false)

        MAKE_TYPEINFO(signed char, true, false)
        //MAKE_TYPEINFO(signed short, true, false)
        //MAKE_TYPEINFO(signed long, true, false)
        //MAKE_TYPEINFO(signed int, true, false)
        //MAKE_TYPEINFO(signed long long, true, false)



    }//end namespace detail

}//end namespace ztest



#endif // TypeInfo_h__