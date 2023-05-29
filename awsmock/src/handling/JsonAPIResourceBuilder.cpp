#include "awsmock/resource/handling/JsonAPIResourceBuilder.h"

namespace AwsMock {

    JsonAPIResourceBuilder::JsonAPIResourceBuilder() : JsonAPIAbstractRootResourceBuilder("") {}

    JsonAPIResourceBuilder::JsonAPIResourceBuilder(const std::string &url) : JsonAPIAbstractRootResourceBuilder(url) {}

    JsonAPIResourceBuilder::~JsonAPIResourceBuilder() {}
}
