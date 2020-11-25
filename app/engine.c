#include "sandbox/sandbox.h"

int main()
{
    sandboxInit();
    
    while(sandboxIsRunning())
    {
        sandboxPerFrame();
    }

    sandboxCleanUp();

    return 0;
}