#pragma once
#include <awsmock/core/logging/plog/Record.h>
#include <awsmock/core/logging/plog/Util.h>

namespace plog
{
    class PLOG_LINKAGE IAppender
    {
    public:
        virtual ~IAppender()
        {
        }

        virtual void write(const Record& record) = 0;
    };
}
