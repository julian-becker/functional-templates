#pragma once

#include <type_traits>
#include <utility>
#include <type_traits/index_of.h>
#include <type_traits/type_at.h>
#include <concepts/insertable.h>

namespace ftmpl {

    /// @brief Union template that allows storage of any value of any of the types listed in the template arguments
    template <typename...> struct
    any_of;
    
    /// @brief specialization of the template any_of for one particular type
    template <typename T> struct
    any_of<T> {
        private: T
        value;
        
        /// @brief Move constructor
        public: explicit constexpr
        any_of(T&& t) noexcept : value(std::forward<T>(t)) {}
        
        
        /// @brief Constructor
        public: explicit constexpr
        any_of(const T& t) noexcept : value(t) {}
        
        /// @brief Destructor
        public:
        ~any_of() {};

        /// @brief copy constructor
        public:
        any_of(const any_of&) = delete;
        
        
        /// @brief Casts the value to the specified type
        public: template<typename T1>
        const typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() {
            return value;
        }
        
        /// @brief Casts the value to the specified type
        public: template<typename T1>
        const typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() const {
            return value;
        }
        
        /// @brief Type conversion to T
        public: constexpr explicit
        operator T() const noexcept {
            return value;
        }
        
        /// @brief Assignment operator for values of type T
        /* public: template<
            typename OTHER_T,
            typename = typename std::enable_if<
                !std::is_same<OTHER_T,T>::value
                && std::is_convertible<T, OTHER_T>::value
            >::type
        >
        operator OTHER_T () const {
            return (OTHER_T)value;
        }*/
        
        /// @brief Assignment operator for values of type T
        public: any_of&
        operator = (const T& val) {
            new (&value) T(val);
            return *this;
        }
        
    };
    
    
    /// @brief Specialization of any_of template for multiple types
    template <typename T, typename...Ts> struct
    any_of<T,Ts...> {
        private: union {
            T
            value;
            
            any_of<Ts...>
            alternative_values;
        };
        
        /// @brief destructor
        public:
        ~any_of() {};
        
        
        /// @brief Move constructor
        public: explicit constexpr
        any_of(T&& t) noexcept : value(std::forward<T>(t)) {}
        
        /// @brief Constructor
        /// @param t value
        public: explicit constexpr
        any_of(const T& t) noexcept : value(t) {}
        
        /// @brief Move constructor
        /// @param alt_val The value
        public: template<typename OTHER_T> explicit constexpr
        any_of(OTHER_T&& alt_val)
        : alternative_values(std::forward<OTHER_T>(alt_val)){}
        
        /// @brief Constructor
        /// @param alt_val The value to assign this instance
        public: template<typename OTHER_T> explicit constexpr
        any_of(const OTHER_T& alt_val)
        : alternative_values(alt_val){}
        
        
        /// @brief Casts (reinterprets) the value to the specified type
        public: template<typename T1>
        const typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() {
            return value;
        }
        
        /// @brief Casts (reinterprets) the value to the specified type
        public: template<typename T1>
        const typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() const {
            return value;
        }
        
        /// @brief Casts (reinterprets) the value to the specified type
        public: template<typename T2>
        const typename std::enable_if<!std::is_same<T,T2>::value,typename std::remove_const<T2>::type>::type&
        as() {
            return alternative_values.template as<T2>();
        }
        
        /// @brief Casts (reinterprets) the value to the specified type
        public: template<typename T2>
        const typename std::enable_if<!std::is_same<T,T2>::value,typename std::remove_const<T2>::type>::type&
        as() const {
            return alternative_values.template as<T2>();
        }
        
        /// @brief Type conversion to T
        public: constexpr explicit
        operator T() const noexcept {
            return value;
        }
        
        /// @brief Assignment operator for values of type T
        public: template<typename OTHER_T> explicit
        operator OTHER_T () const {
            return (OTHER_T)alternative_values;
        }
        
        /// @brief Assignment operator for values of type T
        /* public: template<
            typename OTHER_T,
            typename = typename std::enable_if<
                !std::is_same<OTHER_T,T>::value
                && std::is_convertible<T, OTHER_T>::value
            >::type
        >
        operator OTHER_T () const {
            return (OTHER_T)value;
        }*/
        
        /// @brief Assignment operator for values of type T
        public: any_of<T>&
        operator = (const T& val) {
            new (&value) T(val);
            return *this;
        }
        
        /// @brief Assignment operator for values of type T
        public: any_of&
        operator = (T&& val) {
            new (&value) T(std::forward<T>(val));
            return *this;
        }

        
        /// @brief Assignment operator for values of types different than T
        public: template<typename OTHER_T>
        any_of& operator = (const OTHER_T& alt_val) {
            alternative_values = alt_val;
            return *this;
        }
        
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /// @brief Union template that allows storage of any value of any of the types listed in the template arguments
    template <typename...Ts> struct
    union_of {
    
        private: unsigned
        type_index;
        
        private: any_of<Ts...> value;
        
        /// @brief destructor
        public:
        ~union_of() {};
        
        
        /// @brief Move constructor
        public: template <typename T> constexpr
        union_of(T&& t) noexcept : value(std::forward<T>(t)), type_index(index_of<T,Ts...>::value) {}
        
        /// @brief Constructor
        /// @param ts value
        public: template <typename T> constexpr
        union_of(const T& t) noexcept : value(t), type_index(index_of<T,Ts...>::value) {}
        
        /// @brief Casts (reinterprets) the value to the specified type
        private: template<typename T1>
        const T1&
        as() throw (std::out_of_range) {
            if(type_index != index_of<T1,Ts...>::value)
                throw std::out_of_range("invalid cast to type out of range");
            return value.template as<T1>();
        }
        
        /// @brief Casts (reinterprets) the value to the specified type
        private: template<typename T1>
        const T1&
        as() const throw (std::out_of_range) {
            if(type_index != index_of<T1,Ts...>::value)
                throw std::out_of_range("invalid cast to type out of range");
            return value.template as<T1>();
        }
        
        /// @brief Type conversion to T
        public: template <typename T1> constexpr explicit
        operator T1() const throw (std::out_of_range) {
            return value.template as<T1>();
        }
        
        /// @brief Assignment operator for values of type T
        public: template <typename T1>
        union_of&
        operator = (const T1& val) {
            value = val;
            return *this;
        }
        
        /// @brief Assignment operator for values of type T
        public: template <typename T1>
        union_of&
        operator = (T1&& val) {
            value = std::forward<T1>(val);
            return *this;
        }
        
        
        public: template<
            typename OTHER_T
        > struct
        __helper {
            public: template<
                unsigned INDEX,
                typename = typename std::enable_if<
                    type_traits::is_insertible<OTHER_T,typename type_at<INDEX,Ts...>::type>::value
                >::type
            >
            static OTHER_T& insert (OTHER_T& ostr,const union_of& some_val) {
                if(INDEX == some_val.type_index)
                    return ostr << (typename type_at<INDEX, Ts...>::type)some_val.value;
                else
                    return __helper<OTHER_T>::template insert<(INDEX+1<sizeof...(Ts)?INDEX+1:INDEX)>(ostr,some_val);
            }
        };
        
        public: template<
            typename OTHER_T,
            unsigned INDEX=0,
            typename = typename std::enable_if<
                type_traits::is_insertible<OTHER_T,typename type_at<INDEX,Ts...>::type>::value
            >::type
        >
        friend OTHER_T&
        operator << (OTHER_T& ostr, const union_of& some_val) {
            return __helper<OTHER_T>::template insert<0>(ostr,some_val);
        }
        

    
    };
    
    
    
        static_assert(
            type_traits::is_insertible<
                std::basic_ostream<char,std::__1::char_traits<char> >,
                int
            >::value,
            "error"
        );
    
    
    namespace __testing {
        
    
    }
    
}