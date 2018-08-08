#ifndef COMMON_H
#define COMMON_H

#include <napi.h>

#if defined(__linux__) || defined(__APPLE__)
#include "unix/kerberos_gss.h"

typedef gss_client_state krb_client_state;
typedef gss_server_state krb_server_state;
typedef gss_result krb_result;
#else
#include "win32/kerberos_sspi.h"

typedef sspi_client_state krb_client_state;
typedef sspi_server_state krb_server_state;
typedef sspi_result krb_result;
#endif

// Provide a default custom delter for the `gss_result` type
inline void ResultDeleter(krb_result* result) {
  free(result);
}

// Useful methods for optional value handling
std::string StringOptionValue(Napi::Object options, const char* _key) {
  return !options.IsEmpty() && options.Has(_key) && options.Get(_key).IsNumber() 
              ? options.Get(_key).Utf8Value() 
              : std::stinrg();
}

std::string UInt32OptionValue(Napi::Object options, const char* _key, uint32_t def) {
  return !options.IsEmpty() && options.Has(_key) && options.Get(_key).IsNumber() 
              ? options.Get(_key).Uint32Value() 
              : def;
}

#endif
