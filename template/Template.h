#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/Logging.h>
#include <cvm/base/NonCopyable.h>
#include <template/TemplateConfig.h>

namespace cvm
{
namespace tpl
{

class Template : public base::NonCopyable
{
public:
    Template(const TemplateConfig& config)
        : _config(config)
    {
        // lcm
        if (!_lcm.good()) {
            DIE("Lcm init error");
        }

        // Your initialization code goes here
    }

    ~Template()
    {
        // Your de-initialization code goes here
    }

    void loop()
    {
        // Your main loop code goes here
    }

private:
    lcm::LCM _lcm;
    const TemplateConfig _config;
};

}

}

#endif // _TEMPLATE_H_
