#include <stdlib.h>

#include "nt.h"
#include "win.h"

#define X(return_type, declarators, name, parameters) \
  EPOLL_INTERNAL return_type(declarators* name) parameters = NULL;
NTDLL_IMPORT_LIST(X)
#undef X

int nt_global_init(void) {
  HMODULE ntdll;

  ntdll = GetModuleHandleW(L"ntdll.dll");
  if (ntdll == NULL)
    return -1;

#define X(return_type, declarators, name, parameters)                         \
  name = (return_type(declarators*) parameters) GetProcAddress(ntdll, #name); \
  if (name == NULL)                                                           \
    return -1;
  NTDLL_IMPORT_LIST(X)
#undef X

  return 0;
}
