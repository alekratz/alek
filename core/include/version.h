#ifndef ALEK_VERSION_H
#define ALEK_VERSION_H

#define STR(s) _STR(s)
#define _STR(s) #s
#define VERSION_STR "v" STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_REVISION) \
        "-" STR(VERSION_TAG)

#endif