#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include "network.h"
#include "net_sock.h"
#include "log.h"
#include "dns_cache.h"
#include "string_token.h"
#include "cmd_send.h"


//*************************************************************************
//*************************************************************************

int main(int argc, char **argv)
{
  int bufsize = 1024*1024;
  char buffer[bufsize], *bstate;
  int i, port, duration, trash_type, timeout;
  Net_timeout_t dt;
  NetStream_t *ns;
  char *host, *trash_id, *rid;

  if (argc < 7) {
     printf("ibp_undelete host port RID trash_type trash_id duration [timeout]\n");
     printf("   where trash_type is 'expired' or 'deleted'.\n");
     printf("\n");
     return(0);
  }

  i = 1;
  host = argv[i]; i++;
  port = atoi(argv[i]); i++;
  rid = argv[i]; i++;

  if (strcmp(argv[i], "deleted") == 0) {
     trash_type = 0;
  } else if (strcmp(argv[i], "expired") == 0) {
     trash_type = 1;
  } else {
     printf("Invalid trash_type!  Should be 'expired' or 'deleted'.\n");
     return(-1);
  }
  i++;

  trash_id = argv[i]; i++;
  duration = atoi(argv[i]); i++;
  
  timeout = 15;

  if (argc < i) timeout = atoi(argv[i]);

  sprintf(buffer, "1 96 %s %d %s %d %d\n", rid, trash_type, trash_id, duration, timeout);  // IBP_INTERNAL_UNDELETE command

  assert(apr_initialize() == APR_SUCCESS);

  dns_cache_init(10);

  ns = cmd_send(host, port, buffer, &bstate, timeout);
  if (ns == NULL) return(-1);
  if (bstate != NULL) free(bstate);

  set_net_timeout(&dt, 5, 0);

  //** Close the connection
  close_netstream(ns);

  apr_terminate();

  return(0);
}
