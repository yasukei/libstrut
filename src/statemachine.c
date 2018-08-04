#include "statemachine.h"

// ------------------------------------------------------------------
// State
// ------------------------------------------------------------------
void State_initializeVFuncs(
	State* self,
	StateVFuncs* vfuncs
	)
{
	self->vfuncs = vfuncs;
}

// ------------------------------------------------------------------
void State_onEntry(
	State* self
	)
{
	self->vfuncs->onEntry(self);
}

// ------------------------------------------------------------------
void State_onExit(
	State* self
	)
{
	self->vfuncs->onExit(self);
}

// ------------------------------------------------------------------
void State_onEvent(
	State* self,
	int event
	)
{
	self->vfuncs->onEvent(self, event);
}

// ------------------------------------------------------------------
// Transition
// ------------------------------------------------------------------
typedef struct Transition Transition;
struct Transition
{
	State* src;
	State* dst;
	int event;
};

// ------------------------------------------------------------------
void Transition_initialize(
	Transition* self,
	State* src,
	State* dst
	)
{
	self->src = src;
	self->dst = dst;
	self->event = event;
}

// ------------------------------------------------------------------
// StateMachine
// ------------------------------------------------------------------
typedef struct StateMachine StateMachine;

#define cSTATEMACHINE_NUMOF_ALLOC	16

struct StateMachine
{
	uint32_t capacityTransitions;
	uint32_t numofTransitions;
	Transition* transitions;
};

// ------------------------------------------------------------------
static void __StateMachine_initialize(
	StateMachine* self
	)
{
	self->numofTransitions = 0;
	self->transitions = malloc(sizeof(Transition*) * cSTATEMACHINE_NUMOF_ALLOC);
}

// ------------------------------------------------------------------
StateMachine* StateMachine_create(
	void
	)
{
	StateMachine* self;

	self = malloc(sizeof(StateMachine));
	if(self == NULL)
	{
		return NULL;
	}

	__StateMachine_initialize(self);
	return self;
}

// ------------------------------------------------------------------
void StateMachine_addTransition(
	StateMachine* self,
	State* src,
	State* dst,
	int event
	)
{
	if(self
}


