# -*- cmake -*-

# - Find Phoebus libraries and includes
#
# This module defines
#    UNISC_INCLUDE_DIR - where to find libxsp_client.h
#    UNISC_LIBRARIES - the libraries needed to use Phoebus.
#    UNISC_FOUND - If false didn't find phoebus

# Find the include path

find_path(UNISC_INCLUDE_DIR unis_registration.h)

find_library(UNISC_LIBRARY NAMES unis-c curl jansson)
find_library(CURL_LIBRARY NAMES curl)
find_library(JANSSON_LIBRARY NAMES jansson)

if (CURL_LIBRARY)
  SET(CURL_FOUND "YES")
endif (CURL_LIBRARY)

if (JANSSON_LIBRARY)
  SET(JANSSON_FOUND "YES")
endif (JANSSON_LIBRARY)

if (UNISC_LIBRARY AND UNISC_INCLUDE_DIR)
    SET(UNISC_FOUND "YES")
endif (UNISC_LIBRARY AND UNISC_INCLUDE_DIR)

if (UNISC_FOUND)
  message(STATUS "Found unis-c library: ${UNISC_LIBRARY}")
else (UNISC_FOUND)
   message(STATUS "Could not find unis-c library")
endif (UNISC_FOUND)

if (CURL_FOUND)
  message(STATUS "Found curl library: ${CURL_LIBRARY}")
else (CURL_FOUND)
   message(STATUS "Could not find curl library")
endif (CURL_FOUND)

if (JANSSON_FOUND)
  message(STATUS "Found jansson library: ${JANSSON_LIBRARY}")
else (JANSSON_FOUND)
   message(STATUS "Could not find jansson library")
endif (JANSSON_FOUND)

MARK_AS_ADVANCED(
  UNISC_LIBRARY
  JANSSON_LIBRARY
  CURL_LIBRARY
  UNISC_FOUND
  JANSSON_FOUND
  CURL_FOUND
)

