/*
Advanced Computing Center for Research and Education Proprietary License
Version 1.0 (April 2006)

Copyright (c) 2006, Advanced Computing Center for Research and Education,
 Vanderbilt University, All rights reserved.

This Work is the sole and exclusive property of the Advanced Computing Center
for Research and Education department at Vanderbilt University.  No right to
disclose or otherwise disseminate any of the information contained herein is
granted by virtue of your possession of this software except in accordance with
the terms and conditions of a separate License Agreement entered into with
Vanderbilt University.

THE AUTHOR OR COPYRIGHT HOLDERS PROVIDES THE "WORK" ON AN "AS IS" BASIS,
WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS FOR A PARTICULAR
PURPOSE, AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Vanderbilt University
Advanced Computing Center for Research and Education
230 Appleton Place
Nashville, TN 37203
http://www.accre.vanderbilt.edu
*/ 

#include "ibp_server.h"
#include <unis_registration.h>

//*************************************************************************
//  install_commands - Install all the depot commans in the global function table
//*************************************************************************

void register_unis(inip_file_t *kf)
{
  /*name = "Phoebus Gateway";
    type = "phoebus";
    endpoint = "http://monitor.incntre.iu.edu:9000";
    init_register = TRUE;
    registration_interval = 120;
    */
  char* unis_name = inip_get_string(kf, "unis", "name", NULL);
  char* unis_type = inip_get_string(kf, "unis", "type", NULL);
  char* unis_endpoint = inip_get_string(kf, "unis", "endpoint", NULL);
  //Todo: Do we need to support more than one ips here?
  char* unis_publicip = inip_get_string(kf, "unis", "publicip", NULL);
  //Todo: Do we need to obtain interfaces?
  char* unis_publicport = inip_get_integer(kf, "unis", "publicport", -1);
  int unis_do_register = inip_get_integer(kf, "unis", "init_register", 0);
  int unis_reg_interval = inip_get_integer(kf, "unis", "registration_interval", UNIS_REG_INTERVAL);

  if(!unis_name || !unis_type || !unis_endpoint) {
    log_printf(0, "register_unis: no unis information present. Unis registration will not be done.");
    return;
  }

  unis_ip_port ip_port = { .ip = unis_publicip, .port=unis_publicport};
  unis_ip_port ip_ports[ ] = {ip_port};
  unis_ip_port_array ip_port_array = {
    .ip_ports = ip_ports,
    .count = 1
  };

  unis_config config = {
    .name = unis_name,
    .type = unis_type,
    .endpoint = unis_endpoint,
    .ifaces = ip_port_array,
    .do_register = unis_do_register,
    .registration_interval = unis_reg_interval,
    .refresh_timer = UNIS_REFRESH_TO
  };

  if(unis_init(config) == 0) {
    log_printf(5, "register_unis: unis registration is successful.");
  } else {
    log_printf(5, "register_unis: error in unis registration.");
  }

}
