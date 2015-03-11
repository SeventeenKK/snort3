//--------------------------------------------------------------------------
// Copyright (C) 2014-2015 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// ips_rem.cc author Russ Combs <rucombs@cisco.com>

#include <sys/types.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "snort_types.h"
#include "snort_debug.h"
#include "snort.h"
#include "detection/detection_defines.h"
#include "framework/ips_option.h"
#include "framework/parameter.h"
#include "framework/module.h"

#define s_name "rem"

//-------------------------------------------------------------------------
// module
//-------------------------------------------------------------------------

static const Parameter s_params[] =
{
    { "~", Parameter::PT_STRING, nullptr, nullptr,
      "comment" },

    { nullptr, Parameter::PT_MAX, nullptr, nullptr, nullptr }
};

#define s_help \
    "rule option to convey an arbitrary comment in the rule body"

class RemModule : public Module
{
public:
    RemModule() : Module(s_name, s_help, s_params) { }
    bool set(const char*, Value&, SnortConfig*) override;
};

bool RemModule::set(const char*, Value& v, SnortConfig*)
{
    if ( !v.is("~") )
        return false;

    return true;
}

//-------------------------------------------------------------------------
// api methods
//-------------------------------------------------------------------------

static Module* mod_ctor()
{
    return new RemModule;
}

static void mod_dtor(Module* m)
{
    delete m;
}

static IpsOption* rem_ctor(Module*, OptTreeNode*)
{
    return nullptr;
}

static const IpsApi rem_api =
{
    {
        PT_IPS_OPTION,
        sizeof(IpsApi),
        IPSAPI_VERSION,
        0,
        API_RESERVED,
        s_name,
        s_help,
        API_OPTIONS,
        mod_ctor,
        mod_dtor
    },
    OPT_TYPE_META,
    0, PROTO_BIT__NONE,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    rem_ctor,
    nullptr,
    nullptr
};

#ifdef BUILDING_SO
SO_PUBLIC const BaseApi* snort_plugins[] =
{
    &rem_api.base,
    nullptr
};
#else
const BaseApi* ips_rem = &rem_api.base;
#endif

