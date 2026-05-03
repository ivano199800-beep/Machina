#include "core.h"


Status CreateCore(Device* self , State* state) {
    self->data = calloc(1 , sizeof(CoreData));
    CoreData* data = self->data;
    memcpy(data->InstructionRom  , (void*)state->argV[0] , 512 * 4);
    data->state = 1;
    return 1;
}
Status ClockCore(Device* self , State* state) {
    // this function is about to be the biggest
    if (!state->argV) state->argV = malloc(1 + state->argC * sizeof(unsigned long long));
    uint64_t CoreState = ((CoreData*)self->data)->state;
    CoreData* data = self->data;
    data->counter++;
    if (!CoreState) {
        state->argV[0] |= 0b1; // HALTED SIGNAL
        return 0;
    }
    else if ((CoreState & 0b1111) == 1) {
        //fetch
    }
    else if ((CoreState & 0b1111) == 2) {
        //execute
    }
    else if ((CoreState & 0b1111) == 3) {
        //pending
        // sub ops here
    }
    else return 0;
    return 1;
}
Status DestroyCore(Device* self , State* state) {
    if (self) free(self->data);
    free(self);
    return 1;
}
Device* NewBaseCore(const char* config) {
    Device* d =  malloc(sizeof(Device));
    d->Create = CreateCore;
    d->Destroy = DestroyCore;
    d->Clock = ClockCore;
    d->DID = 0; // 0 for now since i dont have a register system yet
    snprintf( d->CID ,  36 , "Core-%d" , VERSION_ );
    return d;
}
