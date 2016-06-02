//
// main.c
// taka-wang
//

#include "modbusd.h"
    
void load_config()
{
    // TODO
}

void init_zmq(zctx_t **zmq_context, void ** pub, void ** sub)
{
    // @setup zmq
    *zmq_context = zctx_new ();
    // init zmq subscriber: zmq_sub
    *sub = zsocket_new (zmq_context, ZMQ_SUB);
    // bind zmq subscriber
    zsocket_bind (*sub, IPC_SUB);
    // set zmq subscriber filter
    zsocket_set_subscribe (*sub, ""); 
    // init zmq publisher: zmq_pub
    *pub = zsocket_new (zmq_context, ZMQ_PUB);
    // bind zmq publisher
    zsocket_bind (*pub, IPC_PUB);
}


// ENTRY
int main(int argc, char *argv[])
{    
    // @load external config
    load_config();
    void * pub, sub;
    zctx_t *zmq_context;

    init_zmq(&zmq_context, &pub, &sub);
    /*
    // @setup zmq
    zctx_t *zmq_context = zctx_new ();
    // init zmq subscriber: zmq_sub
    void *zmq_sub = zsocket_new (zmq_context, ZMQ_SUB);
    // bind zmq subscriber
    zsocket_bind (zmq_sub, IPC_SUB);
    // set zmq subscriber filter
    zsocket_set_subscribe (zmq_sub, ""); 
    // init zmq publisher: zmq_pub
    void *zmq_pub = zsocket_new (zmq_context, ZMQ_PUB);
    // bind zmq publisher
    zsocket_bind (zmq_pub, IPC_PUB);
    */
    
    // @start receiving zmq command
    printf("start command listener\n");
    while (!zctx_interrupted) // handle ctrl+c
    {
        zmsg_t *msg = zmsg_recv(sub);
        if (msg != NULL)
        {
            //zmsg_dump(msg);
        }
    }
    
    // @resource clean up
    printf("clean up\n");
    zctx_destroy(&zmq_context);
    exit(EXIT_SUCCESS);
}