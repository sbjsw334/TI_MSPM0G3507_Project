#include "board.h"
#include "app_state_machine.h"
#include "msg_map.h"
#include "sub_state_machine.h"

int main(void)
{
    Board_Init();
    MsgMap_Init();
    AppSM_Init();
    SubSM_Init();

    while (1) {
        MsgId_t msg = MsgMap_Get();

        AppSM_Run(msg);
        SubSM_Run(msg);

        MsgMap_Clear();
    }
}
