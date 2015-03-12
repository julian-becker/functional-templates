//
//  Factory.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 22.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#pragma once
#include <memory> // for std::unique_ptr
#include <functional> // for std::function
#include <type_traits> // for std::enable_if and std::is_base_of
#include <unordered_map> // for std::unordered_map
#include <typeindex>
#include <future>

namespace
factory {
    
    /// @brief Generic factory interface for class hierarchies with base class BASE
    /// @tparam BASE        The Base class for all created instances.
    template <typename BASE> struct
    IFactory {
    
        /// @brief create a new instance
        public: virtual std::unique_ptr<BASE>
        create() const = 0;
        
        public: virtual
        ~IFactory() throw() {}
    };


    /// @brief Concrete generic factory
    /// @tparam BASE    The base class of all instances this factory is able to manufacture
    template <typename BASE>
    struct
    CFactory : public IFactory<BASE> {
        private: std::function<std::unique_ptr<BASE>()>
        creatorFn;
        
        
        /// @brief Setup the constructor arguments for the construction of instances of type DERIVED (must be inherited from BASE)
        /// @tparam DERIVED                     The concrete type this factory will create upon call to create()
        /// @tparam DERIVED_CONSTRUCTOR_ARGS    The constructor arguments to DERIVED
        public: template <
            typename DERIVED,
            typename...DERIVED_CONSTRUCTOR_ARGS,
            typename std::enable_if<std::is_base_of<BASE, DERIVED>::value>::type* = nullptr // sfinae
        > void
        setup(DERIVED_CONSTRUCTOR_ARGS&&...args) {
            creatorFn = [=]{
                return std::unique_ptr<BASE>(new DERIVED(std::forward<DERIVED_CONSTRUCTOR_ARGS>(args)...));
            };
        }
        
        
        /// @brief create a new instance. Before the first call to create(), the factory must be prepared using a call to setup() first.
        /// @result pointer to the newly created instance
        public: virtual std::unique_ptr<BASE>
        create() const {
            return creatorFn();
        }

    };
    
    /// @brief Generic interface for a factory selector. This is typically used in deserialization scenarios, where a key is read that indicates what type is the object that follows.
    /// @tparam BASE            The base class of all instances created by the associated concrete factories.
    template <typename BASE,typename KEY_T> struct
    IFactorySelector {
    
        /// @brief Select a concrete factory based upon some key
        public: virtual std::unique_ptr<IFactory<BASE>>
        get(KEY_T key) const = 0;
        
        public: virtual
        ~IFactorySelector() throw() {}
    };
    
    template <typename BASE,typename KEY_T> struct
    FactorySelector : public IFactorySelector<BASE,KEY_T> {
        private: std::unordered_map<KEY_T,std::type_index>
        keyToTypeMap;
    
        private: std::unordered_map<std::type_index,std::function<std::unique_ptr<IFactory<BASE>>()>>
        creatorFn;
        
        public:
        FactorySelector(std::unordered_map<KEY_T,std::type_index> keyToTypeMap)
        : keyToTypeMap(keyToTypeMap) {}
        
        public: template <
            typename DERIVED,
            typename...DERIVED_CONSTRUCTOR_ARGS,
            typename std::enable_if<std::is_base_of<BASE, DERIVED>::value>::type* = nullptr
        > void
        setup(DERIVED_CONSTRUCTOR_ARGS...args) {
            creatorFn[std::type_index(typeid(DERIVED))] = [=]{
                std::unique_ptr<CFactory<BASE>> f(new CFactory<BASE>);
                f->template setup<DERIVED>(args...);
                return f;
            };
        }
        
        public: virtual std::unique_ptr<IFactory<BASE>>
        get(KEY_T key) const {
            return creatorFn.at(keyToTypeMap.at(key))();
        }

    };

    
};