#ifndef GALLERYCORE_GLOBAL_H
#define GALLERYCORE_GLOBAL_H

#include <QtCore/qglobal.h>

//the cross-platform way to handle symbol visibility in a shared library
#if defined(GALLERYCORE_LIBRARY)
#  define GALLERYCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define GALLERYCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GALLERYCORE_GLOBAL_H
