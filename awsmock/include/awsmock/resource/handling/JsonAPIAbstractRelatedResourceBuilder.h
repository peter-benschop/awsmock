//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRELATEDRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRELATEDRESOURCEBUILDER_H

#include "awsmock/resource/handling/JsonAPIAbstractResourceBuilder.h"
#include "awsmock/resource/handling/IRelatedResourceBuilder.h"

namespace AwsMock {

    /**
     * @see IRelatedResourceBuilder
     * @see JsonAPIAbstractResourceBuilder
     */
    class JsonAPIAbstractRelatedResourceBuilder :
            public JsonAPIAbstractResourceBuilder,
            public IRelatedResourceBuilder {
    public:
        std::string identifier() const override;

    protected:
        JsonAPIAbstractRelatedResourceBuilder(
                const std::string &,
                const std::string &
        );

    private:
        std::string _identifier;

    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRELATEDRESOURCEBUILDER_H
