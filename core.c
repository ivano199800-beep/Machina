#include "core.h"


Status CreateCore(Device* self , State* state) {
    self->data = calloc(1 , sizeof(CoreData));
    CoreData* data = self->data;
    memcpy(data->InstructionRom  , (void*)state->argV[0] , 512 * 4);
    data->state = 0;
    return 1;
}
Status ClockCore(Device* self , State* state) {
    // this function is about to be the biggest
    CoreData* data = self->data;
    uint64_t core_state = data->state;
    if (!state->argV) 
    state->argV = malloc((state->argC + 1) * sizeof(unsigned long long));
    if (!core_state) {
        //HALT
        if (state->argV[0] == 0) {
            //scheduler
            if (state->argV[1] == 0) {
                return 1;
            }
            if (state->argV[1] == 1) {
                //restart
                memcpy(data->registers , (uint16_t[]){0,0,0,0} , sizeof(uint16_t) * 4);
                data->state = 1; // fetch
                return 1; 
            }
        }
    }
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
