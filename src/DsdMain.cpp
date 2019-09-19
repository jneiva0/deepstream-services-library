/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "DsdApi.h"

GST_DEBUG_CATEGORY(NVDS_APP);

using namespace DSD;

#define INIT_MEMORY(m) memset(&m, 0, sizeof(m));

#define INIT_STRUCT(type, name) struct type name; INIT_MEMORY(name) 

/**
 * Function to handle program interrupt signal.
 * It installs default handler after handling the interrupt.
 */
static void PrgItrSigIsr(int signum)
{
    LOG_FUNC();
    
    INIT_STRUCT(sigaction, sa);

    sa.sa_handler = SIG_DFL;

    sigaction(SIGINT, &sa, NULL);

    g_main_loop_quit(Driver::GetDriver()->m_pMainLoop);
}

/**
 * Function to install custom handler for program interrupt signal.
 */
static void PrgItrSigIsrInstall(void)
{
    LOG_FUNC();

    INIT_STRUCT(sigaction, sa);

    sa.sa_handler = PrgItrSigIsr;

    sigaction(SIGINT, &sa, NULL);
}

 
int main(int argc, char **argv)
{
    LOG_FUNC();
    
    int returnValue = EXIT_FAILURE;
    
    // initialize the GStreamer library
    gst_init(&argc, &argv);
    
    // Install the custom Program Interrup Signal ISR
    PrgItrSigIsrInstall();    

    
    // First call to GetDriver() for initialization
    Driver* pDriver = Driver::GetDriver();

    dsd_source_new("source1", 5, TRUE, 1280, 720, 30, 1);

    dsd_streammux_new("streammux1", TRUE, 1, 40000, 1280, 720);

    dsd_display_new("display1", 1, 1, 1280, 720);

//    DSD_GIE_NEW("GIE1",
//        "resnet10.caffemodel_b30_int8.engine", 
//        "config_infer_primary.txt", 1, 1, 1, 1, 1);
//        
    dsd_pipeline_new("pipeline1");
    
    dsd_pipeline_source_add("pipeline1", "source1");
    
    dsd_pipeline_streammux_add("pipeline1", "streammux1");

    dsd_pipeline_display_add("pipeline1", "display1");
    
    dsd_pipeline_play("pipeline1");

    // Run the main loop
    dsd_main_loop_run();
    
//
//    DSD_GIE_DELETE("GIE1");
    
    dsd_display_delete("display1");
    
    dsd_streammux_delete("streammux1");
    
    dsd_source_delete("source1");

    dsd_pipeline_delete("pipeline1");


    returnValue = EXIT_SUCCESS;
    
    // Clean-up 
    gst_deinit();
    
    // Main loop has terminated
    return returnValue;
}