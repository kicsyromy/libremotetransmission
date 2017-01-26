#ifndef LIBRT_GLOBAL_H
#define LIBRT_GLOBAL_H

#if defined(_MSC_VER)
    /* Microsoft */
#   define EXPORT_SYMBOL __declspec(dllexport)
#   define IMPORT_SYMBOL __declspec(dllimport)
#elif defined(__GNUC__)
    /* GCC */
#   define EXPORT_SYMBOL __attribute__((visibility("default")))
#   define IMPORT_SYMBOL
#else
#   define EXPORT_SYMBOL
#   define IMPORT_SYMBOL
#   pragma warning Unknown dynamic link import/export semantics.
#endif

#if defined(RT_LIB)
#   define LIBRT_API    EXPORT_SYMBOL
#else
#   define LIBRT_API    IMPORT_SYMBOL
#endif

#define DISABLE_COPY(klass) \
    klass(const klass &other) = delete; \
    klass &operator =(const klass &other) = delete;

#define DISABLE_MOVE(klass) \
    klass(klass &&other) = delete; \
    klass &operator =(klass &&other) = delete;

#endif // LIBRT_GLOBAL_H