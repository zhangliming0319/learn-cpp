
#ifndef FOO_EXPORT_H
#define FOO_EXPORT_H

#ifdef FOO_STATIC_DEFINE
#  define FOO_EXPORT
#  define FOO_NO_EXPORT
#else
#  ifndef FOO_EXPORT
#    ifdef foo_EXPORTS
        /* We are building this library */
#      define FOO_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define FOO_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef FOO_NO_EXPORT
#    define FOO_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef FOO_DEPRECATED
#  define FOO_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef FOO_DEPRECATED_EXPORT
#  define FOO_DEPRECATED_EXPORT FOO_EXPORT FOO_DEPRECATED
#endif

#ifndef FOO_DEPRECATED_NO_EXPORT
#  define FOO_DEPRECATED_NO_EXPORT FOO_NO_EXPORT FOO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FOO_NO_DEPRECATED
#    define FOO_NO_DEPRECATED
#  endif
#endif

#endif /* FOO_EXPORT_H */
