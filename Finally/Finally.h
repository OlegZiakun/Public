#ifndef FINALLY_H
#define FINALLY_H

 namespace System
 {
  #define OUTER_CLASS(name) typedef name outerClassName
  #define finally

  #define CALL(name) m_outerClass.name
  #define LC(name) local.name
  #define LCALL(name) m_local.name

  #define trying(tryCatchBlock, finallyBlock) \
  { \
     class Finally_ \
     { \
      public: \
          Finally_ (outerClassName& outerClass, Local_& localClass) : m_outerClass(outerClass), m_local(localClass) {} \
          ~Finally_ () finallyBlock  \
      private: \
          outerClassName& m_outerClass; \
          Local_& m_local; \
      }finally_(*this, local); \
      tryCatchBlock \
  }

  #define trying_(tryCatchBlock, finallyBlock, ...) \
  { \
     class Finally_ \
     { \
      public: \
           Finally_ (outerClassName& outerClass, __VA_ARGS__& localClass) : m_outerClass(outerClass), m_local(localClass) { } \
          ~Finally_ () finallyBlock \
      private: \
          outerClassName& m_outerClass; \
          __VA_ARGS__& m_local; \
      }finally_(*this, local##__VA_ARGS__); \
      tryCatchBlock \
  }

  #define LOCAL(...) struct Local_ { __VA_ARGS__ } local;
  #define LOCAL_(name, ...) struct name { __VA_ARGS__ }; name local##name;
 }

#endif // FINALLY_H
