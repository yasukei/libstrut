#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// ------------------------------------------------------------------

// ------------------------------------------------------------------
// StateVFuncs
// ------------------------------------------------------------------
typedef struct StateVFuncs StateVFuncs;
typedef void (*StateVFuncs_onEntry)(State* self);
typedef void (*StateVFuncs_onExit)(State* self);
typedef void (*StateVFuncs_onEvent)(State* self, int event);
typedef void (*StateVFuncs_destroy)(State* self);

// ------------------------------------------------------------------
struct StateVFuncs
{
	StateVFuncs_onEntry	onEntry;
	StateVFuncs_onExit	onExit;
	StateVFuncs_onEvent onEvent;
	StateVFuncs_destroy destroy;
};

// ------------------------------------------------------------------
// State
// ------------------------------------------------------------------
typedef struct State State;

// ------------------------------------------------------------------
struct State
{
	StateVFuncs* vfuncs;
};

// ------------------------------------------------------------------
void State_initializeVFuncs(
	State* self,
	StateVFuncs* vfuncs
	);

// ------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _STATEMACHINE_H_

