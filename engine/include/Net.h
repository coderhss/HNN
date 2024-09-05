#ifndef HNN_NET_H
#define HNN_NET_H
#include "NetBase.h"
#include "Executer.h"

namespace HNN {
    class Net : public NetBase {
    public:
        Net() = default;
        
        std::shared_ptr<Executer> getExecuter();
    };
} // namespace Net

#endif
