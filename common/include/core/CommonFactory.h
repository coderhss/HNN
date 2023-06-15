//
// Created by bryab on 23-6-9.
//

#ifndef HNN_COMMONFACTORY_H
#define HNN_COMMONFACTORY_H
#include <unordered_map>
#include <functional>
#include <memory>
#include "log.h"

template < typename Base > class CommonFactory {
public:
    using FactoryCreator = std::function< std::shared_ptr< Base >() >;
    using FactoryMap = std::unordered_map< std::string, FactoryCreator >;

    static CommonFactory& getInstance() {
        static CommonFactory< Base > factory;
        return factory;
    }

    void Register(const std::string& key, FactoryCreator creator) {
        if (mCreatorMap.count(key)) {
            return;
        }
        mCreatorMap[key] = creator;
    }

    std::shared_ptr< Base > Create(const std::string& key) {
        if (!mCreatorMap.count(key)) {
            LOG_E("common factory {} not register", key);
            return nullptr;
        }
        return mCreatorMap[key]();
    }

private:
    FactoryMap mCreatorMap;
};

template < typename Base > class CommonRegister {
public:
    using FactoryCreator = std::function< std::shared_ptr< Base >() >;
    CommonRegister(const std::string& type, FactoryCreator creator) {
        CommonFactory< Base >::getInstance().Register(type, creator);
    }
};

#define REGISTER_COMMON_ENGINE(namespaces, key, classbase, classname)                       \
    namespace {                                                                             \
        std::shared_ptr< namespaces::classbase > creator_##key##_##classname() {            \
            return std::shared_ptr< namespaces::classbase >(new namespaces::classname());   \
        }                                                                                   \
        static CommonRegister< namespaces::classbase >                                      \
                g_creator_##key##_##classname(#key, creator_##key##_##classname);           \
    }

#endif //HNN_COMMONFACTORY_H
