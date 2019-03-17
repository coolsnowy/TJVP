/**
 * @file Main.h
 * @brief 统一定义每个模块的主函数
 *
 */
#ifndef _CVM_MAIN_H_
#define _CVM_MAIN_H_

#define MAIN(AppType, ConfigType, configFile) \
    int main(int argc, char** argv) { \
        ConfigType::printHelp(); \
        ConfigType config(argc, argv, configFile); \
        config.printConfig(); \
        AppType app(config); \
        app.loop(); \
        return 0; \
    }

#endif // _CVM_MAIN_H_
