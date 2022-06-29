
#include "platform/IPlatform.h"

namespace Engine::XR
{
    class XrPlatform :
            public Core::Platform::IPlatform
    {
    public:
        ~XrPlatform() override = default;

        void Update() override;
    };
}

