/**
 * @file Factory.h
 * @brief Implememtation of factory pattern
 */
#ifndef _CVM_BASE_FACTORY_H_
#define _CVM_BASE_FACTORY_H_

#include <map>
#include <memory>

namespace cvm
{

namespace base
{
/**
 * @class Factory
 * @brief Implements a Factory design pattern with register and create methods
 *
 * The objects created by this factory all implement the same interface
 * (namely, Product). This design pattern is useful in settings where
 * multiple implementations of an interface are available, and one wishes to
 * defer the choice of the implementation in use.
 *
 * @param IdentifierType Type used for identifying the registered classes,
 * typically std::string.
 * @param ProductType The interface implemented by the registered classes
 * @param Producer Function returning a pointer to an instance of
 * the registered class
 */
template<typename IdentifierType,
         typename ProductType,
         typename Producer = ProductType* (*)()>
class Factory
{
public:
      /**
       * @brief Registers the class given by the creator function, linking it to id.
       * Registration must happen prior to calling CreateObject.
       * @param id Identifier of the class being registered
       * @param creator Function returning a pointer to an instance of
       * the registered class
       * @return True iff the key id is still available
       */
      bool regist(const IdentifierType& id, Producer producer)
      {
          return _producers.insert(std::make_pair(id, producer)).second;
      }

      /**
       * @brief Unregisters the class with the given identifier
       * @param id The identifier of the class to be unregistered
       */
      bool unregist(const IdentifierType& id)
      {
          return _producers.erase(id) == 1;
      }

      /**
       * @brief Creates and transfers membership of an object of type matching id.
       * Need to register id before CreateObject is called.
       * @param id The identifier of the class we which to instantiate
       */
      template<typename ...Args>
      std::unique_ptr<ProductType> createObject(const IdentifierType& id, Args&& ...args)
      {
          auto it = _producers.find(id);
          if (it == _producers.end()) {
              return nullptr;
          }else {
              return std::unique_ptr<ProductType>((it->second)(std::forward<Args>(args)...));
          }
      }

private:
    std::map<IdentifierType, Producer> _producers;
};

}

}


#endif // _CVM_BASE_FACTORY_H_
