//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/module/mapper/Mapper.h>

namespace AwsMock::Dto::Module {

    Dto::Module::Module::ModuleList Mapper::map(const std::vector<Database::Entity::Module::Module> &moduleList) {

        Dto::Module::Module::ModuleList dtoList;
        for (const auto &module: moduleList) {
            Dto::Module::Module moduleDto = {
                    .name = module.name,
                    .status = module.state,
                    .created = module.created,
                    .modified = module.modified};
            dtoList.emplace_back(moduleDto);
        }
        return dtoList;
    }

}// namespace AwsMock::Dto::Module