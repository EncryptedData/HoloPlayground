//
// Created by russr on 6/28/2022.
//

#pragma once

namespace Engine::Core::Platform
{
    class IPlatform
    {
    public:

        IPlatform() = default;

        virtual ~IPlatform() = default;

        virtual void Update() = 0;
    };
}
