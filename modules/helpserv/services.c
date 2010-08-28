/*
 * Copyright (c) 2005-2006 Atheme Development Group
 * Rights to this code are documented in doc/LICENSE.
 *
 * This file contains functionality which implements the HelpServ SERVICES command.
 *
 */

#include "atheme.h"
#include "uplink.h"

DECLARE_MODULE_V1
(
	"helpserv/services", false, _modinit, _moddeinit,
	PACKAGE_STRING,
	"Atheme Development Group <http://www.atheme.org>"
);

static void helpserv_cmd_services(sourceinfo_t *si, int parc, char *parv[]);

command_t helpserv_services = { "SERVICES", N_("List all services currently running on the network."), AC_NONE, 1, helpserv_cmd_services };

list_t *helpserv_cmdtree;
list_t *helpserv_helptree;

void _modinit(module_t *m)
{
	MODULE_USE_SYMBOL(helpserv_cmdtree, "helpserv/main", "helpserv_cmdtree");
	MODULE_USE_SYMBOL(helpserv_helptree, "helpserv/main", "helpserv_helptree");

        command_add(&helpserv_services, helpserv_cmdtree);
	help_addentry(helpserv_helptree, "SERVICES", "help/helpserv/services", NULL);
}

void _moddeinit()
{
	command_delete(&helpserv_services, helpserv_cmdtree);
	help_delentry(helpserv_helptree, "SERVICES");
}

static void helpserv_cmd_services(sourceinfo_t *si, int parc, char *parv[])
{
	service_t *sptr;
	mowgli_patricia_iteration_state_t state;

	command_success_nodata(si, _("Services running on %s:"), me.netname);

	MOWGLI_PATRICIA_FOREACH(sptr, &state, services_nick)
	{
		command_success_nodata(si, _("%s"), sptr->nick);
	}

	command_success_nodata(si, _("More information on each service is available by messaging it like so: /msg service help"));

        return;
}
/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */