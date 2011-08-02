//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#define lutil_shared_cpp

#include "cbase.h"
#include "luamanager.h"
#include "lbaseentity_shared.h"
#include "lbaseplayer_shared.h"
#include "lgametrace.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int luasrc_UTIL_VecToYaw (lua_State *L) {
  lua_pushnumber(L, UTIL_VecToYaw(*(Vector *)luaL_checkvector(L, 1)));
  return 1;
}

static int luasrc_UTIL_VecToPitch (lua_State *L) {
  lua_pushnumber(L, UTIL_VecToPitch(*(Vector *)luaL_checkvector(L, 1)));
  return 1;
}

static int luasrc_UTIL_YawToVector (lua_State *L) {
  Vector v = UTIL_YawToVector(luaL_checknumber(L, 1));
  lua_pushvector(L, &v);
  return 1;
}

static int luasrc_UTIL_TraceLine (lua_State *L) {
  trace_t tr;
  UTIL_TraceLine(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), luaL_checkinteger(L, 3), lua_toentity(L, 4), luaL_checkinteger(L, 5), &tr);
  lua_pushtrace(L, &tr);
  return 1;
}

static int luasrc_UTIL_TraceHull (lua_State *L) {
  trace_t tr;
  UTIL_TraceHull(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), *(Vector *)luaL_checkvector(L, 3), *(Vector *)luaL_checkvector(L, 4), luaL_checkinteger(L, 5), luaL_checkentity(L, 6), luaL_checkinteger(L, 7), &tr);
  lua_pushtrace(L, &tr);
  return 1;
}

static int luasrc_UTIL_TraceEntity (lua_State *L) {
  trace_t tr;
  UTIL_TraceEntity(luaL_checkentity(L, 1), *(Vector *)luaL_checkvector(L, 2), *(Vector *)luaL_checkvector(L, 3), luaL_checkinteger(L, 4), luaL_checkentity(L, 5), luaL_checkinteger(L, 5), &tr);
  lua_pushtrace(L, &tr);
  return 1;
}

static int luasrc_UTIL_EntityHasMatchingRootParent (lua_State *L) {
  lua_pushboolean(L, UTIL_EntityHasMatchingRootParent(luaL_checkentity(L, 1), luaL_checkentity(L, 2)));
  return 1;
}

static int luasrc_UTIL_PointContents (lua_State *L) {
  lua_pushinteger(L, UTIL_PointContents(*(Vector *)luaL_checkvector(L, 1)));
  return 1;
}

static int luasrc_UTIL_TraceModel (lua_State *L) {
  trace_t tr;
  UTIL_TraceModel(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), *(Vector *)luaL_checkvector(L, 3), *(Vector *)luaL_checkvector(L, 4), luaL_checkentity(L, 5), luaL_checkinteger(L, 6), &tr);
  lua_pushtrace(L, &tr);
  return 1;
}

static int luasrc_UTIL_ParticleTracer (lua_State *L) {
  UTIL_ParticleTracer(luaL_checkstring(L, 1), *(Vector *)luaL_checkvector(L, 2), *(Vector *)luaL_checkvector(L, 3), luaL_optint(L, 4, 0), luaL_optint(L, 5, 0), luaL_optboolean(L, 6, 0));
  return 0;
}

static int luasrc_UTIL_Tracer (lua_State *L) {
  UTIL_Tracer(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), luaL_optint(L, 3, 0), luaL_optint(L, 4, -1), luaL_optnumber(L, 5, 0), luaL_optboolean(L, 6, 0), luaL_optstring(L, 7, 0), luaL_optint(L, 8, 0));
  return 0;
}

static int luasrc_UTIL_BloodDrips (lua_State *L) {
  UTIL_BloodDrips(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4));
  return 0;
}

static int luasrc_UTIL_IsLowViolence (lua_State *L) {
  lua_pushboolean(L, UTIL_IsLowViolence());
  return 1;
}

static int luasrc_UTIL_ShouldShowBlood (lua_State *L) {
  lua_pushboolean(L, UTIL_ShouldShowBlood(luaL_checkinteger(L, 1)));
  return 1;
}

static int luasrc_UTIL_BloodImpact (lua_State *L) {
  UTIL_BloodImpact(*(Vector *)luaL_checkvector(L, 1), *(Vector *)luaL_checkvector(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4));
  return 0;
}

static int luasrc_UTIL_BloodDecalTrace (lua_State *L) {
  UTIL_BloodDecalTrace(luaL_checktrace(L, 1), luaL_checkinteger(L, 2));
  return 0;
}

static int luasrc_UTIL_DecalTrace (lua_State *L) {
  UTIL_DecalTrace(luaL_checktrace(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int luasrc_UTIL_IsSpaceEmpty (lua_State *L) {
  lua_pushboolean(L, UTIL_IsSpaceEmpty(luaL_checkentity(L, 1), *(Vector *)luaL_checkvector(L, 2), *(Vector *)luaL_checkvector(L, 3)));
  return 1;
}

static int luasrc_UTIL_PlayerByIndex (lua_State *L) {
  lua_pushplayer(L, UTIL_PlayerByIndex(luaL_checkinteger(L, 1)));
  return 1;
}


static const luaL_Reg util_funcs[] = {
  {"UTIL_VecToYaw",  luasrc_UTIL_VecToYaw},
  {"UTIL_VecToPitch",  luasrc_UTIL_VecToPitch},
  {"UTIL_YawToVector",  luasrc_UTIL_YawToVector},
  {"UTIL_TraceLine",  luasrc_UTIL_TraceLine},
  {"UTIL_TraceHull",  luasrc_UTIL_TraceHull},
  {"UTIL_TraceEntity",  luasrc_UTIL_TraceEntity},
  {"UTIL_EntityHasMatchingRootParent",  luasrc_UTIL_EntityHasMatchingRootParent},
  {"UTIL_PointContents",  luasrc_UTIL_PointContents},
  {"UTIL_TraceModel",  luasrc_UTIL_TraceModel},
  {"UTIL_ParticleTracer",  luasrc_UTIL_ParticleTracer},
  {"UTIL_Tracer",  luasrc_UTIL_Tracer},
  {"UTIL_IsLowViolence",  luasrc_UTIL_IsLowViolence},
  {"UTIL_ShouldShowBlood",  luasrc_UTIL_ShouldShowBlood},
  {"UTIL_BloodDrips",  luasrc_UTIL_BloodDrips},
  {"UTIL_BloodImpact",  luasrc_UTIL_BloodImpact},
  {"UTIL_BloodDecalTrace",  luasrc_UTIL_BloodDecalTrace},
  {"UTIL_DecalTrace",  luasrc_UTIL_DecalTrace},
  {"UTIL_IsSpaceEmpty",  luasrc_UTIL_IsSpaceEmpty},
  {"UTIL_PlayerByIndex",  luasrc_UTIL_PlayerByIndex},
  {NULL, NULL}
};


int luaopen_UTIL_shared (lua_State *L) {
  luaL_register(L, "_G", util_funcs);
  lua_pop(L, 1);
  return 1;
}
