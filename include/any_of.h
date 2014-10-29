#pragma once

#include <type_traits>
#include <utility>

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
        public: template<typename T1> typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() {
            return value;
        }
        
        /// @brief Type conversion to T
        public: constexpr
        operator T() const noexcept {
            return value;
        }
        
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
        typename std::enable_if<std::is_same<T,T1>::value,T>::type&
        as() {
            return value;
        }
        
        /// @brief Casts (reinterprets) the value to the specified type
        public: template<typename T2>
        typename std::enable_if<!std::is_same<T,T2>::value,T2>::type&
        as() {
            return alternative_values.template as<T2>();
        }
        
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
    
    namespace __testing {
        
    
    }
    
}