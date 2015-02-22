//
//  factory_evolution.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 22.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include "factory_evolution.h"


//
//  main.cpp
//  range-v3
//
//  Created by Julian Becker on 02.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include <iostream>
#include <thread>

/*template <typename BASE>*/ struct
Base {
    virtual
    ~Base() throw() {}
};

#include <unordered_map>
#include <typeindex>



template <typename Base>
struct
Factory {
    private: using
    TInheritanceCheckFn = std::function<bool(std::weak_ptr<Base const>)>;
    
    private:
    static std::unordered_map<std::shared_ptr<Base>,TInheritanceCheckFn> inheritanceCheckFnMap;
    
    public: template <typename DERIVED_TYPE, typename...TS>
    static std::weak_ptr<Base>
    create(TS...args) {
        const std::shared_ptr<Base> pObj = std::make_shared<DERIVED_TYPE>(args...);
        inheritanceCheckFnMap[pObj] = [](std::weak_ptr<Base const> other){
            return dynamic_cast<DERIVED_TYPE const *>(other.lock().get()) != nullptr;
        };
        return pObj;
    }
    
    public: static bool
    isBaseOf(std::weak_ptr<Base const> first, std::weak_ptr<Base const> other) {
        return inheritanceCheckFnMap[first.lock()](other) && !isSameAs(first,other);
    }
    
    public: static bool
    isSameAs(std::weak_ptr<Base const> first, std::weak_ptr<Base const> other) {
        return inheritanceCheckFnMap[first.lock()](other) && inheritanceCheckFnMap[other.lock()](first);
    }
    
    public: static bool
    isDerivedFrom(std::weak_ptr<Base const> first, std::weak_ptr<Base const> other) {
        return isBaseOf(other,first);
    }
    
    public: static void destroy(std::weak_ptr<Base> pObj) {
        inheritanceCheckFnMap.erase(pObj.lock());
    }
};

template <typename Base>
std::unordered_map<std::shared_ptr<Base>,typename Factory<Base>::TInheritanceCheckFn> Factory<Base>::inheritanceCheckFnMap;


// -----------------------
class Channel {};

class
ChannelFactory {
    public: static Channel*
    create() {
        return new Channel;
    }
};

class ChannelFactory_client {
    void useFactory() {
        Channel* ch = ChannelFactory::create();
        // ...
        delete ch;
    }
};

// ------------------------

class SockChannel {};
class
SockChannelFactory {
    public: static SockChannel*
    create() {
        return new SockChannel;
    }
};

class SockChannelFactory_client {
    void useFactory() {
        SockChannel* ch = SockChannelFactory::create();
        // ...
        delete ch;
    }
};

// ------------------------

class FaroBusChannel {};

class
FaroBusChannelFactory {
    public: static FaroBusChannel*
    create() {
        return new FaroBusChannel;
    }
};

class FaroBusChannelFactory_client {
    void useFactory() {
        FaroBusChannel* ch = FaroBusChannelFactory::create();
        // ...
        delete ch;
    }
};

// -------------------------

class WebSocketChannel {};

template <typename CHANNEL_TYPE> class
TChannelFactory {
    public: static CHANNEL_TYPE*
    create() {
        return new CHANNEL_TYPE;
    }
};

class TChannelFactory_client {
    void useFactory() {
        WebSocketChannel* ch1 = TChannelFactory<WebSocketChannel>::create();
        SockChannel* ch2 = TChannelFactory<SockChannel>::create();
        // ...
        delete ch2;
        delete ch1;
    }
};


namespace GenericFactoryRev000 {
// -------------------------
// SockChannel requires some args for construction...
class
SockChannelArgs {
    public:
    SockChannelArgs(unsigned port) {}
};

template <typename CHANNEL_TYPE> class
TChannelFactoryExt {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static CHANNEL_TYPE*
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return new CHANNEL_TYPE(args...);
    }
};

class TChannelFactoryExt_client {
    void useFactory() {
        WebSocketChannel* ch1 = TChannelFactoryExt<WebSocketChannel>::create();
        SockChannelArgs* ch2 = TChannelFactoryExt<SockChannelArgs>::create(5678);
        // ...
        delete ch2;
        delete ch1;
    }
};

}

#include <memory>

namespace GenericFactoryRev001 {

// -------------------------
// We want to use smart pointers to keep track of ownership

class
SockChannelArgs {
    public:
    SockChannelArgs(unsigned port) {}
};

template <typename CHANNEL_TYPE> class
TChannelFactoryExtSmart {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static std::unique_ptr<CHANNEL_TYPE>
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return std::unique_ptr<CHANNEL_TYPE>(new CHANNEL_TYPE(args...));
    }
};

class TChannelFactoryExt_client {
    void useFactory() {
        std::unique_ptr<WebSocketChannel> ch1 = TChannelFactoryExtSmart<WebSocketChannel>::create();
        /// unique -> shared conversion possible:
        std::shared_ptr<SockChannelArgs> ch2 = TChannelFactoryExtSmart<SockChannelArgs>::create(5678);
    }
};

}

namespace GenericFactoryRev002 {

// -------------------------
// We want to use smart pointers to keep track of ownership

class
SockChannelArgs {
    public:
    SockChannelArgs(unsigned port) {}
};

enum class Delegation {
    ERawPointer,
    EUniquePointer
};

template <typename CHANNEL_TYPE,Delegation DELEGATE_TYPE> class
TChannelFactoryExtSmart;


template <typename CHANNEL_TYPE> class
TChannelFactoryExtSmart<CHANNEL_TYPE,Delegation::ERawPointer>
 {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static CHANNEL_TYPE*
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return new CHANNEL_TYPE(args...);
    }
};

template <typename CHANNEL_TYPE> class
TChannelFactoryExtSmart<CHANNEL_TYPE,Delegation::EUniquePointer> {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static std::unique_ptr<CHANNEL_TYPE>
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return std::unique_ptr<CHANNEL_TYPE>(new CHANNEL_TYPE(args...));
    }
};

class TChannelFactoryExt_client {
    void useFactory() {
        std::unique_ptr<WebSocketChannel> ch1 = TChannelFactoryExtSmart<WebSocketChannel,Delegation::EUniquePointer>::create();
        /// unique -> shared conversion possible:
        SockChannelArgs* ch2 = TChannelFactoryExtSmart<SockChannelArgs,Delegation::ERawPointer>::create(5678);
        
        delete ch2;
    }
};

}


namespace GenericFactoryRev003 {

// -------------------------
// We want to use smart pointers to keep track of ownership

class
SockChannelArgs {
    public:
    SockChannelArgs(unsigned port) {}
};

enum class Delegation {
    ERawPointer,
    EUniquePointer
};


template <typename,Delegation> class
TChannelFactory_Impl;

template <typename CHANNEL_TYPE> class
TChannelFactory_Impl<CHANNEL_TYPE,Delegation::ERawPointer> {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static CHANNEL_TYPE*
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return new CHANNEL_TYPE(args...);
    }
};

template <typename CHANNEL_TYPE> class
TChannelFactory_Impl<CHANNEL_TYPE,Delegation::EUniquePointer> {
    public:
    template <typename...CONSTRUCTOR_ARG_TYPES> static std::unique_ptr<CHANNEL_TYPE>
    create(CONSTRUCTOR_ARG_TYPES...args) {
        return std::unique_ptr<CHANNEL_TYPE>(new CHANNEL_TYPE(args...));
    }
};



template <typename> struct
PDelegationPolicy {
    // default policy
    static constexpr Delegation policy = Delegation::EUniquePointer;
};

template <> struct
PDelegationPolicy<SockChannelArgs> {
    static constexpr Delegation policy = Delegation::ERawPointer;
};
template <> struct
PDelegationPolicy<WebSocketChannel> {
    static constexpr Delegation policy = Delegation::EUniquePointer;
};

template <typename CHANNEL_TYPE> using
TChannelFactory = TChannelFactory_Impl<CHANNEL_TYPE,PDelegationPolicy<CHANNEL_TYPE>::policy>;


class TChannelFactoryExt_client {
    void useFactory() {
        std::unique_ptr<WebSocketChannel> ch1 = TChannelFactory<WebSocketChannel>::create();
        /// unique -> shared conversion possible:
        SockChannelArgs* ch2 = TChannelFactory<SockChannelArgs>::create(5678);
        
        delete ch2;
    }
};

}

template <
    typename KEY, typename VALUE
> struct
pair {};

template <typename...PS> struct
map {
    private: using
    type = map<PS...>;
    
    public: template <
        typename KEY,
        typename VALUE
    > using
    insert = map<PS...,pair<KEY,VALUE>>;

    public: template <
        typename PAIR
    > using
    insert_pair = map<PS...,PAIR>;
    
    private: template <typename,typename> struct
    get_impl;
    
    template <typename KEY,typename VALUE,typename...REST> struct
    get_impl<map<pair<KEY,VALUE>,REST...>,KEY> {
        using type = VALUE;
    };

    template <typename FIRST_PAIR, typename KEY,typename...REST> struct
    get_impl<map<FIRST_PAIR,REST...>,KEY> {
        using type = typename get_impl<map<REST...>,KEY>::type;
    };
    
    public: template <
        typename key
    > using
    get = typename get_impl<type,key>::type;
};

template <typename POLICIES, typename KEY> using
get = typename POLICIES::template get<KEY>;



struct PAllocationPolicy {
    struct NewDelete {};
    struct MallocFree {};
};

struct PSerializationPolicy {
    struct Xml {};
    struct Json {};
};

struct POperatinSystem {
    struct Windows {};
    struct Linux {};
    struct MacOSX {};
    struct Android {};
};

struct PChannelType {
    struct SockChannel {};
    struct FaroBusChannel {};
};

using policies = map<pair<PAllocationPolicy,PAllocationPolicy::NewDelete>>;
using new_policies =
        policies
        ::insert<PSerializationPolicy,PSerializationPolicy::Xml>
        ::insert<POperatinSystem,POperatinSystem::Windows>;


#include <type_traits>
static_assert(std::is_same<new_policies::get<PAllocationPolicy>,PAllocationPolicy::NewDelete>::value,"error");
static_assert(std::is_same<new_policies::get<PSerializationPolicy>,PSerializationPolicy::Xml>::value,"error");

#include <string>


/// Interface: IFile ----------------------------------
struct IFile {
    virtual std::string getName() const = 0;
    virtual void touch() = 0;
    virtual ~IFile() throw() {}
};

/// Implementations for IFile -------------------------
template <typename OPERATING_SYSTEM> struct
ConcreteFile;

template <typename POLICY> using
File = ConcreteFile<get<POLICY,POperatinSystem>>;

template <> struct
ConcreteFile<POperatinSystem::Windows> : IFile {
    private: virtual std::string getName() const {
        return "WindowsFile";
    }
    private: virtual void touch(){};
};

template <> struct
ConcreteFile<POperatinSystem::Android> : IFile {
    private: virtual std::string getName() const {
        return "AndroidFile";
    }
    private: virtual void touch() {}
};

/// Factory for IFile -------------------------


template <typename POLICIES, typename=void> struct
FileFactory;

template <typename POLICIES> struct
FileFactory<
    POLICIES,
    typename std::enable_if<
        std::is_same<typename POLICIES::template get<PAllocationPolicy>,PAllocationPolicy::NewDelete>::value
    >::type
>
{
    static IFile* create(){
        return new File<POLICIES>;
    }
};


/// Interface: Allocator ---------------------
class IAllocator {
    public: virtual void allocate(const size_t) = 0;
    public: virtual ~IAllocator() throw() {}
};

template <typename ALLOCATION_POLICY> struct
ConcreteAllocator;

template <typename POLICIES> using
Allocator = ConcreteAllocator<get<POLICIES,PAllocationPolicy>>;



template <> struct
ConcreteAllocator<PAllocationPolicy::NewDelete> : IAllocator {
    template <typename T,typename...ARGS> static T* allocate(ARGS...args) {
        return new T(args...);
    }
};

template <> struct
ConcreteAllocator<PAllocationPolicy::MallocFree> : IAllocator {
    template <typename T,typename...ARGS> static T* allocate(ARGS...args) {
        T* p = std::malloc(sizeof(T));
        if(!p) throw std::bad_alloc();
        return new (p) T(args...);
    }
};

